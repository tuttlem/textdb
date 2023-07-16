//
// Created by michael on 15/07/23.
//

#ifndef TEXTDB_TABLE_H
#define TEXTDB_TABLE_H

#include "../common.h"
#include "../core/dberror.h"

namespace textdb {

    struct ColumnInfo {
        unsigned short width;
    };

    typedef std::shared_ptr<ColumnInfo> ColumnInfoPtr;

    struct Row {
        std::map<std::string, std::string> c;
    };

    typedef std::shared_ptr<Row> RowPtr;

    class Table {
    public:
        /** Default constructor */
        Table(void);

        static std::shared_ptr<Table> attachToFile(const std::string &path);

        bool columnExists(const std::string &name);
        void createColumn(const std::string &name, int width);
        void dropColumn(const std::string &name);

        RowPtr newRow(void);
        RowPtr newRow(std::map<std::string, std::string> data);

        void insertRow(RowPtr row, int at = INT_MAX);
        void insertRow(std::map<std::string, std::string> data, int at = INT_MAX);
        void deleteRow(int at);
        void updateRow(std::map<std::string, std::string> changes, int at);
        std::map<std::string, std::string> retrieveRow(int at);

        void flush(void);
        void ingest(void);

        void show(void);

        void writeHeader(std::ostream &s);
        void writeBody(std::ostream &s);

    public:
        void detach(void);
        void attach(bool rewrite = false);

    private:
        std::string filePath;
        std::fstream stream;
        std::map<std::string, ColumnInfoPtr> columns;
        std::vector<RowPtr> rows;

        unsigned int rowWidth;
    };

}


#endif //TEXTDB_TABLE_H
