#ifndef WEBPP_DEMO_CONFIG_HPP
#define WEBPP_DEMO_CONFIG_HPP

#include <webpp/context.hpp>
#include <webpp/controller.hpp>
#include <webpp/database_context.hpp> //  FIXME: currently database needs to be included before html_page and xmlrenderer, to make render_dbarray work.
#include <webpp/xmlrenderer_context.hpp>
#include <webpp/html_page.hpp>


#include "entities.hpp"

typedef webpp::request request_t;
typedef webpp::response response_t;

class database_session_t : public webpp::database_session {
public:
	entities::tags tags;
	entities::posts posts;
	database_session_t(const std::string& dburl)
		: webpp::database_session(dburl)
		, tags(get_database_session())
		, posts(get_database_session()) {}


	virtual void test() {

	}
};

class context_factory_t {
public:
	typedef webpp::database_context<database_session_t, webpp::xmlrenderer_context<webpp::base_context<request_t, response_t>>> context_t;
private:
	struct options_t {
		const int argc;
		char **argv;

		const bool debugging;
		const std::string xmllib;
		const std::string database_url;
	};
	options_t options;

	static options_t make_options(int argc, char **argv) {
		// TODO: parse arguments here
		return options_t {
			argc, argv, true, "../private/xml", "sqlite3://:memory:"
		};
	}

	webpp::basic_config basic_config_;
	webpp::xmlrenderer_context_config xml_config_;
	database_session_t database_;

public:
	context_factory_t(int argc, char **argv)
		: options(make_options(argc, argv))
		, basic_config_ { options.debugging }
		, xml_config_(options.xmllib)
		, database_(options.database_url) {
		xml_config_.attach_xslt("bootstrap-form");
		entities::createdb(database_.get_database_session());
		entities::filldb(database_.get_database_session());			
	}

	context_t operator()() {
		return context_t(database_, xml_config_, basic_config_);
	}

};

#endif // WEBPP_DEMO_CONFIG_HPP
