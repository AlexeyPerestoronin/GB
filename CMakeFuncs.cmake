# brief: finds all files recursively which must be using as target compiler files
# param: i_whichDirectory - first directory for to start recursively viewing
# param: o_result - result list with files
function(FindAllSourceFiles i_whichDirectory o_result)
    set(listTargetSourceFiles "")
	file(GLOB_RECURSE items "${i_whichDirectory}/*")
    foreach(item ${items})
        # consider only files
        if(IS_DIRECTORY ${item})
            continue()
        endif()

        set(isOneRestrictedItem "false")

        # ignore some specific directories
        get_filename_component(fileDirectory ${item} PATH)
        foreach(ignoredDir ${LIST_INGNORED_DIRECTORYES})
            if(${fileDirectory} MATCHES "^${ignoredDir}.*")
                set(isOneRestrictedItem "true")
                break()
            endif()
        endforeach()

        if("${isOneRestrictedItem}" MATCHES "^true?")
            continue()
        endif()

        set(isOneRestrictedItem "true")
        
        # consider only files with avalible extensions
        get_filename_component(fileExtension ${item} EXT)
        foreach(avalibleExt ${LIST_AVALIBLE_EXTENSIONS})
            if("${avalibleExt}" MATCHES "^${fileExtension}?")
                set(isOneRestrictedItem "false")
                break()
            endif()
        endforeach()

        if("${isOneRestrictedItem}" MATCHES "^true?")
            continue()
        endif()

        # add file to result
        list(APPEND listTargetSourceFiles ${item})
    endforeach()
    
    set(${o_result} ${listTargetSourceFiles} PARENT_SCOPE)
endfunction(FindAllSourceFiles)


# brief: filters files in VS-solution by theirs self directory
# param: i_baseDiretory - common part of path for all files
# param: i_listOfFiles - target list of files to filtering
function(ComposeFileBySourceGroup i_baseDirectory i_listOfFiles)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    foreach(fileFullPath ${i_listOfFiles}) 
        # Get the directory of the source file
        get_filename_component(fileDir "${fileFullPath}" DIRECTORY)

        # Remove common directory prefix to make the group
        string(REPLACE "${i_baseDirectory}" "" fileGroup "${fileDir}")

        # place the target source file in detected group
        source_group("${fileGroup}" FILES "${fileFullPath}")
    endforeach()
endfunction(ComposeFileBySourceGroup)
