message("LLMToolKit: ----- ----- ----- ----- -----")
set(ENABLE_LLAMA		ON)
set(ENABLE_SPARK		ON)
set(SpackMainVersion	"3.5")
set(SpackVersion		"v1.1")

if(ENABLE_LLAMA) 
	add_compile_definitions(__REF_LLAMA)
	add_subdirectory("llama")
	target_include_directories(llama PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/LightDiagram> $<INSTALL_INTERFACE:include/Core>)
endif()

message(STATUS "LLMToolKit aux source -> ${PlatformName}")
message(STATUS "LLMToolKit src source -> ${PROJECT_SOURCE_DIR}")

# Init Setting
set(LLMToolKit_LibCpps EmptyToolkit.cpp)
file(GLOB LLMToolKit_Header_List ${PROJECT_SOURCE_DIR}/LLMToolKit/LLM/*.h)
include_directories(.)
# Spack Config
set(Spack_Part_Path		${PlatformName}/Spark/3.5/${SpackVersion})
set(Spack_Part_Dir		LLMToolKit/${Spack_Part_Path})
include_directories(${Spack_Part_Dir}/include)
if (DEFINED _LINUX_ON_WINDOWS)
	include_directories("${Spack_Part_Dir}/libs/${_LINUX_ON_WINDOWS}")
elseif (DEFINED _WINDOWS)
	include_directories("${Spack_Part_Dir}/libs/${_WINDOWS}")
elseif(DEFINED _LINUX)
	include_directories("${Spack_Part_Dir}/lib")
else()
	set(ENABLE_SPARK OFF)
endif()

# Add Cpp Sources
if(ENABLE_SPARK)
	set(LLMToolKit_LibCpps ${LLMToolKit_LibCpps} Spark.cpp)
	add_compile_definitions(_REF_SPARK)
endif()

# Add Library
add_library(LLMToolKit "${LLMToolKit_LibCpps}")
message("LLMToolKit: LLMToolKit_LibCpps = ${LLMToolKit_LibCpps}")
target_link_libraries(LLMToolKit PUBLIC LightDiagram)

if(ENABLE_SPARK)
# Spack Lib
	set(Spack_Lib_Path												"None - UnBuild")
	set(Spack_DLL_Path												"None - UnBuild")
	set(Spack_Lib_BasicPath											${CMAKE_SOURCE_DIR}/LLMToolKit/${PlatformName}/Spark/${SpackMainVersion}/${SpackVersion})
	if (DEFINED _LINUX_ON_WINDOW)
		set(Spack_Lib_Path											${Spack_Lib_BasicPath}/libs/${_LINUX_ON_WINDOWS}/SparkChain.lib)
		set(Spack_DLL_Path											${Spack_Lib_BasicPath}/libs/${_LINUX_ON_WINDOWS}/SparkChain.dll)
		install(
			FILES													${Spack_DLL_Path}
			DESTINATION												${CMAKE_INSTALL_PREFIX}/bin)
		target_link_libraries(LLMToolKit PUBLIC						${Spack_Lib_Path})
	elseif (DEFINED _WINDOWS)
		set(Spack_Lib_Path											${Spack_Lib_BasicPath}/libs/${_WINDOWS}/SparkChain.lib)
		set(Spack_DLL_Path											${Spack_Lib_BasicPath}/libs/${_WINDOWS}/SparkChain.dll)
		install(
			FILES													${Spack_DLL_Path}
			DESTINATION												${CMAKE_INSTALL_PREFIX}/bin)
		target_link_libraries(LLMToolKit PUBLIC						${Spack_Lib_Path})
	elseif(DEFINED _LINUX)
		set(Spack_Lib_Path											${Spack_Lib_BasicPath}/libs/${_WINDOWS}/SparkChain)
		set(Spack_DLL_Path											"None - Linux UnBuild")
		add_library(SparkLib STATIC IMPORTE)
		set_target_properties(SparkLib PROPERTIES IMPORTED_LOCATION	${Spack_Lib_BasicPath}/lib/SparkChain)
		message(						   "LLMToolKit: Spack_Lib = ${Spack_Lib_BasicPath}/lib/SparkChain")
		target_link_libraries(LLMToolKit SparkLib)
	else()
		message(	"LLMToolKit: ENABLE_SPARK is ON, but working on ${PlatformName} is not support")
	endif()
	message(							   "LLMToolKit: Spack_Lib = ${Spack_Lib_Path}")
# Spack Install
	file(GLOB LLMToolKit_Spack_Header_List						${Spack_Part_Dir}/include/*.h)
	install(
		FILES													${LLMToolKit_Spack_Header_List}
		DESTINATION												${CMAKE_INSTALL_PREFIX}/include/${Spack_Part_Path})
	message("LLMToolKit: Spack is enable on ${PlatformName}")
else()
	message("LLMToolKit: Spack is disable")
endif()

message(					  "LLMToolKit: CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}" )

#ToolKit Install
set_target_properties(LLMToolKit PROPERTIES PUBLIC_HEADER		${LLMToolKit_Header_List})
install(FILES ${PROJECT_SOURCE_DIR}/LLMToolKit/LLMToolKit.h 
				DESTINATION										${CMAKE_INSTALL_PREFIX}/include/)
install(TARGETS LLMToolKit 
		PUBLIC_HEADER DESTINATION								${CMAKE_INSTALL_PREFIX}/include/LLM
        RUNTIME DESTINATION										${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION										${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION										${CMAKE_INSTALL_PREFIX}/lib/static)
message("LLMToolKit: ----- ----- ----- ----- -----")
