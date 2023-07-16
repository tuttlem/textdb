#include <iostream>

#include "util/log.h"
#include "db/table.h"
#include "core/dberror.h"

int main() {
    try {
        auto table1 = textdb::Table::attachToFile("table1.dat");

        table1->createColumn("id", 5);
        table1->createColumn("name", 25);
        table1->createColumn("age", 3);
        table1->writeHeader(std::cout);

        for (int i = 1; i < 20; i ++) {
            table1->insertRow({
                {"id", std::to_string(i)},
                {"name", "Peter"},
                {"age", std::to_string(19 + (std::rand() % 50))}
            });
        }

        table1->deleteRow(3);
        table1->deleteRow(7);

        table1->updateRow({{"name", "Joe"}}, 5);
        table1->flush();

    } catch (textdb::DatabaseError &e) {
        log_error << e.what();
    }

    return 0;
}
