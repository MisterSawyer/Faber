add_subdirectory( src )

add_subdirectory(opengl-renderer-context)
add_subdirectory(opengl-render-frame)
add_subdirectory(opengl-shader)

if( BUILD_TESTS )
    add_subdirectory( tests )
endif()