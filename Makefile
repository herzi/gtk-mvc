CCFLAGS=$(shell pkg-config --cflags gtk+-2.0)
LDFLAGS=$(shell pkg-config --libs gtk+-2.0)
CCLDFLAGS=$(CCFLAGS) $(LDFLAGS)

all: scroll-demo test-scroll

check: test-scroll
	./test-scroll

clean:
	rm -rf *.o libscoll.so scroll-demo test-scroll

libscroll_so_sources=\
	gtk-scroll-controller.c \
	gtk-scroll-controller.h \
	gtk-scroll-model.c \
	gtk-scroll-model.h \
	gtk-scroll-view.c \
	gtk-scroll-view.h \
	$(NULL)
libscroll_so_objects=$(patsubst %.c,%.o,$(filter %.c,$(libscroll_so_sources)))

%.o: %.c $(filter %.h,$(libscroll_so_sources))
	gcc -c -o $@ $< $(CCFLAGS)

libscroll.so: $(libscroll_so_objects)
	gcc -shared -o $@ $^ $(LDFLAGS)

scroll-demo: scroll-demo.c libscroll.so
	gcc -o $@ $< -L. -lscroll -Wl,"-rpath=$(shell pwd)" $(CCLDFLAGS)

test-scroll: test-scroll.c libscroll.so
	gcc -o $@ $< -L. -lscroll -Wl,"-rpath=$(shell pwd)" $(CCLDFLAGS)

