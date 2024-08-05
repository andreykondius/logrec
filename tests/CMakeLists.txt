# Author: Kondius A.V.
# kondius@mail.ru, andreykondius@gmail.com
# 2024

file(GLOB_RECURSE TestSources *.h *.cpp)
find_package(GTest)
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(UnitTestsLogrec ${TestSources})

target_include_directories(UnitTestsLogrec
    PRIVATE
    ../sources
)

target_link_libraries(UnitTestsLogrec
    GTest::gtest_main
    ${LOGREC_LIB}
)

set(bin_folder ${CMAKE_CURRENT_SOURCE_DIR}/../bin/${CMAKE_BUILD_TYPE})
file(MAKE_DIRECTORY ${bin_folder}/logs)

set(EXECUTABLE_OUTPUT_PATH ${bin_folder})

