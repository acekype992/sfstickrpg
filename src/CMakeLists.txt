set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(SFSTICKRPG_HEADERS sfstickrpg/GameEngine/game_engine_data.hpp
                       sfstickrpg/GameEngine/asset_manager.hpp
                       sfstickrpg/GameEngine/state_manager.hpp
                       sfstickrpg/GameEngine/state.hpp
                       sfstickrpg/GameEngine/state_game.hpp
)

set(SFSTICKRPG_SOURCES sfstickrpg/GameEngine/asset_manager.cpp
                       sfstickrpg/GameEngine/state_manager.cpp
                       sfstickrpg/game.cpp
                       sfstickrpg/game_state_start.cpp
                       sfstickrpg/game_state_running.cpp
)

add_executable(sfstickrpg ${SFSTICKRPG_SOURCES} ${SFSTICKRPG_HEADERS})

target_link_libraries(sfstickrpg ${SFML_LIBS})

set_target_properties(sfstickrpg
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/sfstickrpg
)
