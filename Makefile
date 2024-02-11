all: compile link 

compile:
	g++ -Isfml/include -c src/Main.cpp  src/ClassReq.cpp src/ClassBus.cpp src/ClassMetro.cpp src/menu.cpp src/Class-Taxi.cpp src/Short.cpp

link:
	g++ Main.o ClassBus.o ClassMetro.o ClassReq.o menu.o Class-Taxi.o Short.o