#include <iostream>
#include <string>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/operation_exception.hpp>
#include <mongocxx/instance.hpp>

#include <includes/DatabaseConfig.h>
#include <includes/MongoDBCollection.h>

MongoDBCollection::MongoDBCollection(const std::string& collectionName)
    : collectionName_(collectionName) {
  static bool isInstanceCreated = false;
  if (!isInstanceCreated) {
    mongocxx::instance instance{};
    isInstanceCreated = true;
  }

  client_ = mongocxx::client{mongocxx::uri{DatabaseConfig::host}};
  collection_ = client_[DatabaseConfig::database][collectionName];
}

void MongoDBCollection::addDocument(const bsoncxx::document::view& document) {
  bsoncxx::document::value documentValue{document};
  collection_.insert_one(documentValue.view());
}

void MongoDBCollection::removeDocument(
    const bsoncxx::document::view& document) {
  bsoncxx::document::value documentValue{document};
  collection_.delete_one(documentValue.view());
}

void MongoDBCollection::printDocuments() {
  mongocxx::cursor cursor = collection_.find({});
  for (auto&& document : cursor) {
    std::cout << bsoncxx::to_json(document) << std::endl;
  }
}

mongocxx::cursor MongoDBCollection::find(
    const bsoncxx::document::view& filter) {
  return collection_.find(filter);
}