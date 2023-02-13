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

EXEC = maccess prlimit

all: maccess prlimit

maccess: maccess.o
	$(CC) $(LDFLAGS) -o $@ $^

prlimit: prlimit.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<


test: maccess
	bash test.sh	


clean:
	rm *.o
	rm $(EXEC)
