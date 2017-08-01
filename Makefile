smsh:
	gcc smsh.c process.c controlflow.c memory.c signal.c error.c string_op.c builtin.c vartable.c utils.c -o smsh

clean:
	rm ./smsh
