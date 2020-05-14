cmake_minimum_required(VERSION 3.12)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

##
# Function that generates source groups
##
function(GenerateSourceGoups Sources)
	foreach(Source ${Sources})
		get_filename_component(SourcePath "${Source}" PATH)
		if (WIN32)
			string(REPLACE "/" "\\" SourcePath "${SourcePath}")
		endif()
		source_group("${SourcePath}" FILES "${Source}")
	endforeach()
endfunction()

##
# Start
##
project(PolyTools VERSION "1.0.0")
include(GNUInstallDirs)

configure_file(
	"${PROJECT_SOURCE_DIR}/config/CmakeConfig.hpp.in" 
	"${PROJECT_BINARY_DIR}/config/CmakeConfig.hpp"
)
include_directories("${PROJECT_BINARY_DIR}/config")

set(POLYTOOLS_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(DIST_DIR "${POLYTOOLS_ROOT_DIR}/Dist")
set(COMMON_BUILD_DIR "${POLYTOOLS_ROOT_DIR}/CommonBuild")

# Output dirs
if (WIN32)
	set(FULL_DIST_DIR "${DIST_DIR}") # Config name is added autmatically on windows
else()
	set(FULL_DIST_DIR "${DIST_DIR}/${BUILD_CONFIG_NAME}")
endif()
	
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FULL_DIST_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FULL_DIST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FULL_DIST_DIR})

# C++ standard 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find externals
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(PolyPlugin REQUIRED)

# Add our targets
set(POLYTOOLS_TARGET PolyTools)
set(ACTIONSREGISTRY_TARGET ActionsRegistry)
set(CODE_TOOL_API_TARGET CodeToolAPI)
set(CODE_TOOL_TARGET CodeTool)

add_subdirectory(PolyTools)
add_subdirectory(ActionsRegistry)
add_subdirectory(Test/CodeToolAPI)
add_subdirectory(Test/CodeTool)