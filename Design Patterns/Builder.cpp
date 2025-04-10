#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    string engine;
    int seats;
    bool gps;

    void showDetails() {
        cout << "Car details: \n";
        cout << "Engine: " << engine << "\n";
        cout << "Seats: " << seats << "\n";
        cout << "GPS: " << (gps ? "Yes" : "No") << "\n";
    }
};

// Builder class to create a car
class CarBuilder {
private:
    Car* car; // The object being built

public:
    
    CarBuilder() {
        car = new Car();  
    }

   
    CarBuilder* setEngine(string engine) {
        car->engine = engine;
        return this; // Return the builder itself to chain methods
    }

    
    CarBuilder* setSeats(int seats) {
        car->seats = seats;
        return this; 
    }

   
    CarBuilder* setGPS(bool gps) {
        car->gps = gps;
        return this; 
    }

    
    Car* getProduct() {
        return car;
    }
};

int main() {
    // Create a car using the builder pattern
    CarBuilder builder;
    Car* car = builder.setEngine("V8 Engine")
                      .setSeats(4)
                      .setGPS(true)
                      .getProduct();

  
    car->showDetails();

    delete car; 
    return 0;
}
