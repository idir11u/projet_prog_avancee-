CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -L./SDL2_ttf/.libs -L./SDL2_image/.libs
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image
INCLUDES =  -I./SDL2_ttf -I./SDL2_image
SCR = fonctions_SDL.h fonctions_fichiers.h gestion_terrain.h
EXEC = main
SRC = main.c fonctions_SDL.c fonctions_fichiers.c gestion_terrain.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)
main: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c $(SCR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf *.o *~
mrproper: cleanrm 
	-rf $(EXEC)