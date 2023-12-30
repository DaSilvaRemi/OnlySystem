CC = gcc
OBJ = listNode.o linkedList.o node.o tree.o fileSystem.o ui.o main.o 
EXE = run

all: $(EXE)

.c.o: ; $(CC) -c $*.c

$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ)

clean: 
	rm -rf $(EXE) *.o *d core