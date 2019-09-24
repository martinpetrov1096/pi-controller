all: pi_main pi_fan pi_led

clean: 
	rm *.out

pi_fan:
	g++ -std=c++11 -o pi_fan.out pi_fan.cpp -lwiringPi

pi_led:
	g++ -std=c++11 -o pi_led.out pi_led.cpp -lwiringPi

pi_main:
	g++ -std=c++11 -o pi_main.out pi_main.cpp -lwiringPi
