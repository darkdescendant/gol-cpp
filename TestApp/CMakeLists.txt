include(ExternalProject)

set(IGLOO_ROOT ${CMAKE_CURRENT_BINARY_DIR}/../external/igloo)
set(IGLOO_INCLUDE_DIRS ${IGLOO_ROOT}/include/igloo)
set(IGLOO_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/../external/igloo")
set(IGLOO_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${IGLOO_INSTALL_DIR})

ExternalProject_Add(igloo
        PREFIX ${IGLOO_ROOT}
        GIT_REPOSITORY https://github.com/joakimkarlsson/igloo.git
        BINARY_DIR ${IGLOO_ROOT}
        INSTALL_DIR ${IGLOO_ROOT}
        CMAKE_ARGS ${IGLOO_CMAKE_ARGS}
        )

include_directories("${IGLOO_ROOT}/include")


file(GLOB SRCS *.cpp)
add_executable(TestApp ${SRCS})
target_link_libraries(TestApp LINK_PUBLIC GameOfLife)

