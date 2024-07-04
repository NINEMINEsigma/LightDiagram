# @Author Lin Ya
# @Email xxbbb@vip.qq.com

# @Author Liu Bai
# @Email ninemine@qq.com

aux_source_directory	(. WebServer_Cpp_List)
message( STATUS "web server part cpp = ${WebServer_Cpp_List}")
include_directories(${PROJECT_SOURCE_DIR}/WebServer/base)


add_executable(WebServer ${WebServer_Cpp_List})
target_link_libraries(WebServer libserver_base)


add_subdirectory(base)
add_subdirectory(tests)
