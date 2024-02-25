cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)

project(TobiasAI)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

#add_subdirectory(vendor/festival)


#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
#  COMMAND "${CMAKE_COMMAND}" -E copy_directory 
#  "${CMAKE_CURRENT_SOURCE_DIR}/Shaders"
#  "${CMAKE_CURRENT_SOURCE_DIR}/build/Shaders" 
#    COMMENT "Copying to output directory")

target_include_directories(${PROJECT_NAME}
  PUBLIC include
  PUBLIC vendor/espeak-ng/src/include
  )

target_link_libraries(${PROJECT_NAME}
  espeak-ng
  )
