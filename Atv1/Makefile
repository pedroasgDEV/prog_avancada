all:
	g++ main.cpp -o main -Wall

1:
	make
	./main < input/1.in

2:
	make
	./main < input/2.in

3:
	make
	./main < input/3.in

4:
	make
	./main < input/4.in

5:
	make
	./main < input/5.in

test:
	make
	./main < input/1.in > temp.out
	diff temp.out output/1.out
	./main < input/2.in > temp.out
	diff temp.out output/2.out
	./main < input/3.in > temp.out
	diff temp.out output/3.out
	./main < input/4.in > temp.out
	diff temp.out output/4.out
	./main < input/5.in > temp.out
	diff temp.out output/5.out
	rm temp.out
	make clear

clear:
	rm main