run:
	cc src/utils/* src/logger.c src/http/*  src/core/* main.c -o bin/server
	./bin/server

ab:
	ab -c 10 -n 10 http://127.0.0.1:8080/
