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

        app &name(std::string_view name);

        [[nodiscard]] std::string name() const;

        app &description(std::string_view description);

        [[nodiscard]] std::string description() const;

        app &usage(std::string_view usage);

        [[nodiscard]] std::string usage() const;

        options::app &add_option(const option &option);

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

    inline parse_result parse_options(app &app, int argc, const char **argv) noexcept {
        return parse_options(app.option_spec(), argc, argv);
    }
}

#endif //OPTIONS_APP_HPP
