enable_testing()
find_package(GTest REQUIRED)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories (${GTEST_INCLUDE_DIRS})
file(GLOB_RECURSE test_source_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable (run_test ${test_source_files})

if(BUILD_SHARED_LIBS)
    target_link_libraries(run_test
                    ${PROJECT_NAME}
                    ${GTEST_BOTH_LIBRARIES}
                    pthread)
else()
    target_link_libraries(run_test
                    ${PROJECT_NAME} ${llvm_libs}
                    ${GTEST_BOTH_LIBRARIES}
                    pthread)
endif()


add_test(FirTest run_test)

add_custom_target( runtest ALL
                   DEPENDS run_test)

add_custom_command(TARGET runtest
                   POST_BUILD
                   COMMAND run_test)
