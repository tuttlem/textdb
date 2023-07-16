//
// Created by michael on 15/07/23.
//

#ifndef TEXTDB_CONFIG_H
#define TEXTDB_CONFIG_H

#include "../common.h"
#include "./log.h"

namespace textdb {

    /**
     * All of the configuration information required to run this system is
     * available within this structure
     */
    struct Config {
        std::string _logLevel;

        /** Default constructor */
        Config() = default;
        /** Copy constructor */
        Config(const Config&) = default;
        /** Move constructor */
        Config(Config&&) = default;

        /**
         * Factor construction of a config object from a pre-defined
         * configuration file location
         * @param path Location of the configuration file
         * @return std::shared_ptr<Config>
         */
        static std::shared_ptr<Config> loadFromFile(const std::string& path);

        /**
         * Produces a configuration object with the default values
         * @return std::shared_ptr<Config>
         */
        static std::shared_ptr<Config> getDefault(void);

        /**
         * Using the runtime environment, this function will overwrite
         * configurable parameters with environment variables
         * @param conf The configuration object to update
         */
        static void adjustWithEnvironment(const std::shared_ptr<Config> conf);

    };

}

#endif //TEXTDB_CONFIG_H
