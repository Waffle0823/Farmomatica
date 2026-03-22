#include <any>
#include <string>
#include <unordered_map>

class GlobalSettings {
public:
  template <typename T> static void Set(const std::string &key, const T value);
  template <typename T> static T Get(const std::string &key);
  static bool Has(const std::string &key);

private:
  static std::unordered_map<std::string, std::any> settings;
};
