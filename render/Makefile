TARGET:=render

CXXFLAGS?=-g -O2 -Wall -Wno-unknown-pragmas -std=c++17 
CXXINCFLAGS?=
LDFLAGS?=
CXX?=g++
BISON:=bison
FLEX:=flex

$(TARGET): parser.o scanner.o driver.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CXXINCFLAGS) -c $< -o $@
	$(CXX) -MM -MT $@ $(CXXFLAGS) $(CXXINCFLAGS) -c $< > $*.d

parser.cc parser.h: parser.y
	$(BISON) -o parser.cc $<

scanner.cc: scanner.l
	$(FLEX) -o$@ $<

.PHONY: clean

clean:
	rm -f *.o *.d
	rm -f parser.cc parser.hh location.hh scanner.cc
	rm -f $(TARGET)

-include *.d
