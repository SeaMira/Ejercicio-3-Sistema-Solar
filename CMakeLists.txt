cmake_minimum_required(VERSION 3.20)

project(solar_system_ogre_sln CXX)

# Ogre CMakeLists.txt file will build its dependencies at 'cmake configure time', which means,
# configuring it for the first time will take a few minutes.
add_subdirectory("extern/ogre")
add_subdirectory("src")

add_executable(solar_system
    "main.cpp"
)

set(INCLUDES "include")

set_property(TARGET solar_system PROPERTY CXX_STANDARD 20)

# we are using ogre headers from the install directory, so you need to build and install ogre
# targets before building solar_system.
target_include_directories(solar_system PRIVATE 
    "${CMAKE_INSTALL_PREFIX}/include/OGRE"
    "${CMAKE_INSTALL_PREFIX}/include/OGRE/Bites"
    "${CMAKE_INSTALL_PREFIX}/include/OGRE/RTShaderSystem"
    ${INCLUDES}
)

target_link_libraries(solar_system PRIVATE
    OgreBites
    solar_sistem_lib
)

# installing all build files
install(TARGETS solar_system
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT solar_system_Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT solar_system_Runtime
        NAMELINK_COMPONENT solar_system_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT solar_system_Development
)

# installing assets folder
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

# When executing the exe from visual studio, we the install directory as the working directory,
# this is to find the asset folder. We need to run the install target before hand se the asset
# folder is placed there.
set_target_properties( solar_system
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin
)