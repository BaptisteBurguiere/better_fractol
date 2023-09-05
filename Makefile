NAME=better_fractol
CC=c++
FLAGS=-Wall -Wextra -Werror -g
SRCS=$(wildcard *.cpp) \
	$(wildcard shaders/*.cpp) \
	$(wildcard window/*.cpp) \

${NAME} :
	$(CC) -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -I/usr/local/include/glm/glm/glm -Iincludes $(SRCS) -o $(NAME) `sdl2-config --cflags --libs` -g

all : ${NAME}

clean :
	rm -rf ${NAME}

fclean : clean

re : fclean all