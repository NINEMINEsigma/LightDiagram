message("LLMToolKit: ----- ----- ----- ----- -----")
set(ENABLE_LLAMA		ON)
set(ENABLE_SPARK		ON)
set(SpackMainVersion	"3.5")
set(SpackVersion		"v1.1")

if(ENABLE_LLAMA) 
	add_compile_definitions(__REF_LLAMA)
	add_subdirectory("llama")
	target_include_directories(llama PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../LightDiagram> $<INSTALL_INTERFACE:include>)
endif()

message(STATUS "LLMToolKit aux source -> ${PlatformName}")
message(STATUS "LLMToolKit src source -> ${PROJECT_SOURCE_DIR}")
include_directories(.)

add_library(LLMToolKit EmptyToolkit.cpp)
file(GLOB LLMToolKit_Header_List ${PROJECT_SOURCE_DIR}/LLMToolKit/LLM/*.h)
target_link_libraries(LLMToolKit PUBLIC LightDiagram)
#Spack Config
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
if(ENABLE_SPARK)
	target_sources(LLMToolKit PUBLIC Spark.cpp)
	add_compile_definitions(_REF_SPARK)
#Spack Lib
	set(Spack_Lib_BasicPath											${PlatformName}/Spark/${SpackMainVersion}/${SpackVersion})
	if (DEFINED _LINUX_ON_WINDOW)
		target_link_libraries(LLMToolKit							${Spack_Lib_BasicPath}/libs/${_LINUX_ON_WINDOWS}/SparkChain.lib)
		message(						   "LLMToolKit: Spack_Lib = ${Spack_Lib_BasicPath}/libs/${_LINUX_ON_WINDOWS}/SparkChain.lib")
	elseif (DEFINED _WINDOW)
		target_link_libraries(LLMToolKit							${Spack_Lib_BasicPath}/libs/${_WINDOWS}/SparkChain.lib)
		message(						   "LLMToolKit: Spack_Lib = ${Spack_Lib_BasicPath}/libs/${_WINDOWS}/SparkChain.lib")
	elseif(DEFINED _LINUX)
		add_library(SparkLib STATIC IMPORTE)
		set_target_properties(SparkLib PROPERTIES IMPORTED_LOCATION	${Spack_Lib_BasicPath}/lib/SparkChain)
		message(						   "LLMToolKit: Spack_Lib = ${Spack_Lib_BasicPath}/lib/SparkChain")
		target_link_libraries(LLMToolKit SparkLib)
	endif()
#Spack Install
	file(GLOB LLMToolKit_Spack_Header_List						${Spack_Part_Dir}/include/*.h)
	install(
		FILES													${LLMToolKit_Spack_Header_List}
		DESTINATION												${CMAKE_INSTALL_PREFIX}/include/${Spack_Part_Path})
	install(
		FILES													${Spack_Lib_BasicPath}/SparkChain.dll
		DESTINATION												${CMAKE_INSTALL_PREFIX}/lib)
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
