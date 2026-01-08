/**
 * @file Dog.h
 * @brief Declaration of Dog class
 */

#ifndef DOG_H
#define DOG_H

#include "Animal.h"

#include <string>

/**
 * @class Dog
 * @brief Derived class representing a dog (inherits from Animal)
 *
 * This class demonstrates inheritance in C++. Dog IS-A Animal.
 * It inherits all public and protected members from Animal and adds dog-specific behavior.
 */
class Dog : public Animal {
public:
    /**
     * @brief Default constructor
     */
    Dog();

    /**
     * @brief Parameterized constructor
     * @param name Name of the dog
     * @param age Age of the dog in years
     * @param breed Breed of the dog
     */
    Dog(const std::string& name, int age, const std::string& breed);

    /**
     * @brief Virtual destructor
     */
    virtual ~Dog();

    // Getter for breed
    std::string getBreed() const;

    // Setter for breed
    void setBreed(const std::string& breed);

    /**
     * @brief Override makeSound - dogs bark
     * This overrides the virtual function from Animal
     */
    virtual void makeSound() const override;

    /**
     * @brief Override describe - provide dog-specific description
     * This overrides the virtual function from Animal
     */
    virtual void describe() const override;

    /**
     * @brief Dog-specific behavior - fetching
     * This is a new method not in the base class
     */
    void fetch() const;

    /**
     * @brief Dog-specific behavior - wagging tail
     * This is a new method not in the base class
     */
    void wagTail() const;

protected:
    // No additional protected members for this example

private:
    std::string breed;  ///< Breed of the dog (dog-specific property)
};

#endif // DOG_H
