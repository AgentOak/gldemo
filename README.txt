Build Dependencies:
clang make pkg-config libglfw3-dev glslang-tools

Note: Run make clean before switching between debug/release

Make debug build:
make -j$(nproc)

Make release build (no debugging symbols, more optimizations):
make -j$(nproc) release
