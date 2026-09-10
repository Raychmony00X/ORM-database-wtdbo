#pragma once

#include <Wt/Dbo/backend/Postgres.h>
#include <Wt/Dbo/Dbo.h>

class Sale {
public:
	int count = 0;
	double price = 0.0;
	std::string date_sale = "";
	Wt::Dbo::ptr<Stock> id_stock;

	template<class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::field(a, price, "price");
		Wt::Dbo::field(a, date_sale, "date_sale");
		Wt::Dbo::belongsTo(a, id_stock, "stock");
	}

};