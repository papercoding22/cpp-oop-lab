# Inheritance - Practice Exercises

This file contains hands-on exercises to practice and deepen your understanding of inheritance in C++.

---

## Exercise 1: Create a Cat Class 🐱

**Difficulty:** Beginner
**Estimated Time:** 30-45 minutes

### Objective
Create a Cat class that inherits from Animal, similar to how Dog inherits from Animal. This will help you practice all the key concepts of inheritance.

### Step-by-Step Guide

#### Step 1: Generate Cat Class Files

Use the script to create the Cat class files:

```bash
python3 scripts/create_class.py inheritance Cat --base-class Animal
```

This creates `Cat.h` and `Cat.cpp` in the inheritance folder.

#### Step 2: Plan Your Cat's Behavior

Before coding, answer these questions:

1. **What sound does a cat make?** (This will override `makeSound()`)
   - Your answer: _______________

2. **What's a cat-specific property?** (Dogs have `breed`)
   - Ideas: `color`, `isIndoor`, `favoriteToy`, `furLength`
   - Your choice: _______________
   - Data type: _______________

3. **What behaviors are unique to cats?** (Dogs `fetch()` and `wagTail()`)
   - Ideas: `purr()`, `scratch()`, `climb()`, `meow()`, `nap()`, `huntMice()`
   - Your choices (pick 2-3): _______________

#### Step 3: Update Cat.h (Header File)

Open `concepts/inheritance/Cat.h` and make these modifications:

##### 3a. Add Your Cat-Specific Property
```cpp
private:
    // TODO: Add your cat-specific property here
    // Example: std::string color;
```

##### 3b. Update Parameterized Constructor
```cpp
/**
 * @brief Parameterized constructor
 * @param name Name of the cat
 * @param age Age of the cat in years
 * @param ??? Your cat property parameter
 */
Cat(const std::string& name, int age, const ???& ???);
```

##### 3c. Add Getter and Setter
```cpp
// TODO: Add getter for your property
??? get???() const;

// TODO: Add setter for your property
void set???(const ???& ???);
```

##### 3d. Override Virtual Methods
```cpp
/**
 * @brief Override makeSound - cats meow/purr
 */
virtual void makeSound() const override;

/**
 * @brief Override describe - provide cat-specific description
 */
virtual void describe() const override;
```

##### 3e. Add Cat-Specific Methods
```cpp
/**
 * @brief Cat-specific behavior 1
 */
void ???() const;

/**
 * @brief Cat-specific behavior 2
 */
void ???() const;

// Add more as you planned!
```

#### Step 4: Implement Cat.cpp

Open `concepts/inheritance/Cat.cpp` and implement all methods:

##### 4a. Default Constructor
```cpp
Cat::Cat()
    : Animal(), ??? {  // Initialize your property with a default value
    std::cout << "Cat default constructor called" << std::endl;
}
```

**Reference:** Look at Dog.cpp lines 13-16

##### 4b. Parameterized Constructor
```cpp
Cat::Cat(const std::string& name, int age, const ???& ???)
    : Animal(name, age), ???(???) {
    std::cout << "Cat parameterized constructor called for " << name << std::endl;
}
```

**Reference:** Look at Dog.cpp lines 22-25

##### 4c. Implement Getter and Setter
```cpp
??? Cat::get???() const {
    return ???;
}

void Cat::set???(const ???& ???) {
    this->??? = ???;
}
```

**Reference:** Look at Dog.cpp lines 35-42

##### 4d. Override makeSound()
```cpp
void Cat::makeSound() const {
    std::cout << name << " says: ???" << std::endl;
}
```

**Think:** What sound should a cat make?

##### 4e. Override describe()
```cpp
void Cat::describe() const {
    std::cout << "I am a cat named " << name << ", "
              << age << " years old, ???: " << ??? << std::endl;
}
```

##### 4f. Implement Cat-Specific Methods
```cpp
void Cat::???() const {
    std::cout << name << " is ???ing! (description)" << std::endl;
}

// Implement your other cat behaviors!
```

**Reference:** Look at Dog's `fetch()` and `wagTail()` methods

#### Step 5: Test Your Cat in main.cpp

Add a new demo section to test your Cat class:

