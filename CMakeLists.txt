# Basic parameters; check that these match your project / environment
cmake_minimum_required(VERSION 3.9)

OPTION(DISABLE_READ_ONLY_SURFACES "Disable Readonly Surfaces" OFF) # Enabled by default

# Replace "game" with a name for your project (this is used the name of the output)
project(Waternet)

IF(DISABLE_READ_ONLY_SURFACES)
    ADD_DEFINITIONS(-DDISABLE_READ_ONLY_SURFACES)
ENDIF(DISABLE_READ_ONLY_SURFACES)

# Add your sources here (adding headers is optional, but helps some CMake generators)
set(PROJECT_SOURCE waternet.cpp intro.cpp commonvars.cpp palettes.cpp palettedefines.cpp 
  printfuncs.cpp helperfuncs.cpp savestate.cpp level.cpp titlescreen.cpp sound.cpp
  helpscreens.cpp cursor.cpp levelselect.cpp game.cpp levelscleared.cpp)

# ... and any other files you want in the release here
set(PROJECT_DISTRIBS LICENSE README.md)

# Build configuration; approach this with caution!
if(MSVC)
  add_compile_options("/W4" "/wd4244" "/wd4324" "/wd4458" "/wd4100")
else()
  add_compile_options("-Wall" "-Wextra" "-Wdouble-promotion" "-Wno-unused-parameter")
endif()

find_package (32BLIT CONFIG REQUIRED PATHS ../32blit-sdk $ENV{PATH_32BLIT_SDK})

blit_executable (${PROJECT_NAME} ${PROJECT_SOURCE})
blit_assets_yaml (${PROJECT_NAME} assets.yml)
blit_metadata (${PROJECT_NAME} metadata.yml)
add_custom_target (flash DEPENDS ${PROJECT_NAME}.flash)

# setup release packages
install (FILES ${PROJECT_DISTRIBS} DESTINATION .)
set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set (CPACK_GENERATOR "ZIP" "TGZ")
include (CPack)
