set( LIB_NAME renderer-creator)

add_library( faber-${LIB_NAME} OBJECT
	renderer-creator.cpp
)

add_library( fbr::${LIB_NAME} ALIAS faber-${LIB_NAME} )

target_compile_options( faber-${LIB_NAME} PRIVATE ${FABER_COMPILER_FLAGS} )

target_include_directories(
    faber-${LIB_NAME}
    PUBLIC
    ${ADDITIONAL_LIBS}/
    ${FABER_FRAMEWORK_INCLUDE_DIRECTORY}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_link_libraries( faber-${LIB_NAME}
    PUBLIC

)


message(STATUS " ___ Analyzing " ${LIB_NAME} " ___ ")
message(STATUS "FABER_FRAMEWORK_INCLUDE_DIRECTORY: " ${FABER_FRAMEWORK_INCLUDE_DIRECTORY})
get_target_property(OUT faber-${LIB_NAME} INCLUDE_DIRECTORIES)
message(STATUS "INCLUDE_DIR: " ${OUT})
get_target_property(OUT faber-${LIB_NAME} LINK_LIBRARIES)
message(STATUS "LINK_LIBRARIES: " ${OUT})
message(STATUS)