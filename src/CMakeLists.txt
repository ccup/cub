file(GLOB_RECURSE SOURCES
    "*.c" "*.C" "*.cc" "*.CC" "*.cpp" "*.CPP" "*.c++"
)

if (SHARED)
    set(LIB_TYPE SHARED)
else()
    set(LIB_TYPE STATIC)
endif()

add_library(${TARGET_LIB} ${LIB_TYPE} ${SOURCES})

target_include_directories(${TARGET_LIB}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(${TARGET_LIB} PUBLIC cxx_std_17)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/cub DESTINATION include)
install(TARGETS cub ARCHIVE DESTINATION lib)

