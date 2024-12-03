# Make Setting
# All Configs
cmake_minimum_required (VERSION 3.12)
list(APPEND CMAKE_PREFIX_PATH "C:/Boost")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ENABLE_OPEN_XLSX OFF)
set(ENABLE_LLM_TOOLKIT ON)
set(ENABLE_LIGHT_MATH OFF)
set(ENABLE_LINE_SCRIPT OFF)
set(ENABLE_TEST ON)

set(ENABLE_LF_EXPORT OFF)
set(ENABLE_LF_ANYCLASS_MONITOR OFF)
# Disable anyclass's monitor
if(ENABLE_LF_ANYCLASS_MONITOR)
	add_compile_definitions(not_monitor_the_constructor_of_anyclass)
endif()
# Enable Export
if(ENABLE_LF_EXPORT)
	add_compile_definitions(_Source_DLL_EXPORT)
endif()
# Enable C++17
set(CMAKE_CXX_STANDARD 17)
# Enable C11
set(C_STANDARD 11)
if(DEFINED _WINDOWS OR DEFINED _LINUX_ON_WINDOWS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive- /std:c++17 /Zc:__cplusplus") 
elseif(DEFINED _LINUX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") 
endif()
add_compile_definitions(UNICODE)

message("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")

# MSVC Policy
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Defined Platfrom
set(Platform_Name "Unknown")
if (DEFINED _LINUX_ON_WINDOWS)
	message ( STATUS "current on window, but support some linux features")
	message ( STATUS ${_LINUX_ON_WINDOWS})
	add_compile_definitions(_LINUX_ON_WINDOW_)
	set(Platform_Name "Windows")
elseif (DEFINED _WINDOWS)
	message ( STATUS "current on windows")
	message ( STATUS ${_WINDOWS})
	add_compile_definitions(_WINDOW_)
	set(Platform_Name "Windows")
elseif(DEFINED _LINUX)
	message ( STATUS "current on linux")
	message ( STATUS ${_LINUX})
	add_compile_definitions(_LINUX_)
	set(Platform_Name "Linux")
elseif(DEFINED _ANDROID)
	message	( STATUS "current on android")
	message	( STATUS ${_ANDROID})
	add_compile_definitions(_ANDROID_)
	set(Platform_Name "Android")
elseif(DEFINED _MACOS)
	message	( STATUS "current on android")
	message	( STATUS ${_MACOS})
	add_compile_definitions(_MACOS_)
	set(Platform_Name "Android")
endif()

# Threads Enable
add_compile_definitions(_PTHREADS)

# Project
project ("LightDiagram")

# Version
set (LightDiagram_VERSION_MAJOR 1)
set (LightDiagram_VERSION_MINOR 1)

# Sub Project(buf from third-party)
if(ENABLE_OPEN_XLSX)
	add_compile_definitions(__REF_OPEN_XLSX)
	add_subdirectory ("OpenXLSX")
endif()
# Project
include_directories ("${PROJECT_SOURCE_DIR}/LightDiagram")
add_subdirectory ("LightDiagram")
if(ENABLE_LLM_TOOLKIT)
	add_subdirectory ("LLMToolkit")
endif()
# Linux WebServer
if(DEFINED _LINUX OR DEFINED _LINUX_ON_WINDOWS)
	include_directories ("${PROJECT_SOURCE_DIR}/WebServer")
	add_subdirectory ("WebServer")
endif()
# LightMath
if(ENABLE_LIGHT_MATH)
	add_subdirectory("LightMath")
endif()
# LineScript
if(ENABLE_LINE_SCRIPT)
	add_subdirectory("LineScript")
endif()
# Test Demo
if(ENABLE_TEST)
	add_subdirectory("Test")
endif()

message("CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}" )
message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")

