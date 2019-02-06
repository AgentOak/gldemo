UFLAGS=

CC=gcc
WFLAGS=-Wall -Wextra -Wshadow -Wno-conversion -Wformat=2

#CC=clang
#WFLAGS=-Weverything -Wno-reserved-id-macro -Wno-conversion -Wno-double-promotion

CFLAGS=-O2 -g -std=c99 -pedantic $(WFLAGS) $(UFLAGS)

LIB=-lglfw -ldl -lm
INC=-Iinclude

SRCDIR=src
SHADERDIR=shader
BUILDDIR=build
EXTERNALSDIR=externals

EXE=gldemo
DEPS=src/master.h src/window.h src/renderer.h src/model.h src/light.h src/input.h src/util.h include/glad/glad.h include/linmath.h include/tinyobj_loader_c.h
OBJ=main.o window.o renderer.o model.o light.o input.o util.o glad.o tinyobj_loader_c.o
SHADER=main.vert main.frag

# TODO: Release build option with LTO, -DNDEBUG, no debug info, stripped

#---------------------------------------------------------------------------------
# Do not edit below this line
#---------------------------------------------------------------------------------
OBJ_PATH=$(addprefix $(BUILDDIR)/,$(OBJ))
SHADER_PATH=$(addprefix $(SHADERDIR)/,$(SHADER))

all: $(EXE) validateshaders

# Miscellaneous goals
rebuild: clean all

clean:
	rm -Rf $(BUILDDIR) $(EXE)

validateshaders: $(SHADER_PATH)

# Link main executable
$(EXE): $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

# Build dependencies using different flags
$(BUILDDIR)/glad.o: $(EXTERNALSDIR)/glad.c include/glad/glad.h include/KHR/khrplatform.h | $(BUILDDIR)/
	$(CC) -O3 -Wall -Wextra -Wshadow -Wconversion -Wformat=2 -std=c89 $(INC) -c -o $@ $<

$(BUILDDIR)/tinyobj_loader_c.o: $(EXTERNALSDIR)/tinyobj_loader_c.c include/tinyobj_loader_c.h | $(BUILDDIR)/
	$(CC) -O3 -Wall -Wextra -Wshadow -Wconversion -Wformat=2 -std=c89 $(INC) -c -o $@ $<

# Build own source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS) | $(BUILDDIR)/
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Validate shader
$(SHADER_PATH):
	glslangValidator $@

# Directories
%/:
	mkdir -p $@

.PHONY: all rebuild clean $(SHADER_PATH) validateshaders
