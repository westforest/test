// Copyright Xiaobo Fan 2010
//
//
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <unordered_set>

using namespace std;
typedef std::unordered_set<string> Dict;

void search(string letters, int i, int depth, const Dict& dict) {
  if (i == depth) {
    const string word(letters.substr(0, depth));
    //cout << "checking " << word << endl;
    if (dict.find(word) != dict.end()) {
      cout << "FOUND: " << word << endl;
    }
    return;
  }
  std::unordered_set<char> used;
  for (int j = i; j < letters.size(); ++j) {
    char t = letters[j];
    if (used.find(t) != used.end()) continue;
    letters[j] = letters[i];
    letters[i] = t;
    search(letters, i + 1, depth, dict);
    used.insert(t);
  }
}

int main(int argc, char *argv[]) {
  string word;
  Dict dict;
  ifstream file("/usr/share/dict/words");
  if (file.is_open()) {
    while (file.good()) {
      getline (file, word);
      assert(dict.insert(word).second);
    }
  }
  cout << dict.size() << " words scanned" << endl;

  string letters;
  cout << "Letters: ";
  cin >> letters;
  sort(letters.begin(), letters.end());
  for (int depth = 3; depth <= letters.size(); ++depth) {
    search(letters, 0, depth, dict);
  }
  return 0;
}
