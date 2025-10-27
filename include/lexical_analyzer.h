#pragma once
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "../include/token.h"
#include "../include/exception.h"
#include "../include/error_reporter.h"
#include "../include/symbol_table.h"
#include "../include/token_stream.h"


void read_prog(std::string& prog);

void Analysis();