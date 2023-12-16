#include "server.h"
#include "../indexer/indexer.h"


Server::Server(const Config& config) : Database(config)
{
	c.prepare("search",
		"SELECT docs.query, docs.host, sum(wd.total) as total "
		"FROM documents docs "
		"JOIN words_documents wd ON docs.id = wd.document_id "
		"GROUP BY(docs.query, docs.host) "
		"ORDER BY total limit 10"
	);

}