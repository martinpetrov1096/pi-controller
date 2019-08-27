all: tower_main tower_fan

clean: 
	-rm tower_main tower_fan


tower_main:
	g++ -std=c++11 -o tower_main server_side.cpp

tower_fan:
	g++ -std=c++11 -o tower_fan fan_client_side.cpp