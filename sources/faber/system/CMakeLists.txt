add_subdirectory( src )

#TODO 
add_subdirectory( system-win )

if( BUILD_TESTS )
    add_subdirectory( tests )
endif()