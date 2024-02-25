
set(Festival_DIR "${CMAKE_CURRENT_LIST_DIR}/")
find_package(Festival REQUIRED)
set(EST_DIR "${CMAKE_CURRENT_LIST_DIR}"/)
find_package(EST REQUIRED)

INCLUDE_DIRECTORIES(include ${CMAKE_SOURCE_DIR}
                            ${EST_INCLUDE_DIR}
                            ${Festival_INCLUDE_DIR})

file(GLOB_RECURSE headers "include/*.h*")
file(GLOB_RECURSE sources "src/*.c*")

add_executable(festivalProject ${sources} ${headers} )
target_link_libraries(Project ${EST_LIBRARIES} ${Festival_LIBRARIES})
