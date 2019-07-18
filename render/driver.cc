#include "driver.h"

#include <ostream>

#include "parser.hh"
#include "graphviz.h"

using namespace std;

driver::driver(): 
		trace_parsing(false), 
		trace_scanning(false) {
}

int driver::parse(const string &f) {
	file = f;
	location.initialize(&file);
	scan_begin();
	yy::parser parse(*this);
	parse.set_debug_level(trace_parsing);
	int res = parse();
	scan_end();

    cout << result << endl;
    // XXX do somethign with it

	return res;
}

int main(int argc, char **argv) {
	driver drv;
    // XXX proper cmdline args
    if (argc == 1) {
	    drv.parse("sample");
    }
    else {
	    drv.parse(argv[1]);
    }
	return 0;
}
