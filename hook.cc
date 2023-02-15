#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

const string WHITESPACE = " \n\r\t\f\v";

string ltrim(const string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string &s) {
    return rtrim(ltrim(s));
}
string getLastWord (string s) {
    reverse(s.begin(),s.end());
    string lastWord = "";
    for (auto word:s) {
        if (word==' ') {
            reverse(lastWord.begin(),lastWord.end());
            return lastWord;
        }
        lastWord += word;
    }
    reverse(lastWord.begin(),lastWord.end());
    return lastWord;
}
vector<string> getFiles(char* fileName) {
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
        bool isFileSupported  = line.ends_with(".java") ||
                                line.ends_with(".js")||
                                line.ends_with(".ts")||
                                line.ends_with(".jsx")||
                                line.ends_with(".tsx")||
                                line.ends_with(".cpp")||
                                line.ends_with(".c")||
                                line.ends_with(".py");
        if (isFileSupported) {
            files.push_back(getLastWord(trim(line)));
        }
    }
    system("rm -rf git_status_output");
    return files;
}

string getExtension (string filename) {
    reverse(filename.begin(),filename.end());
    string ext = "";
    for (auto chr:filename) {
        if (chr == '.')
            break;
        ext+=chr;
    }
    reverse(ext.begin(),ext.end());
    return ext;
}

string getCommenter (string ext) {
    if (ext=="java" || ext=="cpp" || ext=="c" || ext=="js" || ext=="ts" || ext=="jsx" || ext=="tsx") {
        return "//";
    }
    if ( ext=="py") {
        return "#";
    }
    return NULL;
}

void alert(string text) {
    cout << text << "\n";
}

int main(int argc, char** argv) {
    vector<string> files = getFiles(argv[0]);
    for (string file:files) {
        ifstream fileContents(file);
        string extension = getExtension(file);
        string commenter = getCommenter(extension);
        while (!fileContents.eof()) {
            string line;
            getline(fileContents,line);
            if (line.starts_with(commenter)) {
                alert("you have a comment in file -> "+file);
                return -1;
            }
        }
    }
    alert("no comments found :)");
    return 0;
}