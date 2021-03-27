#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string trim(const string& s);
string stringFromFile(const string& fileName);
 
int main(int argc, char** argv)
{
    assert ("must specify an input file" && argc > 1);

    string tape1 = string(stringFromFile(argv[1]));
    string tape2 = tape1.substr(tape1.find("000"));
    string tape3 = "1";

    return 0;
}

string stringFromFile(const string& fileName)
{
    // write string from file
    ifstream ifs(fileName);;
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    assert ("input can't be empty" && !input.empty()); 
    input = trim(input); // remove leading and trailing whitespaces
    assert ("input must composed by only 0's and 1's" && (input.find_last_not_of("01") == string::npos));

    return input;
}

string trim(const string& s)
{
    const string WHITESPACE = " \n\r\t\f\v";

    auto ltrim = [&](const string& s) -> string
    {
        size_t start = s.find_first_not_of(WHITESPACE);
        return (start == string::npos) ? "" : s.substr(start);
    };
     
    auto rtrim = [&](const string& s) -> string
    {
        size_t end = s.find_last_not_of(WHITESPACE);
        return (end == string::npos) ? "" : s.substr(0, end + 1);
    };

    return rtrim(ltrim(s));
}
