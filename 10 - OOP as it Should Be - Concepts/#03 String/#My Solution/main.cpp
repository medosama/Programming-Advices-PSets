// This file is a modified version of instructor's main file.
// https://programmingadvices.com/courses/1936515/lectures/44268525/comments/25945096

#include <iostream>

#include "str.h"

using std::cout;
using std::endl;

int main() {
  Str str1;
  Str str2("Mohamed");

  str1.value = "Ali Ahmed";

  cout << "str1 = " << str1.value << endl;
  cout << "str2 = " << str2.value << endl;

  cout << "Number of words: " << str1.countWords() << endl;
  cout << "Number of words: " << str1.countWords("Fadi ahmed omer") << endl;
  cout << "Number of words: " << Str::countWords("Mohammed") << endl;

  //----------------

  Str str3("hi how are you?");

  cout << "str3 = " << str3.value << endl;

  cout << "String Length = " << str3.length() << endl;

  str3.upperFirstLetterOfEachWord();
  cout << str3.value << endl;

  //----------------

  str3.lowerFirstLetterOfEachWord();
  cout << str3.value << endl;

  //----------------

  str3.upper();
  cout << str3.value << endl;

  //----------------

  str3.lower();
  cout << str3.value << endl;

  //----------------

  cout << "After inverting a : " << Str::invertCase("a") << endl;

  //----------------

  str3.value = "AbCdEfg";

  str3.invertCase();
  cout << str3.value << endl;

  str3.invertCase();
  cout << str3.value << endl;

  //----------------

  cout << "Upper count : " << Str::countUpper("Mohammed Abu-Hadhoud") << endl;

  //----------------

  str3.value = "Welcome to Jordan";
  cout << str3.value << endl;

  cout << "Capital letters count : " << str3.countUpper() << endl;

  //----------------

  cout << "Small letters count : " << str3.countLower() << endl;

  //----------------

  cout << "Vowels count : " << str3.countVowels() << endl;

  //----------------

  cout << "Letter E count : " << str3.countChar('E', false) << endl;

  //----------------

  cout << "Is letter u vowel? " << Str::isVowel('u') << endl;

  //----------------

  cout << "Words count : " << str3.countWords() << endl;

  //----------------

  vector<string> words = str3.split();

  cout << "\nWords = " << words.size() << endl;

  for (string &word : words) {
    cout << word << endl;
  }

  //----------------

  // Trims
  str3.value = "    Mohammed Abu-Hahdoud     ";
  cout << "\nString     = " << str3.value << '.';

  str3.trim(Str::TrimType::Left);
  cout << "\n\nTrim Left  = " << str3.value << '.';

  //----------------

  str3.value = "    Mohammed Abu-Hahdoud     ";
  str3.trim(Str::TrimType::Right);
  cout << "\nTrim Right = " << str3.value << '.';

  //----------------

  str3.value = "    Mohammed Abu-Hahdoud     ";
  str3.trim();
  cout << "\nTrim       = " << str3.value << '.';

  //----------------

  // Joins
  vector<string> words2 = {"Mohammed", "Faid", "Ali", "Maher"};

  cout << "\n\nJoin String From Vector: \n";
  cout << Str::join(words2, " ");

  string arr[] = {"Mohammed", "Faid", "Ali", "Maher"};

  cout << "\n\nJoin String From Array: \n";
  cout << Str::join(arr, 4, " ");

  //----------------

  str3.value = "Mohammed Saqer Abu-Hahdoud";
  cout << "\n\nString     = " << str3.value;

  str3.reverse();
  cout << "\nReverse Words : " << str3.value << endl;

  //---------------

  str3.value = "Mohammed Saqer Abu-Hahdoud";
  cout << "\nReplace : " << str3.replace("Mohammed", "Sari") << endl;

  //---------------

  str3.value = "This is: a sample text, with punctuations.";
  cout << "\n\nString     = " << str3.value;

  str3.removePunct();
  cout << "\nRemove Punctuations : " << str3.value << endl;

  //---------------
  return 0;
};
