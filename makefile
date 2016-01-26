#
# Charles Smith
#
# Wed Jan 20, 2016
#
# To build project, cd to pay_share/ and run "make"
# This will produce the executable pay_share which can be run like:
#     ./pay_share
#
# To clean, run "make clean"
#

IDIR   =include
SRCDIR =src
ODIR   =obj
LDIR   =lib

CC     =gcc
CFLAGS =-I$(IDIR)
LIBS   =-lm

_DEPS = pay.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o pay_init.o pay_print.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pay_share: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

