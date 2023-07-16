//
// Created by michael on 15/07/23.
//

#include "table.h"
#include "../util/log.h"
#include "../core/dberror.h"

namespace textdb {

    Table::Table(void) {
        this->rowWidth = 0;
    }

    /**
     * Diagnostic log
     */
    void Table::show(void) {
        log_info << "row width: " << this->rowWidth;

        for (auto& col : this->columns) {
            log_info << "column: " << col.first << " (" << col.second->width << ")";
        }
    }
}