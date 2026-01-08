/**
 * @file Dog.cpp
 * @brief Implementation of Dog class
 */

#include "Dog.h"
#include <iostream>

/**
 * @brief Constructor
 */
Dog::Dog()
    : Animal() {
    std::cout << "Dog constructor called" << std::endl;
}

/**
 * @brief Destructor
 */
Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
}

// TODO: Implement your methods here
