#include "publisher.h"
#include "book.h"
#include "shop.h"
#include "stock.h"
#include "sale.h"
#include "sales_managment.h"

#include <exception>

SalesManagmentDatabase::SalesManagmentDatabase() {
	m_connection = "host=localhost port=5432 user=postgres password=1488";
}

bool SalesManagmentDatabase::ConnectToDatabase(const std::string& dbname) {
	try {
		std::string connection = m_connection + " dbname=" + dbname;
		auto postgres = std::make_unique<Wt::Dbo::backend::Postgres>(connection);
		session.setConnection(std::move(postgres));
		session.mapClass<Publisher>("publisher");
		session.mapClass<Book>("book");
		session.mapClass<Shop>("shop");
		session.mapClass<Stock>("stock");
		session.mapClass<Sale>("sale");
	} catch (const Wt::Dbo::Exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;
}

bool SalesManagmentDatabase::CreateDatabase() {
	try {
		Wt::Dbo::Transaction transaction(session);
		session.createTables();
	} catch (const Wt::Dbo::Exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;
}

