cmake_minimum_required( VERSION 3.10 )

#-------- project ---------------------------------------------------
project( iv_components )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

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
	message( SEND_ERROR "Target 'ivorium' not found (add the module ivorium using add_subdirectory)." )
endif()
target_link_libraries( iv_components PUBLIC ivorium )

# PlayRho
add_subdirectory( libs/PlayRho EXCLUDE_FROM_ALL )
target_link_libraries( iv_components PUBLIC PlayRho )
