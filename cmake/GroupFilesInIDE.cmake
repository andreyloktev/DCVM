#Group files under filters in a IDE.
#/param filterName name of the filter. For example 'include' in the Visual Studio
#/param files list of files to group.
function(GroupFiles files)
    foreach(file ${files})
        get_filename_component(_group "${file}" PATH)
        string(REPLACE "/" "\\" _group "${_group}")
        source_group(${_group} FILES ${file})
    endforeach() 
endfunction()
