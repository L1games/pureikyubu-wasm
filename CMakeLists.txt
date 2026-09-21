cmake_minimum_required (VERSION 3.10)
project (pureikyubu_wasm)

add_definitions (-D_LINUX)
add_compile_options(-Wno-attributes)

if (MSVC)
  add_compile_options(/utf-8)
endif ()

set (PUREIKYUBU_CORE
	src/ai.cpp
	src/bootrtc.cpp
	src/bump.cpp
	src/config.cpp
	src/cp.cpp
	src/debug.cpp
	src/debugui.cpp
	src/di.cpp
	src/dsp.cpp
	src/dspcore.cpp
	src/dspjit.cpp
	src/dspdebug.cpp
	src/dspdec.cpp
	src/dspdisasm.cpp
	src/dspai.cpp
	src/dsparam.cpp
	src/dspdma.cpp
	src/dvd.cpp
	src/dvddebug.cpp
	src/exi.cpp
	src/flipper.cpp
	src/flipperdebug.cpp
	src/gekko.cpp
	src/gekkoc.cpp
	src/gekkojit.cpp
	src/gekkojit_ps.cpp
	src/gekkodebug.cpp
	src/gekkodec.cpp
	src/gekkodisasm.cpp
	src/gfx.cpp
	src/gfxosd.cpp
	src/hwosd.cpp
	src/hwprof.cpp
	src/jdi.cpp
	src/jdiserver.cpp
	src/jdispecs.cpp
	src/json.cpp
	src/main.cpp
	src/mcp.cpp
	src/mem.cpp
	src/memcard.cpp
	src/os.cpp
	src/osdebug.cpp
	src/pe.cpp
	src/pi.cpp
	src/ras.cpp
	src/rvz.cpp
	src/si.cpp
	src/su.cpp
	src/sym.cpp
	src/tev.cpp
	src/tx.cpp
	src/uijdi.cpp
	src/utils.cpp
	src/vi.cpp
	src/xf.cpp

	thirdparty/zstd/zstddeclib.c
)

set (PUREIKYUBU_FRONTEND
	src/audiosdl.cpp
	src/bench.cpp
	src/cuisdl.cpp
	src/debugui2.cpp
	src/debugui2gl.cpp
	src/padsdl.cpp
	src/uisdl.cpp
	src/videosdl.cpp

	src/gba/arm7tdmi.cpp
	src/gba/gba.cpp
	src/gba/gba_apu.cpp
	src/gba/gba_armasm.cpp
	src/gba/gba_bootrom.cpp
	src/gba/gba_bus.cpp
	src/gba/gba_cart.cpp
	src/gba/gba_dma.cpp
	src/gba/gba_hlebios.cpp
	src/gba/gba_irq.cpp
	src/gba/gba_keypad.cpp
	src/gba/gba_ppu.cpp
	src/gba/gba_sdl.cpp
	src/gba/gba_settings.cpp
	src/gba/gba_sio.cpp
	src/gba/gba_timers.cpp
	src/gba/gba_types.cpp

	src/gba/gb.cpp
	src/gba/gb_asm.cpp
	src/gba/gb_apu.cpp
	src/gba/gb_bootrom.cpp
	src/gba/gb_bus.cpp
	src/gba/gb_cart.cpp
	src/gba/gb_cpu.cpp
	src/gba/gb_ppu.cpp

	thirdparty/imgui/imgui.cpp
	thirdparty/imgui/imgui_demo.cpp
	thirdparty/imgui/imgui_draw.cpp
	thirdparty/imgui/backends/imgui_impl_sdl2.cpp
	thirdparty/imgui/backends/imgui_impl_opengl3.cpp
	thirdparty/imgui/imgui_tables.cpp
	thirdparty/imgui/imgui_widgets.cpp
)

add_executable (pureikyubu_wasm
	${PUREIKYUBU_CORE}
	${PUREIKYUBU_FRONTEND}
)

if(EMSCRIPTEN)
    target_compile_options(pureikyubu_wasm PRIVATE
        -O3 
        -gsource-map 
		-flto
        -pthread
		-msimd128
		-sUSE_SDL=2
        -sEXPORTED_FUNCTIONS=['_main']
		-sINITIAL_MEMORY=805306368 
		-sMAX_WEBGL_VERSION=2
		-sMIN_WEBGL_VERSION=2
        -sEXPORTED_RUNTIME_METHODS=['ccall','cwrap','FS','callMain']
		-sOFFSCREEN_FRAMEBUFFER=1
        -sOFFSCREENCANVAS_SUPPORT=1
    )
    target_link_options(pureikyubu_wasm PRIVATE
        -O3 
        -gsource-map 
		-flto
		-msimd128
        -pthread	
        "-sUSE_SDL=2"
        "-sFORCE_FILESYSTEM=1"   
		"-sINITIAL_MEMORY=805306368" 
		"-sOFFSCREEN_FRAMEBUFFER=1"
        "-sOFFSCREENCANVAS_SUPPORT=1"
        "-sSHARED_MEMORY=1"
		"-sMAX_WEBGL_VERSION=2"
		"-sMIN_WEBGL_VERSION=2"
		"-sEXPORTED_FUNCTIONS=['_main']"
        "-sEXPORTED_RUNTIME_METHODS=['ccall','cwrap','FS','callMain']"
    )
endif()

target_compile_features(pureikyubu_wasm PRIVATE cxx_std_17)

include_directories(
    ${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/src/gba
	${CMAKE_SOURCE_DIR}/src/res
	${CMAKE_SOURCE_DIR}/thirdparty
	${CMAKE_SOURCE_DIR}/thirdparty/imgui
	${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends
	${CMAKE_SOURCE_DIR}/thirdparty/imgui-filebrowser
	${CMAKE_SOURCE_DIR}/thirdparty/stb
	${CMAKE_SOURCE_DIR}/thirdparty/zstd
)

