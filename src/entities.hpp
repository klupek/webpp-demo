#ifndef WEBPP_DEMO_ENTITES_HPP
#define WEBPP_DEMO_ENTITES_HPP

#include <webpp/database.hpp>


namespace entities {
	namespace db = webpp::database;
	void createdb(db::session& s) {
		s.get_session() << "CREATE TABLE tags(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR)";
		s.get_session() << "CREATE TABLE users(id INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR)";
		s.get_session() << "CREATE TABLE posts(id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, content VARCHAR, created DATETIME)";
	}

	struct tag : public db::entity<tag, db::serial, db::string> {
		db::serial& id;
		db::string& name;

		WEBPP_DB_EntityCtors2(tag, entity_super_t, id, name)

		static std::vector<std::string> columns() {
			return { "id", "name" };
		}

		static std::string table_name() {
			return "tags";
		}
	};

	struct user : public db::entity<user, db::serial, db::string> {
		db::serial& id;
		db::string& username;

		WEBPP_DB_EntityCtors2(user, entity_super_t, id, username)

		static std::vector<std::string> columns() {
			return { "id", "username" };
		}

		static std::string table_name() {
			return "users";
		}
	};

	struct post : public db::entity<post, db::serial, db::serial, db::string, db::datetime> {
		db::serial& id;
		db::serial& user_id;
		db::string& content;
		db::datetime& created;

		WEBPP_DB_EntityCtors4(post, entity_super_t, id, user_id, content, created)

		static std::vector<std::string> columns() {
			return { "id", "user_id", "content", "created" };
		}

		static std::string table_name() {
			return "posts";
		}
	};

	void filldb(db::session& s) {
		db::insert_statement<user> iuser(s);
		user u1(db::null, std::string("abuser1")), u2(db::null, std::string("abuser2"));
		iuser(u1); iuser(u2);

		db::insert_statement<tag> itag(s);
		tag t1(db::null, std::string("test1")), t2(db::null, std::string("test2"));
		itag(t1); itag(t2);

		db::insert_statement<post> ipost(s);
		post p1(db::null, u1.id, std::string("ala ma kota"), db::datetime_impl(12,0,0, 3,1,2012));
		post p2(db::null, u1.id, std::string("ale juz go zjadla"), db::datetime_impl(9,31,0, 04,01,2012));
		post p3(db::null, u2.id, std::string("ten kot byl zly"), db::datetime_impl(13,7,0, 3,1,2012));
		post p4(db::null, u2.id, std::string("niedobra ala"), db::datetime_impl(9,33,0,4,1,2012));
		ipost(p1);
		ipost(p2);
		ipost(p3);
		ipost(p4);
	}
}

WEBPP_DB_Relation_HasOne(entities::post, entities::user, author);

namespace entities {
	struct tags {
		db::select_statement<tag> all;
		tags(db::session& s)
			: all(s, db::order(tag::table_name(), "name")) {}
	};

	struct posts {
		//db::select_statement<db::join<post, user>::type, int> get_latest;
		db::select_statement<db::join<post, user>::type, int> get_latest;

		posts(db::session& s)
			: get_latest(s, "SELECT p.*, u.* FROM posts p JOIN users u ON p.user_id = u.id LIMIT ?") {}
	};
}



#endif // WEBPP_DEMO_ENTITES_HPP
