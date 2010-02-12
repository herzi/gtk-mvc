CCLDFLAGS=$(shell pkg-config --cflags --libs gtk+-2.0)

all: scroll-demo test-scroll

check: test-scroll
	./test-scroll

clean:
	rm -rf scroll-demo libscoll.so test-scroll

libscroll.so: \
	gtk-scroll-controller.c \
	gtk-scroll-controller.h \
	gtk-scroll-model.c \
	gtk-scroll-model.h \
	gtk-scroll-view.c \
	gtk-scroll-view.h
	gcc -shared -o $@ $(filter %.c,$^) $(CCLDFLAGS)

scroll-demo: scroll-demo.c libscroll.so
	gcc -o $@ $< -L. -lscroll -Wl,"-rpath=$(shell pwd)" $(CCLDFLAGS)

test-scroll: test-scroll.c libscroll.so
	gcc -o $@ $< -L. -lscroll -Wl,"-rpath=$(shell pwd)" $(CCLDFLAGS)

