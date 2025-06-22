set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(virtual_assistant main.cpp)

target_compile_features(virtual_assistant PRIVATE cxx_std_17)

target_link_libraries(virtual_assistant PRIVATE assistant_object eye_object Threads::Threads )
