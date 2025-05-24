cmake_minimum_required(VERSION 3.28)
project(Chess LANGUAGES CXX)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(WINDOWS TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LINUX TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set(EMSCRIPTEN TRUE)
endif()

if (EMSCRIPTEN)
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

if (EMSCRIPTEN)
    set(SFML_ROOT "../SFML")
endif()

file(GLOB_RECURSE Project_SOURCES "src/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(ASSETS_DIR "assets/")

if (NOT EXISTS "${ASSETS_DIR}")
    file(MAKE_DIRECTORY "${ASSETS_DIR}")
endif()

if (WINDOWS OR LINUX)
    file(COPY "${ASSETS_DIR}" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

if (NOT EMSCRIPTEN)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)

    FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                            GIT_TAG 1.11.2)
    FetchContent_MakeAvailable(cpr)
endif()

add_executable (${CMAKE_PROJECT_NAME} ${Project_SOURCES})

if(EMSCRIPTEN)
    set(SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_DEBUG -g3 -gsource-map -O0)

    set(SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_RELEASE -O3)

    set(SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS
        $<$<CONFIG:Debug>:${SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_DEBUG}>
        $<$<CONFIG:Release>:${SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_RELEASE}>
        #-pthread
    )

    set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_DEBUG -g3 -gsource-map -sASSERTIONS=2 -sCHECK_NULL_WRITES=1 -sSAFE_HEAP=1 -sSTACK_OVERFLOW_CHECK=1)

    set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_RELEASE -O3)

    set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_ASYNCIFY -sASYNCIFY=1)

    set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS
        $<$<CONFIG:Debug>:${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_DEBUG}>
        $<$<CONFIG:Release>:${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_RELEASE}>

        ${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_ASYNCIFY}

        -Wno-limited-postlink-optimizations # warning: running limited binaryen optimizations because DWARF info requested (or indirectly required)
        -Wno-pthreads-mem-growth            # warning: -pthread + ALLOW_MEMORY_GROWTH may run non-wasm code slowly, see https://github.com/WebAssembly/design/issues/1271

        -sALLOW_MEMORY_GROWTH=1             # Grow the memory arrays at runtime
        -sEXIT_RUNTIME=1                    # Execute cleanup (e.g. `atexit`) after `main` completes
        -sFETCH=1                           # Enables `emscripten_fetch` API
        -sFORCE_FILESYSTEM=1                # Makes full filesystem support be included
        -sFULL_ES2=1                        # Forces support for all GLES2 features, not just the WebGL-friendly subset
        -sMAX_WEBGL_VERSION=1               # Specifies the highest WebGL version to target
        -sMIN_WEBGL_VERSION=1               # Specifies the lowest WebGL version to target
        -sSTACK_SIZE=4mb                    # Set the total stack size
        #-sUSE_PTHREADS=1                    # Enable threading support
        -sWASM=1                            # Compile code to WebAssembly

        -sGL_EXPLICIT_UNIFORM_LOCATION=1  # TODO P0:
        -sGL_EXPLICIT_UNIFORM_BINDING=1   # TODO P0:

        --emrun                             # Add native support for `emrun` (I/O capture)
        --embed-file ${CMAKE_SOURCE_DIR}/assets@/
        -sTOTAL_MEMORY=32mb

        --shell-file=${CMAKE_SOURCE_DIR}/shell.html
    )
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    set(Freetype_DIR ${SFML_ROOT}/lib/cmake/freetype)
    set(Vorbis_DIR ${SFML_ROOT}/lib/cmake/Vorbis)
    set(Ogg_DIR ${SFML_ROOT}/lib/cmake/Ogg)
    set(FLAC_DIR ${SFML_ROOT}/lib/cmake/FLAC)
    set(SFML_DIR ${SFML_ROOT}/lib/cmake/SFML)
    find_package(SFML 3 COMPONENTS Graphics Audio Window System Network REQUIRED)

    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE ${SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS})
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE ${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS})
endif()

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)

if (EMSCRIPTEN)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE SFML_OPENGL_ES)
endif()

set (LINK_SFML SFML::System SFML::Window SFML::Graphics SFML::Audio SFML::Network)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
if (EMSCRIPTEN)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LINK_SFML})
else()
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SFML::Graphics cpr::cpr)
endif()


set(CMAKE_CXX_FLAGS "-fsanitize=address")
