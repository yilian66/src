CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi addc.cgi delc.cgi modc.cgi selc.cgi  addsc.cgi delsc.cgi modsc.cgi selsc.cgi 

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi

install:
	cp *.cgi /usr/lib/cgi-bin/sx/
	sudo cp -r public/ main.html /var/www/html
	sudo cp -r public/ index.html /var/www/html
	sudo cp -r public/ course.html /var/www/html
	sudo cp -r public/ sc.html /var/www/html
