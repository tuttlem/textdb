//
// Created by michael on 16/07/23.
//

#include "table.h"

namespace textdb {

    RowPtr Table::newRow(void) {
        auto row = std::make_shared<Row>();

        for (auto& col : this->columns) {
            row->c[col.first] = std::string(col.second->width, ' ');
        }

        return row;
    }

    RowPtr Table::newRow(std::map<std::string, std::string> data) {
        auto row = std::make_shared<Row>();

        for (auto& col : this->columns) {
            row->c[col.first] = data[col.first];
        }

        return row;
    }

    void  Table::insertRow(RowPtr row, int at) {
        if (at < 0) {
            this->rows.insert(this->rows.begin(), row);
        } else if (at >= this->rows.size()) {
            this->rows.push_back(row);
        } else {
            this->rows.insert(this->rows.begin() + at, row);
        }
    }

    void Table::insertRow(std::map<std::string, std::string> data, int at) {
        auto row = this->newRow(data);
        this->insertRow(row, at);
    }

    void  Table::deleteRow(int at) {
        if (at < 0 || at > this->rows.size()) {
            throw DatabaseError(DBERR_ROW_NOTF, "Requested row can not be found");
        }

        this->rows.erase(this->rows.begin() + at);
    }

    void  Table::updateRow(std::map<std::string, std::string> changes, int at) {
        if (at < 0 || at > this->rows.size()) {
            throw DatabaseError(DBERR_ROW_NOTF, "Requested row can not be found");
        }

        auto row = this->rows.at(at);

        for (auto& col : changes) {
            row->c[col.first] = changes[col.first];
        }
    }

    std::map<std::string, std::string> Table::retrieveRow(int at) {
        if (at < 0 || at > this->rows.size()) {
            throw DatabaseError(DBERR_ROW_NOTF, "Requested row can not be found");
        }

        auto row = this->rows.at(at);
        return row->c;
    }
}