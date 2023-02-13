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

EXEC = mtail

mtail: mtail.o
	$(CC) $(CFLAGS) $< -o $@

mtail_stupide: mtail_stupide.o
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

test: mtail
	bash test.sh

clean:
	rm -f *.o
	rm -f $(EXEC)
	rm -f mtail
	rm -f mtail_stupide
