message(STATUS "LLMToolKit aux source -> ${Platform_Name}")
message(STATUS "LLMToolKit src source -> ${PROJECT_SOURCE_DIR}")
include_directories(".")
include_directories("${PROJECT_SOURCE_DIR}/LLMToolKit/${Platform_Name}/Spark/3.5/v1.1/include")

if (DEFINED _LINUX_ON_WINDOWS)
	include_directories("${PROJECT_SOURCE_DIR}/LLMToolKit/${Platform_Name}/Spack/3.5/v1.1/libs/${_LINUX_ON_WINDOWS}")
elseif (DEFINED _WINDOWS)
	include_directories("${PROJECT_SOURCE_DIR}/LLMToolKit/${Platform_Name}/Spack/3.5/v1.1/libs/${_WINDOWS}")
elseif(DEFINED _LINUX)
	include_directories("${PROJECT_SOURCE_DIR}/LLMToolKit/${Platform_Name}/Spack/3.5/v1.1/lib")
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
	target_link_libraries(LLMToolKit "${PROJECT_SOURCE_DIR}/LLMToolkit/Linux/Spark/3.5/v1.1/lib/libSparkChain.so")
endif()

#install(TARGETS LightDiagram)
#install(TARGETS ${head_files} DESTINATION  ${CMAKE_BINARY_DIR}/Lib)
install(TARGETS LLMToolKit 
        RUNTIME DESTINATION ${Install_Path}/bin
        LIBRARY DESTINATION ${Install_Path}/lib
        ARCHIVE DESTINATION ${Install_Path}/lib/static)
