# CMakeLists.txt for basic_class concept

# Get the concept name from the directory
get_filename_component(CONCEPT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Collect all .cpp files in this directory
file(GLOB CONCEPT_SOURCES "*.cpp")

# Create executable
add_executable(${CONCEPT_NAME}_demo ${CONCEPT_SOURCES})

# Set output directory to concepts/<concept_name>/
set_target_properties(${CONCEPT_NAME}_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/concepts/${CONCEPT_NAME}
)
