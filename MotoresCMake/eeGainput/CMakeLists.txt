set(EE_GAINPUT_PREREQUISITES_INCLUDES
    "include/eeGainputKeyboardDevice.h"
    "include/eeGaInputManager.h"
    "include/eePrerequisitesGainput.h"
)

set(EE_GAINPUT_PREREQUISITES_SOURCES
    "src/eeGainputKeyboardDevice.cpp"
    "src/eeGaInputManager.cpp"
)

#file(GLOB util_inc include/*.h)
#file(GLOB util_src src/*.cpp)

add_library(eeGainput SHARED ${EE_GAINPUT_PREREQUISITES_INCLUDES} ${EE_GAINPUT_PREREQUISITES_SOURCES})
add_compile_definitions(EE_GAINPUT_EXPORTS)

set_target_properties(eeGainput PROPERTIES
                      VS_DEBUGGER_WORKING_DIRECTORY ${EE_BINARY_OUTPUT_DIR}
                      OUTPUT_NAME_DEBUG 			eeGainputd
					  OUTPUT_NAME_MINSIZEREL 		eeGainput
					  OUTPUT_NAME_RELWITHDEBINFO 	eeGainput
					  OUTPUT_NAME_RELEASE 			eeGainput)
target_include_directories(eeGainput PUBLIC
                           include
						   ../eeUtilities/include
						   ../eeCore/include
						   $ENV{DEVLIBS}/Boost
						   $ENV{DEVLIBS}/Gainput/include
						   )
target_link_directories(eeGainput PUBLIC
                        ../lib/$(PlatformTarget)/
						$ENV{DEVLIBS}/Gainput/lib/$(PlatformTarget)/
						)

list(APPEND LIBRARIES_LINK optimized 	eeUtilities.lib)
list(APPEND LIBRARIES_LINK debug 		eeUtilitiesd.lib)
list(APPEND LIBRARIES_LINK optimized 	eeCore.lib)
list(APPEND LIBRARIES_LINK debug 		eeCored.lib)
list(APPEND LIBRARIES_LINK optimized 	gainput.lib)
list(APPEND LIBRARIES_LINK debug 		gainput-d.lib)

target_link_libraries(eeGainput PUBLIC ${LIBRARIES_LINK})

add_dependencies(eeGainput eeCore)