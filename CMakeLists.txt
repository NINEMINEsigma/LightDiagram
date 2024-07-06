# Make Setting
cmake_minimum_required (VERSION 3.12)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if (DEFINED _LINUX_ON_WINDOWS)
	message ( STATUS "current window will support some linux features")
	message ( STATUS ${_LINUX_ON_WINDOWS})
	add_compile_definitions(_LINUX_ON_WINDOW_)
elseif (DEFINED _WINDOWS)
	message ( STATUS "current on windows")
	message ( STATUS ${_WINDOWS})
	add_compile_definitions(_WINDOW_)
elseif(DEFINED _LINUX)
	message ( STATUS "current on linux")
	message ( STATUS ${_LINUX})
	add_compile_definitions(_LINUX_)
endif()

add_compile_definitions(_PTHREADS)

project ("LightDiagram")

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
# Enable C11
set(C_STANDARD 11)

# Version
set (LightDiagram_VERSION_MAJOR 1)
set (LightDiagram_VERSION_MINOR 0)

# Sub Project
include_directories ("${PROJECT_SOURCE_DIR}/LightDiagram")
add_subdirectory ("LightDiagram")
if(DEFINED _LINUX OR DEFINED _LINUX_ON_WINDOWS)
	include_directories ("${PROJECT_SOURCE_DIR}/WebServer")
	add_subdirectory ("WebServer")
endif()

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/out/")
