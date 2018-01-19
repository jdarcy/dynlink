EXE	= dyn-shell.so
E_OBJ	= dyn-shell.o
LIB	= dyn-plugin.so
L_OBJ	= dyn-plugin.o
CFLAGS	= -fPIC

all: $(EXE) $(LIB)

$(EXE): $(E_OBJ)
	$(LD) -shared $(E_OBJ) -ldl -e main -o $@

$(LIB): $(L_OBJ)
	$(LD) -shared $(L_OBJ) -u callback -o $@

clean:
	rm -f $(E_OBJ) $(L_OBJ)
