cmake_minimum_required( VERSION 3.10 )

#-------- project ---------------------------------------------------
project( iv_components )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

if( IVORIUM_PATH )
    message( STATUS "Adding ivorium from directory ${IVORIUM_PATH}" )
    add_subdirectory( "${IVORIUM_PATH}" "ivorium" )
endif()

#-------- binary ----------------------------------------------------
file(
	GLOB_RECURSE cpp_SOURCES
	LIST_DIRECTORIES false
	CONFIGURE_DEPENDS
	"src/*.cpp"
)

add_library( iv_components "${cpp_SOURCES}" )
set_target_properties( iv_components PROPERTIES OUTPUT_NAME iv_components )
target_include_directories( iv_components PUBLIC "src" )
target_compile_options( iv_components PUBLIC "-Werror=undef" )
set_property( TARGET iv_components PROPERTY IVORIUM_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources )

#-------- libraries ----------------------------------------------------
# depends on ivorium
if( NOT TARGET ivorium )
	message( FATAL_ERROR "Target 'ivorium' not found - add the module using add_subdirectory command." )
endif()
target_link_libraries( iv_components PUBLIC ivorium )

# PlayRho
add_subdirectory( libs/PlayRho EXCLUDE_FROM_ALL )
target_link_libraries( iv_components PUBLIC PlayRho )

#------------ documentation -------------------------------------------
# download ivorium tagfile
file( DOWNLOAD "https://ivorne.github.io/ivorium/ivorium.tag" "${CMAKE_CURRENT_BINARY_DIR}/ivorium.tag" )

# create target
set( DOXYBOOT_HTML_HEADER "doxyboot/header.html" )
set( DOXYBOOT_HTML_FOOTER "doxyboot/footer.html" )
set( DOXYGEN_TAGFILES "${CMAKE_CURRENT_BINARY_DIR}/ivorium.tag=https://ivorne.github.io/ivorium/" )
set( DOXYGEN_WARN_IF_UNDOCUMENTED "NO" )
doxyboot_add_docs( iv_components_doc iv_components "src" )
