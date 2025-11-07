#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
std::regex brCheck(R"([^\s]+)");
std::regex H(R"(^\s*(#{1,6})\s(.*))");
std::regex Br(R"(\s{2,2}$)");
std::regex EB(R"([*]{3,3}([^*]+)[*]{3,3})");
std::regex Bold(R"([*]{2,2}([^*]+)[*]{2,2}|[_]{2,2}([^_]+)[_]{2,2})");
std::regex Em(R"([*]([^*]+)[*]|[_]([^_]+)[_])");
std::regex Hr(R"(^([-_*])\1{2,}+$)");
std::regex S(R"([^~]~([^~]+)~[^~]|~~([^~]+)~~)");

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
  oFile << "<!DOCTYPE HTML>\n<body>" << std::endl;

  bool br_flag = false;

  std::string line;
  std::string latest_line;
  std::smatch m;
  while (std::getline(iFile, line)) {
    latest_line = line;
    latest_line = line = "" && br_flag ? "<br>" : "<br><br>";
    if (!br_flag) {
      latest_line += std::regex_replace(latest_line, Br, "<br>");
      br_flag = true;
    } else {
      if (std::regex_match(latest_line, m, brCheck))
        br_flag = false;
    }
    if (std::regex_match(latest_line, m, H))
      latest_line = "<h" + std::to_string(m[1].str().length()) + '>' +
                    m[2].str() + "</h" + std::to_string(m[1].str().length()) +
                    '>';
    latest_line = std::regex_replace(latest_line, Hr, "<hr>");
    latest_line =
        std::regex_replace(latest_line, EB, "<strong><em>$1</em></strong>");
    latest_line =
        std::regex_replace(latest_line, Bold, "<strong>$2$4</strong>");
    latest_line = std::regex_replace(latest_line, Em, "<em>$1</em>");
    latest_line = std::regex_replace(latest_line, S, "<s>$1</s>");
    oFile << latest_line << std::endl;
  }
  oFile << "</body>\n</HTML>" << std::endl;
  oFile.close();
  iFile.close();
  return 0;
}
