set(MAPEDITOR_SOURCES mapeditor/mapeditor.cpp)

add_executable(map_editor ${MAPEDITOR_SOURCES})

target_link_libraries(map_editor ${SFML_LIBS} gui)

set_target_properties(map_editor
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/extlib
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
