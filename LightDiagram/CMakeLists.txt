#Project Setting
message("LightDiagram: ----- ----- ----- ----- -----")
option(ENABLE_MPI "Enable MPI parallelization" ON)
set(MPI_NO_SYSTEM_PATHS ON)
set(BOOST_ROOT "C:/Boost")

# MPI
find_package(MPI)
if(MPI_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MPI_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MPI_EXE_LINKER_FLAGS}")
    include_directories(${MPI_C_HEADER_DIR})
    MESSAGE( STATUS "MPI_C_HEADER_DIR = ${MPI_C_HEADER_DIR}") 
    include_directories(${MPI_C_ADDITIONAL_INCLUDE_DIRS})
    MESSAGE( STATUS "MPI_C_ADDITIONAL_INCLUDE_DIRS = ${MPI_C_ADDITIONAL_INCLUDE_DIRS}") 
    MESSAGE( "LightDiagram: MPI setting successfully")
else()
    MESSAGE( "LightDiagram: MPI setting faild")
endif()

# Boost
set(Boost_NO_SYSTEM_PATHS ON) 
find_package(Boost)
if(Boost_FOUND)
	#add_compile_definitions(__REF_BOOST)
    include_directories(${Boost_INCLUDE_DIR})
    MESSAGE( STATUS "Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
    message("LightDiagram: Boost setting successfully")
else()
    message("LightDiagram: Boost setting failed and ${Boost_Preset_Dir} not find")
    if(DEFINED __REF_BOOST)
        remove_definitions(__REF_BOOST)
    endif()
endif()

aux_source_directory    (. Main_Cpp_List)
aux_source_directory    (./Core Core_Cpp_List)
aux_source_directory    (./Engine Engine_Cpp_List)
message( STATUS "main part cpp = ${Main_Cpp_List}")
message( STATUS "core part cpp = ${Core_Cpp_List}")
add_library (LightDiagram ${Main_Cpp_List} ${Core_Cpp_List})
file(GLOB LightDiagram_Header_List Core/*.h)
set_target_properties(LightDiagram PROPERTIES PUBLIC_HEADER "${LightDiagram_Header_List}")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LightDiagram PROPERTY CXX_STANDARD 17)
endif()

if(MPI_FOUND)
    target_link_libraries(LightDiagram      ${MPI_C_LIBRARIES})
    set_property(TARGET LightDiagram PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    message(    STATUS   "MPI_C_LIBRARIES = ${MPI_C_LIBRARIES}")
endif()

if(Boost_FOUND)
    target_link_libraries (LightDiagram     ${Boost_LIBRARIES})
    message(    STATUS   "Boost_LIBRARIES = ${Boost_LIBRARIES}")
endif()

install(FILES LightDiagram.h DESTINATION    ${CMAKE_INSTALL_PREFIX}/include)
install(TARGETS LightDiagram 
        PUBLIC_HEADER DESTINATION           ${CMAKE_INSTALL_PREFIX}/include/Core
        RUNTIME DESTINATION                 ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION                 ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION                 ${CMAKE_INSTALL_PREFIX}/lib/static)

install(FILES ${LightDiagram_Engines_List} DESTINATION  ${CMAKE_INSTALL_PREFIX}/include/Engine)

message("LightDiagram: ----- ----- ----- ----- -----")
