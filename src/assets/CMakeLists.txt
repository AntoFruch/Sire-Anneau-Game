add_library(lib_assets
        scripts/entities/PlayerController.cpp
        scripts/entities/PlayerController.h
        scripts/entities/EntityController.cpp
        scripts/entities/EntityController.h
        scripts/entities/EnemyController.cpp
        scripts/entities/EnemyController.h
        scripts/UI/MainMenu.h
        scripts/UI/MainMenu.cpp
        scripts/UI/PauseMenu.cpp
        scripts/Maps/LoadingZone.h
        scripts/Maps/LoadingZone.cpp
        scripts/Maps/LoadingZoneManager.cpp
        scripts/Maps/LoadingZoneManager.h
        scripts/UI/HUD/HealthBar.cpp
        scripts/UI/HUD/HealthBar.h
        scripts/GameManager.cpp
        scripts/GameManager.h
        scripts/entities/BossController.h
        scripts/entities/BossController.cpp
        scripts/UI/BossHealthBar.cpp
        scripts/UI/BossHealthBar.h
        scripts/Maps/TheaterBehavior.cpp
        scripts/Maps/TheaterBehavior.h

)
target_include_directories(lib_assets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lib_assets PUBLIC lib_engine pugixml sfml-graphics tgui)

