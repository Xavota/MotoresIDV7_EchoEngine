set(EE_FMOD_PREREQUISITES_INCLUDES
    "include/eeFModAudio.h"
    "include/eeFModAudioManager.h"
    "include/eeFModSound.h"
    "include/eePrerequisitesFMod.h"
)

set(EE_FMOD_PREREQUISITES_SOURCES
    "src/eeFModAudio.cpp"
    "src/eeFModAudioManager.cpp"
    "src/eeFModSound.cpp"
)

#file(GLOB util_inc include/*.h)
#file(GLOB util_src src/*.cpp)

add_library(eeFModAudioApi SHARED ${EE_FMOD_PREREQUISITES_INCLUDES} ${EE_FMOD_PREREQUISITES_SOURCES})
add_compile_definitions(EE_FMOD_AUDIO_API_EXPORTS)

set_target_properties(eeFModAudioApi PROPERTIES
                      VS_DEBUGGER_WORKING_DIRECTORY ${EE_BINARY_OUTPUT_DIR}
                      OUTPUT_NAME_DEBUG 			eeFModAudioApid
					  OUTPUT_NAME_MINSIZEREL 		eeFModAudioApi
					  OUTPUT_NAME_RELWITHDEBINFO 	eeFModAudioApi
					  OUTPUT_NAME_RELEASE 			eeFModAudioApi)
target_include_directories(eeFModAudioApi PUBLIC
                           include
						   ../eeUtilities/include
						   ../eeCore/include
						   $ENV{DEVLIBS}/Boost
						   $ENV{DEVLIBS}/FMod/include
						   )
target_link_directories(eeFModAudioApi PUBLIC
                        ../lib/$(PlatformTarget)/
						$ENV{DEVLIBS}/FMod/lib/$(PlatformTarget)
						)

list(APPEND LIBRARIES_LINK optimized 	eeUtilities.lib)
list(APPEND LIBRARIES_LINK debug 		eeUtilitiesd.lib)
list(APPEND LIBRARIES_LINK optimized 	eeCore.lib)
list(APPEND LIBRARIES_LINK debug 		eeCored.lib)
list(APPEND LIBRARIES_LINK optimized 	fmod_vc.lib)
list(APPEND LIBRARIES_LINK debug 		fmod_vc.lib)
list(APPEND LIBRARIES_LINK optimized 	fmodL_vc.lib)
list(APPEND LIBRARIES_LINK debug 		fmodL_vc.lib)

target_link_libraries(eeFModAudioApi PUBLIC ${LIBRARIES_LINK})

add_dependencies(eeFModAudioApi eeCore)