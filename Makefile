
# note: -Wall flag turns on all compiler warnings

igrep: igrep.c
	gcc -Wall -o igrep igrep.c

iecho: iecho.c
	gcc -Wall -o iecho iecho.c

clean:
	rm -f igrep iecho
