CC=g++
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lm -lGL -lGLU -lglut -lglfw -lGLEW

NAME = demo

SRC =  main.cpp blocks/blocks.cpp view/opengl.cpp view/loader.cpp
DEPS = blocks/blocks.hpp view/opengl.hpp
# nazwy wszystkich plikow zrodlowych
OBJS = main.o blocks/blocks.o view/opengl.o
# nazwy wszystkich modulow
YOU: $(SRC) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME) 
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(NAME)
