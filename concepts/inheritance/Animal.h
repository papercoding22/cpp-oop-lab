/**
 * @file Animal.h
 * @brief Declaration of Animal class
 */

#ifndef ANIMAL_H
#define ANIMAL_H


#include <string>

/**
 * @class Animal
 * @brief Base class representing a generic animal
 *
 * This class demonstrates the base class in an inheritance hierarchy.
 * It provides common properties and behaviors for all animals.
 */
class Animal {
public:
    /**
     * @brief Default constructor
     */
    Animal();

    /**
     * @brief Parameterized constructor
     * @param name Name of the animal
     * @param age Age of the animal in years
     */
    Animal(const std::string& name, int age);

    /**
     * @brief Virtual destructor (important for inheritance)
     */
    virtual ~Animal();

    // Getters
    std::string getName() const;
    int getAge() const;

    // Setters
    void setName(const std::string& name);
    void setAge(int age);

    /**
     * @brief Make the animal's sound (virtual - can be overridden)
     * Virtual function allows derived classes to provide their own implementation
     */
    virtual void makeSound() const;

    /**
     * @brief Describe the animal (virtual - can be overridden)
     * Virtual function for polymorphic behavior
     */
    virtual void describe() const;

    /**
     * @brief Common behavior - eating
     * Non-virtual function - inherited as-is by derived classes
     */
    void eat() const;

    /**
     * @brief Common behavior - sleeping
     * Non-virtual function - all animals sleep the same way
     */
    void sleep() const;

protected:
    // Protected members - accessible by derived classes
    std::string name;  ///< Name of the animal
    int age;           ///< Age of the animal

private:
    // Private members - not accessible by derived classes
};

#endif // ANIMAL_H
