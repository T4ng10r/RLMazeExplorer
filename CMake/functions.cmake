macro(set_c11_flags)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
		add_definitions(-D__GXX_EXPERIMENTAL_CXX0X__)		
    elseif(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
		add_definitions(-D__GXX_EXPERIMENTAL_CXX0X__)		
    else()
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endmacro()

macro(CreateProjectStructure BASE_DIRECTORY )
	if (MSVC)
		foreach(f ${ARGN})
			file(RELATIVE_PATH SRC_GROUP ${BASE_DIRECTORY} ${f})
			string(FIND ${SRC_GROUP} / IS_SUBFOLDER)
			if (${IS_SUBFOLDER} GREATER -1)
				set(SRC_GROUP "${SRC_GROUP}")

				# Extract the folder, ie remove the filename part
				string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRC_GROUP ${SRC_GROUP})
				string(REPLACE "../" "" SRC_GROUP ${SRC_GROUP})

				# Source_group expects \\ (double antislash), not / (slash)
				string(REPLACE / "\\" SRC_GROUP ${SRC_GROUP})
				source_group(${SRC_GROUP} FILES ${f})
			endif()
		endforeach()
	endif()
endmacro()

macro(GatheringFiles DirectoryToScan FileExts )

foreach(e ${FileExts})
    SET(PathsToScan ${PathsToScan} ${DirectoryToScan}/*.${e})
endforeach()

file(GLOB_RECURSE TMP_FILES ${PathsToScan})
foreach(f ${TMP_FILES})
	set_source_files_properties(${f} PROPERTIES )
ENDFOREACH()

CreateProjectStructure(${CMAKE_CURRENT_SOURCE_DIR} ${TMP_FILES})

endmacro(GatheringFiles)

