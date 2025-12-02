add_executable(MunGameTest game.cpp)

target_link_libraries(MunGameTest PRIVATE MunGameSource)

configure_file(${PROJECT_SOURCE_DIR}/media/setupAssignmentOne.cfg ${CMAKE_CURRENT_BINARY_DIR}/media/setupAssignmentOne.cfg COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/fonts/tech.ttf ${CMAKE_CURRENT_BINARY_DIR}/fonts/tech.ttf COPYONLY)
