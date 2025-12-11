message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(nlohmann_json)
find_package(httplib)
find_package(spdlog)
find_package(RdKafka)

set(CONANDEPS_LEGACY  nlohmann_json::nlohmann_json  httplib::httplib  spdlog::spdlog  RdKafka::rdkafka++ )