
//ProgrammingAdvices.com
//Mohammed Abu-Hadhoud

#pragma once

#include <iostream>
#include <vector>

using namespace std;

class clsString 
{

private:
    string _Value;

public:

    clsString()
    {
       _Value = "";
    }

    clsString(string Value)
    {
        _Value = Value;
    }

    void SetValue(string Value) {
        _Value = Value;
    }

    string GetValue() {
        return _Value;
    }

    __declspec(property(get = GetValue, put = SetValue)) string Value;

   
    static short Length(string S1)
    {
        return S1.length();
    };

    short Length()
    {
        return _Value.length();
    };

   static short CountWords(string S1)
    {

        string delim = " "; // delimiter  
        short Counter = 0;
        short pos = 0;
        string sWord; // define a string variable  

        // use find() function to get the position of the delimiters  
        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word   
            if (sWord != "")
            {
                Counter++;
            }

            //erase() until positon and move to next word.
            S1.erase(0, pos + delim.length());
        }

        if (S1 != "")
        {
            Counter++; // it counts the last word of the string.
        }

        return Counter;

    }

    short CountWords()
    {
        return CountWords(_Value);
    };

    static string  UpperFirstLetterOfEachWord(string S1)
    {

        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = toupper(S1[i]);

            }

            isFirstLetter = (S1[i] == ' ' ? true : false);

        }

        return S1;
    }

    void  UpperFirstLetterOfEachWord()
    {
        // no need to return value , this function will directly update the object value  
       _Value = UpperFirstLetterOfEachWord(_Value);
    }

   static string  LowerFirstLetterOfEachWord(string S1)
    {

        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = tolower(S1[i]);

            }

            isFirstLetter = (S1[i] == ' ' ? true : false);

        }

        return S1;
    }

    void  LowerFirstLetterOfEachWord()
    {

       
        // no need to return value , this function will directly update the object value  
        _Value = LowerFirstLetterOfEachWord(_Value);
    }
    
   static string  UpperAllString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            S1[i] = toupper(S1[i]);
        }
        return S1;
    }

   void  UpperAllString()
   {
       _Value = UpperAllString(_Value);
   }

   static string  LowerAllString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            S1[i] = tolower(S1[i]);
        }
        return S1;
    }

   void  LowerAllString()
    {
        _Value = LowerAllString(_Value);
    }

   static char  InvertLetterCase(char char1)
    {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

   static string  InvertAllLettersCase(string S1)
   {
       for (short i = 0; i < S1.length(); i++)
       {
           S1[i] = InvertLetterCase(S1[i]);
       }
       return S1;
   }

   void  InvertAllLettersCase()
   {
       _Value = InvertAllLettersCase(_Value);
   }

   enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };

   static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
   {


       if (WhatToCount == enWhatToCount::All)
       {
           return S1.length();
       }

       short Counter = 0;

       for (short i = 0; i < S1.length(); i++)
       {

           if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
               Counter++;


           if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
               Counter++;


       }

       return Counter;

   }
  
   static short  CountCapitalLetters(string S1)
   {

       short Counter = 0;

       for (short i = 0; i < S1.length(); i++)
       {

           if (isupper(S1[i]))
               Counter++;

       }

       return Counter;
   }

   short  CountCapitalLetters()
   {
       return CountCapitalLetters(_Value);
   }

   static short  CountSmallLetters(string S1)
   {

       short Counter = 0;

       for (short i = 0; i < S1.length(); i++)
       {

           if (islower(S1[i]))
               Counter++;

       }

       return Counter;
   }

   short  CountSmallLetters()
   {
       return CountSmallLetters(_Value);
   }
   
   static short  CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
   {

       short Counter = 0;

       for (short i = 0; i < S1.length(); i++)
       {

           if (MatchCase)
           {
               if (S1[i] == Letter)
                   Counter++;
           }
           else
           {
               if (tolower(S1[i]) == tolower(Letter))
                   Counter++;
           }

       }

       return Counter;
   }

   short  CountSpecificLetter( char Letter, bool MatchCase = true)
  {
      return CountSpecificLetter(_Value,Letter, MatchCase);
  }

   static bool IsVowel(char Ch1)
  {
      Ch1 = tolower(Ch1);

      return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));

  }

   static short  CountVowels(string S1)
  {

      short Counter = 0;

      for (short i = 0; i < S1.length(); i++)
      {

          if (IsVowel(S1[i]))
              Counter++;

      }

      return Counter;
  }

   short  CountVowels()
  {
      return CountVowels(_Value);
  }

   static vector<string> Split(string S1, string Delim)
  {

      vector<string> vString;

      short pos = 0;
      string sWord; // define a string variable  

      // use find() function to get the position of the delimiters  
      while ((pos = S1.find(Delim)) != std::string::npos)
      {
          sWord = S1.substr(0, pos); // store the word   
          if (sWord != "")
          {
              vString.push_back(sWord);
          }

          S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
      }

      if (S1 != "")
      {
          vString.push_back(S1); // it adds last word of the string.
      }

      return vString;

  }

   vector<string> Split( string Delim)
  {
      return Split(_Value, Delim);
  }

   static string TrimLeft(string S1)
  {


      for (short i = 0; i < S1.length(); i++)
      {
          if (S1[i] != ' ')
          {
              return S1.substr(i, S1.length() - i);
          }
      }
      return "";
  }

   void TrimLeft()
 {
     _Value = TrimLeft(_Value);
 }

   static string TrimRight(string S1)
  {


      for (short i = S1.length() - 1; i >= 0; i--)
      {
          if (S1[i] != ' ')
          {
              return S1.substr(0, i + 1);
          }
      }
      return "";
  }
 
   void TrimRight()
  {
      _Value = TrimRight(_Value);
  }

   static string Trim(string S1)
  {
      return (TrimLeft(TrimRight(S1)));

  }

   void Trim()
  {
      _Value= Trim(_Value);
  }

   static string JoinString(vector<string> vString, string Delim)
  {

      string S1 = "";

      for (string& s : vString)
      {
          S1 = S1 + s + Delim;
      }

      return S1.substr(0, S1.length() - Delim.length());


  }

   static string JoinString(string arrString[], short Length, string Delim)
  {

      string S1 = "";

      for (short i = 0; i < Length; i++)
      {
          S1 = S1 + arrString[i] + Delim;
      }

      return S1.substr(0, S1.length() - Delim.length());

  }

   static string ReverseWordsInString(string S1)
  {

      vector<string> vString;
      string S2 = "";

      vString = Split(S1, " ");

      // declare iterator
      vector<string>::iterator iter = vString.end();

      while (iter != vString.begin())
      {

          --iter;

          S2 += *iter + " ";

      }

      S2 = S2.substr(0, S2.length() - 1); //remove last space.

      return S2;
  }

   void ReverseWordsInString()
  {
      _Value = ReverseWordsInString(_Value);
  }

   static string ReplaceWord(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
  {

      vector<string> vString = Split(S1, " ");

      for (string& s : vString)
      {

          if (MatchCase)
          {
              if (s == StringToReplace)
              {
                  s = sRepalceTo;
              }

          }
          else
          {
              if (LowerAllString(s) == LowerAllString(StringToReplace))
              {
                  s = sRepalceTo;
              }

          }

      }

      return JoinString(vString, " ");
  }

   string ReplaceWord(string StringToReplace, string sRepalceTo)
 {
     return ReplaceWord(_Value, StringToReplace, sRepalceTo);
 }

   static string RemovePunctuations(string S1)
 {

     string S2 = "";

     for (short i = 0; i < S1.length(); i++)
     {
         if (!ispunct(S1[i]))
         {
             S2 += S1[i];
         }
     }

     return S2;

 }

   void RemovePunctuations()
 {
     _Value = RemovePunctuations(_Value);
 }


};

