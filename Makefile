includes= 	includes/gl.h\
			-I/usr/include/vulkan/\
			-I/usr/include/libevdev-1.0

SRC=		src/main.c\
			src/window.c\

LINKS=  -lvulkan -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lcsfml-network -levdev -ludev

all: clean build

run: build
		./gl.exe

build:
	gcc $(SRC) -o gl.exe $(includes) $(LINKS)

clean:
	rm gl.exe

.PHONY : build
