#!/usr/bin/env python3
"""
Script to create a new OOP concept directory with template files.

Usage:
    python3 create_concept.py <concept_name> [--description "Description"]

Example:
    python3 create_concept.py inheritance --description "Demonstrating IS-A relationships"
"""

import argparse
import os
import re
import sys
from pathlib import Path


def validate_concept_name(name):
    """Validate that the concept name is a valid identifier."""
    if not re.match(r'^[a-zA-Z][a-zA-Z0-9_]*$', name):
        return False, "Concept name must start with a letter and contain only letters, numbers, and underscores"
    return True, ""


def concept_exists(concepts_dir, name):
    """Check if concept directory already exists."""
    concept_path = concepts_dir / name
    return concept_path.exists()


def get_main_cpp_template(concept_name, description):
    """Generate main.cpp template content."""
    concept_upper = concept_name.upper().replace('_', ' ')

    template = f'''/**
 * @file main.cpp
 * @brief Demonstrates {concept_name}
 *
 * {description}
 */

#include <iostream>

int main() {{
    std::cout << "=== {concept_upper} Demo ===" << std::endl;
    std::cout << std::endl;

    // TODO: Add your demonstration code here

    std::cout << std::endl;
    std::cout << "Demo completed successfully!" << std::endl;
    return 0;
}}
'''
    return template


def get_cmake_template(concept_name):
    """Generate CMakeLists.txt template content."""
    template = f'''# CMakeLists.txt for {concept_name} concept

# Get the concept name from the directory
get_filename_component(CONCEPT_NAME ${{CMAKE_CURRENT_SOURCE_DIR}} NAME)

# Collect all .cpp files in this directory
file(GLOB CONCEPT_SOURCES "*.cpp")

# Create executable
add_executable(${{CONCEPT_NAME}}_demo ${{CONCEPT_SOURCES}})

# Set output directory to concepts/<concept_name>/
set_target_properties(${{CONCEPT_NAME}}_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${{CMAKE_BINARY_DIR}}/concepts/${{CONCEPT_NAME}}
)
'''
    return template


def get_readme_template(concept_name, description):
    """Generate README.md template content."""
    concept_title = concept_name.replace('_', ' ').title()

    template = f'''# {concept_title}

## Overview
{description if description else "TODO: Add concept description"}

## Learning Objectives
- TODO: Add learning objectives
- TODO: What should you understand after studying this?

## Key Concepts
- TODO: List key concepts covered
- TODO: Important terminology

## Code Structure
- `main.cpp` - Demonstration entry point
- TODO: List classes and their purposes

## Building

From project root:
```bash
mkdir -p build && cd build
cmake ..
make {concept_name}_demo
```

## Running

From build directory:
```bash
./concepts/{concept_name}/{concept_name}_demo
```

## Exercises

1. TODO: Add suggested exercises
2. TODO: Modifications to try
3. TODO: Extensions to implement

## Key Takeaways

- TODO: What are the main lessons?
- TODO: When to use this concept?
- TODO: Common pitfalls to avoid?

## References

- TODO: Add helpful links
- TODO: Recommended reading
- TODO: Related concepts
'''
    return template


def create_concept(project_root, concept_name, description):
    """Create the concept directory with all template files."""
    concepts_dir = project_root / "concepts"
    concept_path = concepts_dir / concept_name

    # Validate concept name
    is_valid, error_msg = validate_concept_name(concept_name)
    if not is_valid:
        print(f"✗ Invalid concept name: {error_msg}")
        return False

    # Check if concept already exists
    if concept_exists(concepts_dir, concept_name):
        print(f"✗ Concept '{concept_name}' already exists at {concept_path}")
        return False

    try:
        # Create concepts directory if it doesn't exist
        concepts_dir.mkdir(parents=True, exist_ok=True)

        # Create concept directory
        concept_path.mkdir(parents=False, exist_ok=False)
        print(f"✓ Created {concept_path.relative_to(project_root)}/")

        # Generate and write main.cpp
        main_cpp_content = get_main_cpp_template(concept_name, description)
        main_cpp_path = concept_path / "main.cpp"
        main_cpp_path.write_text(main_cpp_content)
        print(f"✓ Generated {main_cpp_path.relative_to(project_root)}")

        # Generate and write CMakeLists.txt
        cmake_content = get_cmake_template(concept_name)
        cmake_path = concept_path / "CMakeLists.txt"
        cmake_path.write_text(cmake_content)
        print(f"✓ Generated {cmake_path.relative_to(project_root)}")

        # Generate and write README.md
        readme_content = get_readme_template(concept_name, description)
        readme_path = concept_path / "README.md"
        readme_path.write_text(readme_content)
        print(f"✓ Generated {readme_path.relative_to(project_root)}")

        print()
        print("✅ Concept created successfully!")
        print()
        print("Next steps:")
        print(f"  1. cd concepts/{concept_name}")
        print(f"  2. Edit main.cpp and add your demonstration code")
        print(f"  3. Create classes: python3 ../../scripts/create_class.py {concept_name} <ClassName>")
        print(f"  4. Build: cd ../../build && cmake .. && make {concept_name}_demo")
        print(f"  5. Run: ./concepts/{concept_name}/{concept_name}_demo")
        print()

        return True

    except Exception as e:
        print(f"✗ Error creating concept: {e}")
        return False


def main():
    """Main entry point."""
    parser = argparse.ArgumentParser(
        description='Create a new OOP concept directory with template files',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog='''
Examples:
  python3 create_concept.py inheritance
  python3 create_concept.py polymorphism --description "Runtime polymorphism with virtual functions"
  python3 create_concept.py operator_overloading --description "Custom operator implementations"
        '''
    )

    parser.add_argument('concept_name',
                       help='Name of the concept (e.g., inheritance, polymorphism)')
    parser.add_argument('--description',
                       default='',
                       help='Brief description of the concept')

    args = parser.parse_args()

    # Get project root (parent of scripts directory)
    script_dir = Path(__file__).parent
    project_root = script_dir.parent

    # Create the concept
    success = create_concept(project_root, args.concept_name, args.description)

    sys.exit(0 if success else 1)


if __name__ == '__main__':
    main()
