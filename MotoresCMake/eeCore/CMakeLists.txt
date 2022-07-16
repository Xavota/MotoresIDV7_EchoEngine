#######################################################
#                   Include Files                     #
#######################################################

set(Include_Filter_Names
	"Header Files\\Audio"
	"Header Files\\Externals"
	"Header Files\\Graphics"
	"Header Files\\Inputs"
	"Header Files\\Platform"
	"Header Files\\Renderer"
	"Header Files\\Resources"
	"Header Files\\SceneGraph\\Components"
	"Header Files\\SceneGraph"
)
list(LENGTH Include_Filter_Names INCLUDE_FILT_NAMES_LEN)
message(STATUS "There are ${INCLUDE_FILT_NAMES_LEN} filter names")

set("Header Files\\Audio"

	"include/eeAudio.h"
	"include/eeAudioManager.h"
	"include/eeSound.h"
)

set("Header Files\\Externals"

	"externals/stb_image.h"
)

set("Header Files\\Graphics"

	"include/eeBlendState.h"
	"include/eeBuffer.h"
	"include/eeConstantBuffer.h"
	"include/eeDepthStencilState.h"
	"include/eeGraficsApi.h"
	"include/eeIndexBuffer.h"
	"include/eeInputLayout.h"
	"include/eePixelShader.h"
	"include/eeRasterizerState.h"
	"include/eeSamplerState.h"
	"include/eeTexture.h"
	"include/eeVertexBuffer.h"
	"include/eeVertexShader.h"
)

set("Header Files\\Inputs"

	"include/eeEvent.h"
	"include/eeGamepadDevice.h"
	"include/eeInputDevice.h"
	"include/eeInputDeviceEvent.h"
	"include/eeInputManager.h"
	"include/eeKeyboardDevice.h"
	"include/eeMouseDevice.h"
)

set("Header Files\\Platform"

	"include/eeCoreConfiguration.h"
	"include/eeCoreDefines.h"
	"include/eePrerequisitesCore.h"
)

set("Header Files\\Renderer"

	"include/eeRenderer.h"
)

set("Header Files\\Resources"

	"include/eeAnimation.h"
	"include/eeBoneMesh.h"
	"include/eeImage.h"
	"include/eeMaterial.h"
	"include/eeMesh.h"
	"include/eeResourceManager.h"
	"include/eeSkeletal.h"
	"include/eeSkeletalMesh.h"
	"include/eeStaticMesh.h"
)

set("Header Files\\SceneGraph\\Components"

    "include/eeCAnimation.h"
    "include/eeCBounds.h"
    "include/eeCCamera.h"
    "include/eeCLight.h"
    "include/eeComponent.h"
    "include/eeCRender.h"
    "include/eeCSkeletalMesh.h"
    "include/eeCStaticMesh.h"
    "include/eeCTransform.h"
)

set("Header Files\\SceneGraph"

    "include/eeActor.h"
    "include/eeOctree.h"
    "include/eeOctreeNode.h"
    "include/eeScene.h"
    "include/eeSceneManager.h"
)

set(Include_Filterless

    "include/eeBaseApp.h"
    "include/eeInput.h"
    "include/eeWindow.h"
)

#######################################################
#                    Soruce Files                     #
#######################################################

set(Src_Filter_Names
	"Source Files\\Audio"
	"Source Files\\Graphics"
	"Source Files\\Inputs"
	"Source Files\\Renderer"
	"Source Files\\Resources"
	"Source Files\\SceneGraph\\Components"
	"Source Files\\SceneGraph"
)
list(LENGTH Src_Filter_Names SRC_FILT_NAMES_LEN)
message(STATUS "There are ${SRC_FILT_NAMES_LEN} filter names")

set("Source Files\\Audio"

	"src/eeAudio.cpp"
	"src/eeAudioManager.cpp"
	"src/eeSound.cpp"
)

set("Source Files\\Graphics"

	"src/eeBlendState.cpp"
	"src/eeBuffer.cpp"
	"src/eeConstantBuffer.cpp"
	"src/eeDepthStencilState.cpp"
	"src/eeGraficsApi.cpp"
	"src/eeIndexBuffer.cpp"
	"src/eeInputLayout.cpp"
	"src/eePixelShader.cpp"
	"src/eeRasterizerState.cpp"
	"src/eeSamplerState.cpp"
	"src/eeTexture.cpp"
	"src/eeVertexBuffer.cpp"
	"src/eeVertexShader.cpp"
)

set("Source Files\\Inputs"

	"src/eeEvent.cpp"
	"src/eeGamepadDevice.cpp"
	"src/eeInputDevice.cpp"
	"src/eeInputDeviceEvent.cpp"
	"src/eeInputManager.cpp"
	"src/eeKeyboardDevice.cpp"
	"src/eeMouseDevice.cpp"
)

set("Source Files\\Renderer"

	"src/eeRenderer.cpp"
)

set("Source Files\\Resources"

	"src/eeAnimation.cpp"
	"src/eeBoneMesh.cpp"
	"src/eeImage.cpp"
	"src/eeMaterial.cpp"
	"src/eeMesh.cpp"
	"src/eeResourceManager.cpp"
	"src/eeSkeletal.cpp"
	"src/eeSkeletalMesh.cpp"
	"src/eeStaticMesh.cpp"
)

