/*
  A class containing all the implementations of string manipulation functions
  made in problems #23 to #44 in the 7th course (Algorithms & Problem Solving
  Level 3)

  https://programmingadvices.com/courses/1936515/lectures/44268525/comments/25945096
*/

#pragma once

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Str {
 public:
  enum TrimType { All, Right, Left };

  Str() = default;
  Str(string value) { value_ = value; }

  string getValue() { return value_; }
  void setValue(string value) { value_ = value; }

  static short length(string str) { return str.length(); }

  static bool isVowel(char c) {
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    for (char vowel : vowels)
      if (tolower(c) == vowel) return true;
    return false;
  }

  static short countVowels(string str) {
    short count = 0;
    for (char c : str)
      if (isVowel(c)) count++;
    return count;
  }

  static void printVowels(string str) {
    for (char c : str)
      if (isVowel(c)) std::cout << c << "   ";
  }

  static short countChar(string str, char c, bool matchCase = true) {
    short count = 0;

    for (short i = 0; i < str.length(); i++) {
      if (matchCase) {
        if (str[i] == c) count++;
      } else {
        if (tolower(str[i]) == tolower(c)) count++;
      }
    }

    return count;
  }

  static short countUpper(string str) {
    short count = 0;
    for (short i = 0; i < str.length(); i++)
      if (isupper(str[i])) count++;
    return count;
  }

  static short countLower(string str) {
    short count = 0;
    for (short i = 0; i < str.length(); i++)
      if (islower(str[i])) count++;
    return count;
  }

  static short countWords(string str) { return split(str, " ").size(); }

  static void printWords(string str) {
    for (string &word : split(str, " ")) std::cout << word << std::endl;
  }

  static void printFirstLetterOfEachWord(string str) {
    if (!isspace(str[0])) std::cout << str[0] << std::endl;
    for (int i = 1; i < str.length(); i++) {
      if (!isspace(str[i]) && isspace(str[i - 1]))
        std::cout << str[i] << std::endl;
    }
  }

  static string removePunct(string str) {
    string noPunct = "";
    for (char c : str)
      if (!ispunct(c)) noPunct += c;
    return noPunct;
  }

  static string lower(string str) {
    string lower = "";
    for (char c : str) lower += tolower(c);
    return lower;
  }

  static string upper(string str) {
    string upper = "";
    for (char c : str) upper += toupper(c);
    return upper;
  }

  static string lowerFirstLetterOfEachWord(string str) {
    if (isupper(str[0])) str[0] = tolower(str[0]);
    for (int i = 1; i < str.length(); i++) {
      if (isupper(str[i]) && isspace(str[i - 1])) str[i] = tolower(str[i]);
    }
    return str;
  }

  static string upperFirstLetterOfEachWord(string str) {
    if (islower(str[0])) str[0] = toupper(str[0]);
    for (int i = 1; i < str.length(); i++) {
      if (islower(str[i]) && isspace(str[i - 1])) str[i] = toupper(str[i]);
    }
    return str;
  }

  static string invertCase(string str) {
    for (short i = 0; i < str.length(); i++)
      str[i] = isupper(str[i]) ? tolower(str[i]) : toupper(str[i]);
    return str;
  }

  static string join(vector<string> &words, string delim) {
    string joined;
    for (string &word : words) joined += word + delim;
    joined.erase(joined.length() - delim.length(), joined.length());
    // OR: joined = joined.substr(0, joined.length() - delim.length());
    return joined;
  }

  static string join(string words[], short length, string delim) {
    string joined;
    for (short i = 0; i < length; i++) joined += words[i] + delim;
    joined.erase(joined.length() - delim.length(), joined.length());
    // OR: joined = joined.substr(0, joined.length() - delim.length());
    return joined;
  }

  static string trim(string str, TrimType type = TrimType::All) {
    switch (type) {
      case TrimType::All:
        str = trim(str, TrimType::Left);
        str = trim(str, TrimType::Right);
        break;
      case TrimType::Left:
        while (isspace(str[0])) str.erase(0, 1);
        break;
      case TrimType::Right:
        while (isspace(str[str.length() - 1]))
          str.erase(str.length() - 1, str.length());
        break;
    }

    return str;
  }

  static string reverse(string str) {
    vector<string> words = split(str, " ");
    vector<string>::iterator iter = words.end();
    str.clear();

    while (iter != words.begin()) str += *(--iter) + " ";

    return str.substr(0, str.length() - 1);  // remove last space.
  }

  static vector<string> split(string str, string delim) {
    string word;  // define a string variable & delimiter
    vector<string> splitted;
    short pos;

    while ((pos = str.find(delim)) != string::npos) {
      word = str.substr(0, pos);  // store the word
      if (word != "") splitted.push_back(word);
      // erase() until positon and move to next word.
      str.erase(0, pos + delim.length());
    }

    if (str != "") splitted.push_back(str);  // include last word of the string.

    return splitted;
  }

  static string replace(string str, string oldWord, string newWord,
                        bool matchCase = true) {
    vector<string> words = split(str, " ");
    vector<string>::iterator iter;
    str.clear();

    for (string &word : words) {
      if (matchCase) {
        str += (word == oldWord ? newWord : word) + " ";
      } else {
        str += (lower(word) == lower(oldWord) ? newWord : word) + " ";
      }
    }

    return str.substr(0, str.length() - 1);  // remove last space.
  }

  short length() { return value_.length(); }
  short countVowels() { return countVowels(value_); }
  void printVowels() { printVowels(value_); }
  short countChar(char c, bool matchCase = true) {
    return countChar(value_, c, matchCase);
  }
  short countUpper() { return countUpper(value_); }
  short countLower() { return countLower(value_); }
  short countWords() { return countWords(value_); }
  void printWords() { printWords(value_); }
  void printFirstLetterOfEachWord() { printFirstLetterOfEachWord(value_); }
  string removePunct() { return (value_ = removePunct(value_)); }
  string lower() { return (value_ = lower(value_)); }
  string upper() { return (value_ = upper(value_)); }
  string lowerFirstLetterOfEachWord() {
    return (value_ = lowerFirstLetterOfEachWord(value_));
  }
  string upperFirstLetterOfEachWord() {
    return (value_ = upperFirstLetterOfEachWord(value_));
  }
  string invertCase() { return (value_ = invertCase(value_)); }
  string trim(TrimType type = TrimType::All) {
    return (value_ = trim(value_, type));
  }
  string reverse() { return (value_ = reverse(value_)); }
  string replace(string oldWord, string newWord, bool matchCase = true) {
    return (value_ = replace(value_, oldWord, newWord, matchCase));
  }
  vector<string> split(string delim = " ") { return split(value_, delim); }

  __declspec(property(get = getValue, put = setValue)) string value;

 private:
  string value_;
};
