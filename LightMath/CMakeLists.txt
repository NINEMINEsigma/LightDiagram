set(__LINK_STATIC_OPENCV OFF)

include_directories(.)
include_directories(./Math)
include_directories(./Eigen)
include_directories(./opencv2)
aux_source_directory	(./Math Math_Cpp_List)
message( STATUS "math part cpp = ${Math_Cpp_List}")

set(Boost_NO_SYSTEM_PATHS ON) 
set(BOOST_ROOT "C:/Boost")
find_package(Boost 1.85.0 EXACT)
if(Boost_FOUND)
	add_compile_definitions(__REF_BOOST_MATH)
    include_directories(${Boost_INCLUDE_DIR})
    MESSAGE( STATUS "Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
    message("Boost setting successfully")

add_library(LightMath ${Math_Cpp_List} ./LightMath.cpp)

target_link_libraries(LightMath LightDiagram)

if(Boost_FOUND)
    target_link_libraries (LightMath ${Boost_LIBRARIES})
    message( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
endif()

file(GLOB OpenCV2_Lib_List ${PROJECT_SOURCE_DIR}/LightMath/opencv2-lib/static/*.lib)
if(__LINK_STATIC_OPENCV)
    target_link_libraries(LightMath ${OpenCV2_Lib_List})
    message(STATUS "opencv is linking static")
else()
    install(FILES ${OpenCV2_Lib_List} DESTINATION ${Install_Path}/lib/static)
    message(STATUS "opencv-lib is install")
endif()

file(GLOB LightMath_Header_List ${PROJECT_SOURCE_DIR}/LightMath/Math/*.h)
install(FILES ${LightMath_Header_List} DESTINATION ${Install_Path}/include/Math)
install(FILES ${PROJECT_SOURCE_DIR}/LightMath/LightMath.h DESTINATION ${Install_Path}/include)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/LightMath/Eigen DESTINATION ${Install_Path}/include/)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/LightMath/opencv2 DESTINATION ${Install_Path}/include/)
install(TARGETS LightMath 
        RUNTIME DESTINATION ${Install_Path}/bin
        LIBRARY DESTINATION ${Install_Path}/lib
        ARCHIVE DESTINATION ${Install_Path}/lib/static)

else()
    message("Boost setting failed and ${Boost_Preset_Dir} not find, LightMath cannot be used")
endif()

