set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CORE_SOURCES core/asset_manager.cpp
                 core/asset_manager.cpp
                 core/state_manager.cpp

                 core/game_engine_data.hpp
                 core/asset_manager.hpp
                 core/state_manager.hpp
                 core/state.hpp
                 core/state_game.hpp
)

set(GRAPHICS_SOURCES graphics/tileset.cpp
                     graphics/map.cpp
                     graphics/tileset.hpp
                     graphics/map.hpp
)

set(GAME_SOURCES game/game.cpp)

add_executable(sfstickrpg ${CORE_SOURCES}
                          ${GRAPHICS_SOURCES}
                          ${GAME_SOURCES}
)

target_link_libraries(sfstickrpg ${SFML_LIBS})

set_target_properties(sfstickrpg
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/extlib
)


add_subdirectory(tools)

target_sources(map_editor PRIVATE ${CORE_SOURCES} ${GRAPHICS_SOURCES})
