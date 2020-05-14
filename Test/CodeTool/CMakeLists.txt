# Include dir
set(CODE_TOOL_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/src)

# Source files list
file(GLOB_RECURSE CODE_TOOL_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    ${CODE_TOOL_INCLUDE}/*.cpp 
    ${CODE_TOOL_INCLUDE}/*.hpp 
    ${CODE_TOOL_INCLUDE}/*.h)
GenerateSourceGoups("${CODE_TOOL_SRCS}")

add_library(${CODE_TOOL_TARGET} SHARED ${CODE_TOOL_SRCS})
target_include_directories(${CODE_TOOL_TARGET} PUBLIC ${CODE_TOOL_INCLUDE})

target_link_libraries(${CODE_TOOL_TARGET} PUBLIC ${CODE_TOOL_API_TARGET})