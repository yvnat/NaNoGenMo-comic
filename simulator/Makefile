################################################################################
# Makefile
# NaNoGenMo 2020 - Hoplites Comic - yvnat
# for the C++ simulator portion
################################################################################

CXX = g++
CXXFLAGS = -g

################################################################################

MAIN_DEPS = relationship.o misc.o outcome.o character.o simulator.o elaborator.o event.o pagesketch.o main.o report.o 
main: $(MAIN_DEPS)
	$(CXX) $(CXXFLAGS) -o bin/main.out     $(MAIN_DEPS)
	@echo "-----------------"
relationship.o: relationship.cpp relationship.hpp character.hpp misc.hpp
	$(CXX) $(CXXFLAGS) -c relationship.cpp
misc.o: misc.cpp misc.hpp
	$(CXX) $(CXXFLAGS) -c misc.cpp
outcome.o: outcome.cpp outcome.hpp misc.hpp relationship.hpp \
 character.hpp
	$(CXX) $(CXXFLAGS) -c outcome.cpp
character.o: character.cpp character.hpp relationship.hpp misc.hpp
	$(CXX) $(CXXFLAGS) -c character.cpp
simulator.o: simulator.cpp simulator.hpp report.hpp setting.hpp event.hpp \
 outcome.hpp misc.hpp relationship.hpp character.hpp
	$(CXX) $(CXXFLAGS) -c simulator.cpp
elaborator.o: elaborator.cpp elaborator.hpp report.hpp setting.hpp \
 event.hpp outcome.hpp misc.hpp relationship.hpp character.hpp \
 pagesketch.hpp
	$(CXX) $(CXXFLAGS) -c elaborator.cpp
event.o: event.cpp event.hpp
	$(CXX) $(CXXFLAGS) -c event.cpp
pagesketch.o: pagesketch.cpp pagesketch.hpp
	$(CXX) $(CXXFLAGS) -c pagesketch.cpp
main.o: main.cpp simulator.hpp report.hpp setting.hpp event.hpp \
 outcome.hpp misc.hpp relationship.hpp character.hpp elaborator.hpp \
 pagesketch.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp
report.o: report.cpp report.hpp setting.hpp event.hpp outcome.hpp \
 misc.hpp relationship.hpp character.hpp
	$(CXX) $(CXXFLAGS) -c report.cpp

################################################################################
# used to generate a new dependency tree
gen:
	@clear && python3 dependency.py
################################################################################
# used to clear excess files
clear:
	-rm *.o & rm *.gch
################################################################################