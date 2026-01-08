/**
 * @file main.cpp
 * @brief Demonstrates basic_class
 *
 * Introduction to classes and objects in C++
 */

#include <iostream>
#include "Rectangle.h"

int main() {
    std::cout << "=== BASIC CLASS Demo ===" << std::endl;
    std::cout << std::endl;

    // Demonstrate default constructor
    std::cout << "1. Creating rectangle with default constructor:" << std::endl;
    Rectangle rect1;
    rect1.display();
    std::cout << std::endl;

    // Demonstrate parameterized constructor
    std::cout << "2. Creating rectangle with parameterized constructor:" << std::endl;
    Rectangle rect2(5.0, 3.0);
    rect2.display();
    std::cout << std::endl;

    // Demonstrate setters
    std::cout << "3. Modifying rect1 using setters:" << std::endl;
    rect1.setWidth(10.0);
    rect1.setHeight(7.5);
    rect1.display();
    std::cout << std::endl;

    // Demonstrate getters
    std::cout << "4. Using getters to access properties:" << std::endl;
    std::cout << "rect2 width: " << rect2.getWidth() << std::endl;
    std::cout << "rect2 height: " << rect2.getHeight() << std::endl;
    std::cout << std::endl;

    // Demonstrate methods
    std::cout << "5. Computing area and perimeter:" << std::endl;
    std::cout << "rect1 area: " << rect1.area() << std::endl;
    std::cout << "rect1 perimeter: " << rect1.perimeter() << std::endl;
    std::cout << "rect2 area: " << rect2.area() << std::endl;
    std::cout << "rect2 perimeter: " << rect2.perimeter() << std::endl;
    std::cout << std::endl;

    std::cout << "Demo completed successfully!" << std::endl;
    std::cout << std::endl;
    std::cout << "Note: Watch for constructor and destructor calls above and below." << std::endl;

    return 0;
}
