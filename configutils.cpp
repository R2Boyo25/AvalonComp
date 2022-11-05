#include "configutils.hpp"

toml::table loadConfig() {
  if (std::filesystem::exists(".mort")) {
    try {
      toml::table tmltab = toml::parse(".mort");
      return tmltab;
    } catch (...) {
      std::cout << "Failed to parse config file, not valid TOML" << std::endl;
      std::exit(1);
    }
  }

  toml::table cfg = toml::table();
  return cfg;
}

bool configValueExists(std::map<toml::key, toml::value> table,
                       std::string key) {
  return table.count(key);
}

std::map<toml::key, toml::value> tableToMap(toml::value table) {
  return toml::get<std::map<toml::key, toml::value>>(table);
}

bool configInherits(std::map<toml::key, toml::value> table) {
  if (configValueExists(table, "inherits")) {
    if (!configValueExists(tableToMap(CONFIG),
                           getConfigValue<std::string>(table, "inherits"))) {
      std::cout << "Inherited table is not defined" << std::endl;
      std::exit(1);
    }

    return true;
  }

  return false;
}

toml::value getConfigInheritance(std::map<toml::key, toml::value> table) {
  return getConfigValue<toml::value>(
      tableToMap(CONFIG), getConfigValue<std::string>(table, "inherits"));
}