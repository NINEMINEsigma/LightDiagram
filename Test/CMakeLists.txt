message("Test: ----- ----- ----- ----- -----")
project(Test)
set(BOOST_ROOT "C:/Boost")

set(Boost_NO_SYSTEM_PATHS ON) 
find_package(Boost)
if(Boost_FOUND)
	#add_compile_definitions(__REF_BOOST)
    include_directories(${Boost_INCLUDE_DIR})
    MESSAGE( STATUS "Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
    message("Test: Boost setting successfully")
else()
    message("Test: Boost setting failed and ${Boost_Preset_Dir} not find")
endif()

#include_directories(../LightMath)
#include_directories(../LLMToolKit)
if(ENABLE_LLM_TOOLKIT)
    include_directories(../LLMToolKit/llama)
endif()
add_compile_definitions(__REF_LLAMA)
include_directories(../LightDiagram)

include_directories(.)
aux_source_directory	(. Test_Cpp_List)
message( STATUS "test part cpp = ${Test_Cpp_List}")
add_executable(Test ${Test_Cpp_List})

if(Boost_FOUND)
    target_link_libraries (Test ${Boost_LIBRARIES})
    message( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
endif()
target_link_libraries(Test LightDiagram)
if(ENABLE_LLM_TOOLKIT)
    target_link_libraries(Test llama)
endif()
#target_link_libraries(demo_test LLMToolKit)
#target_link_libraries(demo_test OpenXLSX::OpenXLSX)
#target_link_libraries(demo_test LightMath)

file(GLOB OpenCV2_Lib_List ${PROJECT_SOURCE_DIR}/LightMath/opencv2-lib/static/*.lib)
target_link_libraries(Test ${OpenCV2_Lib_List})

install(TARGETS Test 
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/static)

message("Test: CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}" )

message("Test: ----- ----- ----- ----- -----")

