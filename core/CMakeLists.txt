cmake_minimum_required(VERSION 3.6)
project(fir)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()
conan_basic_setup()

set(CMAKE_CXX_STANDARD 11)

set(BUILD_TEST ON)

set(LLVM_TARGETS_TO_BUILD X86)
set(LLVM_BUILD_RUNTIME OFF)
set(LLVM_BUILD_TOOLS OFF)

find_package(BISON)
find_package(FLEX)

FLEX_TARGET(MyScanner ${CMAKE_CURRENT_SOURCE_DIR}/src/redapple_lex.l
        ${CMAKE_CURRENT_BINARY_DIR}/redapple_lex.cpp COMPILE_FLAGS -w)
BISON_TARGET(MyParser ${CMAKE_CURRENT_SOURCE_DIR}/src/redapple_parser.y
        ${CMAKE_CURRENT_BINARY_DIR}/redapple_parser.cpp)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)


# 核心路径配置
include_directories(include src src/Utils src/MetaModel
        src/LLCG/ src/LLCG/LLVMLIB headerlibs ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE source_files
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp)
list(REMOVE_ITEM  source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_library(${PROJECT_NAME}core ${source_files} ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)


# Link against LLVM libraries

include("${CONAN_LIB_DIRS_LLVM}/cmake/llvm/LLVMConfig.cmake")

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs
        support core irreader executionengine interpreter
        mc mcjit bitwriter x86codegen target)



# 指定动态库版本
# VERSION 动态库版本
# SOVERSION API版本
if (BUILD_SHARED_LIBS)
set_target_properties(${PROJECT_NAME}core PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} SOVERSION ${VERSION_MAJOR})
target_link_libraries(${PROJECT_NAME}core ${llvm_libs})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}core.${VERSION_MAJOR})
else()
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}core ${llvm_libs})
endif()

add_subdirectory(runtimeproj)

if(BUILD_TEST)
    add_subdirectory(test)
endif()
