#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
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
  std::regex Br(R"(\s{2,2}$)");
  std::regex Bold(R"([_\*][_\*](.*?)[_\*][_\*])");
  std::regex Em(R"([_\*](.*?)[_\*])");
  std::regex Hr(R"(^[-]{3,}+$)");
  std::regex S1(R"(~(.*?)~)"), S2(R"(~~(.*?)~~)");
  std::string latest_line;
  while (std::getline(iFile, line)) {
    if (line == "")
      line = "<br><br>";
    std::string replaced_br = std::regex_replace(line, Br, "<br>");
    std::string replaced_hr = std::regex_replace(replaced_br, Hr, "<hr>");
    std::string replaced_bold =
        std::regex_replace(replaced_hr, Bold, "<strong>$1</strong>");
    std::string replaced_em =
        std::regex_replace(replaced_bold, Em, "<em>$1</em>");
    latest_line = replaced_em;
    latest_line = std::regex_replace(latest_line, S2, "<s>$1</s>");
    latest_line = std::regex_replace(latest_line, S1, "<s>$1</s>");
    // latest_line = std::regex_replace(latest_line,Sub,)
    oFile << latest_line << std::endl;
  }
  oFile << "</body>\n</HTML>" << std::endl;
  oFile.close();
  iFile.close();
  return 0;
}
