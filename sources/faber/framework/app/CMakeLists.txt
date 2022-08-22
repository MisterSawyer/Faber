add_subdirectory( src )

add_subdirectory( framework-app-listener )


if( BUILD_TESTS )
    add_subdirectory( tests )
endif()