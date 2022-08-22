set( LIB_NAME window)
set( LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(SRC
    window.cpp
    ${LIB_DIR}/framework-window-listener/framework-window-listener.cpp
)

if(FABER_OS_WINDOWS)
    set(PLATFORM_SRC
        ${LIB_DIR}/window-win/window-win.cpp
    )
elseif(FABER_OS_UNIX)
    set(PLATFORM_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/../window-unix/window-unix.cpp
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
    PRIVATE
)

message(STATUS " ___ Analyzing " ${LIB_NAME} " ___ ")
message(STATUS "FABER_FRAMEWORK_INCLUDE_DIRECTORY: " ${FABER_FRAMEWORK_INCLUDE_DIRECTORY})
get_target_property(OUT faber-${LIB_NAME} INCLUDE_DIRECTORIES)
message(STATUS "INCLUDE_DIR: " ${OUT})
get_target_property(OUT faber-${LIB_NAME} LINK_LIBRARIES)
message(STATUS "LINK_LIBRARIES: " ${OUT})
message(STATUS)
