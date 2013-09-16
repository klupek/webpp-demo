#ifndef WEBPP_DEMO_CONFIG_HPP
#define WEBPP_DEMO_CONFIG_HPP

#include <webpp/context.hpp>
#include <webpp/controller.hpp>
#include <webpp/xmlrenderer_context.hpp>
#include <webpp/html_page.hpp>

typedef webpp::request request_t;
typedef webpp::response response_t;

class context_factory_t {
public:
	typedef webpp::xmlrenderer_context<webpp::base_context<request_t, response_t>> context_t;
private:
	struct options_t {
		const int argc;
		char **argv;

		const bool debugging;
		const std::string xmllib;
	};
	options_t options;

	static options_t make_options(int argc, char **argv) {
		// TODO: parse arguments here
		return options_t {
			argc, argv, true, "./xml"
		};
	}

	webpp::basic_config basic_config_;
	webpp::xmlrenderer_context_config xml_config_;

public:
	context_factory_t(int argc, char **argv)
		: options(make_options(argc, argv))
		, basic_config_ { options.debugging }
		, xml_config_(options.xmllib) {}

	context_t operator()() {
		return context_t(xml_config_, basic_config_);
	}

};

#endif // WEBPP_DEMO_CONFIG_HPP
