#Project Setting

include_directories		("${PROJECT_BINARY_DIR}")
aux_source_directory	(. Main_Cpp_List)
add_executable (LightDiagram ${Main_Cpp_List})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LightDiagram PROPERTY CXX_STANDARD 17)
endif()

# TODO: 如有需要，请添加测试并安装目标。
