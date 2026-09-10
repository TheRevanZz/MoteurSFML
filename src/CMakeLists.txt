cmake_minimum_required(VERSION 3.25.1)

#project(R5A12 LANGUAGES CXX)

include_directories(".")

# Linux: install libsfml-dev package.
find_package(SFML REQUIRED)
#COMPONENTS graphics window system)

add_executable(R5A12 main.cpp)
target_link_libraries(R5A12 sfml::sfml)

add_custom_command(
	TARGET R5A12 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/ressources"
		"$<TARGET_FILE_DIR:R5A12>/ressources"
)

install(TARGETS ${CMAKE_PROJECT_NAME})