/************************************************************************/
/**
 * @file eePrerequisitesCore.h
 * @author Diego Castellanos
 * @date 01/10/21
 * @brief The prerequisites for all the Core module.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once

#include <eePrerequisitesUtilities.h>
#include "eeCoreDefines.h"


/************************************************************************/
/**
 * Library export specifics
 */
/************************************************************************/
#if EE_PLATFORM == EE_PLATFORM_WIN32
# if EE_COMPILER == EE_COMPILER_MSVC
#   if defined( EE_STATIC_lib )
#     define EE_CORE_EXPORT
#   else
#     if defined ( EE_CORE_EXPORTS )
#       define EE_CORE_EXPORT __declspec( dllexport )
#     else
#       define EE_CORE_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( EE_STATIC_LIB )
#     define EE_CORE_EXPORT
#   else
#     if defined( EE_CORE_EXPORTS )
#       define EE_CORE_EXPORT __attribute__ ((dllexport))
#     else
#       define EE_CORE_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define EE_CORE_HIDDEN
#else
# define EE_CORE_EXPORT __attribute__ ((visibility ("default")))
# define EE_CORE_HIDDEN __attribute__ ((visibility ("hidden")))
#endif



#define EE_NO_EXIST_RETURN(x) if (!x) return;
#define EE_NO_EXIST_BREAK(x) if (!x) break;



namespace eeEngineSDK {
class Buffer;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class Texture;
class Window;

class BlendState;
class DepthStencilState;
class SamplerState;
class RasterizerState;

class VertexShader;
class PixelShader;
class HullShader;
class DomainShader;
class InputLayout;

class GraphicsApi;
class BaseApp;

class Octree;
class OctreeNode;

class Mesh;
class BoneMesh;
class StaticMesh;
class Texture;
class Skeletal;
class SkeletalMesh;
class Animation;
class Image;
class Material;
struct Audio;
class Sound;

class SceneManager;
class Scene;
class Actor;
class Component;
class CAnimation;
class CTransform;
class CStaticMesh;
class CRender;
class CCamera;
class CSkeletalMesh;
class CBounds;

class ResourceManager;

class InputManager;
class InputDevice;
class GamepadDevice;
class KeyboardDevice;
class MouseDevice;
struct InputDeviceEvent;
}