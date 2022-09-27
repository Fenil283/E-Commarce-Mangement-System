CC=gcc
CFLAGS=-I. -lm


ldir = ~/Documents/project/

ODIR=~/Documents/project/obj
OutDIR=~/Documents/project/out

obj = $(patsubst %,$(ODIR)/%,$(_OBJ))
out = $(patsubst %,$(OutDIR)/%,$(_Out))

o_files =../obj/verify_user_login.o ../obj/open_usr_history.o ../obj/place_order.o ../obj/open_usr_profile.o ../obj/check_already_if_user.o ../obj/login_user.o ../obj/new_user.o ../obj/customer_client.o ../obj/server.o ../obj/main.o

out_files =verify_user_login.out open_usr_history.out place_order.out open_usr_profile.out check_already_if_user.out login_user.out new_user.out customer_client.out server.out main.out 

../obj/main.o: ../src/main.c
	$(CC) -o $@ $< $(CFLAGS)
	
../obj/new_user.o: ../src/new_user.c
	$(CC) -o $@ $^ $(CFLAGS)

../obj/login_user.o: ../src/login_user.c
	$(CC) -o $@ $^ $(CFLAGS)

../obj/check_already_if_user.o: ../src/check_already_if_user.c
	$(CC) -o $@ $^ $(CFLAGS)

../obj/open_usr_history.o: ../src/open_usr_history.c
	$(CC) -o $@ $^ $(CFLAGS)
	
../obj/open_usr_profile.o: ../src/open_usr_profile.c
	$(CC) -o $@ $^ $(CFLAGS)

../obj/place_order.o: ../src/place_order.c
	$(CC) -o $@ $^ $(CFLAGS)

../obj/verify_user_login.o: ../src/verify_user_login.c
	$(CC) -o $@ $^ $(CFLAGS)

../obj/customer_client.o: ../src/customer_client.c
	$(CC) -o $@ $^ $(CFLAGS)
	
../obj/server.o: ../src/server.c
	$(CC) -o $@ $^ $(CFLAGS)
	
	
main.out: ../src/main.c
	$(CC) -o $@ $< $(CFLAGS)
	
new_user.out: ../src/new_user.c
	$(CC) -o $@ $^ $(CFLAGS)

login_user.out: ../src/login_user.c
	$(CC) -o $@ $^ $(CFLAGS)

check_already_if_user.out: ../src/check_already_if_user.c
	$(CC) -o $@ $^ $(CFLAGS)

open_usr_history.out: ../src/open_usr_history.c
	$(CC) -o $@ $^ $(CFLAGS)
	
open_usr_profile.out: ../src/open_usr_profile.c
	$(CC) -o $@ $^ $(CFLAGS)

place_order.out: ../src/place_order.c
	$(CC) -o $@ $^ $(CFLAGS)

verify_user_login.out: ../src/verify_user_login.c
	$(CC) -o $@ $^ $(CFLAGS)

customer_client.out: ../src/customer_client.c
	$(CC) -o $@ $^ $(CFLAGS)
	
server.out: ../src/server.c
	$(CC) -o $@ $^ $(CFLAGS)
	

.PHONY: out
out:$(out_files)


.PHONY: object
object:$(o_files)


	
	



