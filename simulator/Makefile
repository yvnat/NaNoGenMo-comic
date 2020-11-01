################################################################################
# Makefile
# NaNoGenMo 2020 - Hoplites Comic - yvnat
# for the C++ simulator portion
################################################################################

CXX = g++
CXXFLAGS = -g

################################################################################
# dependency tree:
#
# main
# 	report
# 		setting
# 		event
#		outcome
#
################################################################################

MAIN_DEPS = main.o report.o
main: $(MAIN_DEPS)
	$(CXX) $(CXXFLAGS) -o bin/main.out $(MAIN_DEPS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

REPORT_DEPS = report.cpp report.hpp setting.hpp event.hpp outcome.hpp
report.o: $(REPORT_DEPS)
	$(CXX) $(CXXFLAGS) -c report.cpp

################################################################################
# used to clear excess files
clear:
	-rm *.o & rm *.gch
################################################################################