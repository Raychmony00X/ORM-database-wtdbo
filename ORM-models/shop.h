#pragma once

#include <Wt/Dbo/backend/Postgres.h>
#include <Wt/Dbo/Dbo.h>

class Shop {
public:
	std::string name = "";

	template<class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, name, "name");
	}
};