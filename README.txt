Build Dependencies:
make gcc libglfw3 libglfw3-dev glslang-tools

Build:
make -j$(nproc)

Build using clang:
make -j$(nproc) CC=clang

Build with custom flags:
make -j$(nproc) UFLAGS=-flto
