message("LineScript: ----- ----- ----- ----- -----")

aux_source_directory	(. LS_Cpp_List)
message( STATUS "line script part cpp = ${LS_Cpp_List}")
add_executable(LineScript ${LS_Cpp_List})

target_link_libraries(LineScript LightDiagram)

#file(GLOB OpenCV2_Lib_List ${PROJECT_SOURCE_DIR}/LightMath/opencv2-lib/static/*.lib)
#target_link_libraries(demo_test ${OpenCV2_Lib_List})

install(TARGETS LineScript 
		#PUBLIC_HEADER DESTINATION								${CMAKE_INSTALL_PREFIX}/include/LLM
        RUNTIME DESTINATION										${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION										${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION										${CMAKE_INSTALL_PREFIX}/lib/static)

message("CMAKE_CXX_STANDARD(LineScript) = ${CMAKE_CXX_STANDARD}" )
message("LineScript: ----- ----- ----- ----- -----")
