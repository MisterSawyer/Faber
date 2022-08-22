# detect the OS
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(FABER_OS_WINDOWS 1)
	set(FABER_DX 1)
	set(FABER_OPENGL 1)

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(FABER_OS_UNIX 1)
	if(ANDROID)
        set(FABER_OS_ANDROID 1)
    else()
        set(FABER_OS_LINUX 1)
    endif()

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	set(FABER_OS_MACOSX 1)

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	set(FABER_OS_ANDROID 1)
endif()

#os
add_compile_definitions(FABER_OS_WINDOWS=${FABER_OS_WINDOWS})
add_compile_definitions(FABER_OS_UNIX=${FABER_OS_UNIX})
add_compile_definitions(FABER_OS_ANDROID=${FABER_OS_ANDROID})
add_compile_definitions(FABER_OS_LINUX=${FABER_OS_LINUX})
add_compile_definitions(FABER_OS_MACOSX=${FABER_OS_MACOSX})

#Suported renderers
add_compile_definitions(FABER_DX=${FABER_DX})
add_compile_definitions(FABER_OPENGL=${FABER_OPENGL})