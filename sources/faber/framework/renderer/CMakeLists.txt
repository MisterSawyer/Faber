add_subdirectory( src )
add_subdirectory( color )
add_subdirectory( creator )
add_subdirectory( render-frame )

#todo choose renderer
add_subdirectory( dx )
add_subdirectory( opengl )

add_subdirectory( renderer-context )
add_subdirectory( shader )


if( BUILD_TESTS )
    add_subdirectory( tests )
endif()