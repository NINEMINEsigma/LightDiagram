message("LineScript: ----- ----- ----- ----- -----")

aux_source_directory	(. LS_Cpp_List)
message( STATUS "line script part cpp = ${LS_Cpp_List}")
add_executable(LineScript ${LS_Cpp_List})

target_link_libraries(LineScript LightDiagram)

file(GLOB LSHeaders *.h)
set_target_properties(LineScript PROPERTIES PUBLIC_HEADER       "${LSHeaders}")

install(TARGETS LineScript 
		PUBLIC_HEADER DESTINATION								${CMAKE_INSTALL_PREFIX}/include/LineScript
        RUNTIME DESTINATION										${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION										${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION										${CMAKE_INSTALL_PREFIX}/lib/static)

message("CMAKE_CXX_STANDARD(LineScript) = ${CMAKE_CXX_STANDARD}" )
message("LineScript: ----- ----- ----- ----- -----")
