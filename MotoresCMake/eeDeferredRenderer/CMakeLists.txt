set(EE_DEFERRED_RENDERER_PREREQUISITES_INCLUDES
    "include/eeDeferredRenderer.h"
    "include/eePrerequisitesDeferredRenderer.h"
)

set(EE_DEFERRED_RENDERER_PREREQUISITES_SOURCES
    "src/eeDeferredRenderer.cpp"
)

#file(GLOB util_inc include/*.h)
#file(GLOB util_src src/*.cpp)

add_library(eeDeferredRenderer SHARED ${EE_DEFERRED_RENDERER_PREREQUISITES_INCLUDES} ${EE_DEFERRED_RENDERER_PREREQUISITES_SOURCES})
add_compile_definitions(EE_DEFERRED_RENDERER_EXPORTS)

set_target_properties(eeDeferredRenderer PROPERTIES
                      VS_DEBUGGER_WORKING_DIRECTORY ${EE_BINARY_OUTPUT_DIR}
                      OUTPUT_NAME_DEBUG 			eeDeferredRendererd
					  OUTPUT_NAME_MINSIZEREL 		eeDeferredRenderer
					  OUTPUT_NAME_RELWITHDEBINFO 	eeDeferredRenderer
					  OUTPUT_NAME_RELEASE 			eeDeferredRenderer)
target_include_directories(eeDeferredRenderer PUBLIC
                           include
						   ../eeUtilities/include
						   $ENV{DEVLIBS}/Boost
						   ../eeCore/include)
target_link_directories(eeDeferredRenderer PUBLIC
                        ../lib/$(PlatformTarget)/)

list(APPEND LIBRARIES_LINK optimized 	eeUtilities.lib)
list(APPEND LIBRARIES_LINK debug 		eeUtilitiesd.lib)
list(APPEND LIBRARIES_LINK optimized 	eeCore.lib)
list(APPEND LIBRARIES_LINK debug 		eeCored.lib)
target_link_libraries(eeDeferredRenderer PUBLIC ${LIBRARIES_LINK})

add_dependencies(eeDeferredRenderer eeCore)