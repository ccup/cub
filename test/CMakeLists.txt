set(TEST_TARGET ${TARGET_LIB}_test)

CPMAddPackage(
    NAME cctest
    GITHUB_REPOSITORY ccup/cctest
    GIT_TAG v1.0
)

file(GLOB_RECURSE SOURCES 
    "*.c" "*.C" "*.cc" "*.CC" "*.cpp" "*.CPP" "*.c++")

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

add_executable(${TEST_TARGET} ${SOURCES})

target_include_directories(${TEST_TARGET}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TEST_TARGET} PRIVATE ${TARGET_LIB} cctest_main)

include(CTest)
enable_testing()
add_test(NAME test COMMAND ${TEST_TARGET})