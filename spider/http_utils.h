#pragma once 
#include <vector>
#include <string>
#include <unordered_set>
#include <map>

#include "link.h"

std::string getHtmlContent(const Link& link);

std::string remover(const std::string& html);