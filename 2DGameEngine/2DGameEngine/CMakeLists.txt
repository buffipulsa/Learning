# CMakeList.txt : CMake project for 2DGameEngine, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (2DGameEngine "2DGameEngine.cpp" "2DGameEngine.h" "Game.h" "Game.cpp" "Logger.h" "Logger.cpp")

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(2DGameEngine PRIVATE SDL3::SDL3)

find_package(SDL3_image CONFIG REQUIRED)
target_link_libraries(2DGameEngine PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)

find_package(SDL3_ttf CONFIG REQUIRED)
target_link_libraries(2DGameEngine PRIVATE SDL3_ttf::SDL3_ttf)

find_package(glm CONFIG REQUIRED)
target_link_libraries(2DGameEngine PRIVATE glm::glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(2DGameEngine PRIVATE imgui::imgui)

find_package(Lua REQUIRED)
target_include_directories(2DGameEngine PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(2DGameEngine PRIVATE ${LUA_LIBRARIES})

find_path(SOL2_INCLUDE_DIRS "sol/abort.hpp")
target_include_directories(2DGameEngine PRIVATE ${SOL2_INCLUDE_DIRS})

target_compile_definitions(2DGameEngine PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 2DGameEngine PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
