add_executable(mainLauncher
        mainLauncher.cpp
)

# ── Linkage pour le système de composants ────────────────────────────────────────────────────────────
# tout les composants doivent être linkés d'office pour qu'ils s'enregistrent avant le debut du jeu
# et que le ComponentFactory puissent les construire correctement.
if(APPLE)
    # ── macOS (ld) ────────────────────────────────────────────────────────────
    target_link_options(mainLauncher PRIVATE
            -Wl,-force_load,$<TARGET_FILE:lib_engine>
            -Wl,-force_load,$<TARGET_FILE:lib_assets>
    )

elseif(WIN32)
    # ── Windows ───────────────────────────────────────────────────────────────
    if(MSVC)
        # Cas 1 : Visual Studio / MSVC
        target_link_options(mainLauncher PRIVATE
                /WHOLEARCHIVE:$<TARGET_FILE:lib_engine>
                /WHOLEARCHIVE:$<TARGET_FILE:lib_assets>
        )
    elseif(MINGW OR CYGWIN OR CMAKE_COMPILER_IS_GNUCC)
        # Cas 2 : MinGW / GCC sur Windows
        target_link_options(mainLauncher PRIVATE
                -Wl,--whole-archive
                $<TARGET_FILE:lib_engine>
                $<TARGET_FILE:lib_assets>
                -Wl,--no-whole-archive
        )
    endif()

else()
    # ── Linux / Autres (GNU ld / lld) ─────────────────────────────────────────
    target_link_options(mainLauncher PRIVATE
            -Wl,--whole-archive
            $<TARGET_FILE:lib_engine>
            $<TARGET_FILE:lib_assets>
            -Wl,--no-whole-archive
    )
endif()
# ─────────────────────────────────────────────────────────────────────────────────────────────────────


target_link_libraries(mainLauncher PUBLIC lib_engine lib_assets pugixml sfml-graphics)

add_custom_target(copy-resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/src/assets/resources
                ${CMAKE_CURRENT_BINARY_DIR}/resources
        COMMENT "Copying project resources...")
add_dependencies(mainLauncher copy-resources)
