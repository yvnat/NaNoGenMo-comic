################################################################################
# Makefile
# NaNoGenMo 2020 - Hoplites Comic - yvnat
# for the C++ simulator portion
################################################################################

CXX = g++
CXXFLAGS = -g

################################################################################
#
# main
#	simulator
# 		report
# 			setting
# 			event
#			outcome
# 			misc
#		character
#			relationship
#			misc
#		misc
#
################################################################################

MAIN_DEPS = main.o simulator.o report.o character.o misc.o event.o outcome.o
main: $(MAIN_DEPS)
	$(CXX) $(CXXFLAGS) -o bin/main.out $(MAIN_DEPS)
	@echo "-----------------"

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

simulator.o: simulator.cpp report.hpp character.hpp misc.hpp
	$(CXX) $(CXXFLAGS) -c simulator.cpp

REPORT_DEPS = report.cpp report.hpp setting.hpp event.hpp outcome.hpp misc.hpp
report.o: $(REPORT_DEPS)
	$(CXX) $(CXXFLAGS) -c report.cpp

character.o: character.hpp relationship.hpp misc.hpp
	$(CXX) $(CXXFLAGS) -c character.cpp

misc.o: misc.hpp misc.cpp
	$(CXX) $(CXXFLAGS) -c misc.cpp

event.o: event.hpp event.cpp
	$(CXX) $(CXXFLAGS) -c event.cpp

outcome.o: outcome.hpp outcome.cpp
	$(CXX) $(CXXFLAGS) -c outcome.cpp

################################################################################
# used to clear excess files
clear:
	-rm *.o & rm *.gch
################################################################################