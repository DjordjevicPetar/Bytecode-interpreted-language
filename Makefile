Create_FLAGS = -Iinc -I. -Ifl -g

SOURCES = $(wildcard src/*.c)

run:
	./main.exe code.txt

create: 
	gcc ${Create_FLAGS} ${SOURCES} -o main.exe

clean:
	del main.exe