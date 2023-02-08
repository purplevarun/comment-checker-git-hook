#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

bool ends_with(std::string const &value, std::string const &ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

vector<string> getFiles() {
    // generate git_status_output
    string git_status_command = "git status --untracked-files=all > ";
    string git_status_file_name = "git_status_output";
    string cmd = git_status_command + git_status_file_name;
    system(cmd.c_str());
    ifstream git_status_output_file(git_status_file_name);
    vector<string> files;

    // extract filepaths from git_status_output
    while (!git_status_output_file.eof()) {
        string line;
        getline(git_status_output_file, line);
        bool isFileSupported  = ends_with(line,"java") ||
                                ends_with(line,"js")||
                                ends_with(line,"ts")||
                                ends_with(line,"jsx")||
                                ends_with(line,"tsx")||
                                ends_with(line,"cpp")||
                                ends_with(line,"py");

        if (isFileSupported) {
            files.push_back(trim(line));
        }

    }
    system("rm -rf git_status_output");
    return files;
}

int main() {
    vector<string> files = getFiles();
    for (string i:files)
        cout << i << endl;
}