CXX = g++
CXXFLAGS = -O2 -Wall -g


all:crawl docoff rawseg preinvert invert serv

crawl:crawl.cpp
	$(CXX) $(CXXFLAGS) -o crawl crawl.cpp

docoff:docoff.cpp
	$(CXX) $(CXXFLAGS) -o docoff docoff.cpp

rawseg:rawseg.cpp Dict.cpp HzSeg.cpp
	$(CXX) $(CXXFLAGS) -o rawseg rawseg.cpp Dict.cpp HzSeg.cpp

preinvert:preinvert.cpp
	$(CXX) $(CXXFLAGS) -o preinvert preinvert.cpp

invert:invert.cpp
	$(CXX) $(CXXFLAGS) -o invert invert.cpp

serv:serv.cpp query.h
	$(CXX) $(CXXFLAGS) -o serv serv.cpp Dict.cpp HzSeg.cpp
clean:
	rm *.o
