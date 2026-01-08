/**
 * @file Rectangle.cpp
 * @brief Implementation of Rectangle class
 */

#include "Rectangle.h"
#include <iostream>

/**
 * @brief Default constructor - initializes rectangle with 0 dimensions
 */
Rectangle::Rectangle() : width(0.0), height(0.0) {
    std::cout << "Rectangle default constructor called" << std::endl;
}

/**
 * @brief Parameterized constructor
 */
Rectangle::Rectangle(double w, double h) : width(w), height(h) {
    std::cout << "Rectangle parameterized constructor called (w=" << w << ", h=" << h << ")" << std::endl;
}

/**
 * @brief Destructor
 */
Rectangle::~Rectangle() {
    std::cout << "Rectangle destructor called" << std::endl;
}

/**
 * @brief Set the width
 */
void Rectangle::setWidth(double w) {
    width = w;
}

/**
 * @brief Set the height
 */
void Rectangle::setHeight(double h) {
    height = h;
}

/**
 * @brief Get the width
 */
double Rectangle::getWidth() const {
    return width;
}

/**
 * @brief Get the height
 */
double Rectangle::getHeight() const {
    return height;
}

/**
 * @brief Calculate area
 */
double Rectangle::area() const {
    return width * height;
}

/**
 * @brief Calculate perimeter
 */
double Rectangle::perimeter() const {
    return 2.0 * (width + height);
}

/**
 * @brief Display rectangle information
 */
void Rectangle::display() const {
    std::cout << "Rectangle [width=" << width << ", height=" << height
              << ", area=" << area() << ", perimeter=" << perimeter() << "]" << std::endl;
}
