#/**********************************************************\ 
# 
# Auto-generated CMakeLists.txt for the TagLib Audio Meta-Data Library project
#
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

Project(${PLUGIN_NAME})

include(ExternalProject)

file (GLOB GENERAL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    [^.]*.cmake
    )

include_directories(${PLUGIN_INCLUDE_DIRS})

# Generated files are stored in ${GENERATED} by the project configuration
SET_SOURCE_FILES_PROPERTIES(
    ${GENERATED}
    PROPERTIES
        GENERATED 1
    )

SOURCE_GROUP(Generated FILES
    ${GENERATED}
    )

SET( SOURCES
    ${GENERAL}
    ${GENERATED}
    )

# This will include Win/projectDef.cmake, X11/projectDef.cmake, Mac/projectDef 
# depending on the platform
include_platform()

#this will build a Chrome package
#add_chrome_package(${PLUGIN_NAME}
#	${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/ 
#	"${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll"
#	"${CMAKE_CURRENT_SOURCE_DIR}/sign/package_key.pem"
#	${PROJECT_NAME})

#this will build a XPI package using XPISigner (see http://code.google.com/p/xpisigner/ )
# add_signed_xpi_installer(${PLUGIN_NAME}
# 	${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/ 
#   "${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll"
# 	$ENV{XPI_PATH} 
# 	"${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx" 
# 	"${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
# 	${PROJECT_NAME})

# add TagLib C++ library
set(TagLibCpp_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/TagLibCpp)
string(REPLACE ";" " " VALUE_CMAKE_OSX_ARCHITECTURES "${CMAKE_OSX_ARCHITECTURES}")
ExternalProject_Add(
    TagLibCpp_external
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/taglib
    CMAKE_ARGS -DBUILD_FRAMEWORK=ON
               -DCMAKE_BUILD_TYPE=Release
               -DENABLE_STATIC=ON
               -DBUILD_EXAMPLES=OFF
               -DCMAKE_INSTALL_PREFIX=${TagLibCpp_LOCATION}
               -DCMAKE_OSX_ARCHITECTURES=${VALUE_CMAKE_OSX_ARCHITECTURES}
)
add_library(TagLibCpp UNKNOWN IMPORTED)
set_property(TARGET TagLibCpp PROPERTY IMPORTED_LOCATION ${TagLibCpp_LOCATION}/lib/libtag.a)
add_dependencies(TagLibCpp TagLibCpp_external)
set(TagLibCpp_INCLUDE_DIRS ${TagLibCpp_LOCATION}/include)
set(TagLibCpp_LIBRARIES TagLibCpp)

# Link TagLib C++ library
include_directories(${TagLibCpp_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${TagLibCpp_LIBRARIES} -lz)

add_subdirectory(tests/cpp)
