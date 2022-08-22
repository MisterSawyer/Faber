set( LIB_NAME dx-renderer-context)
set( LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(SRC
     dx-renderer-context.cpp
)

if(FABER_OS_WINDOWS)
    set(PLATFORM_SRC
        ${LIB_DIR}/dx-renderer-context-win/dx-renderer-context-win.cpp
    )
elseif(FABER_OS_UNIX)
    set(PLATFORM_SRC
        ${LIB_DIR}/dx-renderer-context-unix/dx-renderer-context-unix.cpp
    )
endif()

add_library( faber-${LIB_NAME} OBJECT
	${SRC}
    ${PLATFORM_SRC}
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
    d3d11
)