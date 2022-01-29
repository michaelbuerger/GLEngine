#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <stdio.h>

#include "CPPML/logging/logging.hpp"

/* Scans FILE till newline, does nothing with any scanned information */
int ScanTillNewline(FILE* file) {
    return fscanf(file, "%*[^\n]\n");
}