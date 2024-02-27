cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)

project(TobiasAI)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

#add_subdirectory(vendor/pocketsphinx)


#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
#  COMMAND "${CMAKE_COMMAND}" -E copy_directory 
#  "${CMAKE_CURRENT_SOURCE_DIR}/Shaders"
#  "${CMAKE_CURRENT_SOURCE_DIR}/build/Shaders" 
#    COMMENT "Copying to output directory")

target_include_directories(${PROJECT_NAME}
  PUBLIC include
  PUBLIC vendor/espeak-ng/src/include
  PUBLIC vendor/pocketsphinx/include
  #PUBLIC vendor/TensorFlow/include
  )

find_library(TensorFlow /vendor/TensorFlow/lib) 

target_link_libraries(${PROJECT_NAME}
  espeak-ng
  pocketsphinx
  #${CMAKE_CURRENT_SOURCE_DIR}/vendor/TensorFlow/lib/libtensorflow.so.2.6.0
  #TensorFlow
  )
