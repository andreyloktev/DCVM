cmake_minimum_required(VERSION 3.12)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CMakeLists.var)
include(${CMAKE_SOURCE_DIR}/cmake/Cmake.cmake)

if("${module_name}" STREQUAL "")
    message(FATAL_ERROR "module_name is empty.")
endif()

if(NOT module_sources)
    message(FATAL_ERROR "module_sources is empty.")
endif()


project(${module_name})

if("${module_type}" STREQUAL "executable")
    add_executable(${module_name} ${module_sources} ${module_public_headers} ${module_private_headers})
else()
    add_library(${module_name} ${module_sources} ${module_public_headers} ${module_private_headers})
endif()

target_include_directories(${module_name} PUBLIC "${CMAKE_SOURCE_DIR}/${module_name}/include")
target_include_directories(${module_name} PRIVATE "${CMAKE_SOURCE_DIR}/${module_name}/src/h")

#Group files in a IDE
GroupFiles(module_sources)

if(module_public_headers)
    GroupFiles(module_public_headers)
endif()

if(module_private_headers)
    GroupFiles(module_private_headers)
endif()
##################################

if(module_defines)
    add_definitions(${module_defines})
endif()

if(module_dependency)
    target_link_libraries(${module_name} ${module_dependency})
endif()

if(module_external_dependency)
    foreach(dependency ${module_external_dependency})
        AddExternalDependency(${module_name} ${dependency})
    endforeach()
endif()

if(module_tests)
    add_executable(${module_name}_test ${module_tests})
    enable_testing()
    find_package(GTest REQUIRED)
    target_link_libraries(${module_name}_test PRIVATE GTest::GTest GTest::Main)
    add_test(AllTestsInMain ${module_name}_test)
endif()

