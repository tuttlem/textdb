
#include "table.h"
#include "../util/log.h"
#include "../core/dberror.h"

namespace textdb {

    /**
     * Creates a database reference that is attached to the passed in file path
     * @param path The path to the database table
     * @return A pointer to the table object
     */
    std::shared_ptr<Table> Table::attachToFile(const std::string &path) {
        try {
            auto table = std::make_shared<Table>();

            table->filePath = path;
            table->attach();

            return table;
        } catch (std::exception const& e) {
            throw DatabaseError(DBERR_FILE, e.what());
        }
    }

    void Table::detach(void) {
        this->stream.close();
    }

    /**
     * Attaches this database table object to the underlying file media
     * @param rewrite Attach to the storage preparing to rewrite
     */
    void Table::attach(bool rewrite) {
        auto extra = rewrite ? std::fstream::trunc : std::fstream::app;

        this->stream.open(
            this->filePath,
            std::fstream::in | std::fstream::out | extra
        );

        this->stream.exceptions(
        std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit
        );
    }

    /**
     * Flushes the dirty internal state to the attached stream
     */
    void Table::flush(void) {
        this->detach();
        this->attach(true);

        this->writeHeader(this->stream);
        this->writeBody(this->stream);
    }

    /**
     * Reads the table off disk, and parses it into the internal table state
     */
    void Table::ingest(void) {

    }

    /**
     * String transformer to create a file header
     * @param s The stream to write the header to
     */
    void Table::writeHeader(std::ostream &s) {
        s << "========================================" << std::endl;
        s << "textdb table" << std::endl;

        for (auto& col : this->columns) {
            s << col.first << "," << col.second->width << std::endl;
        }
    }

    /**
     * String transformer to create a file body
     * @param s The stream to write the body to
     */
    void Table::writeBody(std::ostream &s) {
        s << "========================================" << std::endl;
        for (auto& row : this->rows) {
            for (auto &col: this->columns) {
                s << std::left << std::setw(col.second->width) << row->c[col.first];
            }
            s << std::endl;
        }
    }
}