// Day9Proto_Logging.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Added C:\devtools\boost_1_75_0\stage\lib folder to:
// C++ Linker - Additional Library Directories
//
// Logger Level Hierachy (ordered with most verbose at top)
// trace
// debug
// info
// warning
// fatal

#include <iostream>

#include "pch.h"

namespace logging = boost::log;

void init_logging()
{
    logging::add_file_log("sample.log");

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::error
    );
}

int main(int, char* [])
{
    init_logging();

    BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
    BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
    BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "This is a fatal severity message. What What What";
    
    system("pause");
    return 0;
}
