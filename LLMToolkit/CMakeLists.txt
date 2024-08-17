message(STATUS "LLMToolKit aux source -> ${Platform_Name}")
message(STATUS "LLMToolKit src source -> ${PROJECT_SOURCE_DIR}")
include_directories(".")

#Spack
set(Spack_Part_Path "${Platform_Name}/Spark/3.5/v1.1")
set(Spack_Part_Dir "${PROJECT_SOURCE_DIR}/LLMToolKit/${Spack_Part_Path}")
include_directories(${Spack_Part_Dir}/include)
if (DEFINED _LINUX_ON_WINDOWS)
	include_directories("${Spack_Part_Dir}/libs/${_LINUX_ON_WINDOWS}")
elseif (DEFINED _WINDOWS)
	include_directories("${Spack_Part_Dir}/libs/${_WINDOWS}")
elseif(DEFINED _LINUX)
	include_directories("${Spack_Part_Dir}/lib")
endif()

aux_source_directory	(. LLMToolKit_Cpp_List)
message( STATUS "LLM toolkit part cpp = ${LLMToolKit_Cpp_List}")

add_library(LLMToolKit ${LLMToolKit_Cpp_List})

target_link_libraries(LLMToolKit LightDiagram)

if (DEFINED _LINUX_ON_WINDOWS)
	target_link_libraries(LLMToolKit "${PROJECT_SOURCE_DIR}/LLMToolkit/Windows/Spark/3.5/v1.1/libs/${_LINUX_ON_WINDOWS}/SparkChain.lib")
elseif (DEFINED _WINDOWS)
	target_link_libraries(LLMToolKit "${PROJECT_SOURCE_DIR}/LLMToolkit/Windows/Spark/3.5/v1.1/libs/${_WINDOWS}/SparkChain.lib")
elseif(DEFINED _LINUX)
	add_library(SparkLib STATIC IMPORTED)
	set_target_properties(SparkLib PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/LLMToolkit/Linux/Spark/3.5/v1.1/lib/SparkChain")
	target_link_libraries(LLMToolKit SparkLib)
endif()

message("CMAKE_CXX_STANDARD(LLM) = ${CMAKE_CXX_STANDARD}" )

#Spack
file(GLOB LLMToolKit_Spack_Header_List ${Spack_Part_Dir}/include/*.h)
install(FILES ${LLMToolKit_Spack_Header_List} DESTINATION ${Install_Path}/include/${Spack_Part_Path})
#ToolKit
file(GLOB LLMToolKit_Header_List ${PROJECT_SOURCE_DIR}/LLMToolKit/LLM/*.h)
install(FILES ${LLMToolKit_Header_List} DESTINATION ${Install_Path}/include/LLM/)
install(FILES ${PROJECT_SOURCE_DIR}/LLMToolKit/LLMToolKit.h DESTINATION ${Install_Path}/include/)
install(TARGETS LLMToolKit 
        RUNTIME DESTINATION ${Install_Path}/bin
        LIBRARY DESTINATION ${Install_Path}/lib
        ARCHIVE DESTINATION ${Install_Path}/lib/static)
