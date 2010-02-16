CCFLAGS=$(shell pkg-config --cflags gtk+-2.0)
LDFLAGS=$(shell pkg-config --libs gtk+-2.0)
CCLDFLAGS=$(CCFLAGS) $(LDFLAGS)

all: scroll-demo test-mvc

check: test-mvc
	./test-mvc

clean:
	rm -rf *.o libscoll.so scroll-demo test-mvc

libscroll_so_sources=\
	gdk-window.c \
	gdk-window.h \
	gtk-mvc.h \
	gtk-mvc-adaptor.c \
	gtk-mvc-adaptor.h \
	gtk-mvc-button-controller.c \
	gtk-mvc-button-controller.h \
	gtk-mvc-button-view.c \
	gtk-mvc-button-view.h \
	gtk-mvc-controller.c \
	gtk-mvc-controller.h \
	gtk-mvc-default-controller.c \
	gtk-mvc-default-controller.h \
	gtk-mvc-default-view.c \
	gtk-mvc-default-view.h \
	gtk-mvc-model.c \
	gtk-mvc-model.h \
	gtk-mvc-primitives.h \
	gtk-mvc-scroll-controller.c \
	gtk-mvc-scroll-controller.h \
	gtk-mvc-scroll-view.c \
	gtk-mvc-scroll-view.h \
	gtk-mvc-view.c \
	gtk-mvc-view.h \
	gtk-scroll-model.c \
	gtk-scroll-model.h \
	$(NULL)
libscroll_so_objects=$(patsubst %.c,%.o,$(filter %.c,$(libscroll_so_sources)))

%.o: %.c $(filter %.h,$(libscroll_so_sources))
	gcc -g -c -o $@ $< $(CCFLAGS)

libscroll.so: $(libscroll_so_objects)
	gcc -g -shared -o $@ $^ $(LDFLAGS)

scroll-demo: scroll-demo.c libscroll.so
	gcc -g -o $@ $< -L. -lscroll -Wl,"-rpath=$(shell pwd)" $(CCLDFLAGS)

test-mvc: test-mvc.c libscroll.so
	gcc -g -o $@ $< -L. -lscroll -Wl,"-rpath=$(shell pwd)" $(CCLDFLAGS)

