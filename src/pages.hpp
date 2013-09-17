#ifndef WEBPP_DEMO_PAGES_HPP
#define WEBPP_DEMO_PAGES_HPP

#include "config.hpp"

class demo_app_controller : public webpp::html_page<context_factory_t::context_t> {
public:
	demo_app_controller(const context_factory_t::context_t::request_t& request, context_factory_t::context_t::response_t& response, context_t& ctx)
		: webpp::html_page<context_factory_t::context_t>(request, response, ctx, "html/main") {}

	void base(const std::string& title) {
		render_value("title", title);
		render_value("description", "foo");
		render_value("author", "bar");
		rewrite_asset_links("assets/", "//assets.localhost/");
		auto& tags = context().db().tags.all;
		render_array<webpp::dbarray<decltype(entities::tags::all)>>("tags", tags);
		//rnd_.get("").debug();
	}

	void index() {
		base("index!");
		html5(html5_encoding::REMOVE_COMMENTS); // deal with IEs later.
	}

	template<typename MounterT>
	static void mount(MounterT& mounter) {
		mounter.get("/", &demo_app_controller::index);
	}
};

#endif // WEBPP_DEMO_PAGES_HPP
