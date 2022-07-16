cmake_minimum_required(VERSION 3.12.0)


if (CMAKE_GENERATOR STREQUAL "Ninja")
	check_cxx_compiler_flag("-fdiagnostics-color=always" F_DIAGNOSTIC_COLOR_ALWAYS)
	if (F_DIAGNOSTIC_COLOR_ALWAYS)
		add_compile_options(-fdiagnostics-color=always)
	endif()
endif()

find_path(UTILITIES_SUBMODULE_SOURCE "eeUtilities/include/eePrerequisitesUtilities.h")
if (NOT UTILITIES_SUBMODULE_SOURCE)
	
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/heads/master.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

endif()



set(EE_ENABLE_EXCEPTIONS OFF CACHE BOOL "If true C++ Exceptions will be enabled when compiling.")
set(EE_ENABLE_RTTI OFF CACHE BOOL "If true C++ rtti will be enabled.")

#Crear Proyecto (Solucion)
project(eeEngineSDK)

#Especificamos el standard de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EESDK_MAIN_DIR			${PROJECT_SOURCE_DIR})
set(EE_BINARY_OUTPUT_DIR	${EESDK_MAIN_DIR}/bin)
set(EE_LIBRARY_OUTPUT_DIR	${EESDK_MAIN_DIR}/lib/$(PlatformTarget))

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG			${EE_BINARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL		${EE_BINARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO	${EE_BINARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE			${EE_BINARY_OUTPUT_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG			${EE_LIBRARY_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL		${EE_LIBRARY_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO	${EE_LIBRARY_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE			${EE_LIBRARY_OUTPUT_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG			${EE_LIBRARY_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL		${EE_LIBRARY_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO	${EE_LIBRARY_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE			${EE_LIBRARY_OUTPUT_DIR})

if(WIN32)
	add_compile_options(/W4)
endif()

if (MSVC AND NOT EE_ENABLE_EXCEPTIONS)
	if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
		string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif()
	
	#if(CMAKE_CXX_FLAGS MATCHES "_UNICODE")
	#	string(REPLACE " _UNICODE" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	#endif()
	#if(CMAKE_CXX_FLAGS MATCHES "UNICODE")
	#	string(REPLACE " UNICODE" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	#endif()
	#
	#if(CMAKE_CXX_FLAGS MATCHES "_MBCS")
	#	string(REPLACE "_MBCS" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	#endif()
	#if(CMAKE_CXX_FLAGS MATCHES "MBCS")
	#	string(REPLACE "MBCS" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	#endif()
endif()


if(MSVC)
    if(NOT EE_ENABLE_RTTI)
		string(REPLACE "/GR" "/GR-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif()
endif()

#if(MSVC)
#    if(NOT EE_ENABLE_RTTI)
#        target_compile_options(eeUtilities PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/GR->)
#    endif()
#elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
#    if(NOT BSF_ENABLE_EXCEPTIONS)
#        target_compile_options(eeUtilities PUBLIC -fno-exceptions)
#    endif()
#    if(NOT EE_ENABLE_RTTI)
#        target_compile_options(eeUtilities PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>)
#    endif()
#elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#    if(NOT EE_ENABLE_RTTI)
#        target_compile_options(eeUtilities PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>)
#    endif()
#else()
##TODO_OTHER_COMPILERS_GO_HERE
#endif()


add_subdirectory(eeUtilities)
add_subdirectory(eeUtilities_UnitTest)
add_subdirectory(eeCore)
add_subdirectory(DX11GraphicsApi)
add_subdirectory(eeDeferredRenderer)
add_subdirectory(eeGainput)
add_subdirectory(eeOGLGraphicsApi)
add_subdirectory(FModAudioApi)