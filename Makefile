ServidorTCP: servidor_TCP.o vaga.o 
	gcc -o ServidorTCP servidor_TCP.o vaga.o

servidor_TCP.o: servidor_TCP.c
	gcc -c servidor_TCP.c

vaga.o: vaga.c
	gcc -c vaga.c

clean:
	rm *.o ServidorTCP
