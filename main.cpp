#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
std::regex brCheck(R"(\s*[^\s]{1,}.*)");
std::regex H(R"(^\s*(#{1,6})\s(.*))");
std::regex Br(R"(\s{2,2}$|\\$)");
std::regex EB(R"([*]{3,3}([^*]+)[*]{3,3})");
std::regex Bold(R"([*]{2,2}([^*]+)[*]{2,2}|[_]{2,2}([^_]+)[_]{2,2})");
std::regex Em(R"([*]([^*]+)[*]|[_]([^_]+)[_])");
std::regex Hr(R"(^([-_*])\1{2,}+$)");
std::regex S(R"([^~]~([^~]+)~[^~]|~~([^~]+)~~)");
std::regex Code(R"((^`|[^\\]`)(.+[^(\\`)])`)");
std::regex Codes(R"((^`{3,}))");
std::regex Link(R"(\[([^[]*)\]\((.*)\))");

int main(int argc, char *argv[]) {
  std::string fileName, htmlFile = "index.html";
  if (argc < 2) {
    std::cout << "Error: File can't open" << std::endl;
    return 0;
  } else {
    fileName = argv[1];
    htmlFile = argc == 2 ? "index.html" : argv[2];
  }
  std::ofstream oFile(htmlFile, std::ios::trunc);
  std::ifstream iFile(fileName);
  oFile << "<!DOCTYPE HTML>\n<head>\n\
<meta charset = \"utf-8\"/>\n\
<link rel=\"stylesheet\" href=\"markdown-style.css\">\n\
      <title> "
        << htmlFile << "</title>\n\
</head>\n<body>"
        << std::endl;

  bool br_flag = true, emp_flag = true;
  int code_cnt = 0;
  std::string line;
  std::string latest_line;
  std::smatch m;
  while (std::getline(iFile, line)) {
    latest_line = line;
    if (std::regex_match(latest_line, m, brCheck)) {
      br_flag = false;
      emp_flag = false;
    }
    if (code_cnt == 0) {
      if (!br_flag) {
        if (latest_line.empty()) {
          latest_line = "<br><br>";
          br_flag = true;
        } else if (std::regex_search(latest_line, Br)) {
          latest_line = std::regex_replace(latest_line, Br, "<br>");
          br_flag = true;
        }
      } else {
        if (latest_line.empty() && !emp_flag) {
          latest_line = "<br>";
          emp_flag = true;
        }
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
      latest_line = std::regex_replace(latest_line, S, "<s>$2</s>");
      latest_line = std::regex_replace(latest_line, Code, "<code>$2</code>");
      latest_line = std::regex_replace(latest_line, Link, "<a href=$2>$1</a>");
    }
    if (std::regex_match(latest_line, m, Codes)) {
      if (code_cnt == 0) {
        latest_line = "<pre><code>";
        code_cnt = m[1].str().length();
      } else {
        if (code_cnt <= m[1].str().length()) {
          latest_line = "</code></pre>";
          code_cnt = 0;
        }
      }
    }
    oFile << latest_line << std::endl;
  }
  oFile << "</body>\n</HTML>" << std::endl;
  oFile.close();
  iFile.close();
  return 0;
}
