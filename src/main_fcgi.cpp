#include "application.hpp"
#include <webpp/cgi/cgicc_fcgi.hpp>


int main(int argc, char **argv) {
	application<webpp::cgi::cgicc_fcgi> wpp(argc, argv);
	wpp.run();
	return 0;
}