```cpp
printSeparator();

// ==================== DEMO 7: Testing Cat Class ====================
std::cout << "DEMO 7: Testing Cat class" << std::endl;
std::cout << std::string(60, '=') << std::endl;

// Create a Cat object
Cat whiskers("Whiskers", 2, "???");  // Your property value

std::cout << "\nCalling methods on Cat:" << std::endl;
whiskers.describe();
whiskers.makeSound();

std::cout << "\nCalling inherited methods from Animal:" << std::endl;
whiskers.eat();
whiskers.sleep();

std::cout << "\nCalling Cat-specific methods:" << std::endl;
whiskers.???();  // Your cat methods
whiskers.???();

printSeparator();
```

**Add this before the "Key Takeaways" section in main.cpp**

#### Step 6: Build and Test

```bash
cd build
cmake ..
make inheritance_demo
./concepts/inheritance/inheritance_demo
```

### Expected Output

You should see:
- ✅ "Cat parameterized constructor called for Whiskers"
- ✅ Cat's describe() showing your cat property
- ✅ Cat's makeSound() with cat sounds
- ✅ Inherited eat() and sleep() methods working
- ✅ Your cat-specific behaviors executing
- ✅ "Cat destructor called for Whiskers" at the end

### Self-Check Questions

After completing the exercise, answer these questions:

1. **Why did Cat need to call Animal's constructor in the initializer list?**
   - Hint: Think about initialization order

2. **What happens if you forget the `override` keyword?**
   - Try it: Remove `override` from one method and recompile
   - What's the difference?

3. **Can you access Animal's `name` member directly in Cat methods?**
   - Why or why not?
   - What access specifier is `name` in Animal?

4. **What's printed first when a Cat object is destroyed?**
   - Cat destructor or Animal destructor?
   - Why is this order important?

5. **Could you create an Animal pointer that points to a Cat object?**
   - Try: `Animal* ptr = &whiskers;`
   - Does it work? Why?

---

## Exercise 2: Polymorphism with Cat and Dog 🐶🐱

**Difficulty:** Intermediate
**Estimated Time:** 20-30 minutes

### Objective
Demonstrate polymorphism by treating both Dogs and Cats as Animals.

### Task 2a: Create a Generic Animal Function

Add this function to main.cpp (before the main function):

```cpp
/**
 * @brief Generic function that works with any Animal
 * @param animal Pointer to any Animal (or derived class)
 */
void introduceAnimal(Animal* animal) {
    std::cout << "\n--- Introducing an animal ---" << std::endl;
    // TODO: Call describe() on the animal
    // TODO: Call makeSound() on the animal
    std::cout << "----------------------------\n" << std::endl;
}
```

### Task 2b: Test Polymorphism

In main.cpp, add a new demo section:

```cpp
// ==================== DEMO 8: Polymorphism Test ====================
std::cout << "DEMO 8: Polymorphism - treating Dog and Cat as Animals" << std::endl;
std::cout << std::string(60, '=') << std::endl;

Dog myDog("Rex", 5, "German Shepherd");
Cat myCat("Mittens", 3, "Orange");  // Use your property

std::cout << "\nPassing Dog to generic function:" << std::endl;
introduceAnimal(&myDog);

std::cout << "Passing Cat to generic function:" << std::endl;
introduceAnimal(&myCat);

std::cout << "Notice: Same function, different behavior! (Polymorphism)" << std::endl;
```

### Questions to Consider:
- Why does `introduceAnimal` accept `Animal*` instead of `Animal&`?
- What would happen if `makeSound()` wasn't virtual?
- Can you pass a raw Animal object to this function?

---

## Exercise 3: Collection of Animals 🏡

**Difficulty:** Intermediate
**Estimated Time:** 25-35 minutes

### Objective
Create a collection (vector) that can hold different types of animals and iterate through them.

### Task 3a: Create an Animal Shelter

Add this code to main.cpp:

