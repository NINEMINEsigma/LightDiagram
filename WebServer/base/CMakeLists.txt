aux_source_directory	(. libserver_base_Cpp_List)
message( STATUS "web server libserver part cpp = ${libserver_base_Cpp_List}")
add_library(libserver_base ${libserver_base_Cpp_List})
target_link_libraries(libserver_base pthread rt)

set_target_properties(libserver_base PROPERTIES OUTPUT_NAME "server_base")