cmake_minimum_required(VERSION 3.16)
project(ASD_ShoeLaundryQueue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(ASD_ShoeLaundryQueue
    src/main.cpp
    src/data_structures/Queue.cpp
    src/data_structures/Stack.cpp
    src/ui/ui.cpp
)

target_include_directories(ASD_ShoeLaundryQueue PRIVATE src)
