//
// Created by Riley Quinn on 6/14/20.
//

#include <options/app.hpp>
#include <options/validations.hpp>
#include <iostream>

int main(int argc, const char **argv) {
    auto app = options::app{}
            .name("Thing")
            .description("A sloppy example.")
            .add_option(options::option{"--help", 'h', "Shows this help menu"})
            .add_option(options::option{"--config", 'c', "Path to config file"}
                                .default_value("config.cfg")
                                .validator(options::validations::file_exists))
            .add_option(options::option{"thing", 't', "is a test thing"}
                                .default_value("test")
                                .required(true));

    options::parse_result result = options::parse_options(app, argc, argv);

    if (result["--help"]) {
        std::cout << app.help() << std::endl;
        return 0;
    }

    for (const auto &[_, opt] : result.options) {
        std::cout << opt.name() << "(" << (opt.present() ? "p" : "!p") << ")" << ": "
                  << (opt.has_value() ? (opt.value().empty() ? "empty" : opt.value()) : "no value") << ", "
                  << opt.usage()
                  << "\n\n";
    }

    std::cout << "Remaining: [";
    for (std::size_t i = 0; i < result.remaining.size(); i++) {
        std::cout << result.remaining[i];
        if (i < result.remaining.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    return 0;
}