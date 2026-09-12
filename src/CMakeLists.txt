cmake_minimum_required(VERSION 3.31.12)

#project(R5A12 LANGUAGES CXX)


# Linux: install libsfml-dev package.
find_package(SFML REQUIRED)
#COMPONENTS graphics window system)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "./*.cpp" "./*.h" "./*.hpp")

add_executable(R5A12 ${SOURCES})

target_link_libraries(R5A12 sfml::sfml)

target_include_directories(R5A12 PRIVATE 
		"." 
		"Class" 
		"Macro" 
		"ressources"
)

add_custom_command(
	TARGET R5A12 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/ressources"
		"$<TARGET_FILE_DIR:R5A12>/ressources"
)

install(TARGETS ${CMAKE_PROJECT_NAME})