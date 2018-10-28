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


project(${projectName})

foreach(component ${components})
    add_subdirectory(${component})
endforeach()



