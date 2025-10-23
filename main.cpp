#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string fileName, htmlFile = "a.html";
  if (argc < 2) {
    std::cout << "Error: File can't open" << std::endl;
    return 0;
  } else {
    fileName = argv[1];
    htmlFile = argc == 2 ? "a.html" : argv[2];
  }
  std::ofstream oFile(htmlFile, std::ios::trunc);
  std::ifstream iFile(fileName);
  std::string line;
  oFile << "<!DOCTYPE HTML>\n<body>" << std::endl;
  while (std::getline(iFile, line)) {
    switch (line[0]) {
    case '#':
      for (int i = 0; i < 7; i++) {
        if (line[i] != '#') {
          line.erase(0, i);
          oFile << "<h" << i << ">" << line << "</h" << i << ">" << std::endl;
          break;
        } else if (i == 5 && line[6] == '#') {
          oFile << "<p>" << line << "</p>" << std::endl;
          break;
        }
      }
    }
  }
  oFile << "</body>\n</HTML>" << std::endl;
  oFile.close();
  iFile.close();
  return 0;
}
