set(EE_DX11_PREREQUISITES_INCLUDES
    "include/eeDX11BlendState.h"
    "include/eeDX11ConstantBuffer.h"
    "include/eeDX11DepthStencilState.h"
    "include/eeDX11GraphicsApi.h"
    "include/eeDX11IndexBuffer.h"
    "include/eeDX11PixelShader.h"
    "include/eeDX11RasterizerState.h"
    "include/eeDX11SamplerState.h"
    "include/eeDX11Texture.h"
    "include/eeDX11VertexBuffer.h"
    "include/eeDX11VertexShader.h"
    "include/eeDX11Window.h"
    "include/eePrerequisitesDX11.h"
)

set(EE_DX11_PREREQUISITES_SOURCES
    "src/eeDX11BlendState.cpp"
    "src/eeDX11ConstantBuffer.cpp"
    "src/eeDX11DepthStencilState.cpp"
    "src/eeDX11GraphicsApi.cpp"
    "src/eeDX11IndexBuffer.cpp"
    "src/eeDX11PixelShader.cpp"
    "src/eeDX11RasterizerState.cpp"
    "src/eeDX11SamplerState.cpp"
    "src/eeDX11Texture.cpp"
    "src/eeDX11VertexBuffer.cpp"
    "src/eeDX11VertexShader.cpp"
    "src/eeDX11Window.cpp"
)

#file(GLOB util_inc include/*.h)
#file(GLOB util_src src/*.cpp)

add_library(eeDX11GraphicsApi SHARED ${EE_DX11_PREREQUISITES_INCLUDES} ${EE_DX11_PREREQUISITES_SOURCES})
add_compile_definitions(EE_PLUGINDX11_EXPORTS)

set_target_properties(eeDX11GraphicsApi PROPERTIES
                      VS_DEBUGGER_WORKING_DIRECTORY ${EE_BINARY_OUTPUT_DIR}
                      OUTPUT_NAME_DEBUG 			eeDX11GraphicsApid
					  OUTPUT_NAME_MINSIZEREL 		eeDX11GraphicsApi
					  OUTPUT_NAME_RELWITHDEBINFO 	eeDX11GraphicsApi
					  OUTPUT_NAME_RELEASE 			eeDX11GraphicsApi)
target_include_directories(eeDX11GraphicsApi PUBLIC
                           include
						   ../eeUtilities/include
						   $ENV{DEVLIBS}/Boost
						   ../eeCore/include)
target_link_directories(eeDX11GraphicsApi PUBLIC
                        ../lib/$(PlatformTarget)/)

list(APPEND LIBRARIES_LINK optimized 	eeUtilities.lib)
list(APPEND LIBRARIES_LINK debug 		eeUtilitiesd.lib)
list(APPEND LIBRARIES_LINK optimized 	eeCore.lib)
list(APPEND LIBRARIES_LINK debug 		eeCored.lib)
list(APPEND LIBRARIES_LINK optimized 	d3d11.lib)
list(APPEND LIBRARIES_LINK debug 		d3d11.lib)
list(APPEND LIBRARIES_LINK optimized 	d3dcompiler.lib)
list(APPEND LIBRARIES_LINK debug 		d3dcompiler.lib)
list(APPEND LIBRARIES_LINK optimized 	dxguid.lib)
list(APPEND LIBRARIES_LINK debug 		dxguid.lib)

target_link_libraries(eeDX11GraphicsApi PUBLIC ${LIBRARIES_LINK})

add_dependencies(eeDX11GraphicsApi eeCore)