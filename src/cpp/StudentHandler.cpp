#include <includes/StudentHandler.h>

mongocxx::cursor StudentHandler::getStudentsList() {
  bsoncxx::document::value filter = bsoncxx::builder::basic::make_document(
    bsoncxx::builder::basic::kvp(ROLE_FIELD_KEY, "student")
  );

  mongocxx::cursor cursor = collection_.find(filter.view());

  return cursor;
}
