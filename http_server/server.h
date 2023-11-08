#pragma once

#include "../database/database.h"

class Server : public Database
{
public:
	Server(const Config& config);

};