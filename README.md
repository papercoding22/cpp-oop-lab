# C++ OOP Learning Lab

A personal repository for learning C++ and Object-Oriented Programming, covering core concepts, examples, and hands-on practice.

## Overview

This repository provides a structured approach to learning OOP concepts in C++. Each concept is organized in its own directory with examples, demonstrations, and exercises. The project includes automation scripts to quickly generate templates for new concepts and classes.

## Prerequisites

- **CMake** 3.15 or higher
- **C++17** compatible compiler (GCC 7+, Clang 5+, MSVC 2017+, or Apple Clang)
- **Python** 3.6 or higher

## Project Structure

```
cpp-oop-lab/
├── CMakeLists.txt           # Root build configuration
├── README.md                # This file
├── .gitignore              # Git ignore rules
├── scripts/                 # Automation scripts
│   ├── create_concept.py   # Generate new concept template
│   └── create_class.py     # Generate class/header pairs
└── concepts/                # All OOP concepts
    ├── basic_class/
    │   ├── CMakeLists.txt
    │   ├── main.cpp
    │   ├── README.md
    │   └── *.h, *.cpp
    ├── inheritance/
    ├── polymorphism/
    └── ...
```

## Quick Start

### 1. Create a New Concept

Generate a new concept directory with all necessary files:

```bash
python3 scripts/create_concept.py <concept_name> --description "Brief description"
```

**Example:**
```bash
python3 scripts/create_concept.py inheritance --description "Demonstrating IS-A relationships"
```

This creates:
- `concepts/inheritance/` directory
- `main.cpp` with demo template
- `CMakeLists.txt` configured for the concept
- `README.md` with concept details

### 2. Add Classes to a Concept

Generate class and header files within a concept:

```bash
python3 scripts/create_class.py <concept_name> <ClassName>
```

**Example:**
```bash
# Create base class
python3 scripts/create_class.py inheritance Animal

# Create derived class
python3 scripts/create_class.py inheritance Dog --base-class Animal
```

This creates:
- `<ClassName>.h` with header guards and class declaration
- `<ClassName>.cpp` with constructor/destructor stubs
- Automatic inheritance setup if `--base-class` is specified

### 3. Build and Run

Build your concept:

```bash
# Initial setup (first time only)
mkdir -p build
cd build
cmake ..

# Build specific concept
make <concept_name>_demo

# Run it
./concepts/<concept_name>/<concept_name>_demo
```

**Example:**
```bash
cd build
make inheritance_demo
./concepts/inheritance/inheritance_demo
```

### 4. Build All Concepts

```bash
cd build
make
```

## Detailed Usage

### Creating a Complete Concept Example

Here's a complete workflow for creating an inheritance example:

```bash
# 1. Create the concept
python3 scripts/create_concept.py inheritance --description "Demonstrating class inheritance"

# 2. Create base class
python3 scripts/create_class.py inheritance Animal

# 3. Create derived class
python3 scripts/create_class.py inheritance Dog --base-class Animal

# 4. Edit the generated files
# - Open concepts/inheritance/Animal.h and Animal.cpp
# - Open concepts/inheritance/Dog.h and Dog.cpp
# - Open concepts/inheritance/main.cpp
# - Implement your classes and demo code

# 5. Build
mkdir -p build && cd build
cmake ..
make inheritance_demo

# 6. Run
./concepts/inheritance/inheritance_demo
```

### Script Options

#### create_concept.py

```bash
python3 scripts/create_concept.py <concept_name> [options]

Arguments:
  concept_name              Name of the concept (e.g., polymorphism)

Options:
  --description DESCRIPTION  Brief description of the concept
```

#### create_class.py

```bash
python3 scripts/create_class.py <concept_name> <class_name> [options]

Arguments:
  concept_name              Name of the concept directory
  class_name               Name of the class (e.g., Animal)

Options:
  --base-class BASE_CLASS   Base class for inheritance
```

## Key Features

### Automatic Build Configuration
- **No manual CMake editing required**
- New concepts are auto-discovered when they contain `CMakeLists.txt`
- New classes are auto-included via glob patterns
- Just create files and rebuild

### Modular Organization
- Each concept is self-contained
- Separate executable per concept
- Easy to focus on one concept at a time

### Professional Structure
- Out-of-source builds (build/ directory)
- Proper header guards
- C++17 standards compliance
- Compiler warnings enabled

## Learning Path

Suggested order for studying concepts:

1. **basic_class** - Classes, objects, constructors, destructors
2. **encapsulation** - Access specifiers, getters/setters
3. **inheritance** - Base and derived classes, IS-A relationship
4. **polymorphism** - Virtual functions, runtime polymorphism
5. **abstraction** - Abstract classes, pure virtual functions
6. **composition** - HAS-A relationship
7. **operator_overloading** - Custom operators
8. **templates** - Generic programming
9. **exception_handling** - Try-catch blocks

## Tips

- Each concept folder contains a `README.md` with specific details
- Start simple and gradually add complexity
- Run your demos frequently to verify behavior
- Use the compiler warnings to learn best practices
- Experiment and modify the examples

## Build System Details

### CMake Auto-Discovery
The root `CMakeLists.txt` automatically finds all concept directories:
- Scans `concepts/` for subdirectories
- Includes any directory with a `CMakeLists.txt`
- After creating a new concept, run `cmake ..` to refresh

### Output Structure
Executables are organized by concept:
```
build/
└── concepts/
    ├── basic_class/
    │   └── basic_class_demo
    ├── inheritance/
    │   └── inheritance_demo
    └── ...
```

### Clean Build
To start fresh:
```bash
rm -rf build
mkdir build
cd build
cmake ..
make
```

## Troubleshooting

### CMake doesn't find new concept
After creating a new concept, re-run CMake:
```bash
cd build
cmake ..
```

### Compiler errors
Make sure you're using C++17 compatible compiler:
```bash
g++ --version    # GCC 7+
clang++ --version  # Clang 5+
```

### Python script errors
Ensure Python 3.6+:
```bash
python3 --version
```

## Contributing

This is a personal learning repository, but feel free to fork and adapt for your own learning journey.

## License

This project is for educational purposes. Feel free to use and modify as needed for learning.
