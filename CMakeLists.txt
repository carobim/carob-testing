cmake_minimum_required(VERSION 3.7)
project(TsunagariTestingWorld LANGUAGES CXX)

add_subdirectory(Tsunagari)

set(EXE testing)

set(HERE ${CMAKE_CURRENT_LIST_DIR})

add_executable(${EXE}
    ${HERE}/src/ai/ai-wander.cpp
    ${HERE}/src/ai/ai-wander.h
    ${HERE}/src/areas/big-tree.cpp
    ${HERE}/src/areas/big-tree.h
    ${HERE}/src/areas/cave01.cpp
    ${HERE}/src/areas/cave01.h
    ${HERE}/src/areas/grove01.cpp
    ${HERE}/src/areas/grove01.h
    ${HERE}/src/areas/grove04.cpp
    ${HERE}/src/areas/grove04.h
    ${HERE}/src/areas/grove06.cpp
    ${HERE}/src/areas/grove06.h
    ${HERE}/src/areas/grove-house.cpp
    ${HERE}/src/areas/grove-house.h
    ${HERE}/src/areas/secret-room.cpp
    ${HERE}/src/areas/secret-room.h
    ${HERE}/src/world/clouds.cpp
    ${HERE}/src/world/clouds.h
    ${HERE}/src/world/world.cpp
)

include_directories(${TSUNAGARI_INCLUDE_DIRECTORIES} src)
target_link_libraries(${EXE} PRIVATE tsunagari)

if(NOT ${CMAKE_VERSION} VERSION_LESS 3.8.0)
    get_target_property(EXE_SOURCES ${EXE} SOURCES)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/src
        FILES ${EXE_SOURCES}
    )
endif()
