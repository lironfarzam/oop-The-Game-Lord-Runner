cmake_minimum_required(VERSION 3.15)
project(OOP_ex5)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
	add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

add_executable(OOP_ex5)

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (images)
add_subdirectory (resources)
add_subdirectory (sound)
add_subdirectory (fonts)


file (COPY images  DESTINATION ${CMAKE_BINARY_DIR})


set (SFML_STATIC_LIBRARIES TRUE)
set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")
configure_file(C:/SFML/SFML-2.5.1/bin/openal32.dll ${CMAKE_BINARY_DIR} COPYONLY)

#set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)


set (SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(OOP_ex5 sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

