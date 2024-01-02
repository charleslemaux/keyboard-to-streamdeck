includes= 	includes/gl.h\
			includes/keyboards.h\
			-I/usr/include/vulkan/\
			-I/usr/include/libevdev-1.0

SRC=		src/main.c\
			src/window.c\
			src/menu_ui.c\
			src/keyboards.c\
			src/sfml_utils.c\
			src/keyboard_listener.c\

LINKS=  -lvulkan -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lcsfml-network -levdev -ludev -llua

all: build

re : clean run

run: build
		./gl

build:
	gcc $(SRC) -o gl $(includes) $(LINKS)

clean:
	rm gl

.PHONY : build
