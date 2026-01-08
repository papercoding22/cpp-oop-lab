/**
 * @file main.cpp
 * @brief Demonstrates inheritance
 *
 * Demonstrating class inheritance and IS-A relationships
 */

#include <iostream>
#include "Animal.h"
#include "Dog.h"
#include "Cat.h"

void printSeparator()
{
    std::cout << "\n"
              << std::string(60, '-') << "\n"
              << std::endl;
}

int main()
{
    std::cout << "=== INHERITANCE Demo ===" << std::endl;
    std::cout << "\nThis demo shows how Dog inherits from Animal (IS-A relationship)" << std::endl;

    printSeparator();

    // ==================== DEMO 1: Creating Base Class Object ====================
    std::cout << "DEMO 1: Creating a base class (Animal) object" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    Animal genericAnimal("Charlie", 5);
    std::cout << "\nCalling methods on Animal:" << std::endl;
    genericAnimal.describe();
    genericAnimal.makeSound();
    genericAnimal.eat();
    genericAnimal.sleep();

    printSeparator();

    // ==================== DEMO 2: Creating Derived Class Object ====================
    std::cout << "DEMO 2: Creating a derived class (Dog) object" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "\nNotice the constructor call order: Base -> Derived" << std::endl;

    Dog buddy("Buddy", 3, "Golden Retriever");

    std::cout << "\nCalling methods on Dog:" << std::endl;
    buddy.describe();  // Overridden method
    buddy.makeSound(); // Overridden method

    std::cout << "\nCalling inherited methods from Animal:" << std::endl;
    buddy.eat();   // Inherited from Animal
    buddy.sleep(); // Inherited from Animal

    std::cout << "\nCalling Dog-specific methods:" << std::endl;
    buddy.fetch();   // Dog-specific method
    buddy.wagTail(); // Dog-specific method

    printSeparator();

    // ==================== DEMO 3: IS-A Relationship ====================
    std::cout << "DEMO 3: IS-A Relationship - Dog IS-A Animal" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    std::cout << "\nA Dog pointer can be assigned to an Animal pointer" << std::endl;
    Dog max("Max", 2, "Labrador");
    Animal *animalPtr = &max; // Polymorphism: Dog IS-A Animal

    std::cout << "\nCalling virtual methods through base class pointer:" << std::endl;
    animalPtr->describe();  // Calls Dog::describe() (polymorphism!)
    animalPtr->makeSound(); // Calls Dog::makeSound() (polymorphism!)

    printSeparator();

    // ==================== DEMO 4: Accessing Members ====================
    std::cout << "DEMO 4: Accessing inherited members" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    Dog luna("Luna", 4, "Husky");

    std::cout << "\nUsing inherited getters:" << std::endl;
    std::cout << "Name: " << luna.getName() << std::endl;   // Inherited getter
    std::cout << "Age: " << luna.getAge() << std::endl;     // Inherited getter
    std::cout << "Breed: " << luna.getBreed() << std::endl; // Dog-specific getter

    std::cout << "\nUsing inherited setters:" << std::endl;
    luna.setAge(5); // Inherited setter
    std::cout << "Updated age: " << luna.getAge() << std::endl;

    printSeparator();

    // ==================== DEMO 5: Constructor/Destructor Chain ====================
    std::cout << "DEMO 5: Constructor and Destructor call order" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    std::cout << "\nCreating Dog object in a scope:" << std::endl;
    {
        std::cout << "{ // Entering scope" << std::endl;
        Dog rocky("Rocky", 1, "Beagle");
        std::cout << "\n} // Exiting scope - watch destructor order:" << std::endl;
    }
    std::cout << "\nNotice: Destructors called in reverse order (Derived -> Base)" << std::endl;

    printSeparator();

    // ==================== DEMO 6: Method Overriding ====================
    std::cout << "DEMO 6: Method Overriding demonstration" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    Animal animal1("Generic", 3);
    Dog dog1("Fido", 3, "Poodle");

    std::cout << "\nSame method, different behavior:" << std::endl;
    std::cout << "\nAnimal's makeSound: ";
    animal1.makeSound();

    std::cout << "Dog's makeSound: ";
    dog1.makeSound();

    printSeparator();

    // ==================== DEMO 7: Testing Cat Class ====================
    std::cout << "DEMO 7: Testing Cat class" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    Cat whiskers("Whiskers", 2, true, 8);

    std::cout << "\nCalling overridden methods on Cat:" << std::endl;
    whiskers.describe();
    whiskers.makeSound();

    std::cout << "\nCalling inherited methods from Animal:" << std::endl;
    whiskers.eat();
    whiskers.sleep();

    std::cout << "\nCalling Cat-specific methods:" << std::endl;
    whiskers.scratch();
    whiskers.climb();

    printSeparator();

    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Dog inherits all public/protected members from Animal" << std::endl;
    std::cout << "2. Dog IS-A Animal (can be treated as an Animal)" << std::endl;
    std::cout << "3. Virtual functions enable polymorphism" << std::endl;
    std::cout << "4. Constructors: Base -> Derived order" << std::endl;
    std::cout << "5. Destructors: Derived -> Base order (reverse)" << std::endl;
    std::cout << "6. 'override' keyword ensures we're actually overriding" << std::endl;
    std::cout << "7. 'virtual' destructor is important for proper cleanup" << std::endl;

    std::cout << "\n\nDemo completed successfully!" << std::endl;
    std::cout << "\nWatch for destructor calls below:" << std::endl;

    

    return 0;
}
