#################################################
# build instructions
#################################################

# Include dir
set(ACTIONSREGISTRY_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/src)

# Gather source files list
file(GLOB_RECURSE ACTIONSREGISTRY_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    ${ACTIONSREGISTRY_INCLUDE}/*.cpp 
    ${ACTIONSREGISTRY_INCLUDE}/*.hpp 
    ${ACTIONSREGISTRY_INCLUDE}/*.h)
GenerateSourceGoups("${ACTIONSREGISTRY_SRCS}")

# add library
add_library(${ACTIONSREGISTRY_TARGET} STATIC ${ACTIONSREGISTRY_SRCS})
target_include_directories(${ACTIONSREGISTRY_TARGET} PUBLIC ${ACTIONSREGISTRY_INCLUDE})

target_link_libraries(${ACTIONSREGISTRY_TARGET} PUBLIC ${POLYTOOLS_TARGET})
target_link_libraries(${ACTIONSREGISTRY_TARGET} PRIVATE Qt5::Widgets Qt5::Core)