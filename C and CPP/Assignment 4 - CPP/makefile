Ass5: main.o Party.o Politician.o PoliticalSys.o RepublicanParty.o DemocraticParty.o RepublicanPoliticianLeader.o RepublicanPoliticianSocial.o DemocraticPoliticianLeader.o DemocraticPoliticianSocial.o
	g++ main.o Party.o Politician.o PoliticalSys.o RepublicanParty.o DemocraticParty.o RepublicanPoliticianLeader.o RepublicanPoliticianSocial.o DemocraticPoliticianLeader.o DemocraticPoliticianSocial.o -o Ass5

main.o: main.cpp PoliticalSys.h RepublicanParty.h Party.h Politician.h DemocraticParty.h DemocraticPoliticianSocial.h DemocraticPoliticianLeader.h RepublicanPoliticianLeader.h RepublicanPoliticianSocial.h Exceptions.h
	g++ -c main.cpp
	
DemocraticParty.o: DemocraticParty.cpp DemocraticParty.h Party.h Politician.h
	g++ -c DemocraticParty.cpp
	
DemocraticPoliticianLeader.o: DemocraticPoliticianLeader.cpp DemocraticPoliticianLeader.h Politician.h
	g++ -c DemocraticPoliticianLeader.cpp

DemocraticPoliticianSocial.o: DemocraticPoliticianSocial.cpp DemocraticPoliticianSocial.h Politician.h
	g++ -c DemocraticPoliticianSocial.cpp
	
Party.o: Party.cpp Party.h Politician.h
	g++ -c Party.cpp

PoliticalSys.o: PoliticalSys.cpp PoliticalSys.h RepublicanParty.h Party.h Politician.h DemocraticParty.h DemocraticPoliticianSocial.h DemocraticPoliticianLeader.h RepublicanPoliticianLeader.h RepublicanPoliticianSocial.h Exceptions.h
	g++ -c PoliticalSys.cpp
	
Politician.o: Politician.cpp Politician.h
	g++ -c Politician.cpp

RepublicanParty.o: RepublicanParty.cpp RepublicanParty.h Party.h Politician.h
	g++ -c RepublicanParty.cpp

RepublicanPoliticianLeader.o: RepublicanPoliticianLeader.cpp RepublicanPoliticianLeader.h Politician.h
	g++ -c RepublicanPoliticianLeader.cpp

RepublicanPoliticianSocial.o: RepublicanPoliticianSocial.cpp RepublicanPoliticianSocial.h Politician.h
	g++ -c RepublicanPoliticianSocial.cpp

clean:
	rm -f *.o
