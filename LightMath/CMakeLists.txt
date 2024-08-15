include_directories(.)
aux_source_directory	(. Math_Cpp_List)
message( STATUS "math part cpp = ${Math_Cpp_List}")
add_library(LightMath ${Math_Cpp_List})

target_link_libraries(LightMath LightDiagram)
target_link_libraries(LightMath OpenXLSX::OpenXLSX)

file(GLOB LightMath_Header_List ${PROJECT_SOURCE_DIR}/LightMath/*.h)
install(FILES ${LightMath_Header_List} DESTINATION ${Install_Path}/include/)
install(TARGETS LightMath 
        RUNTIME DESTINATION ${Install_Path}/bin
        LIBRARY DESTINATION ${Install_Path}/lib
        ARCHIVE DESTINATION ${Install_Path}/lib/static)


