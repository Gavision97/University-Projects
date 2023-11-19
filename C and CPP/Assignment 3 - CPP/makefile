Ass4: Game.o Map.o Robot.o
	g++ Game.o Map.o Robot.o -o Ass4

Game.o: Game.cpp Map.h Robot.h
	g++ -c Game.cpp

Map.o: Map.cpp Map.h
	g++ -c Map.cpp

Robot.o: Robot.cpp Robot.h
	g++ -c Robot.cpp

clean: 
	rm -f *.o
