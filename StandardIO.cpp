#include "header.h"

class StandardIO {
 public:
  explicit StandardIO(int socket) : socket_(socket) {}

  bool Read(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }
    std::string line;
    while (getline(file, line)) {
      rows.push_back(line);
    }
    file.close();
    return true;
  }


  bool Write() {
    std::string data;
    for (const auto& row : rows) {
      data += row + '\n';
      std::cout << data;
    }
  }

 private:
  int socket_;
  std::vector<std::string> rows;
};