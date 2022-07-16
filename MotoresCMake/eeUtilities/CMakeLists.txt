#######################################################
#                   Include Files                     #
#######################################################

set(Include_Filter_Names
	"Header Files\\Platform"
)
list(LENGTH Include_Filter_Names INCLUDE_FILT_NAMES_LEN)
message(STATUS "There are ${INCLUDE_FILT_NAMES_LEN} filter names")

set("Header Files\\Platform"

    "include/eeDLLDynamics.h"
    "include/eeFile.h"
    "include/eeLogger.h"
    "include/eeMath.h"
    "include/eeMemoryManager.h"
    "include/eeModule.h"
    "include/eePlatformDefines.h"
    "include/eePlatformMath.h"
    "include/eePlatformTypes.h"
    "include/eePrerequisitesUtilities.h"
    "include/eeSTDHeaders.h"
    "include/eeStringUtilities.h"
    "include/eeTime.h"
)

set(Include_Filterless
	
    "include/eeBox.h"
    "include/eeCapsule.h"
    "include/eeColor.h"
    "include/eeFrustum.h"
    "include/eeMatrix2.h"
    "include/eeMatrix3.h"
    "include/eeMatrix4.h"
    "include/eePlane.h"
    "include/eeQuaternion.h"
    "include/eeRectangle.h"
    "include/eeSphere.h"
    "include/eeTriangle.h"
    "include/eeUtilityCamera.h"
    "include/eeVector2.h"
    "include/eeVector3.h"
    "include/eeVector4.h"
    "include/eeVertex.h"
)

#######################################################
#                    Soruce Files                     #
#######################################################

set(Src_Filter_Names
	"Source Files\\Platform"
)
list(LENGTH Src_Filter_Names SRC_FILT_NAMES_LEN)
message(STATUS "There are ${SRC_FILT_NAMES_LEN} filter names")

set("Source Files\\Platform"

    "src/eeDLLDynamics.cpp"
    "src/eeFile.cpp"
    "src/eeLogger.cpp"
    "src/eeMemoryManager.cpp"
    "src/eePlatformMath.cpp"
    "src/eePlatformMathIndependent.cpp"
    "src/eeStringUtilities.cpp"
    "src/eeTime.cpp"
)

set(Src_Filterless

    "src/eeBox.cpp"
    "src/eeCapsule.cpp"
    "src/eeColor.cpp"
    "src/eeFrustum.cpp"
    "src/eeMatrix2.cpp"
    "src/eeMatrix3.cpp"
    "src/eeMatrix4.cpp"
    "src/eePlane.cpp"
    "src/eeQuaternion.cpp"
    "src/eeRectangle.cpp"
    "src/eeSphere.cpp"
    "src/eeTriangle.cpp"
    "src/eeUtilityCamera.cpp"
    "src/eeVector2.cpp"
    "src/eeVector3.cpp"
    "src/eeVector4.cpp"
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
				
				list(APPEND EE_UTILITIES_PREREQUISITES_INCLUDES ${Include_File})
			endif()
		endforeach()
		
	endif()
endforeach()

list(LENGTH Include_Filterless INCLUDE_FILTERLESS_LEN)
foreach(i RANGE ${INCLUDE_FILTERLESS_LEN})
	if (${i} LESS ${INCLUDE_FILTERLESS_LEN})
		list(GET Include_Filterless ${i} Include_File)
				
		#message(STATUS "Added ${Include_File} to files")
		
		list(APPEND EE_UTILITIES_PREREQUISITES_INCLUDES ${Include_File})
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
				
				list(APPEND EE_UTILITIES_PREREQUISITES_SOURCES ${Src_File})
			endif()
		endforeach()
		
	endif()
endforeach()

list(LENGTH Src_Filterless SRC_FILTERLESS_LEN)
foreach(i RANGE ${SRC_FILTERLESS_LEN})
	if (${i} LESS ${SRC_FILTERLESS_LEN})
		list(GET Src_Filterless ${i} Src_File)
				
		#message(STATUS "Added ${Src_File} to files")
		
		list(APPEND EE_UTILITIES_PREREQUISITES_SOURCES ${Src_File})
	endif()
endforeach()

add_library(eeUtilities SHARED ${EE_UTILITIES_PREREQUISITES_INCLUDES} ${EE_UTILITIES_PREREQUISITES_SOURCES})
add_compile_definitions(EE_UTILITY_EXPORTS)
set_target_properties(eeUtilities PROPERTIES
                      VS_DEBUGGER_WORKING_DIRECTORY ${EE_BINARY_OUTPUT_DIR}
                      OUTPUT_NAME_DEBUG 			eeUtilitiesd
					  OUTPUT_NAME_MINSIZEREL 		eeUtilities
					  OUTPUT_NAME_RELWITHDEBINFO 	eeUtilities
					  OUTPUT_NAME_RELEASE			eeUtilities)
target_include_directories(eeUtilities PUBLIC
                           include) #$(DEVLIBS)Boost)
target_link_directories(eeUtilities PUBLIC
                        ../lib/$(PlatformTarget)/) #$(DEVLIBS)Boost/stage/lib)
#target_link_libraries(eeUtilities PUBLIC cosas_del_boost)
