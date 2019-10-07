include(CMakeLists.var)

if(NOT system_components)
    message(FATAL_ERROR "System has to containe atleast one component")
endif()

foreach(component ${system_components})
    add_subdirectory(${component})
endforeach()