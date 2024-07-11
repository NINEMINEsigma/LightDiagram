
aux_source_directory	(. Test_Cpp_List)
message( STATUS "test part cpp = ${Test_Cpp_List}")
add_executable(demo_test ${Test_Cpp_List})

target_link_libraries(demo_test LightDiagram)
target_link_libraries(demo_test LLMToolKit)

install(TARGETS demo_test)

message("CMAKE_CXX_STANDARD(Test) = ${CMAKE_CXX_STANDARD}" )
