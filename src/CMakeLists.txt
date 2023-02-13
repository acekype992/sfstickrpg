set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_SOURCE_DIR}/extlib)

set(CORE_SOURCES
        core/asset_manager.cpp
        core/asset_manager.hpp
        core/eventHandling.cpp
        core/eventHandling.hpp

        core/notcopyable.hpp
        core/observerptr.hpp
)
add_library(core STATIC ${CORE_SOURCES})
target_link_libraries(core ${SFML_LIBS})



set(GRAPHICS_SOURCES
        graphics/drawable.cpp
        graphics/drawable.hpp
        graphics/tileset_base.cpp
        graphics/tileset_base.hpp
        graphics/tileset.cpp
        graphics/tileset.hpp
        graphics/map_base.cpp
        graphics/map_base.hpp
        graphics/map.cpp
        graphics/map.hpp
)
add_library(graphics STATIC ${GRAPHICS_SOURCES})
target_link_libraries(graphics core)



set(GUI_SOURCES
        gui/widget.cpp
        gui/widget.hpp
        gui/tilesetWidget.cpp
        gui/tilesetWidget.hpp
)
add_library(gui STATIC ${GUI_SOURCES})
target_link_libraries(gui graphics core)



#set(GAME_SOURCES game/game.cpp)

#add_executable(sfstickrpg ${CORE_SOURCES}
#                          ${GRAPHICS_SOURCES}
#                          ${GAME_SOURCES}
#)

#target_link_libraries(sfstickrpg ${SFML_LIBS})

#set_target_properties(sfstickrpg
#    PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
#    INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/extlib
#)


add_subdirectory(tools)

#target_sources(map_editor PRIVATE ${CORE_SOURCES} ${GRAPHICS_SOURCES})
