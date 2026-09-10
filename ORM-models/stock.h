#pragma once

#include <Wt/Dbo/backend/Postgres.h>
#include <Wt/Dbo/Dbo.h>

class Stock {
public:
	int count = 0;
	Wt::Dbo::ptr<Book> id_book;
	Wt::Dbo::ptr<Shop> id_shop;

	template<class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::belongsTo(a, id_book, "book");
		Wt::Dbo::belongsTo(a, id_shop, "shop");
	}

};