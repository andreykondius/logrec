# Author: Kondius A.V.
# kondius@mail.ru, andreykondius@gmail.com
# 2024

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(logrec VERSION 1.0 LANGUAGES CXX)
set(LOGREC_LIB logrec_lib)
set(Test_Sources test_sources)

add_subdirectory(sources)
add_subdirectory(tests)
