cmake_minimum_required(VERSION 3.10)
project(lvgl C CXX)




# Main include files of the project
include_directories(${PROJECT_SOURCE_DIR}/main/inc)

# Define options for LVGL with default values (OFF)
option(LV_USE_DRAW_SDL "Use SDL draw unit" OFF)
option(LV_USE_LIBPNG "Use libpng to decode PNG" OFF)
option(LV_USE_LIBJPEG_TURBO "Use libjpeg turbo to decode JPEG" OFF)
option(LV_USE_FFMPEG "Use libffmpeg to display video using lv_ffmpeg" OFF)
option(LV_USE_FREETYPE "Use freetype library" OFF)

# Set C and C++ standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output path for the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

# Find and include SDL2 library
find_package(SDL2 REQUIRED)

# Remove ARM-specific compile and linker options
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

# Add compile definitions based on the selected options
add_compile_definitions($<$<BOOL:${LV_USE_DRAW_SDL}>:LV_USE_DRAW_SDL=1>)
add_compile_definitions($<$<BOOL:${LV_USE_LIBPNG}>:LV_USE_LIBPNG=1>)
add_compile_definitions($<$<BOOL:${LV_USE_LIBJPEG_TURBO}>:LV_USE_LIBJPEG_TURBO=1>)
add_compile_definitions($<$<BOOL:${LV_USE_FFMPEG}>:LV_USE_FFMPEG=1>)

set(OUTER_PORTING_DIR "/Users/bank23232525/Documents/Eink/rmBifrost_gameboyadvance")

# Add LVGL subdirectory
# add_subdirectory(lvgl)
add_subdirectory(
    /Users/bank23232525/Documents/Eink/rmBifrost_gameboyadvance/external/lvgl
    ${CMAKE_BINARY_DIR}/lvgl_build
)
target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
add_subdirectory(
    /Users/bank23232525/Documents/Eink/rmBifrost_gameboyadvance/external/lv_lib_100ask
    ${CMAKE_BINARY_DIR}/lv_lib_100ask_build
)

# add_definitions(
#         -DDEBUG=0
#         -DFRONTEND_SUPPORTS_RGB565=1
#         -DTILED_RENDERING=1
#         -DSTATIC_LINKING=0
#         -DUSE_TWEAKS=1
#         -DUSE_FRAME_SKIP=1
#         -DHAVE_NEON=0
#         -Dretro_sleep=lv_port_sleep

#         -DNDEBUG
#         -D__LIBRETRO__
#         -DINLINE=inline
#         -DHAVE_STDINT_H
#         -DHAVE_INTTYPES_H

#         -DGBA_FRAME_SKIP="0"
# )

