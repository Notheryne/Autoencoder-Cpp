all:
	g++ visual.cpp -o visual -g \
	-lboost_serialization -lboost_system -lboost_filesystem \
	-lboost_iostreams \
	-lstdc++ -lm -std=c++14

run:
	main

