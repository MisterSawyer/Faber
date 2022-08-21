set( LIB_NAME framework )

add_library( faber-${LIB_NAME} STATIC 
	framework.cpp
)

add_library( fbr::${LIB_NAME} ALIAS faber-${LIB_NAME} )
target_compile_options( faber-${LIB_NAME} PRIVATE ${FABER_COMPILER_FLAGS} )

target_include_directories(
    faber-${LIB_NAME}
    PUBLIC
    ${ADDITIONAL_LIBS}/
    ${FABER_INCLUDE_DIRECTORY}/
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# TODO - ogarn¹æ jak grupowaæ ladnie te pliki OBJ
# interface library to s³aby pomys³ trochê :/ 
# https://stackoverflow.com/questions/49265945/cmake-append-objects-from-different-cmakelists-txt-into-one-library

target_link_libraries( faber-${LIB_NAME}
	PUBLIC
   fbr::app
        fbr::framework-app-listener
   fbr::framework-listener
   fbr::input
   fbr::logger
   fbr::macros
   fbr::renderer
        fbr::color
        fbr::renderer-creator
        fbr::dx-renderer
            fbr::dx-renderer-context
                fbr::dx-renderer-context-win
        fbr::opengl-renderer
            fbr::opengl-shader
            fbr::opengl-render-frame
            fbr::opengl-renderer-context
                fbr::opengl-renderer-context-win
        fbr::renderer-context
        fbr::render-frame
        fbr::shader
   fbr::system
        fbr::system-win
   fbr::timer
   fbr::window
        fbr::framework-window-listener
        fbr::window-win
)



message(STATUS " ___ Analyzing " ${LIB_NAME} " ___ ")
message(STATUS "FABER_INCLUDE_DIRECTORY: " ${FABER_INCLUDE_DIRECTORY})
get_target_property(OUT faber-${LIB_NAME} INCLUDE_DIRECTORIES)
message(STATUS "INCLUDE_DIR: " ${OUT})
get_target_property(OUT faber-${LIB_NAME} LINK_LIBRARIES)
message(STATUS "LINK_LIBRARIES: " ${OUT})
message(STATUS)