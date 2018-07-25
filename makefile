CC = gcc
CFLAGS = -Wall -pedantic -ansi #-g #comment out/in -g as required
OBJ = tvguide.o interface.o fileIO.o linkedList.o comparison.o #unittest.o
EXEC1 = ProductionBuild
ARG1 = test1.txt #file contains 1000 entries, can be changed as needed
ARG2 = output.txt #output to a set file


$(EXEC1) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC1)

tvguide.o : tvguide.c interface.h io.h list.h comparison.h
	$(CC) -c tvguide.c $(CFLAGS)

interface.o : interface.c interface.h list.h data.h boolean.h
	$(CC) -c interface.c $(CFLAGS)

fileIO.o : fileIO.c io.h interface.h list.h comparison.h data.h
	$(CC) -c fileIO.c $(CFLAGS)

linkedList.o : linkedList.c list.h boolean.h
	$(CC) -c linkedList.c $(CFLAGS)

comparison.o : comparison.c comparison.h data.h
	$(CC) -c comparison.c $(CFLAGS)



#used for rebuilding
clean :
	rm $(EXEC1) $(EXEC2) $(OBJ)

cleanobjects :
	rm $(OBJ)



#run the program, passing it a textfile from arg1, and outputting to arg2
run :
	./$(EXEC1) $(ARG1) $(ARG2)

#run the program with valgrind
runm :
	valgrind ./$(EXEC1) $(ARG1) $(ARG2)

#run the program with extended valgrind options
runmext :
	valgrind -v --leak-check=full ./$(EXEC1) $(ARG1) $(ARG2)
