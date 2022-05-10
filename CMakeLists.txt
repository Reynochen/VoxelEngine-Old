cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(VoxEngine)

file(
    GLOB
        cppSRC =    "${PROJECT_SOURCE_DIR}/src/*.cpp"
                    "${PROJECT_SOURCE_DIR}/src/*/*.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/lib")

add_executable(${PROJECT_NAME} ${cppSRC})

#Static mingw
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_subdirectory(lib/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(lib/glad)
target_link_libraries(${PROJECT_NAME} glad)