IDIR=include
CC=gcc
# Optimization level zero for debugging, make clean when changing optimization level
CFLAGS=-I$(IDIR) -Wall -Wextra -Werror -O2 --ansi --pedantic

ODIR=src/obj

LIBS=

_DEPS=
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o trie.o spellcheck.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

spellcheck: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
