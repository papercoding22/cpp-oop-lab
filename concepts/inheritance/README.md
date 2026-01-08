# Inheritance

## Overview
Demonstrating class inheritance and IS-A relationships in C++. This example shows how Dog inherits from Animal, creating a hierarchical relationship where Dog IS-A specialized type of Animal.

## Learning Objectives
After studying this example, you should understand:
- How to create a base class and derived class
- The IS-A relationship in object-oriented design
- How constructors and destructors work in inheritance hierarchies
- The difference between public, protected, and private access specifiers
- Method overriding and the `override` keyword
- Virtual functions and their role in polymorphism
- Why virtual destructors are important in inheritance

## Key Concepts

### 1. Inheritance Syntax
```cpp
class Dog : public Animal {  // Dog inherits from Animal
    // Dog has all of Animal's public/protected members
    // plus its own members
};
```

### 2. Access Specifiers in Inheritance
- **public inheritance**: IS-A relationship (most common)
- **protected members**: Accessible in derived classes but not outside
- **private members**: Not accessible in derived classes

### 3. Constructor/Destructor Chain
- **Constructors**: Base class → Derived class (top-down)
- **Destructors**: Derived class → Base class (bottom-up, reverse order)

### 4. Virtual Functions
- Marked with `virtual` keyword in base class
- Can be overridden in derived classes
- Enable runtime polymorphism
- Use `override` keyword in derived class for safety

### 5. Virtual Destructors
Always make destructors virtual in base classes to ensure proper cleanup when deleting through base class pointers.

## Code Structure

### Animal.h / Animal.cpp (Base Class)
- **Properties**: name, age (protected - accessible by Dog)
- **Virtual methods**: makeSound(), describe() (can be overridden)
- **Regular methods**: eat(), sleep() (inherited as-is)
- **Constructors**: Default and parameterized
- **Destructor**: Virtual (important for polymorphism)

### Dog.h / Dog.cpp (Derived Class)
- **Inherits from**: Animal
- **Additional property**: breed
- **Overridden methods**: makeSound() - dogs bark!, describe() - includes breed
- **New methods**: fetch(), wagTail() (dog-specific behaviors)
- **Constructor**: Calls Animal's constructor using initializer list

### main.cpp
Comprehensive demonstrations of:
1. Creating base and derived class objects
2. IS-A relationship and polymorphism
3. Method overriding
4. Accessing inherited members
5. Constructor/destructor call order
6. Virtual function behavior

## Building

From project root:
```bash
mkdir -p build && cd build
cmake ..
make inheritance_demo
```

## Running

From build directory:
```bash
./concepts/inheritance/inheritance_demo
```

You'll see 6 different demos showing various aspects of inheritance.

## Important Code Patterns

### Calling Base Constructor
```cpp
Dog::Dog(const std::string& name, int age, const std::string& breed)
    : Animal(name, age), breed(breed) {  // Initialize base class first
    // Dog-specific initialization
}
```

### Overriding Virtual Functions
```cpp
// In base class (Animal.h)
virtual void makeSound() const;

// In derived class (Dog.h)
virtual void makeSound() const override;  // 'override' is optional but recommended
```

### Polymorphism Example
```cpp
Dog myDog("Buddy", 3, "Retriever");
Animal* animalPtr = &myDog;  // Dog IS-A Animal
animalPtr->makeSound();      // Calls Dog::makeSound() due to virtual function
```

## Exercises

### Beginner
1. **Create a Cat class**: Inherit from Animal, override makeSound() to meow
2. **Add more properties**: Give Animal a color property, ensure it's inherited
3. **Experiment with access**: Try to access private members from Dog - observe the error

### Intermediate
4. **Create a Pet class hierarchy**: Animal → Pet → Dog/Cat (multi-level inheritance)
5. **Add pure virtual functions**: Make Animal abstract with pure virtual functions
6. **Implement a Bird class**: Add a fly() method that doesn't apply to Dog/Cat

### Advanced
7. **Create an Animal collection**: Use a vector of Animal pointers containing different derived types
8. **Implement the Rule of Three**: Add copy constructor and assignment operator to both classes
9. **Multiple inheritance**: Create a GuardDog that inherits from both Dog and Guard

## Key Takeaways

### When to Use Inheritance
✅ When you have a clear IS-A relationship (Dog IS-A Animal)
✅ When derived classes are specialized versions of the base class
✅ When you want to share common behavior across related classes
✅ When you need polymorphic behavior

### Common Pitfalls to Avoid
❌ **Forgetting virtual destructor**: Always make base class destructor virtual
❌ **Slicing**: Passing derived objects by value to base class parameters
❌ **Deep hierarchies**: Too many inheritance levels make code hard to maintain
❌ **IS-A vs HAS-A confusion**: Use inheritance for IS-A, composition for HAS-A
❌ **Breaking Liskov Substitution**: Derived class should be usable wherever base class is expected

### Best Practices
✅ Use `override` keyword to catch mistakes
✅ Prefer composition over inheritance when in doubt
✅ Keep inheritance hierarchies shallow (ideally 2-3 levels max)
✅ Mark methods as `virtual` only when needed
✅ Use `protected` for members that derived classes should access
✅ Document which methods are meant to be overridden

## Related Concepts

- **Polymorphism**: Virtual functions enable runtime polymorphism
- **Encapsulation**: Access specifiers control what derived classes can access
- **Abstraction**: Base classes can be abstract (pure virtual functions)
- **Composition**: Alternative to inheritance (HAS-A relationship)
- **Multiple Inheritance**: Inheriting from multiple base classes (advanced)
- **Virtual Base Classes**: Solving diamond problem in multiple inheritance

## Further Reading

- C++ Core Guidelines on inheritance: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-class
- Effective C++ by Scott Meyers - Item 7: "Declare destructors virtual in polymorphic base classes"
- SOLID Principles - Liskov Substitution Principle
- Design Patterns (Gang of Four) - Many patterns use inheritance
