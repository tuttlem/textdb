//
// Created by michael on 16/07/23.
//

#ifndef TEXTDB_DBERROR_H
#define TEXTDB_DBERROR_H

#include "../common.h"

#define DBERR_OK                0x00000001

#define DBERR_FILE              0x10000000

#define DBERR_COL_VIO           0x20000000
#define DBERR_COL_WIDTH         0x20000001
#define DBERR_COL_NAME          0x20000002
#define DBERR_ROW_NOTF          0x20000003


namespace textdb {
    class DatabaseError : public std::exception {
    public:
        explicit DatabaseError(const unsigned int code, const char* message)
            : _code(code), _msg(message) {}
        explicit DatabaseError(const unsigned int code, const std::string& message)
            : _code(code), _msg(message) {}

        virtual ~DatabaseError() noexcept {}

        virtual const char* what() const noexcept {
            return _msg.c_str();
        }

    protected:
        std::string _msg;
        unsigned int _code;
    };
}

#endif //TEXTDB_DBERROR_H
