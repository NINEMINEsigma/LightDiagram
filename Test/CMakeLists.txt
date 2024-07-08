aux_source_directory	(. Test_Cpp_List)
message( STATUS "test part cpp = ${Test_Cpp_List}")


add_executable(test ${Test_Cpp_List})

target_link_libraries(test LightDiagram)

install(TARGETS test)
