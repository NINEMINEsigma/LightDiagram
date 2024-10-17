include_directories(../LightDiagram)

include_directories(.)
aux_source_directory	(. LS_Cpp_List)
message( STATUS "line script part cpp = ${LS_Cpp_List}")
add_executable(LineScript ${LS_Cpp_List})

target_link_libraries(LineScript LightDiagram)

#file(GLOB OpenCV2_Lib_List ${PROJECT_SOURCE_DIR}/LightMath/opencv2-lib/static/*.lib)
#target_link_libraries(demo_test ${OpenCV2_Lib_List})

install(TARGETS LineScript)

message("CMAKE_CXX_STANDARD(LineScript) = ${CMAKE_CXX_STANDARD}" )
