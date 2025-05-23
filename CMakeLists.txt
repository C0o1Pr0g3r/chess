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

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 1.11.2)
FetchContent_MakeAvailable(cpr)

add_executable(
    main
    "src/game-save-api/interface.cpp"
    "src/game-save-api/native-game-save-api.cpp"
    "src/get-next-move-api/stockfish-online-get-next-move-api.cpp"
    "src/animation functions.cpp"
    "src/backlight functions.cpp"
    "src/button class.cpp"
    "src/checks.cpp"
    "src/connector.cpp"
    "src/coordinate processing functions.cpp"
    "src/drawing functions.cpp"
    "src/drawn object class.cpp"
    "src/fen.cpp"
    "src/handling functions.cpp"
    "src/label class.cpp"
    "src/main.cpp"
    "src/move functions at mat.cpp"
    "src/move functions.cpp"
    "src/radio button class.cpp"
    "src/secondary functions.cpp"
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics nlohmann_json::nlohmann_json cpr::cpr)

set(CMAKE_CXX_FLAGS "-fsanitize=address")
