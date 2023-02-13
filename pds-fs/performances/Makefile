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
TEST_DIR=fs_test
DATA_FILE=mcat_tm.dat

EXEC = mcat-scd


mcat-scd: mcat-scd.o
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

test: clean mcat-scd
	bash test.sh


clean:
	rm -f *.o
	rm -f $(EXEC)
	rm -f mcat-tm.dat
	rm -rf $(TEST_DIR)
	rm -f $(DATA_FILE)
