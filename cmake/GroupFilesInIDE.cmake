#Group files under filters in a IDE.
#/param filterName name of the filter. For example 'include' in the Visual Studio
#/param files list of files to group.
function(GroupFiles files)
    foreach(file ${${files}})
        get_filename_component(PARENT_DIR "${file}" DIRECTORY)
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
        string(REPLACE "/" "\\" GROUP "${GROUP}")
        message(STATUS "Add ${file} to group ${GROUP}")
        source_group(${GROUP} FILES ${file})
    endforeach() 
endfunction()
