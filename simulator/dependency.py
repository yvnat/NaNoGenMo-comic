# main.cpp
# NaNoGenMo 2020 - Hoplites Comic - yvnat
# automatically generates Makefile dependencies

import os

files = os.listdir("./")

print("MAIN_DEPS = ", end="")
for i in files:
    if str(i).endswith(".cpp"):
        a = str(i);
        a = a[:-3]
        print(a+"o", end=" ")
print("\nmain: $(MAIN_DEPS)\n"+chr(9)+"$(CXX) $(CXXFLAGS) -o bin/main.out \
    $(MAIN_DEPS)\n"+chr(9)+"@echo \"-----------------\"")

for i in files:
    if str(i).endswith(".cpp"):
        a = os.system("g++ "+str(i)+" -MM")
        print(chr(9) + "$(CXX) $(CXXFLAGS) -c", str(i));