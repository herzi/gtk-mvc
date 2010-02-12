all: scroll-demo

scroll-demo: scroll-demo.c
	gcc -o $@ $<

check:

clean:


