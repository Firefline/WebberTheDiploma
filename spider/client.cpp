#include "client.h"

Client::Client(const Config& config) : Database(config)
{
	c.prepare("insert_word", "INSERT INTO words (word) VALUES ($1) RETURNING id;");
	c.prepare("insert_document", "INSERT INTO documents (query, host) VALUES ($1, $2) RETURNING id;");
	c.prepare("insert_word_document", "INSERT INTO words_documents (word_id, document_id, total) VALUES ($1, $2, $3) RETURNING id;");

}

void Client::wordsDoc(const Link& link, const std::map<std::string, int>& wordsTotal)
{
	std::lock_guard<std::mutex> lock(mutex_);
	
	pqxx::work doc_trx{ c };
	pqxx::result res = doc_trx.exec_prepared("insert_document", link.hostName, link.query);
	doc_trx.commit();

	if (!res.empty()) {
		int id = res[0][0].as<int>();

		pqxx::work words_trx{ c };

		for (auto w : wordsTotal)
		{
			words_trx.exec_prepared("insert_word", w.first);
			words_trx.exec_prepared("insert_word_document", w.first, id, w.second);
		}

		words_trx.commit();
	}


}