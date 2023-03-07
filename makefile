data: data.c
	gcc data.c -o data

cli_ser:
	gcc -pthread server.c -o server
	gcc client.c -o client

clean:
	ls | grep -v "\." | grep -v makefile | xargs rm
	clear