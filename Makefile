all: scroll-demo

scroll-demo: scroll-demo.c libscroll.so
	gcc -o $@ $< -L. -lscroll

libscroll.so: \
	gtk-scroll-controller.c \
	gtk-scroll-controller.h \
	gtk-scroll-model.c \
	gtk-scroll-model.h \
	gtk-scroll-view.c \
	gtk-scroll-view.h
	gcc -shared -o $@ $(filter %.c,$^)

check:

clean:


