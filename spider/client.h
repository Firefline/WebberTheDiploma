#pragma once

#include "../database/database.h"

class Client : public Database
{
public:
	Client(const Config& config);

};