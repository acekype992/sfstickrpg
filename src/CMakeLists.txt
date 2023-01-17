set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(sfstickrpg
    sfstickrpg/main.cpp
)

target_link_libraries(sfstickrpg ${SFML_LIBS})

set_target_properties(stickrpg
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/sfstickrpg
)
