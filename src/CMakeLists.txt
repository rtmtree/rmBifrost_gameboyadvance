set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/bifrost/bifrost.hpp")

file(GLOB BSWR_SOURCES ${PROJECT_SOURCE_DIR}/external/BSWR/*.c)
file(GLOB_RECURSE lvgl_sources ${PROJECT_SOURCE_DIR}/external/lvgl/src/*.c ${PROJECT_SOURCE_DIR}/external/lvgl/src/*.cpp)
file(GLOB_RECURSE lv_lib_100ask_sources ${PROJECT_SOURCE_DIR}/external/lv_lib_100ask/src/*.c ${PROJECT_SOURCE_DIR}/external/lv_lib_100ask/src/*.cpp)

# -Wnarrowing
add_compile_options(-Wno-narrowing)
add_compile_definitions(LV_LVGL_H_INCLUDE_SIMPLE)



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
# set(VBA_NEXT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/lv_gba_emu/vba-next)
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
# # Sources
# ## porting
# file(GLOB PORT_SOURCES "lv_gba_emu/port/*.c")

# if (LV_USE_RPI)
# file(GLOB PORT_RPI_SOURCES "lv_gba_emu/port/rpi/*.c")
# endif ()

# ## gba emu
# file(GLOB GBA_EMU_SOURCES "lv_gba_emu/gba_emu/*.c*")



add_library(rmBifrost SHARED entrypoint.cpp
        bifrost.cpp
        bifrost_impl.cpp
        bifrost_impl.h
        gui/lvgl_renderer.cpp
        gui/lvgl_renderer.h
        ${BSWR_SOURCES}
        ${lvgl_sources}
        ${lv_lib_100ask_sources}
        gui/boot_screen.cpp
        gui/boot_screen.h
        
        gui/nes_instance.c
        gui/nes_instance.h

        # gui/happ_instance.cpp
        # gui/happ_instance.h
        # gui/gba_instance.cpp
        # gui/gba_instance.h

        # ${PORT_SOURCES}
        # ${PORT_RPI_SOURCES}
        # ${GBA_EMU_SOURCES}
        # ${VBA_NEXT_SOURCE}
        # ../external/wam_game/custom.c
        # ../external/wam_game/custom.h
        # ../external/wam_game/event_init.c
        # ../external/wam_game/event_init.h
        # ../external/wam_game/gui_guider.c
        # ../external/wam_game/gui_guider.h

        # fonts
        resources/fonts/ebgaramond_48.c
)

target_precompile_headers(rmBifrost PRIVATE "gui/lv_conf.h")

set_target_properties(rmBifrost PROPERTIES OUTPUT_NAME "bifrost")

# import all Qt6 components
find_package(Qt6 COMPONENTS Core Gui REQUIRED)
target_link_libraries(rmBifrost PRIVATE Qt6::Core Qt6::Gui)
target_include_directories(rmBifrost PRIVATE ${Qt6Core_INCLUDE_DIRS} ${Qt6Gui_INCLUDE_DIRS})

add_subdirectory(resources)
target_link_libraries(rmBifrost PRIVATE bifrost::resources)