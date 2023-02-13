# Les règles de compilation peuvent utiliser les variables suivantes
# Consultez la documentation de make pour en savoir plus (et en
# trouver d’autres)
#
# $@  Le nom de la cible
# $<  Le nom de la première dépendance
# $^  La liste des dépendances

CC      = gcc
CFLAGS  = -Wall -Wextra -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

EXEC = multif \
       course \
       observe

.PHONY: clean test


all: $(EXEC)

observe: observe.o
	$(CC) $(CFLAGS) $< -o $@

course: course.o
	$(CC) $(CFLAGS) $< -o $@

multif: multif.o
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

test:
	bash test.sh

clean:
	rm -f *.o
	rm -f $(EXEC)
