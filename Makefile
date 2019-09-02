all: tower_main tower_fan tower_led

clean: 
	-rm tower_main tower_fan tower_led

tower_fan:
	g++ -std=c++11 -o tower_fan tower_fan.cpp

tower_main:
	g++ -std=c++11 -o tower_main tower_main.cpp

tower_led:
	g++ -std=c++11 -o tower_led tower_led.cpp