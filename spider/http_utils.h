#pragma once 
#include <vector>
#include <string>
#include <unordered_set>
#include <map>

#include "link.h"

std::string getHtmlContent(const Link& link);

std::string remover(const std::string& html);

std::map<std::string, int> counter(const std::vector<std::string>& words);

std::unordered_set<Link> getLinks(const std::string& html, ProtocolType protocol, const std::string& hostName);