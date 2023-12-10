#pragma once

#include "../database/database.h"
#include "link.h"
#include <mutex>

class Client : public Database
{
public:
	Client(const Config& config);

	void wordsDoc(const Link& link, const std::map<std::string, int>& wordsTotal);

protected:
	std::mutex mutex_;
};