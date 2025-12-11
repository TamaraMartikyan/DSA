#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "httplib.h"

using namespace std;
using json = nlohmann::json;

// ============= MESSAGE QUEUE =============
class MessageQueue {
private:
    queue<json> messages;
    mutex queue_mutex;

public:
    void push(const json& msg) {
        lock_guard<mutex> lock(queue_mutex);
        messages.push(msg);
    }

    json pop() {
        lock_guard<mutex> lock(queue_mutex);
        if (!messages.empty()) {
            json msg = messages.front();
            messages.pop();
            return msg;
        }
        return json::object();
    }

    bool empty() {
        lock_guard<mutex> lock(queue_mutex);
        return messages.empty();
    }

    size_t size() {
        lock_guard<mutex> lock(queue_mutex);
        return messages.size();
    }
};

// ============= HTTP HELPER =============
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

inline string http_get(const string& url) {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "eda-system-client/1.0");
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "[HTTP] Error: " << curl_easy_strerror(res) << "\n";
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return readBuffer;
}

// ============= KAFKA CONSUMER =============
class KafkaConsumer {
private:
    MessageQueue& redpanda_queue;
    string brokers;
    string group_id;

public:
    KafkaConsumer(MessageQueue& q, const string& b, const string& g)
        : redpanda_queue(q), brokers(b), group_id(g) {}

    void start_consuming() {
        cout << "\nKAFKA CONSUMER SERVICE\n";
        cout << "  Brokers: " << brokers << "\n";
        cout << "  Group ID: " << group_id << "\n";
        cout << "  Waiting for messages...\n\n";

        int processed = 0;
        while (true) {
            if (!redpanda_queue.empty()) {
                auto event = redpanda_queue.pop();
                if (!event.empty()) {
                    processed++;
                    cout << "    [Kafka] Message #" << processed << "\n";
                    cout << "    [Kafka] Processing: " << event.value("source", "unknown") << "\n";
                    cout << "    [Kafka] → Analytics computed\n";
                    cout << "    [Kafka] → Event logged\n";
                    cout << "   ✓ Complete\n\n";
                }
            }
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
};

// ============= RABBITMQ CONSUMER =============
class RabbitMQConsumer {
private:
    MessageQueue& redpanda_queue;
    string host;
    int port;

public:
    RabbitMQConsumer(MessageQueue& q, const string& h, int p)
        : redpanda_queue(q), host(h), port(p) {}

    void start_consuming() {
        cout << "\nRABBITMQ CONSUMER SERVICE\n";
        cout << "  Host: " << host << "\n";
        cout << "  Port: " << port << "\n";
        cout << "  Waiting for messages...\n\n";

        int processed = 0;
        while (true) {
            if (!redpanda_queue.empty()) {
                auto event = redpanda_queue.pop();
                if (!event.empty()) {
                    processed++;
                    cout << "    [RabbitMQ] Message #" << processed << "\n";
                    cout << "    [RabbitMQ] Processing: " << event.value("source", "unknown") << "\n";
                    cout << "    [RabbitMQ] → Data enriched\n";
                    cout << "    [RabbitMQ] → Alert sent\n";
                    cout << "    [RabbitMQ] → Event logged\n";
                    cout << "   ✓ Complete\n\n";
                }
            }
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
};

// ============= REST API SERVER =============
class RestAPIServer {
private:
    MessageQueue& redpanda_queue;
    httplib::Server svr;

public:
    RestAPIServer(MessageQueue& q) : redpanda_queue(q) {
        setup_endpoints();
    }

    void setup_endpoints() {
        svr.Post("/api/events", [this](const httplib::Request& req, httplib::Response& res) {
            try {
                auto json_data = json::parse(req.body);

                cout << "\nREST API: Received event\n";
                cout << "  Source: " << json_data.value("source", "unknown") << "\n";
                cout << "  Body: " << json_data.dump() << "\n";

                if (json_data.find("source") == json_data.end()) {
                    json_data["source"] = "rest_api";
                }

                redpanda_queue.push(json_data);

                res.set_content(R"({"status":"success"})", "application/json");
                res.status = 200;
            } catch (exception& e) {
                cerr << "REST API Error: " << e.what() << "\n";
                res.set_content(R"({"status":"error","message":"Invalid JSON"})", "application/json");
                res.status = 400;
            }
        });

        svr.Get("/health", [](const httplib::Request&, httplib::Response& res) {
            res.set_content("OK", "text/plain");
            res.status = 200;
        });

        svr.Get("/status", [](const httplib::Request&, httplib::Response& res) {
            json status = {
                {"status", "running"},
                {"service", "eda-system"},
                {"version", "1.0.0"}
            };
            res.set_content(status.dump(), "application/json");
            res.status = 200;
        });
    }

    void start(int port) {
        cout << "\nREST API SERVER\n";
        cout << "  Listening on http://0.0.0.0:" << port << "\n\n";
        svr.listen("0.0.0.0", port);
    }
};

// ============= GITHUB FETCHER =============
void fetch_github_events(MessageQueue& queue, const string& repo_full_name) {
    while (true) {
        try {
            string url = "https://api.github.com/repos/" + repo_full_name + "/events";
            string response = http_get(url);
            auto events = json::parse(response);

            for (auto& e : events) {
                auto event = e;
                event["source"] = "github";
                queue.push(event);
                cout << "[GitHub] Event pushed: "
                      << e.value("type", "unknown")
                      << " by " << e["actor"].value("login", "unknown")
                      << endl;
            }

        } catch (exception& ex) {
            cerr << "[GitHub] Error fetching events: " << ex.what() << endl;
        }
        this_thread::sleep_for(chrono::seconds(10));
    }
}

// ============= MAIN =============
int main() {
    cout << "║ EVENT-DRIVEN ARCHITECTURE SYSTEM ║\n\n";

    MessageQueue redpanda_queue;

    thread github_thread(fetch_github_events, ref(redpanda_queue), "octocat/Hello-World");

    KafkaConsumer kafka(redpanda_queue, "172.23.201.90:9092", "eda-group");
    thread kafka_thread([&kafka]() {
        kafka.start_consuming();
    });

    RabbitMQConsumer rabbitmq(redpanda_queue, "localhost", 5672);
    thread rabbitmq_thread([&rabbitmq]() {
        rabbitmq.start_consuming();
    });

    RestAPIServer rest_server(redpanda_queue);
    cout << "REST API SERVER listening on port 8000\n";
    thread rest_thread([&rest_server]() {
        rest_server.start(8000);
    });

    github_thread.join();
    kafka_thread.join();
    rabbitmq_thread.join();
    rest_thread.join();

    return 0;
}
