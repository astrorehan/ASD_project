cmake_minimum_required(VERSION 3.15)
project(ASD_ShoeLaundryBackend CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_definitions(-D_WIN32_WINNT=0x0A00)

add_executable(backend
    main.cpp
    models/Pesanan.cpp
    data_structures/Queue.cpp
    data_structures/Stack.cpp
    data_structures/Node.cpp
)

if(WIN32)
    target_link_libraries(backend ws2_32)
endif()
