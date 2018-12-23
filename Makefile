CC=gcc

CFLAGS=-O2 -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-error=unused-function -std=c99 -pedantic
LIB=-lglfw -ldl -lm
INC=-Iinclude

SRCDIR=src
SHADERDIR=shader
BUILDDIR=build

EXE=gldemo
DEPS=src/message.h src/gldemo.h src/scene.h src/util.h include/glad/glad.h include/linmath.h
OBJ=main.o gldemo.o scene.o util.o glad.o
SHADER=

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
	$(CC) $(CFLAGS) $(LIB) -o $@ $^

# Build GLAD using different flags
$(BUILDDIR)/glad.o: $(SRCDIR)/glad.c include/glad/glad.h include/KHR/khrplatform.h | $(BUILDDIR)/
	$(CC) -O2 -Wall -Wextra -Werror -std=c99 $(INC) -c -o $@ $<

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
