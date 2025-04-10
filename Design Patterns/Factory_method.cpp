#include <iostream>
#include <string>
using namespace std;

// Abstract class for Study Material
class StudyMaterial {
public:
    virtual void displayMaterial() = 0;  // Abstract function to display the material
    virtual ~StudyMaterial() {}
};


// Concrete classes for specific study materials
class MathNotes : public StudyMaterial {
public:
    void displayMaterial() override {
        cout << "Math Notes: Algebra, Geometry, Trigonometry\n";
    }
};

class PhysicsNotes : public StudyMaterial {
public:
    void displayMaterial() override {
        cout << "Physics Notes: Mechanics, Electricity, Magnetism\n";
    }
};

class HistoryNotes : public StudyMaterial {
public:
    void displayMaterial() override {
        cout << "History Notes: Ancient Civilizations, World Wars, Modern History\n";
    }
};



// StudyMaterialFactory class
class StudyMaterialFactory {
public:


    // Factory method to create the appropriate study material
    static StudyMaterial* createStudyMaterial(const string& materialType) {
      
        
        if (materialType == "math") {
            return new MathNotes();
        }
        else if (materialType == "physics") {
            return new PhysicsNotes();
        }
        else if (materialType == "history") {
            return new HistoryNotes();
        }
        else {
            return nullptr;  // If the material type is unknown
        }
    }
};

int main() {
    // Student asks the factory for study materials
    StudyMaterial* material1 = StudyMaterialFactory::createStudyMaterial("math");
    if (material1) {
        material1->displayMaterial();
        delete material1;  // Don't forget to free memory
    }

    StudyMaterial* material2 = StudyMaterialFactory::createStudyMaterial("physics");
    if (material2) {
        material2->displayMaterial();
        delete material2;
    }

    StudyMaterial* material3 = StudyMaterialFactory::createStudyMaterial("history");
    if (material3) {
        material3->displayMaterial();
        delete material3;
    }

    StudyMaterial* material4 = StudyMaterialFactory::createStudyMaterial("chemistry");
    if (material4) {
        material4->displayMaterial();
        delete material4;
    }
    else {
        std::cout << "Sorry, we don't have Chemistry Notes\n";
    }

    return 0;
}











#include <iostream>
using namespace std;

// Abstract Product 
class Shape {
public:
    virtual void draw() = 0; // Pure virtual method
    virtual ~Shape() {}
};

// Concrete Product 
class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing a Circle.\n";
    }
};

 
class Square : public Shape {
public:
    void draw() override {
        cout << "Drawing a Square.\n";
    }
};

//  Factory 
class ShapeFactory {
public:
    virtual Shape* createShape() = 0; // Factory method
    virtual ~ShapeFactory() {}
};

// Concrete Factory
class CircleFactory : public ShapeFactory {
public:
    Shape* createShape() override {
        return new Circle(); // Creates a Circle object
    }
};


class SquareFactory : public ShapeFactory {
public:
    Shape* createShape() override {
        return new Square(); 
    }
};

// Client Code
void drawShape(ShapeFactory* factory) {
    Shape* shape = factory->createShape(); // Create shape using factory
    shape->draw();                         // Call the draw method
    delete shape;                          // Clean up memory
}

int main() {
    // Create factories
    CircleFactory circleFactory;
    SquareFactory squareFactory;

    // Draw shapes
    cout << "Using Circle Factory:\n";
    drawShape(&circleFactory);

    cout << "Using Square Factory:\n";
    drawShape(&squareFactory);

    return 0;
}

