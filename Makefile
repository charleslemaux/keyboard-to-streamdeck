includes= 	includes/gl.h\
			includes/keyboards.h\
			-I/usr/include/vulkan/\
			-I/usr/include/libevdev-1.0

SRC=		src/main.c\
			src/window.c\
			src/keyboards.c\

LINKS=  -lvulkan -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lcsfml-network -levdev -ludev

all: build

run: build
		./gl

build:
	gcc $(SRC) -o gl $(includes) $(LINKS)

clean:
	rm

.PHONY : build
