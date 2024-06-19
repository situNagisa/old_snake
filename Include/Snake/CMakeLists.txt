file(GLOB_RECURSE snake_src "./*.c" "./*.cpp","./include/NGS/*.cpp")
set(snake_include "./include/")

idf_component_register(
    SRCS            ${snake_src}
    INCLUDE_DIRS    ${snake_include}
)