set("Source Files\\SceneGraph\\Components"

    "src/eeCAnimation.cpp"
    "src/eeCBounds.cpp"
    "src/eeCCamera.cpp"
    "src/eeCLight.cpp"
    "src/eeComponent.cpp"
    "src/eeCRender.cpp"
    "src/eeCSkeletalMesh.cpp"
    "src/eeCStaticMesh.cpp"
    "src/eeCTransform.cpp"
)

set("Source Files\\SceneGraph"

    "src/eeActor.cpp"
    "src/eeOctree.cpp"
    "src/eeOctreeNode.cpp"
    "src/eeScene.cpp"
    "src/eeSceneManager.cpp"
)

set(Src_Filterless

    "src/eeBaseApp.cpp"
    "src/eeInput.cpp"
    "src/eeWindow.cpp"
)

#######################################################
#                Add files to filters                 #
#######################################################

#file(GLOB util_inc include/*.h)
#file(GLOB util_src src/*.cpp)

foreach(i RANGE ${INCLUDE_FILT_NAMES_LEN})
	if (${i} LESS ${INCLUDE_FILT_NAMES_LEN})
		list(GET Include_Filter_Names ${i} Include_Filt_Key)
		list(LENGTH ${Include_Filt_Key} INCLUDE_FILT_LEN)
		
		message(STATUS "There are ${INCLUDE_FILT_LEN} Items in ${Include_Filt_Key}")
		
		foreach(j RANGE ${INCLUDE_FILT_LEN})
			if (${j} LESS ${INCLUDE_FILT_LEN})
				list(GET ${Include_Filt_Key} ${j} Include_File)
				source_group(${Include_Filt_Key} FILES "${Include_File}")
				
				#message(STATUS "Added ${Include_File} to ${Include_Filt_Key} filter")
				
				list(APPEND EE_CORE_PREREQUISITES_INCLUDES ${Include_File})
			endif()
		endforeach()
		
	endif()
endforeach()

list(LENGTH Include_Filterless INCLUDE_FILTERLESS_LEN)
foreach(i RANGE ${INCLUDE_FILTERLESS_LEN})
	if (${i} LESS ${INCLUDE_FILTERLESS_LEN})
		list(GET Include_Filterless ${i} Include_File)
				
		#message(STATUS "Added ${Include_File} to files")
		
		list(APPEND EE_CORE_PREREQUISITES_INCLUDES ${Include_File})
	endif()
endforeach()

foreach(i RANGE ${SRC_FILT_NAMES_LEN})
	if (${i} LESS ${SRC_FILT_NAMES_LEN})
		list(GET Src_Filter_Names ${i} Src_Filt_Key)
		list(LENGTH ${Src_Filt_Key} SRC_FILT_LEN)
		
		message(STATUS "There are ${SRC_FILT_LEN} Items in ${Src_Filt_Key}")
		
		foreach(j RANGE ${SRC_FILT_LEN})
			if (${j} LESS ${SRC_FILT_LEN})
				list(GET ${Src_Filt_Key} ${j} Src_File)
				source_group(${Src_Filt_Key} FILES "${Src_File}")
				
				#message(STATUS "Added ${Src_File} to ${Src_Filt_Key} filter")
				
				list(APPEND EE_CORE_PREREQUISITES_SOURCES ${Src_File})
			endif()
		endforeach()
		
	endif()
endforeach()

list(LENGTH Src_Filterless SRC_FILTERLESS_LEN)
foreach(i RANGE ${SRC_FILTERLESS_LEN})
	if (${i} LESS ${SRC_FILTERLESS_LEN})
		list(GET Src_Filterless ${i} Src_File)
				
		#message(STATUS "Added ${Src_File} to files")
		
		list(APPEND EE_CORE_PREREQUISITES_SOURCES ${Src_File})
	endif()
endforeach()

add_library(eeCore SHARED ${EE_CORE_PREREQUISITES_INCLUDES} ${EE_CORE_PREREQUISITES_SOURCES})



add_compile_definitions(EE_CORE_EXPORTS)

set_target_properties(eeCore PROPERTIES
                      VS_DEBUGGER_WORKING_DIRECTORY ${EE_BINARY_OUTPUT_DIR}
                      OUTPUT_NAME_DEBUG 			eeCored
					  OUTPUT_NAME_MINSIZEREL 		eeCore
					  OUTPUT_NAME_RELWITHDEBINFO 	eeCore
					  OUTPUT_NAME_RELEASE 			eeCore)
target_include_directories(eeCore PUBLIC
                           include
                           include/externals
						   ../eeUtilities/include
						   $ENV{DEVLIBS}/Assimp/include
						   $ENV{DEVLIBS}/Boost
						   $ENV{DEVLIBS}/LUA/include
						   $ENV{DEVLIBS}/Sol/include)
target_link_directories(eeCore PUBLIC
                        ../lib/$(PlatformTarget)/
						$ENV{DEVLIBS}/Assimp/lib/$(PlatformTarget)/
						$ENV{DEVLIBS}/LUA/lib/$(PlatformTarget)/)

list(APPEND LIBRARIES_LINK optimized 	eeUtilities.lib)
list(APPEND LIBRARIES_LINK debug 		eeUtilitiesd.lib)
list(APPEND LIBRARIES_LINK optimized 	assimp-vc142-mt.lib)
list(APPEND LIBRARIES_LINK debug 		assimp-vc142-mtd.lib)
list(APPEND LIBRARIES_LINK optimized 	LUATest.lib)
list(APPEND LIBRARIES_LINK debug 		LUATestd.lib)

target_link_libraries(eeCore PUBLIC ${LIBRARIES_LINK})

add_dependencies(eeCore eeUtilities)