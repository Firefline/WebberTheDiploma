#include "server.h"
#include "../indexer/indexer.h"


Server::Server(const Config& config) : Database(config)
{
	c.prepare("search",
		"SELECT doc.document, sum(wd.total) as total "
		"FROM documents doc "
		"JOIN words_documents wd ON doc.id = wd.document_id "
		"GROUP BY(doc.document) "
		"ORDER BY total limit 10"
	);

}