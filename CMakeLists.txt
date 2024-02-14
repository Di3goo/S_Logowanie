cmake_minimum_required (VERSION 3.11)
set (CMAKE_CXX_STANDARD 17)
set (SOURCES_DIR src)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

project(pk-student-journal
  LANGUAGES CXX
  VERSION 1.0.0
)

include(FetchContent)

# --- Fetch MongoDB Driver --------------------------------------------------------------
FetchContent_Declare(
  mongo-cxx-driver
  GIT_REPOSITORY https://github.com/mongodb/mongo-cxx-driver.git
  GIT_TAG r3.7.1
)

FetchContent_MakeAvailable(mongo-cxx-driver)

# ------------------------------------------------------------------------------

# --- Fetch FTXUI --------------------------------------------------------------
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v4.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------

file(GLOB_RECURSE SOURCES "${SOURCES_DIR}/*.cpp")

add_executable(pk-student-journal ${SOURCES})
target_include_directories(pk-student-journal PRIVATE src)

find_package(mongocxx REQUIRED)
target_link_libraries(pk-student-journal
  PRIVATE ${CONAN_LIBS} mongo::mongocxx_shared mongo::bsoncxx_shared
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
