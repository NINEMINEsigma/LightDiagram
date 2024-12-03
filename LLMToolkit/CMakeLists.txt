set(ENABLE_LLAMA ON)
set(ENABLE_SPARK ON)

if(ENABLE_LLAMA) 
	add_compile_definitions(__REF_LLAMA)
	add_subdirectory("llama")
endif()

message(STATUS "LLMToolKit aux source -> ${Platform_Name}")
message(STATUS "LLMToolKit src source -> ${PROJECT_SOURCE_DIR}")
include_directories(.)

add_library(LLMToolKit)
target_link_libraries(LLMToolKit LightDiagram)
#Spack Config
set(Spack_Part_Path "${Platform_Name}/Spark/3.5/v1.1")
set(Spack_Part_Dir "${PROJECT_SOURCE_DIR}/LLMToolKit/${Spack_Part_Path}")
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
endif()
#Spack Lib
if (DEFINED _LINUX_ON_WINDOWS)
	target_link_libraries(LLMToolKit "${PROJECT_SOURCE_DIR}/LLMToolkit/Windows/Spark/3.5/v1.1/libs/${_LINUX_ON_WINDOWS}/SparkChain.lib")
elseif (DEFINED _WINDOWS)
	target_link_libraries(LLMToolKit "${PROJECT_SOURCE_DIR}/LLMToolkit/Windows/Spark/3.5/v1.1/libs/${_WINDOWS}/SparkChain.lib")
elseif(DEFINED _LINUX)
	add_library(SparkLib STATIC IMPORTED)
	set_target_properties(SparkLib PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/LLMToolkit/Linux/Spark/3.5/v1.1/lib/SparkChain")
	target_link_libraries(LLMToolKit SparkLib)
endif()
#Spack Install
if(ENABLE_SPARK)
	file(GLOB LLMToolKit_Spack_Header_List ${Spack_Part_Dir}/include/*.h)
	install(
		FILES ${LLMToolKit_Spack_Header_List}
		DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${Spack_Part_Path})
	install(
		FILES ${PROJECT_SOURCE_DIR}/LLMToolkit/Windows/Spark/3.5/v1.1/libs/${_WINDOWS}/SparkChain.dll
		DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()

message("CMAKE_CXX_STANDARD(LLM) = ${CMAKE_CXX_STANDARD}" )

#ToolKit Install
file(GLOB LLMToolKit_Header_List ${PROJECT_SOURCE_DIR}/LLMToolKit/LLM/*.h)
install(FILES ${LLMToolKit_Header_List} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/LLM/)
install(FILES ${PROJECT_SOURCE_DIR}/LLMToolKit/LLMToolKit.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/)
install(TARGETS LLMToolKit 
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/static)
