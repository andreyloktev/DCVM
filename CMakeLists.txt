cmake_minimum_required(VERSION 3.12)

include(CMakeLists.var)

if(NOT projectName)
    message(FATAL_ERROR "Project name must be specified")
endif()

if(NOT components)
    message(FATAL_ERROR "Project has to containe atleast one component")
endif()

if(NOT EXISTS $ENV{BUILDTLS})
    message(FATAL_ERROR "Path $ENV{BUILDTLS} does not exist. Specify environmnet variable BUILDTLs where vcpkg must be placed.")
endif()

if(NOT EXISTS "$ENV{BUILDTLS}/vcpkg")
    message(FATAL_ERROR "Path $ENV{BUILDTLS}/vcpkg does not exist. Specify environmnet variable BUILDTLs where vcpkg must be placed.")
endif()

# Add output directory for archives project.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    CACHE PATH "Directory where all the .lib files are dumped.")

# Add output directory for shared lib and executive files project.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    CACHE PATH "Directory where .exe and .dll files are dumped.")

# Add output directory for shared .so.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    CACHE PATH "Directory where .so files are dumped.")


project(${projectName})

foreach(component ${components})
    add_subdirectory(${component})
endforeach()



