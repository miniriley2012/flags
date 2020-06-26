//
// Created by Riley Quinn on 6/24/20.
//

#ifndef OPTIONS_APP_HPP
#define OPTIONS_APP_HPP

#include "option_spec.hpp"
#include <string>
#include <sstream>

namespace options {
    class app {
    public:

        [[nodiscard]] std::string_view name() const;

        app &name(std::string_view name);

        [[nodiscard]] std::string_view description() const;

        app &description(std::string_view description);

        [[nodiscard]] std::string_view usage() const;

        app &usage(std::string_view usage);

        options::app &add_help_flag(const std::string &name, char shorthand, const std::string &usage);

        [[nodiscard]] std::string default_usage();

        [[nodiscard]] std::string help();

        app &option_spec(const option_spec &spec);

        [[nodiscard]] options::option_spec &option_spec();

        inline parse_result parse(int argc, const char **argv) {
            return spec_.parse(argc, argv);
        }

    private:
        std::string name_;
        std::string description_;
        std::string usage_;

        options::option_spec spec_;
    };
}

#endif //OPTIONS_APP_HPP
