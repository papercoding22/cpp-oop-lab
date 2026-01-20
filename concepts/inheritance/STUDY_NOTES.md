# Inheritance - Detailed Study Notes

**Topic:** Virtual Methods, Method Overriding, and Polymorphism in C++

**Date Created:** 2026-01-08

---

## Table of Contents
1. [Access Specifiers in Inheritance](#access-specifiers-in-inheritance)
2. [Virtual Methods - The Foundation of Polymorphism](#virtual-methods)
3. [Method Overriding](#method-overriding)
4. [Polymorphism - The Power of Virtual Functions](#polymorphism)
5. [Virtual Destructors](#virtual-destructors)
6. [Behind the Scenes - How Virtual Functions Work](#behind-the-scenes)
7. [Common Pitfalls and Best Practices](#common-pitfalls)
8. [Quick Reference](#quick-reference)

---

## Access Specifiers in Inheritance

Understanding access control is fundamental to inheritance. There are three access levels in C++.

### The Three Access Specifiers

```cpp
class Animal {
public:
    // ✅ PUBLIC: Accessible from anywhere
    void eat();                    // Anyone can call this
    std::string getName() const;   // Anyone can call this

protected:
    // ⚠️ PROTECTED: Accessible in this class AND derived classes
    std::string name;  // Dog and Cat can access this directly
    int age;           // Dog and Cat can access this directly

private:
    // 🔒 PRIVATE: Only accessible in this class
    int secretValue;   // ONLY Animal can access this
};
```

### Access Control Table

| Member Type | Same Class | Derived Class | Outside Code |
|-------------|-----------|---------------|--------------|
| `public`    | ✅ Yes    | ✅ Yes        | ✅ Yes       |
| `protected` | ✅ Yes    | ✅ Yes        | ❌ No        |
| `private`   | ✅ Yes    | ❌ No         | ❌ No        |

### Practical Example from Our Code

```cpp
class Cat : public Animal {
public:
    void describe() const override {
        // ✅ Can access 'name' and 'age' because they're PROTECTED in Animal
        std::cout << "I am a cat named " << name << ", "
                  << age << " years old" << std::endl;

        // ❌ CANNOT access private members from Animal (if any existed)
        // std::cout << secretValue;  // ERROR! Private in Animal
    }
};

// Outside code (main.cpp):
int main() {
    Cat whiskers("Whiskers", 2, true, 8);

    // ✅ Can call public methods
    whiskers.describe();
    whiskers.eat();

    // ✅ Can call public getters
    std::cout << whiskers.getName();  // Works! getName() is public

    // ❌ CANNOT access protected members directly
    // std::cout << whiskers.name;  // ERROR! name is protected
    // std::cout << whiskers.age;   // ERROR! age is protected
}
```

### Why Use Protected?

**Question:** Why not just make everything public or private?

**Answer:** `protected` is the **sweet spot** for inheritance:

```cpp
// ❌ If name/age were PUBLIC:
class Animal {
public:
    std::string name;  // Anyone can modify!
    int age;           // Anyone can modify!
};

// Problem: No control over values
whiskers.age = -5;      // Oops! Negative age is invalid
whiskers.name = "";     // Oops! Empty name doesn't make sense

// ❌ If name/age were PRIVATE:
class Animal {
private:
    std::string name;
    int age;
};

class Dog : public Animal {
    void makeSound() const {
        // ERROR! Can't access private members
        std::cout << name << " says woof!";  // Won't compile!
    }
};

// ✅ PROTECTED is perfect:
class Animal {
protected:
    std::string name;  // Derived classes can use it
    int age;           // Derived classes can use it
public:
    // But we control access through public methods
    void setName(const std::string& n) {
        if (!n.empty()) name = n;  // Validation!
    }
};
```

**Key Takeaway:** Protected members are **accessible to derived classes** but **hidden from outside code**, giving you both flexibility and control.

---

## Virtual Methods

Virtual methods are the foundation of **polymorphism** in C++. They allow derived classes to provide their own implementation of a method.

### What is a Virtual Method?

A **virtual method** is a function declared with the `virtual` keyword that can be overridden by derived classes.

```cpp
class Animal {
public:
    // Virtual method - can be overridden
    virtual void makeSound() const {
        std::cout << "Generic animal sound" << std::endl;
    }

    // Non-virtual method - cannot be overridden (well, it can, but...)
    void eat() const {
        std::cout << "Eating..." << std::endl;
    }
};
```

### Syntax of Virtual Methods

```cpp
class BaseClass {
public:
    // Format: virtual return_type methodName(parameters) const;
    virtual void method1() const;           // Virtual method
    virtual int method2(int x);             // Virtual method with return value
    virtual std::string method3() const;    // Virtual method returning string

    void normalMethod();                    // NOT virtual - regular method
};
```

### Virtual vs Non-Virtual: The Critical Difference

Let's see the difference with an example:

```cpp
class Animal {
public:
    // VIRTUAL method
    virtual void makeSound() const {
        std::cout << "Generic animal sound" << std::endl;
    }

    // NON-VIRTUAL method
    void eat() const {
        std::cout << "Eating..." << std::endl;
    }
};

class Dog : public Animal {
public:
    // Override the virtual method
    void makeSound() const override {
        std::cout << "Woof!" << std::endl;
    }

    // Override the non-virtual method (but it won't work as expected!)
    void eat() const {
        std::cout << "Dog eating dog food..." << std::endl;
    }
};

int main() {
    Dog myDog;
    Animal* animalPtr = &myDog;

    // VIRTUAL method - calls Dog's version ✅
    animalPtr->makeSound();  // Prints: "Woof!" (Dog's version)

    // NON-VIRTUAL method - calls Animal's version ❌
    animalPtr->eat();        // Prints: "Eating..." (Animal's version)

    // Direct call works for both
    myDog.makeSound();       // Prints: "Woof!"
    myDog.eat();            // Prints: "Dog eating dog food..."
}
```

### Why Does This Happen?

**Virtual Methods:** Use **runtime polymorphism** (dynamic binding)
- At runtime, C++ checks: "What type is this object really?"
- Calls the appropriate method based on the actual object type

**Non-Virtual Methods:** Use **compile-time binding** (static binding)
- At compile time, C++ looks at the pointer type
- Calls the method based on the pointer type, not the object type

### Visualizing Virtual vs Non-Virtual

```
Animal* ptr = &myDog;
ptr->makeSound();  // Virtual
ptr->eat();        // Non-virtual

┌─────────────────────────────────────┐
│ VIRTUAL (makeSound)                 │
├─────────────────────────────────────┤
│ Compile time:                       │
│   "This is an Animal pointer"       │
│   "makeSound() is virtual"          │
│   "Store: call through vtable"      │
│                                     │
│ Runtime:                            │
│   "Check vtable: what's the real    │
│    type of the object?"             │
│   "It's a Dog!"                     │
│   "Call Dog::makeSound()" ✅        │
└─────────────────────────────────────┘

┌─────────────────────────────────────┐
│ NON-VIRTUAL (eat)                   │
├─────────────────────────────────────┤
│ Compile time:                       │
│   "This is an Animal pointer"       │
│   "eat() is NOT virtual"            │
│   "Call Animal::eat() directly" ❌  │
│                                     │
│ Runtime:                            │
│   (No check, already decided)       │
└─────────────────────────────────────┘
```

### When to Use Virtual Methods?

Use `virtual` when:
- ✅ You want derived classes to provide their own implementation
- ✅ You need polymorphic behavior (base class pointers to derived objects)
- ✅ The method represents behavior that varies by type
- ✅ You're designing a base class meant to be inherited

Don't use `virtual` when:
- ❌ The method should behave the same for all derived classes
- ❌ You're concerned about performance (virtual has tiny overhead)
- ❌ The class is not meant to be inherited (final classes)

### Examples from Our Code

```cpp
// In Animal.h
class Animal {
public:
    // VIRTUAL - Different animals make different sounds
    virtual void makeSound() const;     // ✅ Should be virtual

    // VIRTUAL - Different animals describe themselves differently
    virtual void describe() const;       // ✅ Should be virtual

    // NON-VIRTUAL - All animals eat the same way
    void eat() const;                    // ✅ Doesn't need to be virtual

    // NON-VIRTUAL - All animals sleep the same way
    void sleep() const;                  // ✅ Doesn't need to be virtual
};
```

---

## Method Overriding

**Method overriding** is when a derived class provides a different implementation for a virtual method inherited from the base class.

### Basic Syntax

```cpp
class Base {
public:
    virtual void method() const {
        std::cout << "Base version" << std::endl;
    }
};

class Derived : public Base {
public:
    // Override the method
    void method() const override {  // 'override' keyword is important!
        std::cout << "Derived version" << std::endl;
    }
};
```

### The `override` Keyword

The `override` keyword (C++11 and later) is **optional but highly recommended**.

```cpp
class Animal {
public:
    virtual void makeSound() const;
};

class Dog : public Animal {
public:
    // ✅ GOOD: Using 'override'
    void makeSound() const override {
        std::cout << "Woof!" << std::endl;
    }

    // ❌ BAD: Typo in function signature
    void makeSond() const override {  // Typo: 'Sond' instead of 'Sound'
        std::cout << "Woof!" << std::endl;
    }
    // Compiler ERROR: "method does not override any base class method"
    // This catches the typo!
};

class Cat : public Animal {
public:
    // ⚠️ WORKS BUT NOT RECOMMENDED: No 'override'
    void makeSound() const {  // No override keyword
        std::cout << "Meow!" << std::endl;
    }
    // Compiles, but if you make a typo, compiler won't catch it
};
```

**Why use `override`?**
1. **Catches typos:** Compiler verifies you're actually overriding
2. **Catches signature mismatches:** Ensures parameters match exactly
3. **Self-documenting:** Makes your intent clear to other programmers
4. **Prevents errors:** If base class changes, compiler warns you

### Rules for Overriding

For a method to properly override a base class method, it must match **exactly**:

| Requirement | Must Match | Example |
|-------------|-----------|---------|
| Name | ✅ Yes | `makeSound` not `makeSound_` |
| Parameters | ✅ Yes | `(int x)` not `(int x, int y)` |
| Return type | ✅ Yes (with exceptions*) | `void` not `int` |
| const qualifier | ✅ Yes | `const` or not const |
| Reference qualifiers | ✅ Yes | `&`, `&&`, or none |

*Covariant return types allow derived class to return a more derived type

### Common Mistakes When Overriding

#### Mistake 1: Wrong Signature
```cpp
class Animal {
public:
    virtual void makeSound() const;
};

class Dog : public Animal {
public:
    // ❌ ERROR: Missing 'const'
    void makeSound() override {  // Not const!
        std::cout << "Woof!" << std::endl;
    }
    // Compiler error: "does not override"
};
```

#### Mistake 2: Forgetting Virtual in Base
```cpp
class Animal {
public:
    void makeSound() const;  // ❌ NOT virtual!
};

class Dog : public Animal {
public:
    void makeSound() const override {  // ❌ ERROR!
        std::cout << "Woof!" << std::endl;
    }
    // Error: Cannot override non-virtual function
};
```

#### Mistake 3: Different Parameters
```cpp
class Animal {
public:
    virtual void makeSound() const;
};

class Dog : public Animal {
public:
    // ❌ ERROR: Different parameters
    void makeSound(int volume) const override {
        std::cout << "Woof!" << std::endl;
    }
    // Compiler error: "does not override"
};
```

### Overriding vs Overloading

**These are DIFFERENT concepts!**

```cpp
// OVERRIDING - Same signature, different class
class Animal {
public:
    virtual void makeSound() const;
};
class Dog : public Animal {
public:
    void makeSound() const override;  // ✅ Overriding Animal::makeSound
};

// OVERLOADING - Different signatures, same class
class Dog {
public:
    void makeSound() const;           // Version 1
    void makeSound(int times) const;  // Version 2 - different parameter
    void makeSound(bool loud) const;  // Version 3 - different parameter
};
// ✅ Overloading: same name, different parameters, SAME class
```

### Calling Base Class Version

Sometimes you want to extend the base class behavior, not replace it:

```cpp
class Animal {
public:
    virtual void describe() const {
        std::cout << "I am an animal" << std::endl;
    }
};

class Dog : public Animal {
public:
    void describe() const override {
        // Call base class version first
        Animal::describe();  // Prints: "I am an animal"

        // Then add more
        std::cout << "Specifically, I am a dog" << std::endl;
    }
};

int main() {
    Dog myDog;
    myDog.describe();
    // Output:
    // I am an animal
    // Specifically, I am a dog
}
```

### Our Code Examples

#### Example 1: Cat Overriding makeSound
```cpp
// In Animal.h
virtual void makeSound() const;

// In Cat.cpp
void Cat::makeSound() const override {
    std::cout << name << " says: Meow! Meow!" << std::endl;
}
```

#### Example 2: Dog Overriding describe
```cpp
// In Animal.h
virtual void describe() const;

// In Dog.cpp
void Dog::describe() const override {
    std::cout << "I am a dog named " << name << ", "
              << age << " years old, breed: " << breed << std::endl;
}
```

---

## Polymorphism

**Polymorphism** means "many forms." In C++, it allows objects of different classes to be treated as objects of a common base class.

### What is Polymorphism?

**Greek Origin:** poly (many) + morph (form)

**In C++:** The ability to call the correct method based on the actual object type, even when using a base class pointer or reference.

```cpp
Animal* ptr1 = &dog;   // Animal pointer, Dog object
Animal* ptr2 = &cat;   // Animal pointer, Cat object

ptr1->makeSound();     // Calls Dog::makeSound() - "Woof!"
ptr2->makeSound();     // Calls Cat::makeSound() - "Meow!"

// Same call, different behavior = Polymorphism!
```

### Types of Polymorphism in C++

#### 1. Compile-Time Polymorphism (Static)
- Function overloading
- Operator overloading
- Templates
- Decision made at compile time

#### 2. Runtime Polymorphism (Dynamic) ⭐ **We're focusing on this!**
- Virtual functions
- Decision made at runtime
- Requires base class pointer/reference
- Enabled by virtual functions

### How Runtime Polymorphism Works

```cpp
class Animal {
public:
    virtual void makeSound() const {
        std::cout << "Generic sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() const override {
        std::cout << "Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "Meow!" << std::endl;
    }
};

int main() {
    Dog myDog;
    Cat myCat;

    // ✅ Polymorphism through pointers
    Animal* ptr1 = &myDog;
    Animal* ptr2 = &myCat;

    ptr1->makeSound();  // Woof! (Dog's version)
    ptr2->makeSound();  // Meow! (Cat's version)

    // ✅ Polymorphism through references
    Animal& ref1 = myDog;
    Animal& ref2 = myCat;

    ref1.makeSound();   // Woof! (Dog's version)
    ref2.makeSound();   // Meow! (Cat's version)
}
```

### The Power of Polymorphism: Generic Functions

Polymorphism allows you to write generic functions that work with any derived class:

```cpp
// One function works with ALL animals!
void introduceAnimal(Animal* animal) {
    std::cout << "\n--- Meet an animal ---" << std::endl;
    animal->describe();    // Calls the correct derived class version
    animal->makeSound();   // Calls the correct derived class version
    std::cout << "------------------------\n" << std::endl;
}

int main() {
    Dog myDog("Rex", 5, "Husky");
    Cat myCat("Whiskers", 3, true, 8);

    // Same function, different objects!
    introduceAnimal(&myDog);   // Calls Dog's describe() and makeSound()
    introduceAnimal(&myCat);   // Calls Cat's describe() and makeSound()

    // Output:
    // --- Meet an animal ---
    // I am a dog named Rex, 5 years old, breed: Husky
    // Rex says: Woof! Woof!
    // ------------------------
    //
    // --- Meet an animal ---
    // I am a cat named Whiskers, 3 years old, indoor, claw sharpness: 8
    // Whiskers says: Meow! Meow!
    // ------------------------
}
```

### Polymorphism with Collections

One of the most powerful uses of polymorphism is storing different types in a single collection:

```cpp
#include <vector>

int main() {
    // Create different animals
    Dog dog1("Buddy", 3, "Retriever");
    Dog dog2("Max", 2, "Poodle");
    Cat cat1("Whiskers", 4, true, 7);
    Cat cat2("Shadow", 1, false, 9);

    // Store them all in ONE vector!
    std::vector<Animal*> shelter;
    shelter.push_back(&dog1);
    shelter.push_back(&cat1);
    shelter.push_back(&dog2);
    shelter.push_back(&cat2);

    // Loop through and call methods - polymorphism in action!
    std::cout << "=== All animals in the shelter ===" << std::endl;
    for (Animal* animal : shelter) {
        animal->describe();    // Calls correct version (Dog or Cat)
        animal->makeSound();   // Calls correct version (Dog or Cat)
        std::cout << std::endl;
    }

    // Output:
    // I am a dog named Buddy...
    // Buddy says: Woof! Woof!
    //
    // I am a cat named Whiskers...
    // Whiskers says: Meow! Meow!
    //
    // I am a dog named Max...
    // Max says: Woof! Woof!
    //
    // I am a cat named Shadow...
    // Shadow says: Meow! Meow!
}
```

### When Does Polymorphism NOT Work?

#### ❌ Case 1: Using Objects (not pointers/references)
```cpp
void printAnimalByValue(Animal animal) {  // Passing by VALUE!
    animal.makeSound();
}

Dog myDog("Rex", 5, "Husky");
printAnimalByValue(myDog);  // ❌ Calls Animal::makeSound(), not Dog::makeSound()!

// Why? Object slicing! The Dog is "sliced" to fit into an Animal.
```

#### ❌ Case 2: Non-Virtual Methods
```cpp
class Animal {
public:
    void eat() {  // NOT virtual
        std::cout << "Animal eating" << std::endl;
    }
};

class Dog : public Animal {
public:
    void eat() {
        std::cout << "Dog eating" << std::endl;
    }
};

Dog myDog;
Animal* ptr = &myDog;
ptr->eat();  // ❌ Calls Animal::eat(), not Dog::eat()
```

#### ✅ Case 3: Correct Polymorphism
```cpp
class Animal {
public:
    virtual void eat() {  // ✅ Virtual!
        std::cout << "Animal eating" << std::endl;
    }
};

class Dog : public Animal {
public:
    void eat() override {
        std::cout << "Dog eating" << std::endl;
    }
};

Dog myDog;
Animal* ptr = &myDog;
ptr->eat();  // ✅ Calls Dog::eat()
```

### Real-World Analogy

Think of polymorphism like a universal remote control:

```
Universal Remote (Animal*)
         ↓
    Press "Play"
         ↓
Is this controlling a TV? → TV plays video
Is this controlling a stereo? → Stereo plays music
Is this controlling a DVD player? → DVD plays movie

Same button ("Play" / makeSound()),
Different devices (TV/Stereo/DVD / Dog/Cat),
Different behaviors (video/music/movie / bark/meow)
```

### The Three Requirements for Polymorphism

For runtime polymorphism to work, you need ALL three:

1. ✅ **Inheritance:** Derived class inherits from base class
2. ✅ **Virtual function:** Method is declared `virtual` in base class
3. ✅ **Base class pointer/reference:** Using base class pointer or reference to derived object

```cpp
// ✅ All three requirements met
class Animal {
    virtual void makeSound();  // ✅ Requirement 2: Virtual
};

class Dog : public Animal {    // ✅ Requirement 1: Inheritance
    void makeSound() override;
};

Animal* ptr = &myDog;          // ✅ Requirement 3: Base class pointer
ptr->makeSound();              // ✅ Polymorphism works!
```

---

## Virtual Destructors

Virtual destructors are **critically important** for proper memory management in inheritance.

### The Problem Without Virtual Destructors

```cpp
class Animal {
public:
    Animal() { std::cout << "Animal constructor" << std::endl; }
    ~Animal() { std::cout << "Animal destructor" << std::endl; }  // ❌ NOT virtual!
};

class Dog : public Animal {
private:
    int* data;  // Dynamically allocated memory
public:
    Dog() {
        data = new int[100];
        std::cout << "Dog constructor" << std::endl;
    }
    ~Dog() {
        delete[] data;  // Clean up memory
        std::cout << "Dog destructor" << std::endl;
    }
};

int main() {
    Animal* ptr = new Dog();  // Create Dog through Animal pointer
    delete ptr;               // ❌ MEMORY LEAK!

    // Output:
    // Animal constructor
    // Dog constructor
    // Animal destructor  ← Only Animal destructor called!
    //
    // Dog destructor NEVER called → Memory leak!
}
```

**What went wrong?**
- `delete ptr` sees `Animal*` pointer
- Animal's destructor is NOT virtual
- Only `Animal::~Animal()` is called
- `Dog::~Dog()` is NEVER called
- Dog's `data` is never freed → **Memory leak!**

### The Solution: Virtual Destructor

```cpp
class Animal {
public:
    Animal() { std::cout << "Animal constructor" << std::endl; }
    virtual ~Animal() { std::cout << "Animal destructor" << std::endl; }  // ✅ Virtual!
};

class Dog : public Animal {
private:
    int* data;
public:
    Dog() {
        data = new int[100];
        std::cout << "Dog constructor" << std::endl;
    }
    ~Dog() {  // Can use 'override' here too (C++11+)
        delete[] data;
        std::cout << "Dog destructor" << std::endl;
    }
};

int main() {
    Animal* ptr = new Dog();
    delete ptr;  // ✅ Correct cleanup!

    // Output:
    // Animal constructor
    // Dog constructor
    // Dog destructor     ← Dog destructor called first!
    // Animal destructor  ← Then Animal destructor
    //
    // No memory leak! ✅
}
```

### Why Our Code Has Virtual Destructors

Look at Animal.h:
```cpp
class Animal {
public:
    virtual ~Animal();  // ✅ Virtual destructor
};
```

This is why when you run the program, you see:
```
Dog destructor called for Rex
Animal destructor called for Rex
```

Both destructors are called in the correct order (Derived → Base).

### The Rule of Thumb

**If a class has ANY virtual functions, its destructor should be virtual.**

```cpp
class Base {
public:
    virtual void someMethod();  // Has virtual method
    virtual ~Base();            // ✅ Destructor should be virtual too!
};
```

### Our Code Examples

#### Animal.h
```cpp
class Animal {
public:
    virtual ~Animal();  // ✅ Virtual destructor
    virtual void makeSound() const;  // Has virtual methods
};
```

#### Dog.h
```cpp
class Dog : public Animal {
public:
    virtual ~Dog();  // ✅ Also virtual (inherited virtual property)
};
```

#### Cat.h
```cpp
class Cat : public Animal {
public:
    virtual ~Cat();  // ✅ Also virtual
};
```

---

## Behind the Scenes: How Virtual Functions Work

Understanding the mechanism behind virtual functions helps you appreciate their power and cost.

### The Virtual Table (vtable)

When a class has virtual functions, the compiler creates a **virtual table** (vtable) for that class.

```cpp
class Animal {
public:
    virtual void makeSound();
    virtual void describe();
    void eat();  // Not virtual
};

// Compiler creates a vtable for Animal:
Animal_vtable:
  [0] → Animal::makeSound
  [1] → Animal::describe
```

### The Virtual Pointer (vptr)

Each object of a class with virtual functions contains a hidden pointer to its class's vtable.

```cpp
Dog myDog;

// myDog actually contains:
// - vptr (hidden pointer to Dog_vtable)
// - name
// - age
// - breed
```

### Visual Representation

```
┌─────────────────────────────────────────────────────┐
│ Dog object: myDog                                   │
├─────────────────────────────────────────────────────┤
│ vptr ────────────┐                                  │
│ name: "Rex"      │                                  │
│ age: 5           │                                  │
│ breed: "Husky"   │                                  │
└──────────────────┼──────────────────────────────────┘
                   │
                   ↓
         ┌─────────────────┐
         │ Dog_vtable      │
         ├─────────────────┤
         │ [0] → Dog::makeSound   │
         │ [1] → Dog::describe    │
         └─────────────────┘

┌─────────────────────────────────────────────────────┐
│ Cat object: myCat                                   │
├─────────────────────────────────────────────────────┤
│ vptr ────────────┐                                  │
│ name: "Whiskers" │                                  │
│ age: 3           │                                  │
│ isIndoor: true   │                                  │
│ clawSharpness: 8 │                                  │
└──────────────────┼──────────────────────────────────┘
                   │
                   ↓
         ┌─────────────────┐
         │ Cat_vtable      │
         ├─────────────────┤
         │ [0] → Cat::makeSound   │
         │ [1] → Cat::describe    │
         └─────────────────┘
```

### How a Virtual Function Call Works

```cpp
Animal* ptr = &myDog;
ptr->makeSound();
```

**Step-by-step:**

1. **Compile time:** Compiler sees `makeSound()` is virtual
   - Generates code to lookup function through vtable

2. **Runtime:**
   - Follow `ptr` to the actual object (myDog)
   - Access the hidden `vptr` in myDog
   - `vptr` points to Dog_vtable
   - Look up `makeSound` in Dog_vtable (index [0])
   - Call `Dog::makeSound()`

```
ptr (Animal*) → myDog object
                   ↓
                 vptr
                   ↓
              Dog_vtable
                   ↓
          [0] Dog::makeSound ← Call this!
```

### Comparison: Virtual vs Non-Virtual Call

#### Non-Virtual Call (Direct)
```cpp
ptr->eat();  // eat() is NOT virtual

Compile time: "Call Animal::eat() directly"
Runtime: Jump directly to Animal::eat()

Fast! ✅ (Direct function call)
```

#### Virtual Call (Indirect)
```cpp
ptr->makeSound();  // makeSound() IS virtual

Compile time: "Call through vtable"
Runtime:
  1. Access object's vptr
  2. Look up function in vtable
  3. Jump to the function

Slightly slower ⚠️ (Extra indirection)
But still very fast in practice!
```

### Performance Cost

**How much slower are virtual functions?**
- One extra pointer dereference
- Typically 5-20 nanoseconds overhead
- Usually negligible compared to what the function does

**When to worry about performance:**
- ❌ Calling virtual functions millions of times per frame in performance-critical code
- ✅ Normal application code - the cost is insignificant

**Rule of thumb:** Don't optimize prematurely. Use virtual functions where they make sense for design, not performance.

### Memory Cost

Each object with virtual functions has one extra pointer (vptr):
- 32-bit system: 4 bytes
- 64-bit system: 8 bytes

Plus one vtable per class (shared by all objects of that class).

**Example:**
```cpp
class Animal {
    virtual void makeSound();
    std::string name;  // ~24 bytes
    int age;           // 4 bytes
};
// Size: ~32-40 bytes (including vptr)

// 1000 Animal objects: ~32-40 KB
// Plus one vtable: ~16 bytes
// Total: ~32-40 KB (vtable is shared, so minimal overhead)
```

---

## Common Pitfalls and Best Practices

### Pitfall 1: Forgetting Virtual Destructor

❌ **Problem:**
```cpp
class Base {
public:
    ~Base() { }  // NOT virtual!
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() { data = new int[100]; }
    ~Derived() { delete[] data; }
};

Base* ptr = new Derived();
delete ptr;  // Memory leak! Derived destructor not called
```

✅ **Solution:**
```cpp
class Base {
public:
    virtual ~Base() { }  // Virtual!
};
```

**Rule:** If a class has virtual functions OR is meant to be inherited, make the destructor virtual.

---

### Pitfall 2: Object Slicing

❌ **Problem:**
```cpp
void processAnimal(Animal animal) {  // Pass by value!
    animal.makeSound();
}

Dog myDog("Rex", 5, "Husky");
processAnimal(myDog);  // Dog is "sliced" to fit into Animal
// Output: Generic animal sound (not Woof!)
```

**What happened?**
- When passing by value, only the `Animal` part of `myDog` is copied
- The `Dog`-specific parts (breed, vtable pointer) are lost
- This is called "object slicing"

✅ **Solution 1: Pass by pointer**
```cpp
void processAnimal(Animal* animal) {
    animal->makeSound();
}
processAnimal(&myDog);  // ✅ Polymorphism works!
```

✅ **Solution 2: Pass by reference**
```cpp
void processAnimal(Animal& animal) {
    animal.makeSound();
}
processAnimal(myDog);  // ✅ Polymorphism works!
```

---

### Pitfall 3: Calling Virtual Functions in Constructors

❌ **Problematic:**
```cpp
class Animal {
public:
    Animal() {
        initialize();  // Calls virtual function in constructor
    }

    virtual void initialize() {
        std::cout << "Animal initialized" << std::endl;
    }
};

class Dog : public Animal {
public:
    Dog() : Animal() { }

    void initialize() override {
        std::cout << "Dog initialized" << std::endl;
    }
};

Dog myDog;
// Output: "Animal initialized" (NOT "Dog initialized"!)
```

**Why?**
- During construction, the Dog object is not fully constructed yet
- When Animal's constructor runs, the Dog part doesn't exist yet
- So calling `initialize()` calls Animal's version, not Dog's

**Rule:** Don't rely on polymorphism in constructors/destructors. The object isn't fully constructed yet.

---

### Pitfall 4: Not Using `override` Keyword

❌ **Problem:**
```cpp
class Animal {
public:
    virtual void makeSound() const;
};

class Dog : public Animal {
public:
    void makeSund() const {  // Typo! But no error without 'override'
        std::cout << "Woof!" << std::endl;
    }
};

Dog myDog;
Animal* ptr = &myDog;
ptr->makeSound();  // Calls Animal::makeSound() - bug!
```

✅ **Solution:**
```cpp
class Dog : public Animal {
public:
    void makeSund() const override {  // Compiler error: "does not override"
        std::cout << "Woof!" << std::endl;
    }
};
```

**Rule:** Always use `override` keyword when overriding virtual functions.

---

### Pitfall 5: Hiding Instead of Overriding

❌ **Problem:**
```cpp
class Animal {
public:
    virtual void makeSound() const;
};

class Dog : public Animal {
public:
    void makeSound() {  // Missing 'const' - doesn't match!
        std::cout << "Woof!" << std::endl;
    }
};

Dog myDog;
Animal* ptr = &myDog;
ptr->makeSound();  // Calls Animal::makeSound() - not overridden!
```

The signature doesn't match exactly, so it's not an override - it's a completely different function!

✅ **Solution:** Use `override` to catch this:
```cpp
void makeSound() override {  // ERROR: does not override
```

---

### Best Practices Summary

#### ✅ DO:
1. **Always declare destructors virtual** in base classes
2. **Use `override` keyword** when overriding virtual functions
3. **Pass polymorphic objects by pointer or reference**, not by value
4. **Make functions virtual** when you want derived classes to customize behavior
5. **Use base class pointers/references** when you want polymorphic behavior
6. **Document which functions are meant to be overridden**

#### ❌ DON'T:
1. **Don't forget virtual destructors** - leads to memory leaks
2. **Don't pass polymorphic objects by value** - causes slicing
3. **Don't call virtual functions in constructors/destructors** - polymorphism doesn't work
4. **Don't make everything virtual** - only what needs to be customized
5. **Don't override non-virtual functions** - confusing and doesn't work as expected
6. **Don't forget `override`** - catches errors at compile time

---

## Quick Reference

### Syntax Cheat Sheet

```cpp
// Base class with virtual functions
class Base {
public:
    // Virtual function
    virtual void method1() const;

    // Pure virtual function (abstract)
    virtual void method2() const = 0;

    // Virtual destructor
    virtual ~Base();

    // Non-virtual function
    void normalMethod();
};

// Derived class
class Derived : public Base {
public:
    // Override virtual function
    void method1() const override;

    // Implement pure virtual function
    void method2() const override;

    // Virtual destructor
    virtual ~Derived();

    // New function (not overriding)
    void newMethod();
};

// Usage
int main() {
    Derived obj;
    Base* ptr = &obj;

    ptr->method1();  // Calls Derived::method1() (polymorphism)
    ptr->normalMethod();  // Calls Base::normalMethod()
}
```

### Key Concepts at a Glance

| Concept | Definition | Example |
|---------|-----------|---------|
| **Virtual Function** | Function that can be overridden in derived classes | `virtual void method();` |
| **Override** | Providing a new implementation in derived class | `void method() override;` |
| **Polymorphism** | Different behavior based on actual object type | `Base* ptr = &derived; ptr->method();` |
| **Virtual Destructor** | Destructor that ensures proper cleanup through base pointer | `virtual ~Base();` |
| **Abstract Class** | Class with at least one pure virtual function | `virtual void method() = 0;` |
| **Object Slicing** | Loss of derived class data when passing by value | Avoid with pointers/references |

### Access Specifiers Quick Reference

```cpp
class Base {
public:
    int pub;        // ✅ Anywhere
protected:
    int prot;       // ✅ Base class, ✅ Derived class, ❌ Outside
private:
    int priv;       // ✅ Base class, ❌ Derived class, ❌ Outside
};
```

### When to Use What

| Scenario | Use |
|----------|-----|
| Method should behave differently in derived classes | `virtual` |
| Forcing derived classes to implement a method | `= 0` (pure virtual) |
| Base class meant for inheritance | `virtual` destructor |
| Overriding a virtual function | `override` keyword |
| Generic function for multiple types | Base class pointer/reference |
| Collection of different types | `vector<Base*>` |

---

## Practice Questions

Test your understanding:

### Question 1
Why does this not work as expected?
```cpp
void processAnimal(Animal animal) {
    animal.makeSound();
}
Dog myDog;
processAnimal(myDog);  // Doesn't bark!
```

<details>
<summary>Answer</summary>
Object slicing! Passing by value copies only the Animal part. Use `Animal*` or `Animal&` instead.
</details>

### Question 2
What's wrong with this code?
```cpp
class Base {
    ~Base() { delete data; }  // NOT virtual
    int* data;
};
Base* ptr = new Derived();
delete ptr;  // Problem?
```

<details>
<summary>Answer</summary>
Memory leak! Without virtual destructor, only Base's destructor is called. Derived's destructor never runs, causing memory leaks.
</details>

### Question 3
Why use `override`?
```cpp
class Dog : public Animal {
    void makeSound() override;  // Why override?
};
```

<details>
<summary>Answer</summary>
- Catches typos in function name
- Ensures signature matches exactly
- Self-documenting code
- Compiler verifies you're actually overriding
</details>

---

## Additional Resources

- [C++ Core Guidelines on Virtual Functions](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override)
- [Effective C++ by Scott Meyers](https://www.aristeia.com/books.html) - Items 7, 36, 37, 38, 39
- [Virtual Function Table (Wikipedia)](https://en.wikipedia.org/wiki/Virtual_method_table)

---

**Last Updated:** 2026-01-08
**Next Review:** After completing EXERCISES.md
