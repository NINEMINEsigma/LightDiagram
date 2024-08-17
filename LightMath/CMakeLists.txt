include_directories(.)
include_directories(./Math)
aux_source_directory	(. Math_Cpp_List)
message( STATUS "math part cpp = ${Math_Cpp_List}")

find_package(Boost)
if(Boost_FOUND)
	add_compile_definitions(__REF_BOOST_MATH)
    include_directories(${Boost_INCLUDE_DIR})
    MESSAGE( STATUS "Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
    message("Boost setting successfully")

add_library(LightMath ${Math_Cpp_List})

target_link_libraries(LightMath LightDiagram)
target_link_libraries(LightMath OpenXLSX::OpenXLSX)

if(Boost_FOUND)
    target_link_libraries (LightMath ${Boost_LIBRARIES})
    message( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
endif()

file(GLOB LightMath_Header_List ${PROJECT_SOURCE_DIR}/LightMath/Math/*.h)
install(FILES ${LightMath_Header_List} DESTINATION ${Install_Path}/include/Math)
install(TARGETS LightMath 
        RUNTIME DESTINATION ${Install_Path}/bin
        LIBRARY DESTINATION ${Install_Path}/lib
        ARCHIVE DESTINATION ${Install_Path}/lib/static)

else()
    message("Boost setting failed and ${Boost_Preset_Dir} not find, LightMath cannot be used")
endif()

