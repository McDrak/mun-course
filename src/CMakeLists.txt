file(GLOB_RECURSE MUN_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(MunGameSource ${MUN_SOURCES})

target_include_directories(MunGameSource PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(MunGameSource PUBLIC sfml-system sfml-window sfml-graphics)
