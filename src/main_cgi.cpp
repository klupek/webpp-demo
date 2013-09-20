#include "application.hpp"
#include <webpp/cgi/cgicc_cgi.hpp>


int main(int argc, char **argv) {
	application<webpp::cgi::cgicc_cgi> wpp(argc, argv);
	wpp.run();
	return 0;
}
