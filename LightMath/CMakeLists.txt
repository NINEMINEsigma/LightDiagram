aux_source_directory	(. Math_Cpp_List)
message( STATUS "math part cpp = ${Math_Cpp_List}")
add_executable(LightMath ${Math_Cpp_List})

target_link_libraries(LightMath LightDiagram)

install(TARGETS LightMath 
        RUNTIME DESTINATION ${Install_Path}/bin
        LIBRARY DESTINATION ${Install_Path}/lib
        ARCHIVE DESTINATION ${Install_Path}/lib/static)

message("CMAKE_CXX_STANDARD(LightMath) = ${CMAKE_CXX_STANDARD}" )


