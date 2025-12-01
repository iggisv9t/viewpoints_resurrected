cmake_minimum_required(VERSION 3.15)
project(Viewpoints VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform-specific settings
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")
    add_compile_definitions(__APPLE__)
elseif(UNIX AND NOT APPLE)
    add_compile_definitions(__linux__)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
elseif(WIN32)
    add_compile_definitions(__WIN32__ NOMINMAX)
    add_compile_options(/W4 /WX)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

# Find required packages
# Find OpenGL
find_package(OpenGL REQUIRED)

# Set GLVND policy if available
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.11")
    cmake_policy(SET CMP0072 NEW)
    set(OpenGL_GL_PREFERENCE "GLVND")
endif()

# Find GLEW
find_package(GLEW REQUIRED)

# Find FLTK with required components
find_package(FLTK REQUIRED COMPONENTS gl images)

# Find GSL
find_package(GSL REQUIRED)

# Find CFITSIO using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(CFITSIO REQUIRED cfitsio)

# For older CMake versions that don't support pkg_check_modules
if(NOT CFITSIO_FOUND)
    find_library(CFITSIO_LIBRARIES NAMES cfitsio)
    find_path(CFITSIO_INCLUDE_DIR NAMES fitsio.h)
    if(CFITSIO_LIBRARIES AND CFITSIO_INCLUDE_DIR)
        set(CFITSIO_FOUND TRUE)
    else()
        message(FATAL_ERROR "CFITSIO not found. Please install the cfitsio package.")
    endif()
endif()

# Add definitions for OpenGL
add_definitions(-DGLEW_STATIC)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIRS}
    ${FLTK_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${CFITSIO_INCLUDE_DIRS}
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Set include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIRS}
    ${FLTK_INCLUDE_DIRS}
)

# Add definitions
add_definitions(-DGL_GLEXT_PROTOTYPES)

# Source files
set(SOURCES
    vp.cpp
    global_definitions_vp.cpp
    control_panel_window.cpp
    plot_window.cpp
    data_file_manager.cpp
    Vp_File_Chooser.cpp
    symbol_menu.cpp
    sprite_textures.cpp
    unescape.cpp
    brush.cpp
    Vp_Color_Chooser.cpp
    column_info.cpp
    Vp_Value_Input_Spin.cpp
)

# Headers
set(HEADERS
    global_definitions_vp.h
    control_panel_window.h
    plot_window.h
    data_file_manager.h
    Vp_File_Chooser.h
    symbol_menu.h
    sprite_textures.h
    unescape.h
    brush.h
    Vp_Color_Chooser.h
    column_info.h
    Vp_Value_Input_Spin.H
    Fl_Hor_Value_Slider_Input.H
    include_libraries_vp.h
    flews_compat.h
)

# Add executable
add_executable(vp ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(vp PRIVATE
    fltk
    fltk_gl
    fltk_images
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GSL_LIBRARIES}
    ${CFITSIO_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    dl  # For dynamic loading
    m   # Math library
    X11 # For X11 functions
)

# Set target properties
set_target_properties(vp PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    OUTPUT_NAME "viewpoints"
)

# Install rules
install(TARGETS vp
    RUNTIME DESTINATION bin
)
