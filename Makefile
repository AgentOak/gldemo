#
# Compiler
#
CC = clang
WFLAGS = -Weverything -Wno-reserved-id-macro -Wno-conversion -Wno-double-promotion -Wno-format-nonliteral -Wno-padded -Wno-cast-qual
#CC = gcc
#WFLAGS = -Wall -Wextra -Wshadow -Wformat=2

EXE = gldemo

#
# Directories
#
SRCDIR    = src
SHADERDIR = shader
BUILDDIR  = build
EXTDIR    = externals
INCDIR    = include

#
# CFlags
#
CFLAGS_DEBUG   = -O2 -g -DDEBUG -std=c99 -pedantic $(WFLAGS)
CFLAGS_RELEASE = -O3 -flto -march=core2 -mtune=generic -DNDEBUG -std=c99 -pedantic $(WFLAGS)

LIB = `pkg-config --libs glfw3` -ldl -lm
INC = -I$(INCDIR)

#
# Source files
#
DEPS_SRC = master.h window.h input.h
OBJS_SRC = main.o window.o input.o

DEPS_SRC += util/file.h util/string.h util/math.h
OBJS_SRC += util/file.o util/string.o

# TODO: Build renderer as own "module", nothing should have dependencies to headers other than renderer.h
DEPS_SRC += renderer/renderer.h renderer/model.h renderer/light.h renderer/shader.h
OBJS_SRC += renderer/renderer.o renderer/model.o renderer/light.o renderer/shader.o

DEPS_EXT = glad/glad.h linmath.h tinyobj_loader_c.h
OBJS_EXT = glad.o tinyobj_loader_c.o

SHADERS  = project.vert phong.frag

###############################################################################

DEPS_SRC_PATH = $(addprefix $(SRCDIR)/,$(DEPS_SRC))
DEPS_EXT_PATH = $(addprefix $(INCDIR)/,$(DEPS_EXT))
OBJS_SRC_PATH = $(addprefix $(BUILDDIR)/,$(OBJS_SRC))
OBJS_EXT_PATH = $(addprefix $(BUILDDIR)/$(EXTDIR)/,$(OBJS_EXT))
SHADERS_PATH  = $(addprefix $(SHADERDIR)/,$(SHADERS))

#
# Miscellaneous
#
.PHONY: all
all: debug

.PHONY: debug
debug: CFLAGS=$(CFLAGS_DEBUG)
debug: $(EXE) validateshaders

.PHONY: release
release: CFLAGS=$(CFLAGS_RELEASE)
release: $(EXE) validateshaders
	strip -s $(EXE)

.PHONY: clean
clean:
	rm -Rf $(BUILDDIR) $(EXE)

#
# Link main executable
#
$(EXE): $(OBJS_SRC_PATH) $(OBJS_EXT_PATH)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

#
# Compile
#
$(BUILDDIR)/$(EXTDIR)/glad.o: $(EXTDIR)/glad.c $(DEPS_EXT_PATH)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Wno-pedantic $(INC) -c -o $@ $<

$(BUILDDIR)/$(EXTDIR)/%.o: $(EXTDIR)/%.c $(DEPS_EXT_PATH)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS_EXT_PATH) $(DEPS_SRC_PATH)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

#
# Validate shaders
#
.PHONY: validateshaders
validateshaders: $(SHADERS_PATH)

.PHONY: $(SHADERS_PATH)
$(SHADERS_PATH):
	-glslangValidator $@
