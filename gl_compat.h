#ifndef GL_COMPAT_H
#define GL_COMPAT_H

// Include GLEW first
#include <GL/glew.h>

// Then include system OpenGL headers
#include <GL/gl.h>
#include <GL/glu.h>

// Fallback for glWindowPos2i if not available
#if !defined(glWindowPos2i) && !defined(HAVE_GL_WINDOW_POS)
inline void glWindowPos2i(GLint x, GLint y) {
    // Fallback implementation
    glRasterPos2i(x, y);
}
#endif

// Function to check if we have the required OpenGL version
inline bool has_opengl_version(int major, int minor) {
    const char* version = (const char*)glGetString(GL_VERSION);
    if (!version) return false;
    
    int gl_major = 0, gl_minor = 0;
    if (sscanf(version, "%d.%d", &gl_major, &gl_minor) != 2) {
        return false;
    }
    
    return (gl_major > major) || (gl_major == major && gl_minor >= minor);
}

// Macro to check for OpenGL function availability
#define HAS_GL_FUNC(func) (func != NULL)

// Define a macro to check if VBO functions are available
#define HAS_VBO (GLEW_VERSION_1_5 || GLEW_ARB_vertex_buffer_object)

// Initialize GLEW and check for required extensions
inline bool init_glew() {
    static bool initialized = false;
    if (initialized) return true;
    
    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        return false;
    }
    
    // Check for required OpenGL version
    if (!has_opengl_version(1, 5)) {
        fprintf(stderr, "OpenGL 1.5 or later is required\n");
        return false;
    }
    
    // Check for required extensions
    if (!GLEW_ARB_vertex_buffer_object) {
        fprintf(stderr, "ARB_vertex_buffer_object extension is required\n");
        return false;
    }
    
    initialized = true;
    return true;
}

// Define VBO-related constants if not defined
#ifndef GL_ARRAY_BUFFER
#define GL_ARRAY_BUFFER 0x8892
#endif

#ifndef GL_ELEMENT_ARRAY_BUFFER
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#endif

#ifndef GL_STATIC_DRAW
#define GL_STATIC_DRAW 0x88E4
#endif

#ifndef GL_DYNAMIC_DRAW
#define GL_DYNAMIC_DRAW 0x88E8
#endif

#ifndef GL_READ_WRITE
#define GL_READ_WRITE 0x88BA
#endif

#endif // GL_COMPAT_H
