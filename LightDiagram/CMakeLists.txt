#Project Setting

include_directories		("${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}/Core/Header")
include_directories		("${PROJECT_BINARY_DIR}/Core")
aux_source_directory	(. Main_Cpp_List)
aux_source_directory	(./Core Core_Cpp_List)
message("main part cpp: ")
message(${Main_Cpp_List})
message("core part cpp: ")
message(${Core_Cpp_List})
add_executable (LightDiagram ${Main_Cpp_List} ${Core_Cpp_List})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LightDiagram PROPERTY CXX_STANDARD 17)
endif()

install(TARGETS LightDiagram)