# # Include
# set(VBA_NEXT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/lv_gba_emu/vba-next)
# include_directories(
#         ${PROJECT_SOURCE_DIR}
#         ${VBA_NEXT_SOURCE_DIR}/src
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/include
# )
# ## vba-next
# file(GLOB VBA_NEXT_SOURCE
#         ${VBA_NEXT_SOURCE_DIR}/src/*.c
#         ${VBA_NEXT_SOURCE_DIR}/src/*.cpp
#         ${VBA_NEXT_SOURCE_DIR}/libretro/libretro.cpp
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/rthreads/rsemaphore.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/rthreads/rthreads.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/compat/*.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/encodings/*.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/file/*.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/streams/*.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/string/*.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/time/*.c
# )

# add_subdirectory(${OUTER_PORTING_DIR}/external/lv_lib_100ask)
# add_subdirectory(/Users/bank23232525/Documents/Eink/rmBifrost_gameboyadvance/external/lv_lib_100ask/${CMAKE_BINARY_DIR}/lv_lib_100ask_build)
# add_subdirectory(/Users/bank23232525/Documents/Eink/rmBifrost_gameboyadvance/external/lv_lib_100ask)

# # # add_subdirectory(lv_lib_100ask)
# # target_include_directories(lv_lib_100ask PUBLIC ${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
# # add_subdirectory(lv_lib_100ask)
# # # add_subdirectory(lv_lib_100ask)
# # target_include_directories(lv_lib_100ask PUBLIC ${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
# # Sources
# ## porting
# file(GLOB PORT_SOURCES "lv_gba_emu/port/*.c")

# if (LV_USE_RPI)
# file(GLOB PORT_RPI_SOURCES "lv_gba_emu/port/rpi/*.c")
# endif ()

# ## gba emu
# file(GLOB GBA_EMU_SOURCES "lv_gba_emu/gba_emu/*.c*")


# vba-next config
# add_definitions(
#         -DDEBUG=0
#         -DFRONTEND_SUPPORTS_RGB565=1
#         -DTILED_RENDERING=1
#         -DSTATIC_LINKING=0
#         -DUSE_TWEAKS=1
#         -DUSE_FRAME_SKIP=1
#         -DHAVE_NEON=0
#         -Dretro_sleep=lv_port_sleep

#         -DNDEBUG
#         -D__LIBRETRO__
#         -DINLINE=inline
#         -DHAVE_STDINT_H
#         -DHAVE_INTTYPES_H

#         -DGBA_FRAME_SKIP="0"
# )

# # Include
# set(VBA_NEXT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/vba-next)

# include_directories(
#         ${PROJECT_SOURCE_DIR}
#         ${VBA_NEXT_SOURCE_DIR}/src
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/include
# )

# # Sources
# ## porting
# file(GLOB PORT_SOURCES "lv_gba/port/*.c")

# if (LV_USE_RPI)
# file(GLOB PORT_RPI_SOURCES "lv_gba/port/rpi/*.c")
# endif ()

# ## gba emu
# file(GLOB GBA_EMU_SOURCES "lv_gba/gba_emu/*.c*")

# ## vba-next
# file(GLOB VBA_NEXT_SOURCE
#         ${VBA_NEXT_SOURCE_DIR}/src/*.c
#         ${VBA_NEXT_SOURCE_DIR}/src/*.cpp
#         ${VBA_NEXT_SOURCE_DIR}/libretro/libretro.cpp
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/rthreads/rsemaphore.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/rthreads/rthreads.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/compat/*.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/encodings/*.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/file/*.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/streams/*.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/string/*.c
#         ${VBA_NEXT_SOURCE_DIR}/libretro-common/time/*.c
# )

# ## ALL SOURCES
# set(SOURCES
#         ${PORT_SOURCES}
#         ${PORT_RPI_SOURCES}
#         ${GBA_EMU_SOURCES}
#         ${GBA_PORT_SOURCES}
#         ${VBA_NEXT_SOURCE}
# )

# Subdirectory
# add_subdirectory(${PROJECT_SOURCE_DIR}/lvgl ${PROJECT_BINARY_DIR}/build_lvgl)



#
add_executable(main
    ${PROJECT_SOURCE_DIR}/main/src/main.c
    ${PROJECT_SOURCE_DIR}/main/src/mouse_cursor_icon.c
    # ${PROJECT_SOURCE_DIR}/main/src/happ_instance.c
    ${OUTER_PORTING_DIR}/src/gui/happ_instance.c
    ${OUTER_PORTING_DIR}/src/gui/nes_instance.c

    # ${PROJECT_SOURCE_DIR}/main/src/nes_instance.c
    # ${PROJECT_SOURCE_DIR}/main/src/gba_instance.c
    # ${PORT_SOURCES}
    # ${PORT_RPI_SOURCES}
    # ${GBA_EMU_SOURCES}
    # ${VBA_NEXT_SOURCE}
    # ${SOURCES} ${INCLUDES}
)


# Define LVGL configuration as a simple include
target_compile_definitions(main PRIVATE LV_CONF_INCLUDE_SIMPLE)
target_link_libraries(main lvgl lvgl::examples lvgl::demos lvgl::thorvg ${SDL2_LIBRARIES} m pthread lv_lib_100ask)
# target_link_libraries(main lvgl lvgl::examples lvgl::demos ${SDL2_LIBRARIES} m pthread)



# Custom target to run the executable
add_custom_target(run COMMAND ${EXECUTABLE_OUTPUT_PATH}/main DEPENDS main)

# Conditionally include and link SDL2_image if LV_USE_DRAW_SDL is enabled
if(LV_USE_DRAW_SDL)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
    find_package(SDL2_image REQUIRED)
    target_include_directories(lvgl PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
    target_include_directories(lv_lib_100ask PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(main ${SDL2_IMAGE_LIBRARIES})
endif()

# Conditionally include and link libpng if LV_USE_LIBPNG is enabled
if(LV_USE_LIBPNG)
    find_package(PNG REQUIRED)
    target_include_directories(lvgl PUBLIC ${PNG_INCLUDE_DIRS})
    target_include_directories(lv_lib_100ask PUBLIC ${PNG_INCLUDE_DIRS})
    target_link_libraries(main ${PNG_LIBRARIES})
endif()

# Conditionally include and link libjpeg-turbo if LV_USE_LIBJPEG_TURBO is enabled
if(LV_USE_LIBJPEG_TURBO)
    find_package(JPEG REQUIRED)
    target_include_directories(lvgl PUBLIC ${JPEG_INCLUDE_DIRS})
    target_include_directories(lv_lib_100ask PUBLIC ${JPEG_INCLUDE_DIRS})
    target_link_libraries(main ${JPEG_LIBRARIES})
endif()

# Conditionally include and link FFmpeg libraries if LV_USE_FFMPEG is enabled
if(LV_USE_FFMPEG)
    target_link_libraries(main avformat avcodec avutil swscale z)
endif()

# Conditionally include and link FreeType if LV_USE_FREETYPE is enabled
if(LV_USE_FREETYPE)
    find_package(Freetype REQUIRED)
    target_include_directories(lvgl PUBLIC ${FREETYPE_INCLUDE_DIRS})
    target_include_directories(lv_lib_100ask PUBLIC ${FREETYPE_INCLUDE_DIRS})
    target_link_libraries(main ${FREETYPE_LIBRARIES})
endif()

# Apply additional compile options if the build type is Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode enabled")

    target_compile_options(lvgl PRIVATE
        -pedantic-errors
        -Wall
        -Wclobbered
        -Wdeprecated
        -Wdouble-promotion
        -Wempty-body
        -Wextra
        -Wformat-security
        -Wmaybe-uninitialized
        # -Wmissing-prototypes
        -Wpointer-arith
        -Wmultichar
        -Wno-pedantic # ignored for now, we convert functions to pointers for properties table.
        -Wreturn-type
        -Wshadow
        -Wshift-negative-value
        -Wsizeof-pointer-memaccess
        -Wtype-limits
        -Wundef
        -Wuninitialized
        -Wunreachable-code
        -Wfloat-conversion
        -Wstrict-aliasing
    )

if (ASAN)
    message(STATUS "AddressSanitizer enabled")

    # Add AddressSanitizer flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address")
else()
    message(STATUS "AddressSanitizer disabled")
endif()
endif()
