#ifndef WEBPP_DEMO_ENTITES_HPP
#define WEBPP_DEMO_ENTITES_HPP

#include <webpp/database.hpp>

namespace entities {
	namespace db = webpp::database;

	void createdb(db::session& s) {
		s.get_session() << "CREATE TABLE tags(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR)";
		s.get_session() << "INSERT INTO tags(name) VALUES('test1'),('tests2')";
	}

	struct tag : public db::entity<tag, db::serial, db::string> {
		db::serial& id;
		db::string& name;

		WEBPP_DB_EntityCtors2(tag, entity_super_t, id, name);

		static std::vector<std::string> columns() {
			return { "id", "name" };
		}

		static std::string table_name() {
			return "tags";
		}
	};

	struct tags {
		db::select_statement<tag> all;
		tags(db::session& s)
			: all(s, db::order(tag::table_name(), "name")) {}
	};
}

#endif // WEBPP_DEMO_ENTITES_HPP
