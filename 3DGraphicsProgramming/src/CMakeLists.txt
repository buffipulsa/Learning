# CMakeList.txt : CMake project for 3DGraphicsProgramming, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (3DGraphicsProgramming "Main.cpp" "Logger/Logger.cpp" )

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(3DGraphicsProgramming PRIVATE SDL3::SDL3)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DGraphicsProgramming PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
