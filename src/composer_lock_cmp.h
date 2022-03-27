#include "json.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

using inner_data = std::map<std::string, std::string>;
using packages = std::map<std::string, inner_data>;
using pkgByTypes = std::map<std::string, packages>;


pkgByTypes ReadPackages(std::string&& filename, std::vector<std::string> types);
void Compare(pkgByTypes& first, pkgByTypes& second);
void Print(const pkgByTypes& pkg);