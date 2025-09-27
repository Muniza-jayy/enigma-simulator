// Compile-time shim to ensure OpenGL types are known before ImGui's OpenGL3 backend.
// This prevents "Unknown type name 'GLuint'" on macOS.

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#define GL_SILENCE_DEPRECATION 1

#ifdef __APPLE__
  #include <OpenGL/gl3.h>     // defines GLuint, etc. (Core profile 3.2+)
  #include <OpenGL/gl3ext.h>
#else
  #error "This shim is set up for macOS. On other platforms, use an OpenGL loader (glad/gl3w) or include appropriate headers."
#endif

// Now pull in the ImGui backends as translation units.
#include "../third_party/imgui/backends/imgui_impl_opengl3.cpp"
#include "../third_party/imgui/backends/imgui_impl_glfw.cpp"
