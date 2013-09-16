#include "application.hpp"
#include <webpp/impl/impl_cgicc.hpp>


int main(int argc, char **argv) {
	application<webpp::impl_cgicc> wpp(argc, argv);
	wpp.run();
	return 0;
}
