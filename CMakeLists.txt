cmake_minimum_required(VERSION 3.20)

project(
  loptw-bnc
  VERSION 1.0.1
  DESCRIPTION "Parallel branch and cut for loptw"
  HOMEPAGE_URL "https://lewis-xuwei.github.io/")

option(CXX "enable C++ compilation" ON)
option(BUILD_TESTING "To build unit test" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
add_definitions(-DLOPTW_DATA_DIR="${PROJECT_SOURCE_DIR}/data")

if(CXX)
  enable_language(CXX)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_BUILD_TYPE "Debug")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_definitions(-DDEBUG)
else()
  add_definitions(-UDEBUG)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
if(MSVC_VERSION GREATER_EQUAL "1900")
  # windows settings
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag("/std:c++17" _cpp_latest_flag_supported)
  if(_cpp_latest_flag_supported)
    add_compile_options("/std:c++17")
    set(CMAKE_CXX_STANDARD_NAME "msvc/std:c++latest")
  endif()
  add_compile_options($<$<CONFIG:Debug>:/bigobj>)
else()
  # non-windows settings
  set(CMAKE_CXX_STANDARD_NAME "- c++${CMAKE_CXX_STANDARD}")
endif()

# Visual Studio compiler with static runtime libraries
if(MSVC AND MT)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
endif()

find_package(soplex REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(fmt)
find_package(Threads)
find_package(GUROBI REQUIRED)

add_subdirectory("cmake.utils")
set(GIT_HASH "")
get_git_hash(GIT_HASH)
message(STATUS "Git hash is ${GIT_HASH}")

set(VERSIONINFO_RC "")
if(MSVC)
  set(VERSIONINFO_RC "${CMAKE_BINARY_DIR}/versioninfo.rc")
  configure_file("${CMAKE_SOURCE_DIR}/versioninfo.rc.in" "${VERSIONINFO_RC}")
endif()

file(GLOB_RECURSE HEADERS "./include/*.h*")
file(GLOB_RECURSE SOURCES "./src/loptw/*.cpp" "./src/loptw/*.hpp"
     "${VERSIONINFO_RC}")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
if(MSVC)
  target_compile_definitions(
    loptw-bnc PRIVATE _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC "./include/")
target_link_libraries(${PROJECT_NAME} PRIVATE soplex)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_include_directories(${PROJECT_NAME} PRIVATE ${GUROBI_INCLUDE_DIRS})
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  target_link_libraries(${PROJECT_NAME} PRIVATE ${GUROBI_CXX_DEBUG_LIBRARY})
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE ${GUROBI_CXX_LIBRARY})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${GUROBI_LIBRARY})

add_executable(${PROJECT_NAME}-main "./src/main.cpp" "${VERSIONINFO_RC}")
target_link_libraries(${PROJECT_NAME}-main PRIVATE ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}-main PRIVATE soplex)
target_link_libraries(${PROJECT_NAME}-main PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME}-main PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME}-main PRIVATE fmt::fmt)
target_include_directories(${PROJECT_NAME}-main PRIVATE ${GUROBI_INCLUDE_DIRS})
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  target_link_libraries(${PROJECT_NAME}-main
                        PRIVATE ${GUROBI_CXX_DEBUG_LIBRARY})
else()
  target_link_libraries(${PROJECT_NAME}-main PRIVATE ${GUROBI_CXX_LIBRARY})
endif()

target_link_libraries(${PROJECT_NAME}-main PRIVATE ${GUROBI_LIBRARY})

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  include(FeatureSummary)
  feature_summary(WHAT ALL)
endif()

if(UNIX)
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_START_STATIC ON)
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC ON)
  target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++
                      -static)
  message("Static link with stdc++ libgcc")
endif()

if(BUILD_TESTING)
  find_package(doctest REQUIRED)
  include(CTest)
  enable_testing()

  set(passRegex "SUCCESS" "Test passed" "All ok")
  set(failRegex "Error" "Fail" "FAILED")

  file(GLOB_RECURSE SOURCES "./testings/src/test*.cpp")
  foreach(test_src_file ${SOURCES})
    get_filename_component(test_exe ${test_src_file} NAME_WE)
    add_executable(${test_exe} ${test_src_file})
    target_link_libraries(${test_exe} PRIVATE doctest::doctest)
    target_link_libraries(${test_exe} PRIVATE ${PROJECT_NAME})
    target_include_directories(${test_exe} PRIVATE "./testings/include/")
    if(UNIX)
      set_target_properties(${test_exe} PROPERTIES LINK_SEARCH_START_STATIC ON)
      set_target_properties(${test_exe} PROPERTIES LINK_SEARCH_END_STATIC ON)
      target_link_options(${test_exe} PRIVATE -static-libgcc -static-libstdc++
                          -static)
    endif(UNIX)

    add_test(NAME ${test_exe} COMMAND $<TARGET_FILE:${test_exe}>)
    set_property(TEST ${test_exe} PROPERTY PASS_REGULAR_EXPRESSION
                                           "${passRegex}")
    set_property(TEST ${test_exe} PROPERTY FAIL_REGULAR_EXPRESSION
                                           "${failRegex}")
  endforeach()
endif()
