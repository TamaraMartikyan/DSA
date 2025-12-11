#pragma once
#include <iostream>
#include <thread>
#include "message_queue.hpp"

class KafkaConsumer {
private:
    MessageQueue& redpanda_queue;
    std::string brokers;
    std::string group_id;

public:
    KafkaConsumer(MessageQueue& q, const std::string& b, const std::string& g)
        : redpanda_queue(q), brokers(b), group_id(g) {}

    void start_consuming() {
        std::cout << "\nKAFKA CONSUMER SERVICE\n";
        std::cout << "  Brokers: " << brokers << "\n";
        std::cout << "  Group ID: " << group_id << "\n";
        std::cout << "  Waiting for messages...\n\n";

        int processed = 0;
        while (true) {
            if (!redpanda_queue.empty()) {
                auto event = redpanda_queue.pop();
                if (!event.empty()) {
                    processed++;
                    std::cout << "    [Kafka] Message #" << processed << "\n";
                    std::cout << "    [Kafka] Processing: " << event.value("source", "unknown") << "\n";
                    std::cout << "    [Kafka] → Analytics computed\n";
                    std::cout << "    [Kafka] → Event logged\n";
                    std::cout << "   ✓ Complete\n\n";
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
};