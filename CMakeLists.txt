# Make Setting
cmake_minimum_required (VERSION 3.12)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enable C++17
set(CMAKE_CXX_STANDARD 17)
# Enable C11
set(C_STANDARD 11)
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive- /Zc /std:c++17 /Zc:__cplusplus") 
add_compile_definitions(UNICODE)

message("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(Install_Path ${CMAKE_BINARY_DIR}/Buildup/default)
set(Platform_Name "Unknown")
if (DEFINED _LINUX_ON_WINDOWS)
	message ( STATUS "current window will support some linux features")
	message ( STATUS ${_LINUX_ON_WINDOWS})
	add_compile_definitions(_LINUX_ON_WINDOW_)
	set(Install_Path ${CMAKE_BINARY_DIR}/Buildup/Linux_On_Windows_${_LINUX_ON_WINDOWS})
	set(Platform_Name "Windows")
elseif (DEFINED _WINDOWS)
	message ( STATUS "current on windows")
	message ( STATUS ${_WINDOWS})
	add_compile_definitions(_WINDOW_)
	set(Install_Path ${CMAKE_BINARY_DIR}/Buildup/Windows_${_WINDOWS})
	set(Platform_Name "Windows")
elseif(DEFINED _LINUX)
	message ( STATUS "current on linux")
	message ( STATUS ${_LINUX})
	add_compile_definitions(_LINUX_)
	set(Install_Path ${CMAKE_BINARY_DIR}/Buildup/Linux_${_LINUX})
	set(Platform_Name "Linux")
endif()

add_compile_definitions(_PTHREADS)

project ("LightDiagram")

# Version
set (LightDiagram_VERSION_MAJOR 1)
set (LightDiagram_VERSION_MINOR 0)

# Sub Project
include_directories ("${PROJECT_SOURCE_DIR}/LightDiagram")
add_subdirectory ("LightDiagram")
add_subdirectory ("LLMToolkit")
if(DEFINED _LINUX OR DEFINED _LINUX_ON_WINDOWS)
	include_directories ("${PROJECT_SOURCE_DIR}/WebServer")
	add_subdirectory ("WebServer")
endif()
add_subdirectory("test")

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/out/")

message("CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}" )
message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")

