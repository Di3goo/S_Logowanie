#ifndef MONGODB_COLLECTION_H
#define MONGODB_COLLECTION_H

#include <bsoncxx/document/value.hpp>
#include <mongocxx/collection.hpp>
#include <mongocxx/client.hpp>
#include <string>

class MongoDBCollection {
 public:
  MongoDBCollection(const std::string& collectionName);

  void addDocument(const bsoncxx::document::view& document);
  void removeDocument(const bsoncxx::document::view& document);
  void printDocuments();
  mongocxx::collection getCollection() const;
  mongocxx::cursor find(const bsoncxx::document::view& filter);

 private:
  std::string collectionName_;
  mongocxx::client client_;
  mongocxx::collection collection_;
};

#endif