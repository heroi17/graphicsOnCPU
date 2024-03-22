cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("graphics")
include_directories(include)
file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics/graphics.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/GraphPainter/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GraphPainter/include/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GraphPainter/linker.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/GraphPainter/graph.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_executable(graphics ${SOURCES})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/GraphExamples ${CMAKE_CURRENT_BINARY_DIR}/GraphExamples
    COMMENT "Copying test directory to build directory"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET graphics PROPERTY CXX_STANDARD 20)
endif()
