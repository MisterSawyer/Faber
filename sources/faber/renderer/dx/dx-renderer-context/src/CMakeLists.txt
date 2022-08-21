set( LIB_NAME dx-renderer-context)

add_library( faber-${LIB_NAME} STATIC
	 dx-renderer-context.cpp
)

add_library( fbr::${LIB_NAME} ALIAS faber-${LIB_NAME} )

target_compile_options( faber-${LIB_NAME} PRIVATE ${FABER_COMPILER_FLAGS} )

target_include_directories(
    faber-${LIB_NAME}
    PUBLIC
        ${ADDITIONAL_LIBS}/
    ${FABER_INCLUDE_DIRECTORY}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_link_libraries( faber-${LIB_NAME}
    PUBLIC
   d3d11
   fbr::dx-renderer-context-win
)
