/**
 * @file Dog.cpp
 * @brief Implementation of Dog class
 */

#include "Dog.h"
#include <iostream>

/**
 * @brief Default constructor
 * Calls the base class (Animal) default constructor
 */
Dog::Dog()
    : Animal(), breed("Mixed")
{
    std::cout << "Dog default constructor called" << std::endl;
}

/**
 * @brief Parameterized constructor
 * Calls the base class (Animal) parameterized constructor
 */
Dog::Dog(const std::string &name, int age, const std::string &breed)
    : Animal(name, age), breed(breed)
{
    std::cout << "Dog parameterized constructor called for " << name << " (" << breed << ")" << std::endl;
}

/**
 * @brief Destructor
 */
Dog::~Dog()
{
    std::cout << "Dog destructor called for " << name << std::endl;
}

// Getter for breed
std::string Dog::getBreed() const
{
    return breed;
}

// Setter for breed
void Dog::setBreed(const std::string &breed)
{
    this->breed = breed;
}

/**
 * @brief Override makeSound - dogs bark!
 * This overrides the virtual function from Animal
 */
void Dog::makeSound() const
{
    std::cout << name << " says: Woof! Woof!" << std::endl;
}

/**
 * @brief Override describe - provide dog-specific description
 * This overrides the virtual function from Animal
 */
void Dog::describe() const
{
    // Can still call base class method if needed
    // Animal::describe();

    std::cout << "I am a dog named " << name << ", " << age << " years old, breed: " << breed << std::endl;
}

/**
 * @brief Dog-specific behavior - fetching
 */
void Dog::fetch() const
{
    std::cout << name << " is fetching the ball! Good dog!" << std::endl;
}

/**
 * @brief Dog-specific behavior - wagging tail
 */
void Dog::wagTail() const
{
    std::cout << name << " is wagging tail happily! *wag wag wag*" << std::endl;
}
