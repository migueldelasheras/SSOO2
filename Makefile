DIRSRC := src/
DIREST := estudiantes/

CC := gcc

all : dirs manager pa pb pc pd demonio

dirs:
	mkdir -p $(DIREST)

manager: 
	$(CC) -o manager $(DIRSRC)manager.c

pa: 
	$(CC) -o pa $(DIRSRC)pa.c

pb: 
	$(CC) -o pb $(DIRSRC)pb.c

pc: 
	$(CC) -o pc $(DIRSRC)pc.c

pd: 
	$(CC) -o pd $(DIRSRC)pd.c

demonio:
	$(CC) -o demonio $(DIRSRC)demonio.c

test:
	./manager

clean : 
	rm -rf manager pa pb pc pd demonio log.txt *~ core $(DIREST) *~
