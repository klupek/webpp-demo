#ifndef WEBPP_DEMO_APPLICATION_HPP
#define WEBPP_DEMO_APPLICATION_HPP

#include "config.hpp"
#include "pages.hpp"
#include <webpp/webpp.hpp>

template<typename Impl>
class application : public webpp::Webpp<Impl,context_factory_t, context_factory_t::context_t> {
	using webpp::Webpp<Impl,context_factory_t,context_factory_t::context_t>::sub;
public:
	application(int argc, char** argv)
		: webpp::Webpp<Impl,context_factory_t, context_factory_t::context_t>(argc, argv, argc, argv) {
		demo_app_controller::mount(sub("/"));
	}
};

#endif // APPLICATION_HPP
