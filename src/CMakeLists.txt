file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")

add_library(solar_sistem_lib STATIC
    "planet.cpp"
    "player.cpp"
    ${HEADERS}
)

target_include_directories(solar_sistem_lib PRIVATE 
    "${CMAKE_INSTALL_PREFIX}/include/OGRE" 
    "${CMAKE_INSTALL_PREFIX}/include/OGRE/Bites"
    "${CMAKE_INSTALL_PREFIX}/include/OGRE/RTShaderSystem"
    "${CMAKE_SOURCE_DIR}/include"
)
target_link_libraries(solar_sistem_lib PRIVATE OgreBites)

set_property(TARGET solar_sistem_lib PROPERTY CXX_STANDARD 20)