cmake_minimum_required(VERSION 3.28)
project(Chess LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(
    main
    "src/animation functions.cpp"
    "src/backlight functions.cpp"
    "src/button class.cpp"
    "src/checks.cpp"
    "src/connector.cpp"
    "src/coordinate processing functions.cpp"
    "src/drawing functions.cpp"
    "src/drawn object class.cpp"
    "src/handling functions.cpp"
    "src/label class.cpp"
    "src/main.cpp"
    "src/move functions at mat.cpp"
    "src/move functions.cpp"
    "src/radio button class.cpp"
    "src/secondary functions.cpp"
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics nlohmann_json::nlohmann_json)

set(CMAKE_CXX_FLAGS "-fsanitize=address")
