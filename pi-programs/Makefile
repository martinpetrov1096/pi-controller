all: pi_main pi_fan pi_led

clean: 
	rm *.out

pi_fan:
	g++ -std=c++11 -o pi_fan.out pi_fan.cpp -pthread -lwiringPi

pi_led:
	g++ -std=c++11 -o pi_led.out pi_led.cpp -lwiringPi -lpthread


pi_main:
	g++ -std=c++11 -o pi_main.out pi_main.cpp -lwiringPi
