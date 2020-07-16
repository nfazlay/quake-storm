all:		convert analyze
	gcc -o convertToBinary convertToBinary.o
	gcc -o disasterAnalyzer disasterAnalyzer.o
convert:	convertToBinary.c
	gcc -c convertToBinary.c
analyze:	disasterAnalyzer.c
	gcc -c disasterAnalyzer.c

clean:
	rm -f convertToBinary.o convertToBinary disasterAnalyzer.o disasterAnalyzer CDD2.bin
