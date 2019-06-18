## gldemo

Basic OpenGL 3.2 application for educational purposes.

### Requirements

* OpenGL 3.2 core profile capable renderer
    * (Mesa's llvmpipe software renderer works well)

### Build Dependencies

* `make pkg-config`
* `clang` (or edit `Makefile` to use `gcc` instead)
* `libglfw3 libglfw3-dev`
* `glslang-tools`

### Building

Note: Run `make clean` before switching between debug/release

Make debug build:

```
make -j$(nproc)
```

Make release build (no debugging symbols, more optimizations):

```
make -j$(nproc) release
```

### License

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
