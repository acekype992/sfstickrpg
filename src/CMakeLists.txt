set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SFSTICKRPG_HEADERS sfstickrpg/asset_manager.hpp
                       sfstickrpg/state_manager.hpp
                       sfstickrpg/state.hpp
                       sfstickrpg/game_engine_data.hpp
)

set(SFSTICKRPG_SOURCES sfstickrpg/game.cpp
                       sfstickrpg/asset_manager.cpp
                       sfstickrpg/state_manager.cpp
)

add_executable(sfstickrpg ${SFSTICKRPG_SOURCES} ${SFSTICKRPG_HEADERS})

target_link_libraries(sfstickrpg ${SFML_LIBS})

set_target_properties(sfstickrpg
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/sfstickrpg
)
