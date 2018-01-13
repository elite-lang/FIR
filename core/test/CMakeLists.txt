enable_testing()

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE test_source_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable (run_test ${test_source_files})


target_link_libraries(run_test
        ${PROJECT_NAME}core ${llvm_libs}
        ${CONAN_LIBS_GTEST}


add_test(FirTest run_test)

add_custom_target( runtest ALL
                   DEPENDS run_test)

add_custom_command(TARGET runtest
                   POST_BUILD
                   COMMAND run_test)
