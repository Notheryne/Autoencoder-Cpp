all:
	g++ test.cpp -o test -g \
	-lboost_serialization -lboost_system -lboost_filesystem \
	-lboost_iostreams \
	-lstdc++ -lm -std=c++14

run:
	test

