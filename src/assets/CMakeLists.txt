add_library(lib_assets
        scripts/entities/PlayerController.cpp
        scripts/entities/PlayerController.h
        scripts/entities/EntityController.cpp
        scripts/entities/EntityController.h
        scripts/UI/MainMenuUI.h
        scripts/UI/MainMenuUI.cpp
)
target_include_directories(lib_assets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lib_assets PUBLIC lib_engine pugixml sfml-graphics)

