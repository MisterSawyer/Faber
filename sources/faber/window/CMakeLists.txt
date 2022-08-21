add_subdirectory( src )

#TODO!!!
add_subdirectory( window-win )

add_subdirectory( framework-window-listener )

if( BUILD_TESTS )
    add_subdirectory( tests )
endif()