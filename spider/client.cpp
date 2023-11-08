#include "client.h"

Client::Client(const Config& config) : Database(config)
{
	c.prepare("insert_words", "INSERT INTO words VALUES;");
	c.prepare("insert_documents", "INSERT INTO documents VALUES;");
	c.prepare("insert_words_documents", "INSERT INTO words_documentsVALUES ($1, $2, $3);");

}