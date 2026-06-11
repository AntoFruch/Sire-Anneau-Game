add_library(lib_assets
        scripts/entities/PlayerController.cpp
        scripts/entities/PlayerController.h
        scripts/entities/EntityController.cpp
        scripts/entities/EntityController.h
        scripts/UI/MainMenu.h
        scripts/UI/MainMenu.cpp
        scripts/UI/PauseMenu.cpp
        scripts/Maps/LoadingZone.h
        scripts/Maps/LoadingZone.cpp
        scripts/Maps/LoadingZoneManager.cpp
        scripts/Maps/LoadingZoneManager.h
        scripts/entities/EnemyController.h
        scripts/entities/EnemyController.h
        scripts/entities/EnemyController.cpp
)
target_include_directories(lib_assets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lib_assets PUBLIC lib_engine pugixml sfml-graphics tgui)

