# Enable C++17
set(CMAKE_CXX_STANDARD 17)
# Enable C11
set(C_STANDARD 11)
aux_source_directory	(. WebServer_Cpp_List)
message( STATUS "web server part cpp = ${WebServer_Cpp_List}")
include_directories(${PROJECT_SOURCE_DIR}/WebServer/base)


add_executable(WebServer ${WebServer_Cpp_List})
target_link_libraries(WebServer libserver_base)

add_subdirectory(base)

install(TARGETS WebServer)
