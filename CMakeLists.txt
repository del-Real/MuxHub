cmake_minimum_required(VERSION 3.16)
project(MuxHub VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform-specific configurations
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
endif()

# Find SDL3 - try different methods
find_package(SDL3 CONFIG QUIET)

if(NOT SDL3_FOUND)
    message(STATUS "SDL3 not found via find_package, trying manual detection...")

    # Manual SDL3 detection for Windows
    if(WIN32)
        set(SDL3_SEARCH_PATHS
                "C:/SDL3"
                "C:/dev/SDL3"
                "C:/libs/SDL3"
                "${CMAKE_SOURCE_DIR}/libs/SDL3"
                "${CMAKE_SOURCE_DIR}/third_party/SDL3"
        )

        find_path(SDL3_INCLUDE_DIR
                NAMES SDL3/SDL.h
                PATHS ${SDL3_SEARCH_PATHS}
                PATH_SUFFIXES include
        )

        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(SDL3_LIB_SUFFIX "x64")
        else()
            set(SDL3_LIB_SUFFIX "x86")
        endif()

        find_library(SDL3_LIBRARY
                NAMES SDL3 libSDL3
                PATHS ${SDL3_SEARCH_PATHS}
                PATH_SUFFIXES lib lib/${SDL3_LIB_SUFFIX} lib64
        )

        # Also find the DLL for runtime
        find_file(SDL3_DLL
                NAMES SDL3.dll
                PATHS ${SDL3_SEARCH_PATHS}
                PATH_SUFFIXES lib lib/${SDL3_LIB_SUFFIX} bin bin/${SDL3_LIB_SUFFIX}
        )

        if(SDL3_INCLUDE_DIR AND SDL3_LIBRARY)
            set(SDL3_FOUND TRUE)
            set(SDL3_LIBRARIES ${SDL3_LIBRARY})
            set(SDL3_INCLUDE_DIRS ${SDL3_INCLUDE_DIR})
            message(STATUS "Found SDL3: ${SDL3_LIBRARY}")
            message(STATUS "SDL3 DLL: ${SDL3_DLL}")

            # Create an imported target for consistency
            add_library(SDL3::SDL3 SHARED IMPORTED)
            set_target_properties(SDL3::SDL3 PROPERTIES
                    IMPORTED_LOCATION "${SDL3_DLL}"
                    IMPORTED_IMPLIB "${SDL3_LIBRARY}"
                    INTERFACE_INCLUDE_DIRECTORIES "${SDL3_INCLUDE_DIR}"
            )
        else()
            message(FATAL_ERROR "SDL3 not found! Please download SDL3 development libraries and extract to C:/SDL3")
        endif()
    else()
        # For macOS/Linux, try system package managers
        find_package(PkgConfig QUIET)
        if(PkgConfig_FOUND)
            pkg_check_modules(SDL3 QUIET sdl3)
            if(SDL3_FOUND)
                message(STATUS "Found SDL3 via pkg-config")
            endif()
        endif()

        if(NOT SDL3_FOUND)
            message(FATAL_ERROR "SDL3 not found! Please install SDL3 development libraries")
        endif()
    endif()
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ImGui configuration - ONLY use internal/embedded ImGui with flexible structure
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/lib/imgui")

# Check multiple possible ImGui structures
set(IMGUI_FOUND FALSE)

# Structure 1: Standard ImGui (imgui.h in root)
if(EXISTS "${IMGUI_DIR}/imgui.h")
    set(IMGUI_INCLUDE_ROOT ${IMGUI_DIR})
    set(IMGUI_SOURCE_ROOT ${IMGUI_DIR})
    set(IMGUI_FOUND TRUE)
    message(STATUS "Found standard ImGui structure")

    # Structure 2: Separated structure (include/ and src/ folders)
elseif(EXISTS "${IMGUI_DIR}/include/imgui.h")
    set(IMGUI_INCLUDE_ROOT ${IMGUI_DIR}/include)
    set(IMGUI_SOURCE_ROOT ${IMGUI_DIR}/src)
    set(IMGUI_FOUND TRUE)
    message(STATUS "Found separated ImGui structure (include/ and src/)")

    # Structure 3: Nested structure
elseif(EXISTS "${IMGUI_DIR}/imgui/imgui.h")
    set(IMGUI_INCLUDE_ROOT ${IMGUI_DIR}/imgui)
    set(IMGUI_SOURCE_ROOT ${IMGUI_DIR}/imgui)
    set(IMGUI_FOUND TRUE)
    message(STATUS "Found nested ImGui structure")
endif()

if(IMGUI_FOUND)
    # Define core ImGui sources
    set(IMGUI_CORE_SOURCES
            ${IMGUI_SOURCE_ROOT}/imgui.cpp
            ${IMGUI_SOURCE_ROOT}/imgui_demo.cpp
            ${IMGUI_SOURCE_ROOT}/imgui_draw.cpp
            ${IMGUI_SOURCE_ROOT}/imgui_tables.cpp
            ${IMGUI_SOURCE_ROOT}/imgui_widgets.cpp
    )

    # Find backend sources - try different possible structures
    set(BACKEND_SOURCES "")
    set(BACKEND_INCLUDE_DIRS "")

    # Try your specific backend/src/ directory structure
    if(EXISTS "${IMGUI_DIR}/backend/src/imgui_impl_sdl3.cpp")
        set(BACKEND_SOURCES
                ${IMGUI_DIR}/backend/src/imgui_impl_sdl3.cpp
                ${IMGUI_DIR}/backend/src/imgui_impl_sdlrenderer3.cpp
        )
        set(BACKEND_INCLUDE_DIRS
                ${IMGUI_DIR}/backend/include
        )
        message(STATUS "Using backends from: ${IMGUI_DIR}/backend/src/")

        # Try your specific backend/ directory (source files directly)
    elseif(EXISTS "${IMGUI_DIR}/backend/imgui_impl_sdl3.cpp")
        set(BACKEND_SOURCES
                ${IMGUI_DIR}/backend/imgui_impl_sdl3.cpp
                ${IMGUI_DIR}/backend/imgui_impl_sdlrenderer3.cpp
        )
        set(BACKEND_INCLUDE_DIRS ${IMGUI_DIR}/backend)
        message(STATUS "Using backends from: ${IMGUI_DIR}/backend")

        # Try standard backends/ directory
    elseif(EXISTS "${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp")
        set(BACKEND_SOURCES
                ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
                ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
        )
        set(BACKEND_INCLUDE_DIRS ${IMGUI_DIR}/backends)
        message(STATUS "Using backends from: ${IMGUI_DIR}/backends")

        # Try examples/libs/ directory (some ImGui distributions)
    elseif(EXISTS "${IMGUI_DIR}/examples/libs/imgui_impl_sdl3.cpp")
        set(BACKEND_SOURCES
                ${IMGUI_DIR}/examples/libs/imgui_impl_sdl3.cpp
                ${IMGUI_DIR}/examples/libs/imgui_impl_sdlrenderer3.cpp
        )
        set(BACKEND_INCLUDE_DIRS ${IMGUI_DIR}/examples/libs)
        message(STATUS "Using backends from: ${IMGUI_DIR}/examples/libs")

    else()
        message(FATAL_ERROR "ImGui SDL3 backends not found! Looked in:\n"
                "- ${IMGUI_DIR}/backend/src/\n"
                "- ${IMGUI_DIR}/backend/\n"
                "- ${IMGUI_DIR}/backends/\n"
                "- ${IMGUI_DIR}/examples/libs/\n"
                "Please ensure imgui_impl_sdl3.cpp and imgui_impl_sdlrenderer3.cpp are available.")
    endif()

    # Combine all sources
    set(IMGUI_SOURCES ${IMGUI_CORE_SOURCES} ${BACKEND_SOURCES})

    set(IMGUI_INCLUDE_DIRS
            ${IMGUI_INCLUDE_ROOT}
            ${BACKEND_INCLUDE_DIRS}
    )

    # Verify all ImGui sources exist
    foreach(SRC ${IMGUI_SOURCES})
        if(NOT EXISTS ${SRC})
            message(FATAL_ERROR "ImGui source file not found: ${SRC}")
        endif()
    endforeach()

    message(STATUS "Using internal ImGui from: ${IMGUI_DIR}")
    message(STATUS "ImGui include root: ${IMGUI_INCLUDE_ROOT}")
    message(STATUS "ImGui source root: ${IMGUI_SOURCE_ROOT}")
    message(STATUS "ImGui sources: ${IMGUI_SOURCES}")

else()
    # Print debug info to help troubleshoot
    message(STATUS "Debug: ImGui directory contents:")
    file(GLOB IMGUI_CONTENTS "${IMGUI_DIR}/*")
    foreach(ITEM ${IMGUI_CONTENTS})
        message(STATUS "  ${ITEM}")
    endforeach()

    if(EXISTS "${IMGUI_DIR}/include")
        message(STATUS "Debug: include/ directory contents:")
        file(GLOB INCLUDE_CONTENTS "${IMGUI_DIR}/include/*")
        foreach(ITEM ${INCLUDE_CONTENTS})
            message(STATUS "  ${ITEM}")
        endforeach()
    endif()

    if(EXISTS "${IMGUI_DIR}/src")
        message(STATUS "Debug: src/ directory contents:")
        file(GLOB SRC_CONTENTS "${IMGUI_DIR}/src/*")
        foreach(ITEM ${SRC_CONTENTS})
            message(STATUS "  ${ITEM}")
        endforeach()
    endif()

    message(FATAL_ERROR "Internal ImGui not found! Please ensure ImGui is properly installed.")
endif()

# ImNodes configuration
set(IMNODES_DIR "${CMAKE_SOURCE_DIR}/lib/imnodes")
if(EXISTS "${IMNODES_DIR}")
    # Try different source patterns for ImNodes
    file(GLOB_RECURSE IMNODES_SOURCES
            ${IMNODES_DIR}/*.cpp
            ${IMNODES_DIR}/*.c
    )

    # Filter out example/demo files
    list(FILTER IMNODES_SOURCES EXCLUDE REGEX ".*example.*|.*demo.*|.*test.*")

    message(STATUS "ImNodes sources: ${IMNODES_SOURCES}")
else()
    message(FATAL_ERROR "ImNodes not found at ${IMNODES_DIR}")
endif()

# Project source files
set(MUXHUB_SOURCES
        src/main.cpp
        src/nodes/gates/gate.cpp
        src/nodes/gates/and_gate.cpp
        src/nodes/gates/not_gate.cpp
        # Add other gate implementations as they're completed
        # src/nodes/gates/or_gate.cpp
        # src/nodes/gates/nand_gate.cpp
        # src/nodes/gates/nor_gate.cpp
        # src/nodes/gates/xor_gate.cpp
        # src/nodes/gates/xnor_gate.cpp
)

# Create the executable
add_executable(MuxHub ${MUXHUB_SOURCES} ${IMGUI_SOURCES} ${IMNODES_SOURCES})

# Include directories
target_include_directories(MuxHub PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${IMGUI_INCLUDE_DIRS}
        ${IMNODES_DIR}/include
        ${IMNODES_DIR}
)

# Link with SDL3
if(TARGET SDL3::SDL3)
    target_link_libraries(MuxHub PRIVATE SDL3::SDL3)
    message(STATUS "Linking with SDL3::SDL3 target")
elseif(SDL3_LIBRARIES)
    target_link_libraries(MuxHub PRIVATE ${SDL3_LIBRARIES})
    target_include_directories(MuxHub PRIVATE ${SDL3_INCLUDE_DIRS})
    message(STATUS "Linking with SDL3 libraries: ${SDL3_LIBRARIES}")
else()
    message(FATAL_ERROR "SDL3 configuration error")
endif()

# Platform-specific linking
if(WIN32)
    # Windows-specific libraries
    target_link_libraries(MuxHub PRIVATE
            opengl32
            gdi32
            shell32
            ole32
            oleaut32
            imm32
            winmm
            version
    )

    # Copy SDL3 DLL to output directory
    if(TARGET SDL3::SDL3)
        add_custom_command(TARGET MuxHub POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:SDL3::SDL3>
                $<TARGET_FILE_DIR:MuxHub>
                COMMENT "Copying SDL3.dll to output directory"
        )
    elseif(SDL3_DLL)
        add_custom_command(TARGET MuxHub POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL3_DLL}
                $<TARGET_FILE_DIR:MuxHub>
                COMMENT "Copying SDL3.dll to output directory"
        )
    endif()

elseif(APPLE)
    # macOS-specific frameworks
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    find_library(CARBON_LIBRARY Carbon REQUIRED)

    target_link_libraries(MuxHub PRIVATE
            ${COCOA_LIBRARY}
            ${IOKIT_LIBRARY}
            ${COREVIDEO_LIBRARY}
            ${CARBON_LIBRARY}
    )

elseif(UNIX)
    # Linux-specific libraries
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

    target_link_libraries(MuxHub PRIVATE
            ${GTK3_LIBRARIES}
            GL
            dl
            pthread
    )
    target_include_directories(MuxHub PRIVATE ${GTK3_INCLUDE_DIRS})
    target_compile_options(MuxHub PRIVATE ${GTK3_CFLAGS_OTHER})
endif()

# Compiler-specific options
if(MSVC)
    target_compile_options(MuxHub PRIVATE /W4)
    # Disable specific MSVC warnings if needed
    target_compile_options(MuxHub PRIVATE /wd4996 /wd4244 /wd4267)
else()
    target_compile_options(MuxHub PRIVATE -Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(MuxHub PRIVATE -g -O0)
    else()
        target_compile_options(MuxHub PRIVATE -O3)
    endif()
endif()

# Set up debug/release configurations
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Print configuration information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Using internal ImGui from: ${IMGUI_DIR}")
message(STATUS "SDL3 found and linked")

# Installation rules (optional)
install(TARGETS MuxHub
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

# CPack configuration for packaging (optional)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)