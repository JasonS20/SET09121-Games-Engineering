project(Awakening)
cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")


add_subdirectory("lib/box2d")
set(B2D_INCS "lib/box2d/include")
link_directories("${CMAKE_BINARY_DIR}/lib/box2d/lib")

#### Engine ####
add_library(engine STATIC  engine/game_system.cpp
                        engine/renderer.cpp
                        engine/physics.cpp
                        )
target_include_directories(engine INTERFACE engine)
target_link_libraries(engine sfml-graphics)

#### executable ####
add_executable(Awakening 
    main.cpp
    scenes.cpp
    b2d_utils.cpp
    )
target_include_directories(Awakening PRIVATE ${SFML_INCS} ${B2D_INCS} engine)
target_link_libraries(Awakening sfml-graphics  engine box2d)
set_target_properties(Awakening 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/resources"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
)
add_dependencies(Awakening copy_resources)

# Copy Box2D DLL next to Awakening.exe after build
add_custom_command(TARGET Awakening POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:box2d>
        $<TARGET_FILE_DIR:Awakening>
)

# Copy SFML DLLs next to Awakening.exe
add_custom_command(TARGET Awakening POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE_DIR:Awakening>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE_DIR:Awakening>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:Awakening>
)