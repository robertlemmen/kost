TARGET:=render

CXXFLAGS?=-g -O2 -Wall -Wno-unknown-pragmas -std=c++17 
CXXINCFLAGS?=
LDFLAGS?=
CXX?=g++
BISON:=bison
FLEX:=flex

$(TARGET): parser.o scanner.o driver.o ast.o graphviz.o model.o
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CXXINCFLAGS) -c $< -o $@
	$(CXX) -MM -MT $@ $(CXXFLAGS) $(CXXINCFLAGS) -c $< > $*.d

parser.cc parser.hh location.hh: parser.y
	$(BISON) -o parser.cc $<

%.cc: %.l
	$(FLEX) -o$@ $<

ast.o: location.hh

.PHONY: clean

.NOTPARALLEL : parser.cc parser.hh location.hh

clean:
	rm -f *.o *.d
	rm -f parser.cc parser.hh location.hh scanner.cc
	rm -f $(TARGET)

-include *.d
