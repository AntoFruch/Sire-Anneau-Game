add_library(lib_assets
        scripts/entities/PlayerController.cpp
        scripts/entities/PlayerController.h
        scripts/entities/EntityController.cpp
        scripts/entities/EntityController.h
        scripts/UI/MainMenu.h
        scripts/UI/MainMenu.cpp
        scripts/UI/PauseMenu.cpp
        scripts/HUD/HealthBar.cpp
        scripts/HUD/HealthBar.h
        scripts/HUD/HUDManager.cpp
        scripts/HUD/HUDManager.h
)
target_include_directories(lib_assets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lib_assets PUBLIC lib_engine pugixml sfml-graphics tgui)

