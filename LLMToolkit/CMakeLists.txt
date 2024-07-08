message(STATUS "LLMToolKit aux source -> ${Platform_Name}")
include_directories(".")
include_directories("./Spack/${Platform_Name}/3.5/v1.1/include")

if (DEFINED _LINUX_ON_WINDOWS)
	link_directories(./${Platform_Name}/Spack/3.5/v1.1/libs/${_LINUX_ON_WINDOWS})
else()
	link_directories(./${Platform_Name}/Spack/3.5/v1.1/libs/${Platform_Name})
endif()

aux_source_directory	(. LLMToolKit_Cpp_List)
message( STATUS "LLM toolkit part cpp = ${LLMToolKit_Cpp_List}")

add_library(LLMToolKit ${LLMToolKit_Cpp_List})

target_link_libraries(LLMToolKit LightDiagram)

if (DEFINED _LINUX_ON_WINDOWS OR DEFINED _WINDOWS)
	target_link_libraries(LLMToolKit SparkChain.lib)
	target_link_libraries(LLMToolKit SparkChain.dll)
elseif(DEFINED _LINUX)
	target_link_libraries(LLMToolKit SparkChain.a)
endif()

#install(TARGETS LightDiagram)
#install(TARGETS ${head_files} DESTINATION  ${CMAKE_BINARY_DIR}/Lib)
install(TARGETS LLMToolKit 
        RUNTIME DESTINATION ${Install_Path}/bin
        LIBRARY DESTINATION ${Install_Path}/lib
        ARCHIVE DESTINATION ${Install_Path}/lib/static)
