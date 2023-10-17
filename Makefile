all:	
	gcc -o calc calc.c -lm
	./calc
clean:
	rm -f calc