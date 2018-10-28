#Add external dependency.
#External dependency string must have following format: <namespace>_<target1>_..._<targetN>.
#For example cpprestsdk_cpprest
#/param module_name name of module to link external dependency
#/param dependency dependency string.
function(AddExternalDependency module_name dependency)
    #message("Module name is ${module_name}")
    #message("Dependency is ${dependency}")

    set(targets)
    set(namespaceTargetLength)

    string(REPLACE "_" ";" namespaceTarget ${dependency})
    #message("namespaceTarget is ${namespaceTarget}")

    list(GET namespaceTarget 0 namespace)
    #message("namespace is ${namespace}")

    list(LENGTH namespaceTarget namespaceTargetLength)
    #message("namespaceTarget list length is ${namespaceTargetLength}")

    if(namespaceTargetLength GREATER 1)
        list(SUBLIST namespaceTarget 1 -1 targets)
        list(TRANSFORM targets PREPEND "${namespace}::")
        #message("targets after TRANSFORM is ${targets}")
    endif()

    find_package(${namespace} REQUIRED)

    if(targets)
        target_link_libraries(${module_name} ${targets})
    elseif()
        target_link_libraries(${module_name} ${namespace})
    endif()
endfunction()