```cpp
#include <vector>  // Add at top with other includes

// In main(), add a new demo:
// ==================== DEMO 9: Animal Shelter ====================
std::cout << "DEMO 9: Animal Shelter - Collection of Different Animals" << std::endl;
std::cout << std::string(60, '=') << std::endl;

// Create a vector of Animal pointers
std::vector<Animal*> shelter;

// TODO: Create several Dog and Cat objects
// TODO: Add their addresses to the shelter vector using push_back()

std::cout << "\n=== All animals in the shelter ===\n" << std::endl;

// TODO: Loop through the shelter vector
// TODO: Call describe() and makeSound() on each animal

std::cout << "\n=== Feeding time! ===" << std::endl;
// TODO: Loop through and call eat() on each animal

std::cout << "\n=== Bedtime! ===" << std::endl;
// TODO: Loop through and call sleep() on each animal
```

### Questions:
- Why do we use `Animal*` in the vector instead of `Animal`?
- What would happen if we used `Animal` instead? (Try it!)
- Do you need to delete the animals? Why or why not?

---

## Exercise 4: Abstract Animal (Advanced) 🎯

**Difficulty:** Advanced
**Estimated Time:** 45-60 minutes

### Objective
Make Animal an abstract class with pure virtual functions.

### What You'll Learn:
- Pure virtual functions
- Abstract classes
- Forcing derived classes to implement methods

### Task 4a: Make makeSound() Pure Virtual

In `Animal.h`, change:
```cpp
virtual void makeSound() const;
```

To:
```cpp
virtual void makeSound() const = 0;  // Pure virtual function
```

### Task 4b: Try to Create an Animal Object

In main.cpp, try:
```cpp
Animal genericAnimal("Test", 1);  // What happens?
```

### Questions:
- Can you still create Animal objects? Why not?
- Can you still create Dog and Cat objects? Why?
- What error message do you get if Dog doesn't override makeSound()?

### Task 4c: Add More Pure Virtual Functions

Make these methods pure virtual in Animal:
- `describe()`
- Add a new one: `getSpecies()` that returns a string

Now Dog and Cat must implement all three methods!

---

## Exercise 5: Multi-Level Inheritance 🏗️

**Difficulty:** Advanced
**Estimated Time:** 60+ minutes

### Objective
Create a three-level inheritance hierarchy: Animal → Pet → Dog/Cat

### Task 5a: Create a Pet Class

Pet is:
- A specific type of Animal
- The parent of Dog and Cat
- Adds pet-specific properties like `owner` and `isVaccinated`

```bash
python3 scripts/create_class.py inheritance Pet --base-class Animal
```

### Task 5b: Add Pet-Specific Members

In Pet.h, add:
- `std::string owner`
- `bool isVaccinated`
- Methods: `setOwner()`, `getOwner()`, `vaccinate()`

### Task 5c: Change Dog and Cat to Inherit from Pet

In Dog.h and Cat.h, change:
```cpp
class Dog : public Animal {  // Old
```

To:
```cpp
class Dog : public Pet {  // New
```

### Task 5d: Update Constructors

Dog and Cat constructors now need to call Pet's constructor, which calls Animal's constructor.

```cpp
Dog::Dog(const std::string& name, int age, const std::string& owner, const std::string& breed)
    : Pet(name, age, owner), breed(breed) {
    // ...
}
```

### Questions:
- What's the constructor call order now?
- What's the destructor call order?
- Can a Dog still be treated as an Animal?

---

## Exercise 6: Create a Bird Class 🦅

**Difficulty:** Intermediate
**Estimated Time:** 30-40 minutes

### Objective
Create a Bird class that demonstrates behaviors that don't apply to Dog/Cat.

