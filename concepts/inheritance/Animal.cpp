/**
 * @file Animal.cpp
 * @brief Implementation of Animal class
 */

#include "Animal.h"
#include <iostream>

/**
 * @brief Default constructor
 */
Animal::Animal() : name("Unknown"), age(0) {
    std::cout << "Animal default constructor called" << std::endl;
}

/**
 * @brief Parameterized constructor
 */
Animal::Animal(const std::string& name, int age) : name(name), age(age) {
    std::cout << "Animal parameterized constructor called for " << name << std::endl;
}

/**
 * @brief Virtual destructor
 */
Animal::~Animal() {
    std::cout << "Animal destructor called for " << name << std::endl;
}

// Getters
std::string Animal::getName() const {
    return name;
}

int Animal::getAge() const {
    return age;
}

// Setters
void Animal::setName(const std::string& name) {
    this->name = name;
}

void Animal::setAge(int age) {
    this->age = age;
}

/**
 * @brief Base class implementation of makeSound
 * This is a virtual function that can be overridden by derived classes
 */
void Animal::makeSound() const {
    std::cout << name << " makes a generic animal sound" << std::endl;
}

/**
 * @brief Base class implementation of describe
 * This is a virtual function that can be overridden by derived classes
 */
void Animal::describe() const {
    std::cout << "I am an animal named " << name << ", " << age << " years old" << std::endl;
}

/**
 * @brief Common eating behavior
 */
void Animal::eat() const {
    std::cout << name << " is eating" << std::endl;
}

/**
 * @brief Common sleeping behavior
 */
void Animal::sleep() const {
    std::cout << name << " is sleeping. Zzz..." << std::endl;
}
