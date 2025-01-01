all:
	g++ main.cpp -o main.run -Wall

1:
	make
	./main.run < input/1.in

2:
	make
	./main.run < input/2.in

3:
	make
	./main.run < input/3.in

4:
	make
	./main.run < input/4.in

5:
	make
	./main.run < input/5.in

test:
	make
	./main.run < input/1.in > temp.out
	diff temp.out output/1.out
	./main.run < input/2.in > temp.out
	diff temp.out output/2.out
	./main.run < input/3.in > temp.out
	diff temp.out output/3.out
	./main.run < input/4.in > temp.out
	diff temp.out output/4.out
	./main.run < input/5.in > temp.out
	diff temp.out output/5.out
	rm temp.out
	make clear

clear:
	rm main.run temp.out