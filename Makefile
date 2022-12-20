install: scriptRunner
	rm -rf *.o

scriptRunner: command.o scriptRunner.o
	gcc scriptRunner.o command.o os.o types.o cleanup.o misc.o -o scriptRunner

scriptRunner.o:
	gcc src/scriptRunner.c -c scriptRunner.o

command.o: misc.o cleanup.o types.o os.o
	gcc src/command.c -c command.o

os.o:
	gcc src/os.c -c os.o

types.o: cleanup.o
	gcc src/types.c -c types.o

cleanup.o:
	gcc src/cleanup.c -c cleanup.o

misc.o:
	gcc src/misc.c -c misc.o

uninstall:
	rm -rf scriptRunner