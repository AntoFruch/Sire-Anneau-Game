add_executable(mainLauncher
        mainLauncher.cpp
)


target_link_libraries(mainLauncher PUBLIC lib_engine pugixml sfml-graphics)

add_custom_target(copy-resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/src/assets/resources
                ${CMAKE_CURRENT_BINARY_DIR}/resources
        COMMENT "Copying project resources...")
add_dependencies(mainLauncher copy-resources)
