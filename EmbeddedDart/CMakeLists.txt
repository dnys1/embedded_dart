cmake_minimum_required(VERSION 3.26)
project(EmbeddedDart)

set(CMAKE_CXX_STANDARD 23)

add_executable(EmbeddedDart main.cpp)

# Configure Dart SDK
set(DART_SDK_ROOT "${PROJECT_SOURCE_DIR}/../../dart-sdk/sdk" CACHE FILEPATH "Directory where dart-lang/sdk is cloned")
set(DART_SDK_OUT "${DART_SDK_ROOT}/xcodebuild/ReleaseARM64" CACHE FILEPATH "Directory where Dart SDK is compiled")
target_include_directories(EmbeddedDart PUBLIC
        "${DART_SDK_ROOT}/runtime")
find_library(LIB_DART_DEBUG
        dart_precompiled_runtime
        HINTS "${DART_SDK_OUT}/obj/runtime"
        REQUIRED)
find_library(LIB_DART_RELEASE
        dart_precompiled_runtime_product
        HINTS "${DART_SDK_OUT}/obj/runtime"
        REQUIRED)
target_link_libraries(EmbeddedDart debug ${LIB_DART_DEBUG})
target_link_libraries(EmbeddedDart optimized ${LIB_DART_RELEASE})

# NOTE: This does not work.
# Link in elf_loader so that Dart_LoadELF is available? (not included in precompiled_runtime by default?)
target_link_libraries(EmbeddedDart "${DART_SDK_OUT}/obj/runtime/bin/elf_loader.elf_loader.o")
