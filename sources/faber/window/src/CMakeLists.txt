set( LIB_NAME window)



add_library( faber-${LIB_NAME} STATIC
	window.cpp
)

add_library( fbr::${LIB_NAME} ALIAS faber-${LIB_NAME} )

target_compile_options( faber-${LIB_NAME} PRIVATE ${FABER_COMPILER_FLAGS} )

target_include_directories(
    faber-${LIB_NAME}
    PUBLIC
    ${FABER_INCLUDE_DIRECTORY}/
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

#TODO windows / linux
target_link_libraries( faber-${LIB_NAME}
    PRIVATE
    fbr::framework
    fbr::framework-app-listener
    fbr::framework-window-listener
)

message(STATUS " ___ Analyzing " ${LIB_NAME} " ___ ")
message(STATUS "FABER_INCLUDE_DIRECTORY: " ${FABER_INCLUDE_DIRECTORY})
get_target_property(OUT faber-${LIB_NAME} INCLUDE_DIRECTORIES)
message(STATUS "INCLUDE_DIR: " ${OUT})
get_target_property(OUT faber-${LIB_NAME} LINK_LIBRARIES)
message(STATUS "LINK_LIBRARIES: " ${OUT})
message(STATUS)
