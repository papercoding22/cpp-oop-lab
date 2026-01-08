#!/usr/bin/env python3
"""
Script to create a class/header pair within a concept directory.

Usage:
    python3 create_class.py <concept_name> <class_name> [--base-class BaseClass]

Example:
    python3 create_class.py inheritance Animal
    python3 create_class.py inheritance Dog --base-class Animal
"""

import argparse
import os
import re
import sys
from pathlib import Path


def validate_class_name(name):
    """Validate that the class name is a valid C++ identifier."""
    if not re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', name):
        return False, "Class name must start with a letter or underscore and contain only letters, numbers, and underscores"
    return True, ""


def resolve_concept_path(project_root, concept):
    """Resolve the concept path."""
    # Handle '.' for current directory
    if concept == '.':
        current_dir = Path.cwd()
        # Check if we're in a concept directory
        if (current_dir / "CMakeLists.txt").exists() and current_dir.parent.name == "concepts":
            return current_dir
        else:
            return None, "Current directory doesn't appear to be a concept directory"

    # Otherwise, use concepts/<concept_name>
    concepts_dir = project_root / "concepts"
    concept_path = concepts_dir / concept

    if not concept_path.exists():
        return None, f"Concept '{concept}' doesn't exist at {concept_path}"

    return concept_path, ""


def class_already_exists(concept_path, class_name):
    """Check if class files already exist."""
    header_path = concept_path / f"{class_name}.h"
    impl_path = concept_path / f"{class_name}.cpp"

    if header_path.exists() or impl_path.exists():
        return True
    return False


def get_header_guard(class_name):
    """Generate header guard macro name."""
    return f"{class_name.upper()}_H"


def get_header_template(class_name, base_class=None):
    """Generate header file template content."""
    header_guard = get_header_guard(class_name)

    # Base class include and inheritance
    base_include = ""
    inheritance = ""
    virtual_keyword = ""

    if base_class:
        base_include = f'#include "{base_class}.h"\n'
        inheritance = f" : public {base_class}"
        virtual_keyword = "virtual "

    template = f'''/**
 * @file {class_name}.h
 * @brief Declaration of {class_name} class
 */

#ifndef {header_guard}
#define {header_guard}

{base_include}
/**
 * @class {class_name}
 * @brief TODO: Add class description
 */
class {class_name}{inheritance} {{
public:
    /**
     * @brief Constructor
     */
    {class_name}();

    /**
     * @brief Destructor
     */
    {virtual_keyword}~{class_name}();

    // TODO: Add your public methods here

protected:
    // TODO: Add your protected members here

private:
    // TODO: Add your private members here
}};

#endif // {header_guard}
'''
    return template


def get_implementation_template(class_name, base_class=None):
    """Generate implementation file template content."""
    base_init = ""
    if base_class:
        base_init = f"\n    : {base_class}()"

    template = f'''/**
 * @file {class_name}.cpp
 * @brief Implementation of {class_name} class
 */

#include "{class_name}.h"
#include <iostream>

/**
 * @brief Constructor
 */
{class_name}::{class_name}(){base_init} {{
    std::cout << "{class_name} constructor called" << std::endl;
}}

/**
 * @brief Destructor
 */
{class_name}::~{class_name}() {{
    std::cout << "{class_name} destructor called" << std::endl;
}}

// TODO: Implement your methods here
'''
    return template


def create_class(project_root, concept_name, class_name, base_class):
    """Create the class header and implementation files."""
    # Resolve concept path
    result = resolve_concept_path(project_root, concept_name)
    if isinstance(result, tuple):
        concept_path, error_msg = result
        if concept_path is None:
            print(f"✗ {error_msg}")
            return False
    else:
        concept_path = result

    # Validate class name
    is_valid, error_msg = validate_class_name(class_name)
    if not is_valid:
        print(f"✗ Invalid class name: {error_msg}")
        return False

    # Check if base class specified
    if base_class:
        # Validate base class name
        is_valid, error_msg = validate_class_name(base_class)
        if not is_valid:
            print(f"✗ Invalid base class name: {error_msg}")
            return False

        # Check if base class header exists
        base_class_header = concept_path / f"{base_class}.h"
        if not base_class_header.exists():
            print(f"✗ Base class header '{base_class}.h' not found in concept directory")
            print(f"  Create the base class first: python3 {Path(__file__).name} {concept_name} {base_class}")
            return False

    # Check if class already exists
    if class_already_exists(concept_path, class_name):
        print(f"✗ Class '{class_name}' already exists in concept '{concept_name}'")
        return False

    try:
        # Generate and write header file
        header_content = get_header_template(class_name, base_class)
        header_path = concept_path / f"{class_name}.h"
        header_path.write_text(header_content)
        if base_class:
            print(f"✓ Created {header_path.name} (inherits from {base_class})")
        else:
            print(f"✓ Created {header_path.name}")

        # Generate and write implementation file
        impl_content = get_implementation_template(class_name, base_class)
        impl_path = concept_path / f"{class_name}.cpp"
        impl_path.write_text(impl_content)
        print(f"✓ Created {impl_path.name}")

        print()
        print("✅ Class files created successfully!")
        print()
        print("The files are automatically included in the build (no CMake changes needed).")
        print()
        print("Next steps:")
        print(f"  1. Edit {class_name}.h to add your class interface")
        print(f"  2. Edit {class_name}.cpp to implement your methods")
        print(f"  3. Include in main.cpp: #include \"{class_name}.h\"")
        print(f"  4. Rebuild: cd build && cmake .. && make")
        print()

        return True

    except Exception as e:
        print(f"✗ Error creating class files: {e}")
        return False


def main():
    """Main entry point."""
    parser = argparse.ArgumentParser(
        description='Create a class/header pair within a concept directory',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog='''
Examples:
  # Create a base class
  python3 create_class.py inheritance Animal

  # Create a derived class
  python3 create_class.py inheritance Dog --base-class Animal

  # Create from within a concept directory
  cd concepts/inheritance
  python3 ../../scripts/create_class.py . Cat --base-class Animal
        '''
    )

    parser.add_argument('concept_name',
                       help='Name of the concept (or "." if in concept directory)')
    parser.add_argument('class_name',
                       help='Name of the class to create (e.g., Animal, Dog)')
    parser.add_argument('--base-class',
                       default=None,
                       help='Name of the base class for inheritance')

    args = parser.parse_args()

    # Get project root (parent of scripts directory)
    script_dir = Path(__file__).parent
    project_root = script_dir.parent

    # Create the class
    success = create_class(project_root, args.concept_name, args.class_name, args.base_class)

    sys.exit(0 if success else 1)


if __name__ == '__main__':
    main()
