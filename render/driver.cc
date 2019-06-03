#include "driver.h"

#include <ostream>

#include "parser.hh"

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

    cout << "AST Dump: " << endl;
    cout << result;

	return res;
}

int main(int argc, char **argv) {
	driver drv;
	drv.parse("sample");
	return 0;
}
