#ifndef WEBPP_DEMO_APPLICATION_HPP
#define WEBPP_DEMO_APPLICATION_HPP

#include "config.hpp"
#include "pages.hpp"
#include <webpp/webpp.hpp>
#include <webpp/file_crash_reporter.hpp>

template<typename Impl>
class application : public webpp::Webpp<Impl,context_factory_t, webpp::file_crash_reporter, context_factory_t::context_t> {
	using webpp::Webpp<Impl,context_factory_t,webpp::file_crash_reporter, context_factory_t::context_t>::sub;
public:
	application(int argc, char** argv)
		: webpp::Webpp<Impl,context_factory_t, webpp::file_crash_reporter, context_factory_t::context_t>(argc, argv, webpp::file_crash_reporter<context_factory_t::context_t>("/tmp"), argc, argv) {
		demo_app_controller::mount(sub("/"));
	}
};

#endif // APPLICATION_HPP
