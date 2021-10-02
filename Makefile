CFLAGS = -std=c++17 -O2 -Wall -g

bin/tee: src/main.cpp src/tee.cpp
	g++ $(CFLAGS) -o bin/tee src/main.cpp src/tee.cpp

.PHONY: test clean

testOpt: bin/tee
	bin/tee -a testFile

test: bin/tee
	bin/tee testFile

clean:
	rm -f bin/tee