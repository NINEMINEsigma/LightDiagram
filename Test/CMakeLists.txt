
aux_source_directory	(. Test_Cpp_List)
message( STATUS "test part cpp = ${Test_Cpp_List}")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enable C++17
set(CMAKE_CXX_STANDARD 17)
# Enable C11
set(C_STANDARD 11)
add_executable(test ${Test_Cpp_List})

target_link_libraries(test LightDiagram)
#target_link_libraries(test LLMToolKit)

install(TARGETS test)

message("CMAKE_CXX_STANDARD(Test) = ${CMAKE_CXX_STANDARD}" )
