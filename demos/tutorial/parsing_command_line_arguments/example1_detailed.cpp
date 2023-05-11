#include <iostream>

#include <seqan/arg_parse.h>

int main(int argc, char const ** argv)
{
    //![object]
    // Setup ArgumentParser.
    seqan2::ArgumentParser parser("modify_string");
    //![object]

    //![argument]
    addArgument(parser, seqan2::ArgParseArgument(
        seqan2::ArgParseArgument::STRING, "TEXT"));
    //![argument]

    //![option]
    addOption(parser, seqan2::ArgParseOption(
        "i", "period", "Period to use for the index.",
        seqan2::ArgParseArgument::INTEGER, "INT"));
    addOption(parser, seqan2::ArgParseOption(
        "U", "uppercase", "Select to-uppercase as operation."));
    //![option]

    //![parse]
    // Parse command line.
    seqan2::ArgumentParser::ParseResult res = seqan2::parse(parser, argc, argv);
    //![parse]

    // If parsing was not successful then exit with code 1 if there were errors.
    // Otherwise, exit with code 0 (e.g. help was printed).
    //![check]
    if (res != seqan2::ArgumentParser::PARSE_OK)
        return res == seqan2::ArgumentParser::PARSE_ERROR;
    //![check]

    //![print]
    // Extract option values and print them.
    unsigned period = 0;
    getOptionValue(period, parser, "period");
    bool toUppercase = isSet(parser, "uppercase");
    seqan2::CharString text;
    getArgumentValue(text, parser, 0);

    std::cout << "period   \t" << period << '\n'
              << "uppercase\t" << toUppercase << '\n'
              << "text     \t" << text << '\n';
    //![print]

    return 0;
}

