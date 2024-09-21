Create_FLAGS = -Iinc -I. -Ifl

SOURCES = $(wildcard src/*.c)

create: gcc -o ${Create_FLAGS} ${SOURCES} -o main.exe

clean:
	rm -f main.exe