output: main.cpp
	g++ main.cpp -lcurl -o output

clean:
	rm *.o output

