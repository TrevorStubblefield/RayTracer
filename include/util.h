#ifndef UTIL_H
#define UTIL_H

#include "model.h"

Model ReadPLYFile(string filename);
int WritePLYFile(string filename, Model model);

#endif