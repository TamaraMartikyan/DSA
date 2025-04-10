#include <iostream>
#include <string>

// The existing socket in the house (Target interface)
class Socket {
public:
    virtual void providePower() = 0; 
    virtual ~Socket() = default;
};

// A specific type of plug (Adaptee)
class ForeignPlug {
public:
    void foreignPower() {
        std::cout << "Providing power using a foreign plug.\n";
    }
};

// Adapter: Connects the foreign plug to the socket
class PlugAdapter : public Socket {
private:
    ForeignPlug* plug; // The plug to adapt

public:
    PlugAdapter(ForeignPlug* foreignPlug) : plug(foreignPlug) {}

    void providePower() override {
        std::cout << "Adapter converts the power.\n";
        plug->foreignPower(); // Call the foreign plug's method
    }
};

// The child plugs their toy into the adapter
int main() {
    ForeignPlug* foreignPlug = new ForeignPlug(); // Toy with a foreign plug
    Socket* adapter = new PlugAdapter(foreignPlug); // Adapter to fit the socket

    std::cout << "Child plugs their toy into the adapter:\n";
    adapter->providePower(); // Power the toy using the adapter

    return 0;
}
