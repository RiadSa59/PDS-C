CC      = gcc

CFLAGS  = -Wall -Wextra -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

LDFLAGS = -g

EXEC = do

tout: args do

# Pour construire le programme binaire « args », il est nécessaire de
# faire l’édition des liens de tous les .o qui contiennent son code
# « args » dépend donc de « args.o » mais aussi de « makeargv.o »
args: makeargv.o args.o

# Règles implicites pour la compilation et l’édition de liens
%.o: %.c
	${CC} ${CFLAGS} -c $<

%: %.o
	${CC} ${LDFLAGS} -o $@ $^

%: %.c

# Règles de nettoyage
clean:
	rm -f core *.o

realclean: clean
	rm -f args
	rm -f $(EXEC)

test: tout
	./test.sh

.PHONY: tout clean realclean
