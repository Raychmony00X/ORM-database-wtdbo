#pragma once

#include <Wt/Dbo/backend/Postgres.h>
#include <Wt/Dbo/Dbo.h>

class Book {
public:
	std::string title = "";
	Wt::Dbo::ptr<Publisher> id_publisher;

	template<class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::belongsTo(a, id_publisher, "publisher");
	}

};