#include "server.h"
#include "../indexer/indexer.h"


Server::Server(const Config& config) : Database(config)
{
	c.prepare("search",
		"SELECT docs.query, docs.host, sum(wd.total) as total "
		"FROM documents docs "
		"JOIN words_documents wd ON docs.id = wd.document_id "
		"JOIN words w ON wd.word_id = w.id AND w.id = $1 "
		"GROUP BY(docs.query, docs.host) "
		"ORDER BY total limit 10"
	);

}

std::vector<std::string> Server::searchEngine(const std::string& query)
{
	std::vector<std::string> result;

	auto lowerCase = toLowerCase(query);

	std::vector<std::string> words = indexer(lowerCase);

	pqxx::work txn{ c };

	pqxx::result res;

	if (words.size() == 0)
	{
		return result;
	}
	else
	{
		res = txn.exec_prepared("search", words[0]);
	}

	for (const auto& row : res) {

		std::string url = "https://";

		url += row["host"].as<std::string>();
		url += row["query"].as<std::string>();
		result.push_back(url);
	}

	return result;

}