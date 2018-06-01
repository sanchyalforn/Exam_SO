
PROGS=chaint writer_np reader_np invjump

all: $(PROGS)

invjump: invjump.c
	gcc -o invjump invjump.c

chaint: chaint.c
	gcc -o chaint chaint.c

writer_np: writer_np.c
	gcc -o writer_np writer_np.c

reader_np: reader_np.c
	gcc -o reader_np reader_np.c

clean:
	rm -f $(PROGS)

zip:
	zip sol_clab21617q1.zip *.c *.h Makefile 
	
