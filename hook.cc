#include <iostream>
#include <string>
#include <fstream>

int main () {
    system("git status > git_status_output");
    std::ifstream git_status_output_file("git_status_output");
    while(!git_status_output_file.eof()){
        std::string line;
        getline(git_status_output_file,line);
        std::cout << "line = " << line << std::endl;
    }
}