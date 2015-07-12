#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

void split(vector<string> &tokens, const string &text, string sep) {
    tokens.clear();
    int start = 0, end = 0;
    while ((end = static_cast<int>(text.find(sep, start))) != string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
}

template<class T>
int inline findAndReplace(T& source, const T& find, const T& replace) {
    int num=0;
    size_t fLen = find.size();
    size_t rLen = replace.size();
    for (size_t pos=0; (pos=source.find(find, pos))!=T::npos; pos+=rLen)
    {
        num++;
        source.replace(pos, fLen, replace);
    }
    return num;
}

string putNodeOnDotFormat(const int &info) {
    string pattern = "node$INFO[label = \"<f0> |<f1> $INFO|<f2> \"]";
    findAndReplace<string>(pattern, "$INFO", to_string(info));
    return pattern;
}

string putRelationshipOnDotFormat(const int &infoParent, const int &infoChild, const int &relationship) {
    string pattern = "\"node$INFO_PARENT\":$RELATIONSHIP -> \"node$INFO_CHILD\":f1";
    findAndReplace<string>(pattern, "$INFO_PARENT", to_string(infoParent));
    findAndReplace<string>(pattern, "$INFO_CHILD", to_string(infoChild));
    if (relationship == -1) {
        findAndReplace<string>(pattern, "$RELATIONSHIP", "f0");
    } else if (relationship == +1) {
        findAndReplace<string>(pattern, "$RELATIONSHIP", "f2");
    }
    return pattern;
}

void stringToFile(const string &str, const string &filename) {
    ofstream output;
    output.open(filename);
    output << str;
    output.close();
}

void generateRandomData(int sizeToAdd, int sizeToRemove, string filename) {
    if (sizeToRemove <= sizeToAdd) {
        vector<int> toAdd(sizeToAdd);
        vector<int> toRemove(sizeToRemove);
        srand(time(NULL));

        string content = "ADD " + to_string(sizeToAdd) + "\n";
        for (int i = 0; i < sizeToAdd; i++) {
            toAdd[i] = rand() % sizeToAdd;
            content.append(to_string(toAdd[i]) + "\n");
        }
        content.append("REM " + to_string(sizeToRemove) + "\n");
        for (int i = 0; i < sizeToRemove; i++) {
            toRemove[i] = toAdd[rand() % sizeToAdd];
            content.append(to_string(toRemove[i]) + "\n");
        }
        stringToFile(content, filename);

    } else {
        cout << "Coundn't generate random nodes.";
    }
}


