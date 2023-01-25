set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_custom_target(ackmatrix SOURCES ackmatrix/matrix.hpp)

set(SFSTICKRPG_HEADERS sfstickrpg/Core/game_engine_data.hpp
                       sfstickrpg/Core/asset_manager.hpp
                       sfstickrpg/Core/state_manager.hpp
                       sfstickrpg/Core/state.hpp
                       sfstickrpg/Core/state_game.hpp

                       sfstickrpg/States/game_state_running.hpp

                       sfstickrpg/map.hpp
                       sfstickrpg/tileset.hpp
)

set(SFSTICKRPG_SOURCES sfstickrpg/Core/asset_manager.cpp
                       sfstickrpg/Core/state_manager.cpp
                       sfstickrpg/game.cpp

                       sfstickrpg/States/game_state_running.cpp

                       sfstickrpg/tileset.cpp
)

add_executable(sfstickrpg ${SFSTICKRPG_SOURCES} ${SFSTICKRPG_HEADERS})

target_link_libraries(sfstickrpg ${SFML_LIBS})

set_target_properties(sfstickrpg
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/sfstickrpg
)