### Unique Challenges:
- Birds can `fly()` (but Dogs and Cats can't)
- Birds might `layEggs()` (different from mammals)
- Different sound: `chirp()` or `sing()`

### Task:
1. Create Bird class inheriting from Animal
2. Add bird-specific properties: `species`, `canFly` (bool), `wingspan` (double)
3. Override `makeSound()` appropriately
4. Add unique methods: `fly()`, `buildNest()`, `migrate()`
5. Test in main.cpp

### Thought Exercise:
- Should Pet → Bird? Or Animal → Bird directly?
- Why might the inheritance hierarchy matter here?

---

## Exercise 7: Operator Overloading with Animals 🔧

**Difficulty:** Advanced
**Estimated Time:** 45-60 minutes

### Objective
Add operator overloading to compare animals by age.

### Task 7a: Add Comparison Operators to Animal

In Animal.h, add:
```cpp
bool operator<(const Animal& other) const;
bool operator>(const Animal& other) const;
bool operator==(const Animal& other) const;
```

### Task 7b: Implement in Animal.cpp

```cpp
bool Animal::operator<(const Animal& other) const {
    return this->age < other.age;
}
```

### Task 7c: Test the Operators

```cpp
Dog dog1("Buddy", 5, "Retriever");
Cat cat1("Whiskers", 3, "Tabby");

if (dog1 > cat1) {
    std::cout << dog1.getName() << " is older than " << cat1.getName() << std::endl;
}
```

### Task 7d: Sort Animals by Age

```cpp
std::vector<Animal*> animals = { /* add dogs and cats */ };
std::sort(animals.begin(), animals.end(), [](Animal* a, Animal* b) {
    return *a < *b;
});
```

---

## Debugging Challenges 🐛

Try to fix these intentional errors:

### Challenge 1: Missing Virtual Destructor
```cpp
// In Animal.h, change:
virtual ~Animal();
// To:
~Animal();

// What happens when you run the program?
// Why is this a problem?
```

### Challenge 2: Slicing
```cpp
void printAnimal(Animal animal) {  // Pass by value!
    animal.describe();
    animal.makeSound();
}

Dog myDog("Rex", 3, "Husky");
printAnimal(myDog);  // What's wrong with this?
```

### Challenge 3: Forgetting Override
```cpp
// In Dog.h, remove 'override':
virtual void makeSound() const;  // No override keyword

// Does it still work? What's the risk?
```

---

## Additional Practice Ideas 💡

### Easy:
1. Add more properties to Dog/Cat (gender, weight, etc.)
2. Add validation in setters (age must be positive)
3. Add a `toString()` method to each class
4. Create multiple cats with different characteristics

### Medium:
1. Implement copy constructors for Dog and Cat
2. Add a `speak(int times)` method that calls makeSound() multiple times
3. Create a Zoo class that manages a collection of animals
4. Implement the Rule of Three for all classes

### Hard:
1. Add exception handling for invalid ages/properties
2. Implement smart pointers instead of raw pointers
3. Create a serialization method to save/load animals from a file
4. Implement multiple inheritance (e.g., WorkingDog inherits from Dog and Worker)

---

## Learning Checklist ✅

Mark off each concept as you master it:

- [ ] Create a derived class from a base class
- [ ] Use the `class Derived : public Base` syntax
- [ ] Call base class constructor in initializer list
- [ ] Access protected members from derived class
- [ ] Override virtual functions with `override` keyword
- [ ] Understand constructor call order (Base → Derived)
- [ ] Understand destructor call order (Derived → Base)
- [ ] Use base class pointers for polymorphism
- [ ] Create collections of polymorphic objects
- [ ] Understand when virtual destructors are needed
- [ ] Implement pure virtual functions
- [ ] Create abstract classes
- [ ] Build multi-level inheritance hierarchies
- [ ] Understand object slicing and how to avoid it

---

## Tips for Success 🎯

1. **Compile often** - Don't write too much code before testing
2. **Read error messages carefully** - They usually tell you exactly what's wrong
3. **Use the Dog class as reference** - It's a working example
4. **Draw diagrams** - Visualize the inheritance hierarchy
5. **Experiment** - Try breaking things to understand them better
6. **Ask "why?"** - Understand the reason behind each decision

---

## Getting Help 🆘

If you're stuck:

1. **Check the Dog class** - It's your working reference
2. **Review the README.md** - Key concepts are explained there
3. **Read compiler errors** - They're more helpful than you think
4. **Check the main demo** - See how Dog is being used
5. **Test incrementally** - Add one method at a time and test

---

## Next Steps 🚀

After completing these exercises:

1. Move on to the **Polymorphism** concept
2. Study **Abstract Classes** in depth
3. Learn about **Composition vs Inheritance**
4. Explore **Design Patterns** that use inheritance
5. Study **Virtual Function Tables** (vtables) to understand how it works under the hood

---

**Remember:** The best way to learn is by doing! Don't just read - implement, test, break, fix, and experiment!

Happy coding! 🎉
