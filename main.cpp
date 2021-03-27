#include <cassert>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

string trim(const string& s);
string stringFromFile(const string& fileName);
string getWordUnderHead(const string& tape, const size_t& head);
unordered_set<string> getFinalStates(string tape);
bool findTransition(const string& tape, const string& state, const string& word,
                    string& nextState, string& newWord, string& direction);
 
int main(int argc, char** argv)
{
    assert ("must specify an input file" && argc > 1);

    // assign initial state of tape 1
    string tape1 = string(stringFromFile(argv[1]));

    // assign initial state of tape 2
    size_t separator = tape1.find("000");       // find separator between Turing machine and input representation
    string tape2 = tape1.substr(separator + 3); // copy input to tape2

    // assign initial state of tape 3
    string tape3 = "1";

    unordered_set<string> finalStates = getFinalStates(tape1);

    // erase final states and input from tape1
    tape1.erase(separator);
    tape1.erase(0, tape1.find("00") + 2);

    size_t head1 = 0, head2 = 0, head3 = 0;

    string nextState, newWord, direction;

    return 0;
}

unordered_set<string> getFinalStates(string tape)
{
    unordered_set<string> finalStates;

    // erase transitions, keeping only final states
    tape.erase(tape.find("00"));

    size_t pos = 0;
    while(pos != string::npos)
    {
        if (tape[pos] == '1')
        {
            const string state = getWordUnderHead(tape, pos);
            finalStates.insert(state);
            pos = tape.find("0", pos);
        }
        else
            pos = tape.find("1", pos);
    }

    return finalStates;
}

bool findTransition(const string& tape, const string& state, const string& word, string& nextState, string& newWord, string& direction)
{
    const string auxTape = "00" + tape;

    size_t l = auxTape.find("00" + state + "0" + word);
    if (l == string::npos)
        return false;
    else
        l += 2;

    size_t r = auxTape.find("00", l);

    string transition = auxTape.substr(l, r - l);

    size_t pos = 0;
    int count = 0;
    while(pos != string::npos)
    {
        if (transition[pos] == '1')
        {
            switch(count)
            {
                case 0: break;
                case 1: break;
                case 2: nextState = getWordUnderHead(transition, pos); break;
                case 3: newWord = getWordUnderHead(transition, pos); break;
                case 4: direction = getWordUnderHead(transition, pos); break;
            }

            pos = transition.find("0", pos);
            count ++;
        }
        else
            pos = transition.find("1", pos);
    }

    assert ("wrong format" && !nextState.empty() && !newWord.empty() && !direction.empty());

    return true;
}

string getWordUnderHead(const string& tape, const size_t& head)
{
    const size_t pos = tape.find_first_of("0", head);
    return (pos != string::npos) ? tape.substr(head, pos - head) : tape.substr(head);
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
