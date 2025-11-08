v1: 
	cc version_1.c
	./a.out

check: 
	lsof -i :8080
