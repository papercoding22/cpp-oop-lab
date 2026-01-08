/**
 * @file Cat.cpp
 * @brief Implementation of Cat class
 */

#include "Cat.h"
#include <iostream>

/**
 * @brief Constructor
 */
Cat::Cat()
    : Animal()
{
    std::cout << "Cat constructor called" << std::endl;
}

/**
 * @brief Destructor
 */
Cat::~Cat()
{
    std::cout << "Cat destructor called" << std::endl;
}

Cat::Cat(const string &name, int age, bool isIndoor, int clawSharpness)
    : Animal(name, age), isIndoor(isIndoor), clawSharpness(clawSharpness)
{
    std::cout << "Cat parameterized constructor called for " << name << std::endl;
}

bool Cat::getIsIndoor() const
{
    return isIndoor;
}

void Cat::setIsIndoor(bool isIndoor)
{
    this->isIndoor = isIndoor;
}

int Cat::getClawSharpness() const
{
    return clawSharpness;
}

void Cat::setClawSharpness(int sharpness)
{
    this->clawSharpness = sharpness;
}

void Cat::makeSound() const
{
    std::cout << name << " says: Meow! Meow!" << std::endl;
}

void Cat::describe() const
{
    std::cout << "I am a cat named " << name << ", " << age
              << " years old, "
              << (isIndoor ? "indoor" : "outdoor")
              << ", claw sharpness: " << clawSharpness << std::endl;
}

void Cat::scratch() const
{
    std::cout << name << " is scratching!" << std::endl;
}

void Cat::climb() const
{
    std::cout << name << " is climbing!" << std::endl;
}
