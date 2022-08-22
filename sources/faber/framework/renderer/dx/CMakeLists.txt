add_subdirectory( src )

add_subdirectory(dx-renderer-context)

if( BUILD_TESTS )
    add_subdirectory( tests )
endif()