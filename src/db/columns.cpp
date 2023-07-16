
#include "table.h"
#include "../util/log.h"
#include "../core/dberror.h"

namespace textdb {

    /**
     * Determines if a column exists within this table or not
     * @param name The name of the column
     * @return A boolean indicator
     */
    bool Table::columnExists(const std::string &name) {
        return this->columns.find(name) != this->columns.end();
    }

    /**
     * Adds a new column to the database table
     * @param name The name of the column to add
     * @param width The width of the column to add
     */
    void Table::createColumn(const std::string &name, int width) {
        if (width < 1) {
            throw DatabaseError(DBERR_COL_WIDTH, "Column must have a width greater than 0");
        }

        if (name.length() == 0) {
            throw DatabaseError(DBERR_COL_NAME, "Column must have a name");
        }

        if (this->columnExists(name)) {
            throw DatabaseError(DBERR_COL_VIO, "Column already exists on table");
        }

        auto col = std::make_shared<ColumnInfo>();
        col->width = width;

        this->columns[name] = col;
        this->rowWidth += width;

        // TODO: re-write all of the table data to include the new space
    }

    /**
     * Removes a column from the database table
     * @param name The name of the column to remove
     */
    void Table::dropColumn(const std::string &name) {
        if (name.length() == 0) {
            throw DatabaseError(DBERR_COL_NAME, "Column must have a name");
        }

        if (!this->columnExists(name)) {
            throw DatabaseError(DBERR_COL_VIO, "Column does not exist on table");
        }

        auto col = this->columns[name];

        this->rowWidth -= col->width;
        this->columns.erase(name);

        // TODO: re-write all of the table data to exclude the removed space
    }

}