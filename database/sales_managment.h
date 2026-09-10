#pragma once

#include <Wt/Dbo/backend/Postgres.h>
#include <Wt/Dbo/Dbo.h>

class SalesManagmentDatabase {
public:
	Wt::Dbo::Session session;

	explicit SalesManagmentDatabase();

	bool ConnectToDatabase(const std::string& dbname);

	bool CreateDatabase();

private:
	std::string m_connection;
};