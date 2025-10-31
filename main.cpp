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
    if (line == "")
      oFile << "<br>";
    switch (line[0]) {
    case '#': {
      for (int i = 0; i < 7; i++) {
        if (line[i] != '#') {
          line.erase(0, i);
          oFile << "<h" << i << ">" << line << "</h" << i << ">" << std::endl;
          break;
        } else if (i == 5 && line[6] == '#') {
          oFile << line << std::endl;
          break;
        }
      }
      break;
    }
    case '-': {
      bool flag = true;
      for (int i = 0; i < line.size(); i++) {
        if (line[i] != '-') {
          flag = false;
          break;
        }
      }
      if (flag)
        oFile << "<hr>" << std::endl;
      else
        oFile << line << std::endl;
      break;
    }
    case '*': {
      if (line[1] == '*') {
        line.erase(0, 2);
        line.erase(line.size() - 2, 2);
        oFile << "<strong>" << line << "</strong>" << std::endl;
      } else {
        line.erase(0, 1);
        line.erase(line.end() - 1);
        oFile << "<em>" << line << "</em>" << std::endl;
      }
      break;
    }
    case '_': {
      if (line[1] == '_') {
        line.erase(0, 2);
        line.erase(line.size() - 2, 2);
        oFile << "<strong>" << line << "</strong>" << std::endl;
      } else {
        line.erase(0, 1);
        line.erase(line.end() - 1);
        oFile << "<em>" << line << "</em>" << std::endl;
      }
      break;
    }
    default: {
      oFile << line << std::endl;
      break;
    }
    }
  }
  oFile << "</body>\n</HTML>" << std::endl;
  oFile.close();
  iFile.close();
  return 0;
}
