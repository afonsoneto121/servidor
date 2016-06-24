ServidorTCP: servidor_TCP.o vaga.o lista.o
	gcc -o ServidorTCP servidor_TCP.o vaga.o lista.o

servidor_TCP.o: servidor_TCP.c
	gcc -c servidor_TCP.c

vaga.o: Vaga/vaga.c 
	gcc -c Vaga/vaga.c

lista.o: Vaga/lista.c
	gcc -c Vaga/lista.c

clean:
	rm *.o ServidorTCP
