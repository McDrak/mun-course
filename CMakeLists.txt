cmake_minimum_required(VERSION 3.25)
project(MunGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

fetchcontent_declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 3.0.1
)
fetchcontent_makeavailable(SFML)

add_subdirectory(src)
add_subdirectory(test)
