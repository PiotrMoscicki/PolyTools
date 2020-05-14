#################################################
# build instructions
#################################################

# Include dir
set(POLYTOOLS_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/src)

# Gather source files list
file(GLOB_RECURSE POLYTOOLS_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    ${POLYTOOLS_INCLUDE}/*.cpp 
    ${POLYTOOLS_INCLUDE}/*.hpp 
    ${POLYTOOLS_INCLUDE}/*.h)
GenerateSourceGoups("${POLYTOOLS_SRCS}")

# add library
add_library(${POLYTOOLS_TARGET} INTERFACE)
add_custom_target(${POLYTOOLS_TARGET}_ SOURCES ${POLYTOOLS_SRCS})
target_include_directories(${POLYTOOLS_TARGET} INTERFACE
    $<BUILD_INTERFACE:${POLYTOOLS_INCLUDE}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# link polyPlugin
target_link_libraries(${POLYTOOLS_TARGET} INTERFACE PolyPlugin::PolyPlugin)
target_link_libraries(${POLYTOOLS_TARGET} INTERFACE Qt5::Widgets Qt5::Core)