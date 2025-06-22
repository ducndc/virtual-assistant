# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
# set(HEADER_LIST "../include/*.hpp")

file(GLOB HEADER_FILES "../include/*.hpp")
# Make an automatic library - will be static or dynamic based on user setting
file(GLOB SOURCE_FILES "../src/*.cpp")

add_library(assistant_object assistant_object.cpp ${HEADER_FILES})
add_library(eye_object eye_object.cpp ${HEADER_FILES})

# We need this directory, and users of our library will need it too
target_include_directories(assistant_object PUBLIC ../include)
target_include_directories(eye_object PUBLIC ../include)

# This depends on (header only) boost
#target_link_libraries(modern_library PRIVATE Boost::boost)

# All users of this library will need at least C++11
target_compile_features(assistant_object PUBLIC cxx_std_11)
target_compile_features(eye_object PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_FILES})