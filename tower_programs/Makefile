all: tower_main tower_fan tower_led

clean: 
	-rm tower_main.out tower_fan.out tower_led.out

tower_fan:
	g++ -std=c++11 -o tower_fan.out tower_fan.cpp

tower_main:
	g++ -std=c++11 -o tower_main.out tower_main.cpp

tower_led:
	g++ -std=c++11 -o tower_led.out tower_led.cpp