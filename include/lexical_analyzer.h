#pragma once
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>
#include "token.h"
#include "exception.hpp"
#include "error_reporter.h"
#include "symbol_table.h"

void read_prog(std::string& prog);

void Analysis();