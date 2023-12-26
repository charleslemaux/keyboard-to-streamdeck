includes= includes/gl.h\
					-I/usr/include/vulkan/\

SRC=	src/main.c\
		src/window.c\

LINKS=  -lvulkan -lcsfml-graphics -lcsfml-window -lcsfml-system -l    csfml-audio -lcsfml-network

all: clean build

run: build
		./gl.exe

build:
	gcc $(SRC) -o gl.exe $(includes) $(LINKS)

clean:
	rm gl.exe

.PHONY : build
