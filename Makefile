CC = g++

packer = ./upx.exe

INCLUDE_PATHS = -IC:/mingwDevLibs/include
# #https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
# #change Oz to Os then Ofast + -flto if performance dies
COMPILER_FLAGS = -Oz -s -x -w -Wl,-Bdynamic 

LIBRARY_PATHS = -LC:/mingwDevLibs/lib
LINKER_FLAGS = -pthread -flto -lglfw3 -lopengl32 -lgdi32 #-Wl,-subsystem,windows

srcDir = src
objDir = obj
outDir = out
functDir = $(srcDir)/functs
classDir = $(srcDir)/classes


#external

gl.c = $(srcDir)/gl.c
gl.o = $(objDir)/gl.o

#functs

main.cpp = $(srcDir)/main.cpp
main.o = $(objDir)/main.o

init.cpp = $(functDir)/init/init.cpp
init.o = $(objDir)/init.o

readFile.cpp = $(functDir)/readFile/readFile.cpp
readFile.o = $(objDir)/readFile.o


#classes

VertBuffer.cpp = $(classDir)/VertBuffer/VertBuffer.cpp
VertBuffer.o = $(objDir)/VertBuffer.o

VertArray.cpp = $(classDir)/VertArray/VertArray.cpp
VertArray.o = $(objDir)/VertArray.o

Shader.cpp = $(classDir)/Shader/Shader.cpp
Shader.o = $(objDir)/Shader.o

Object.cpp = $(classDir)/Object/Object.cpp
Object.o = $(objDir)/Object.o


#all the .o files

objs = $(objDir)/*.o #$(gl.o) $(main.o)


#exe

execute = $(outDir)/main



all : main gl init vertBuffer vertArray object


#external dependencies

gl : $(gl.c)
	$(CC) -o $(gl.o) -c $(gl.c) $(INCLUDE_PATHS) $(COMPILER_FLAGS)


#functions

main : $(main.cpp)
	$(CC) -o $(main.o) -c $(main.cpp) $(INCLUDE_PATHS) $(COMPILER_FLAGS)

init : $(init.cpp)
	$(CC) -o $(init.o) -c $(init.cpp) $(INCLUDE_PATHS) $(COMPILER_FLAGS)

readFile : $(readFile.cpp)
	$(CC) -o $(readFile.o) -c $(readFile.cpp) $(INCLUDE_PATHS) $(COMPILER_FLAGS)


#classes

vertBuffer : $(VertBuffer.cpp)
	$(CC) -o $(VertBuffer.o) -c $(VertBuffer.cpp) $(INCLUDE_PATHS) $(COMPILER_FLAGS)

vertArray : $(VertArray.cpp)
	$(CC) -o $(VertArray.o) -c $(VertArray.cpp) $(INCLUDE_PATHS) $(COMPILER_FLAGS)

object : $(Object.cpp)
	$(CC) -o $(Object.o) -c $(Object.cpp) $(INCLUDE_PATHS) $(COMPILER_FLAGS)


#other steps

link :
	$(CC) -o $(execute) $(main.o) $(init.o) $(Object.o) $(VertBuffer.o) $(VertArray.o) $(gl.o) $(LIBRARY_PATHS) $(LINKER_FLAGS)

pack :
	$(packer) $(execute).exe --all-methods

unpack :
	$(packer) -d $(execute).exe

clean:
	rm -f $(objs)

cleanclean: clean 
	rm -f $(execute)