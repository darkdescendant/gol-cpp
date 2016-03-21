file(GLOB SRCS *.cpp)
add_executable(GOLApp ${SRCS})
target_link_libraries(GOLApp LINK_PUBLIC GameOfLife ncurses)
