# include_dir will hold lib's include folder path
function(AddBrigand dependent_target)
    include(ExternalProject)

    # add brigand lib cmake project from github repo
    ExternalProject_Add(
            brigand
            URL https://github.com/edouarda/brigand/archive/master.zip
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/brigand
            # Disable install step
            INSTALL_COMMAND ""
    )

    ExternalProject_Get_Property(brigand source_dir)

    set(include_dir ${source_dir}/include)

    message(${include_dir})

    # CLion does not see headers without SYSTEM flag
    # PUBLIC to ease testings testing
    target_include_directories(${dependent_target} PUBLIC SYSTEM ${include_dir})

    # makes cmake download the actual files when you start building
    add_dependencies(${dependent_target} brigand)
endfunction()