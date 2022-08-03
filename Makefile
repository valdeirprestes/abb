CC = gcc -g -O0 -Wall
MAT = -lm
SRC = abb.c app.c
OBJS = abb.o app.o
APP=app

all : app
	@echo Projeto compilado!
%.o : %.c
	$(CC)  -c -o  $@ $<
app : $(OBJS)
	$(CC)  -o $(APP) $(OBJS) $(MAT)
clean:
	@rm -fv $(OBJS) $(APP)
