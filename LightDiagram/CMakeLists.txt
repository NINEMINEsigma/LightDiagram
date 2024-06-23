#Project Setting

if(DEFINED _WINDOW_)
    set(MSCV_MPI_ROOT "${PROJECT_BINARY_DIR}/MSVC/MPI/Include")
    if(EXISTS MSCV_MPI_ROOT)
        include_directories(MSCV_MPI_ROOT)
    endif()
endif()

include_directories		("${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}/Core/Header" "${PROJECT_BINARY_DIR}/Extension/Header")
include_directories		("${PROJECT_BINARY_DIR}/Core" "${PROJECT_BINARY_DIR}/Extension")
aux_source_directory	(. Main_Cpp_List)
aux_source_directory	(./Core Core_Cpp_List)
aux_source_directory	(./Extension Extension_Cpp_List)
message("main part cpp: ")
message(${Main_Cpp_List})
message("core part cpp: ")
message(${Core_Cpp_List})
message("extension part cpp: ")
message(${Extension_Cpp_List})
add_executable (LightDiagram ${Main_Cpp_List} ${Core_Cpp_List} ${Extension_Cpp_List})

#--------------------------

#Boost Setting 
#You can define __REF_BOOST to include all boost header,
#and you need to include boost lib and directories here
 
if(EXISTS E:/user/boost_1_82_0/boost_1_82_0/buildup )
    set(BOOST_ROOT "E:\\user\\boost_1_82_0\\boost_1_82_0\\buildup")
endif()
if(EXISTS E:/boost_1_85_0/buildup/single_thread/include/boost-1_85/boost/config.hpp )
    set(BOOST_ROOT "E\\boost_1_85_0\\buildup\\single_thread")
endif()
if(EXISTS BOOST_ROOT)
    set(Boost_NO_SYSTEM_PATHS ON) 
    find_package(Boost COMPONENTS regex system REQUIRED)
    
    if(DEFINED Boost_FOUND)
    	add_compile_definitions(__REF_BOOST)
    
        include_directories(${Boost_INCLUDE_DIRS})
        if(DEFINED _WINDOW_)
            target_link_libraries(LightDiagram "${PROJECT_BINARY_DIR}/MSVC/MPI/Lib")
        endif()
        
        MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
        MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
        MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
        target_link_libraries (LightDiagram ${Boost_LIBRARIES})
    endif()
else()
    message( STATUS "Can not find Boost Path" )
endif()

#--------------------------

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LightDiagram PROPERTY CXX_STANDARD 17)
endif()

install(TARGETS LightDiagram)
