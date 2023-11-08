#include "server.h"
#include "../indexer/indexer.h"


Server::Server(const Config& config) : Database(config)
{
	c.prepare("search",
		"SELECT d.document, sum(wd.amount) as total "
		"FROM documents d "
		"JOIN words_documents wd ON d.id = wd.document_id "
		"JOIN words w ON wd.word_id"
		"group by(d.document) "
		"order by total limit 10"
	);

}