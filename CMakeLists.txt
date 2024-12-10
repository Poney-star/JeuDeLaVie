# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.28)

# Nom du projet et langue utilisée
project(PigFarm LANGUAGES CXX)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Trouver SFML
include(FetchContent)
FetchContent_Declare(SFML
GIT_REPOSITORY https://github.com/SFML/SFML.git
GIT_TAG 2.6.x
GIT_SHALLOW ON
EXCLUDE_FROM_ALL
SYSTEM)
FetchContent_MakeAvailable(SFML)

# Inclure les répertoires
include_directories(include)

# Ajouter les fichiers source
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Ajouter les fichiers d'en-tête
file(GLOB_RECURSE HEADERS
    include/*.hpp
)

# Ajouter l'exécutable
add_executable(PigFarm WIN32 ${SOURCES} ${HEADERS} include/icon.o)

# Lier SFML aux cibles
target_link_libraries(PigFarm PRIVATE sfml-system sfml-window sfml-graphics)
target_compile_features(PigFarm PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET PigFarm
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PigFarm>
        VERBATIM
    )
endif()