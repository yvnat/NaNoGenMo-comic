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
#		character
#			relationship
#
################################################################################

MAIN_DEPS = main.o simulator.o report.o character.o
main: $(MAIN_DEPS)
	$(CXX) $(CXXFLAGS) -o bin/main.out $(MAIN_DEPS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

simulator.o: simulator.cpp report.hpp character.hpp misc.hpp
	$(CXX) $(CXXFLAGS) -c simulator.cpp

REPORT_DEPS = report.cpp report.hpp setting.hpp event.hpp outcome.hpp
report.o: $(REPORT_DEPS)
	$(CXX) $(CXXFLAGS) -c report.cpp

character.o: character.hpp relationship.hpp
	$(CXX) $(CXXFLAGS) -c character.cpp

################################################################################
# used to clear excess files
clear:
	-rm *.o & rm *.gch
################################################################################