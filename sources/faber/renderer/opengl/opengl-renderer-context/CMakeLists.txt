add_subdirectory( src )

#TODO if windows
add_subdirectory(opengl-renderer-context-win)


if( BUILD_TESTS )
    add_subdirectory( tests )
endif()