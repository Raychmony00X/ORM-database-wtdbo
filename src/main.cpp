#include "publisher.h"
#include "book.h"
#include "shop.h"
#include "stock.h"
#include "sale.h"
#include "sales_managment.h"

#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
	SalesManagmentDatabase database;
	database.ConnectToDatabase("sales_managment");
	database.CreateDatabase();
	
    std::vector<Wt::Dbo::ptr<Publisher>> publishers;
    std::vector<std::string> publisher_names = {
        "Penguin Random House",
        "HarperCollins",
        "Simon & Schuster",
        "Hachette Livre",
        "Macmillan Publishers"
    };

    Wt::Dbo::Transaction transaction_publisher{ database.session };
    for (const std::string& name : publisher_names) {
        auto publisher = std::make_unique<Publisher>();
        publisher->name = name;
        auto ptr = database.session.add(std::move(publisher));
        publishers.push_back(ptr);
    }

    transaction_publisher.commit();

    std::vector<Wt::Dbo::ptr<Shop>> shops;
    std::vector<std::string> shops_names = {
        "Barnes & Noble",
        "Waterstones",
        "Books-A-Million",
        "Amazon Books",
        "Indigo"
    };

    Wt::Dbo::Transaction transaction_shop{ database.session };
    for (const std::string& name : shops_names) {
        auto shop = std::make_unique<Shop>();
        shop->name = name;
        auto ptr = database.session.add(std::move(shop));
        shops.push_back(ptr);
    }

    transaction_shop.commit();

    std::unordered_map<std::string, Wt::Dbo::ptr<Publisher>> publisher_map;
    for (const auto& ptr : publishers) publisher_map[ptr->name] = ptr;
    std::vector<Wt::Dbo::ptr<Book>> books; 
    std::vector<std::pair<std::string, std::string>> books_publishers = {
     {"The Great Gatsby", "Penguin Random House"},
     {"1984", "Penguin Random House"},
     {"To Kill a Mockingbird", "HarperCollins"},
     {"The Hobbit", "HarperCollins"},
     {"The Catcher in the Rye", "Simon & Schuster"},
     {"Brave New World", "Simon & Schuster"},
     {"The Lord of the Rings", "Hachette Livre"},
     {"Harry Potter", "Hachette Livre"},
     {"The Da Vinci Code", "Macmillan Publishers"},
     {"The Alchemist", "Macmillan Publishers"}
    };

    Wt::Dbo::Transaction transaction_book{ database.session };
    for (const auto& [title, publisher] : books_publishers) {
        auto book = std::make_unique<Book>();
        book->title = title;
        book->id_publisher = publisher_map[publisher];
        auto ptr = database.session.add(std::move(book));
        books.push_back(ptr);
    }

    transaction_book.commit();

    std::unordered_map<std::string, Wt::Dbo::ptr<Shop>> shop_map;
    for (const auto& ptr : shops) shop_map[ptr->name] = ptr;
    std::unordered_map<std::string, Wt::Dbo::ptr<Book>> book_map;
    for (const auto& ptr : books) book_map[ptr->title] = ptr;
    std::vector<Wt::Dbo::ptr<Stock>> stocks;
    std::vector<std::tuple<std::string, std::string, int>> stock_data = {
    {"The Great Gatsby", "Barnes & Noble", 10},
    {"The Great Gatsby", "Waterstones", 5},
    {"1984", "Barnes & Noble", 7},
    {"1984", "Amazon Books", 12},
    {"To Kill a Mockingbird", "Books-A-Million", 15},
    {"To Kill a Mockingbird", "Indigo", 8},
    {"The Hobbit", "Waterstones", 6},
    {"The Hobbit", "Amazon Books", 20},
    {"The Catcher in the Rye", "Barnes & Noble", 3},
    {"The Catcher in the Rye", "Books-A-Million", 9},
    {"Brave New World", "Amazon Books", 25},
    {"Brave New World", "Indigo", 14},
    {"The Lord of the Rings", "Waterstones", 4},
    {"The Lord of the Rings", "Barnes & Noble", 11},
    {"Harry Potter", "Indigo", 18},
    {"Harry Potter", "Books-A-Million", 22},
    {"The Da Vinci Code", "Amazon Books", 5},
    {"The Da Vinci Code", "Waterstones", 7},
    {"The Alchemist", "Barnes & Noble", 16},
    {"The Alchemist", "Books-A-Million", 10}
    };

    Wt::Dbo::Transaction transaction_stock{ database.session };
    for (const auto& [book, shop, count] : stock_data) {
        auto stock = std::make_unique<Stock>();
        stock->count = count;
        stock->id_book = book_map[book];
        stock->id_shop = shop_map[shop];
        auto ptr = database.session.add(std::move(stock));
        stocks.push_back(ptr);
    }

    transaction_stock.commit();

    std::vector<std::tuple<double, std::string, int,  int>> sales_data = {
        {15.99, "2026-09-01", 2,  1},
        {12.50, "2026-09-02", 4,  1},
        {18.75, "2026-09-03", 6,  3},
        {22.00, "2026-09-04", 8,  1},
        {14.25, "2026-09-05", 10, 2},
        {19.99, "2026-09-06", 2,  1},
        {11.30, "2026-09-07", 5,  4},
        {16.40, "2026-09-08", 7,  2},
        {24.99, "2026-09-09", 12, 1},
        {13.75, "2026-09-10", 14, 3},
        {17.50, "2026-09-11", 16, 2},
        {20.00, "2026-09-12", 18, 1},
        {14.80, "2026-09-13", 3,  5},
        {12.90, "2026-09-14", 9,  2},
        {21.50, "2026-09-15", 11, 1},
        {18.25, "2026-09-16", 13, 3},
        {15.00, "2026-09-17", 15, 4},
        {25.00, "2026-09-18", 17, 1},
        {10.99, "2026-09-19", 19, 6},
        {19.50, "2026-09-20", 20, 2}

    };

    Wt::Dbo::Transaction transaction_sale{ database.session };
    for (const auto& [price, date, stock, count] : sales_data) {
        auto sale = std::make_unique<Sale>();
        sale->id_stock = stocks[stock - 1];
        sale->price = price;
        sale->date_sale = date;
        sale->count = count;
        database.session.add(std::move(sale));
    }

    transaction_sale.commit();
    std::map<std::pair<std::string, std::string>, Wt::Dbo::ptr<Stock>> stock_map;
    for (const auto& ptr : stocks) {
        stock_map[{ptr->id_book->title, ptr->id_shop->name}] = ptr;
    }

    std::string input;
    std::cout << "Enter publisher name or ID: ";
    std::getline(std::cin, input);

    Wt::Dbo::ptr<Publisher> targetPublisher;

    try {
        int id = std::stoi(input);
        for (const auto& ptr : publishers) {
            if (ptr.id() == id) {
                targetPublisher = ptr;
                break;
            }
        }
    }
    catch (const std::exception&) {
        for (const auto& ptr : publishers) {
            if (ptr->name == input) {
                targetPublisher = ptr;
                break;
            }
        }
    }

    if (!targetPublisher) {
        std::cout << "Publisher not found." << std::endl;
        return 0;
    }

    std::set<std::string> shopNames;
    for (const auto& [key, stock] : stock_map) {
        if (stock->id_book->id_publisher == targetPublisher) {
            shopNames.insert(stock->id_shop->name);
        }
    }

    std::cout << "\nShops selling books by \"" << targetPublisher->name << "\":" << std::endl;
    if (shopNames.empty()) {
        std::cout << "  (no shops found)" << std::endl;
    }
    else {
        for (const auto& shopName : shopNames) {
            std::cout << "  - " << shopName << std::endl;
        }
    }

	return 0;
}
