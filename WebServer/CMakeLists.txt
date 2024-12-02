aux_source_directory	(. WebServer_Cpp_List)
message( STATUS "web server part cpp = ${WebServer_Cpp_List}")
include_directories(${PROJECT_SOURCE_DIR}/WebServer/base)


add_executable(WebServer ${WebServer_Cpp_List})
target_link_libraries(WebServer libserver_base)
target_link_libraries(WebServer LightDiagram)

add_subdirectory(base)

install(TARGETS WebServer 
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/static)
