
cmake_minimum_required(VERSION 3.15)

project(table
  VERSION 0.1.0
  DESCRIPTION "A simple open addressing hash table"
  LANGUAGES C)

set(CMAKE_C_STANDARD 11)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_executable("${PROJECT_NAME}"
  "src/main.c"
  "src/table.c"
)
