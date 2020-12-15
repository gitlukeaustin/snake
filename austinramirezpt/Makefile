#Auteur: Luke Austin

goal : buildsnake

CFLAGS = -I/Users/Luke/Desktop/graph/include \
	-L/Users/Luke/Desktop/graph/lib \
	-I/opt/X11/include \
	-lgraph

OFILES = sfx.o \
	snake.o

CC = gcc

sfx.o : sfx.h

snake.o : sfx.h

buildsnake : $(OFILES)
	$(CC) -o snake $(CFLAGS) $(OFILES)

.PHONY : clean 
clean:
	-rm $(OFILES) buildsnake


