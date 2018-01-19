EXE	= dyn-shell.so
E_OBJ	= dyn-shell.o
LIB	= dyn-plugin.so
L_OBJ	= dyn-plugin.o
CFLAGS	= -fPIC -fvisibility=hidden

all: $(EXE) $(LIB)

$(EXE): $(E_OBJ) dyn-shell.sym
	$(LD) -shared $(E_OBJ) -ldl -e entry -o $@

$(LIB): $(L_OBJ)
	$(LD) -shared $(L_OBJ) -o $@

clean:
	rm -f $(E_OBJ) $(L_OBJ)
