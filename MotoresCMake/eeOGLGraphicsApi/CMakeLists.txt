set(EE_OGL_PREREQUISITES_INCLUDES
    "include/eeOGLGraphicsApi.h"
    "include/eeOGLIndexBuffer.h"
    "include/eeOGLPixelShader.h"
    "include/eeOGLSamplerState.h"
    "include/eeOGLTexture.h"
    "include/eeOGLVertexBuffer.h"
    "include/eeOGLVertexShader.h"
    "include/eeOGLWindow.h"
    "include/eePrerequisitesOGL.h"
)

set(EE_OGL_PREREQUISITES_SOURCES
    "src/eeOGLGraphicsApi.cpp"
    "src/eeOGLIndexBuffer.cpp"
    "src/eeOGLPixelShader.cpp"
    "src/eeOGLSamplerState.cpp"
    "src/eeOGLTexture.cpp"
    "src/eeOGLVertexBuffer.cpp"
    "src/eeOGLVertexShader.cpp"
    "src/eeOGLWindow.cpp"
	
	"externals/glad.c"
)

#file(GLOB util_inc include/*.h)
#file(GLOB util_src src/*.cpp)

add_library(eeOGLGraphicsApi SHARED ${EE_OGL_PREREQUISITES_INCLUDES} ${EE_OGL_PREREQUISITES_SOURCES})
add_compile_definitions(EE_PLUGINOGL_EXPORTS)

set_target_properties(eeOGLGraphicsApi PROPERTIES
                      VS_DEBUGGER_WORKING_DIRECTORY ${EE_BINARY_OUTPUT_DIR}
                      OUTPUT_NAME_DEBUG 			eeOGLGraphicsApid
					  OUTPUT_NAME_MINSIZEREL 		eeOGLGraphicsApi
					  OUTPUT_NAME_RELWITHDEBINFO 	eeOGLGraphicsApi
					  OUTPUT_NAME_RELEASE 			eeOGLGraphicsApi)
target_include_directories(eeOGLGraphicsApi PUBLIC
                          include
						  include/externals
						  ../eeUtilities/include
						  ../eeCore/include
						   $ENV{DEVLIBS}/Boost
						   $ENV{DEVLIBS}/OpenGL/GLAD/include
						   $ENV{DEVLIBS}/OpenGL/GLFW/include
						  )
target_link_directories(eeOGLGraphicsApi PUBLIC
                        ../lib/$(PlatformTarget)/
						$ENV{DEVLIBS}/OpenGL/GLFW/lib/$(PlatformTarget)
						)

list(APPEND LIBRARIES_LINK optimized 	eeUtilities.lib)
list(APPEND LIBRARIES_LINK debug 		eeUtilitiesd.lib)
list(APPEND LIBRARIES_LINK optimized 	eeCore.lib)
list(APPEND LIBRARIES_LINK debug 		eeCored.lib)
list(APPEND LIBRARIES_LINK optimized 	glfw3.lib)
list(APPEND LIBRARIES_LINK debug 		glfw3.lib)
list(APPEND LIBRARIES_LINK optimized 	opengl32.lib)
list(APPEND LIBRARIES_LINK debug 		opengl32.lib)

target_link_libraries(eeOGLGraphicsApi PUBLIC ${LIBRARIES_LINK})

add_dependencies(eeOGLGraphicsApi eeCore)