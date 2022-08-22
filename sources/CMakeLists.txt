add_subdirectory(faber)
#add_subdirectory(engine)

 set( EXE_NAME main )

add_executable( faber-${EXE_NAME} WIN32  main.cpp)
add_executable( fbr::${EXE_NAME} ALIAS faber-${EXE_NAME} )
target_compile_options( faber-${EXE_NAME} PRIVATE ${FABER_COMPILER_FLAGS} )

set(INCLUDE_DIR                     "${ADDITIONAL_LIBS}/ ")
set(INCLUDE_DIR ${INCLUDE_DIR}      "${CMAKE_CURRENT_SOURCE_DIR}/ ")
set(INCLUDE_DIR ${INCLUDE_DIR}      "${CMAKE_CURRENT_SOURCE_DIR}/framework ")
set(INCLUDE_DIR ${INCLUDE_DIR}      "${CMAKE_CURRENT_SOURCE_DIR}/engine ")

target_include_directories(
    faber-${EXE_NAME}
    PUBLIC
    ${INCLUDE_DIR}/
)


target_link_libraries( faber-${EXE_NAME}
	PUBLIC
    fbr::framework
)