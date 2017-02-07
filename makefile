all : optimize
optimize: rl_time.o
    $(CC) real-time.o -o optimize
rl_time.o: rl-time.c rl-time.h
    $(CC) $(FLAGS) rl-time.c
rl_time.o: rl_time.h tl_time.c
    $(CC) $(FLAGS) rl_time.c
rl_time.s: rl_time.h rl_time.c
    $(CC) $(ASM) -Wall rl_time.c
clean:
    rm -rf *.o
