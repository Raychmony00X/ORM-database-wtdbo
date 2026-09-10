cmake_minimum_required(VERSION 3.5)
project(SalesManagment)

set(Wt_DIR "D:/WT/Wt 4.14.2 msvs2022 x64/lib/cmake/wt")

find_package(Wt REQUIRED COMPONENTS Dbo DboPostgres)

add_executable(my_app main.cpp sales_managment.cpp)

target_link_libraries(my_app PRIVATE
    Wt::Wt
    Wt::Dbo
    Wt::DboPostgres
)