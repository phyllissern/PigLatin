#include<iostream>
using namespace std;
#include <string>
#include <vector>
#include <fstream>

/**
 make all the words in a string into lowercase
 @param str the string
 */
void make_lower(string& str) {
    // gets the length of the string
    size_t n = str.length();
    // for loop to run through each character of the string
    for (size_t i = 0; i < n; ++i) {
        // if statement to see if there are any uppercase letters
        if ('A' <= str[i] && str[i] <= 'Z') {
            str[i] += 32; // adding this number, 32 (got from the ascii table), will change the letter to its respective lowercase letter
        }
    }
}
 
/**
 determines whether a character is letter or not
 @param c the character
 @return true if the character is a letter, false if it is not
 */
bool is_alpha(char c) {
    // if statement to check if the character is a letter, uppercase or lowercase
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return true;
    }
    // if the character is not a letter
    else {
        return false;
    }
}

/**
 determines whether a character inputted is a vowel (a, e, i, o, u) or not
 @param c the character
 @return true if the character is a vowel, false if it is not
 */
bool is_vowel(char c) {
    // if statement to check if the character is one of the 5 vowels (a, e, i, o, u)
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        return true;
    }
    // if the character is not a vowel
    else {
        return false;
    }
}

/**
 determines whether a character inputted is one of the punctuation marks mentioned on the homework
 @param c the character
 @return true if the character is one of the punctuation marks, false if not
 */
bool is_punc(char c) {
    // if statement to check if the character is one of the punctuations mentioned on the homework
    if ((c >= '!' && c <= '"') || (c >= '\'' && c <= ')')) {
        return true;
    }
    // additional punctuation marks mentioned on the homework
    else if (c == ',' || c == '.' || c == ':' || c == ';' || c == '?') {
        return true;
    }
    // if the character is not one of the mentioned punctuation marks
    else {
        return false;
    }
}

/**
 inputs a large, long string and return a vector of strings that are individual words from the original string (including punctuation marks)
 @param str a string
 @return v the vector of strings
 */
vector<string> words(const string& str) {
    vector<string> v; // creates an empty vector
    string words; // creates an empty string
    
    // for loop to go through the whole string
    for (size_t i = 0; i < str.size(); i++) {
        char ch = str[i]; // looks at each character in the string
        // if statement to determine if the character is an empty space
        if ((ch == ' ') && words.size() != 0) {
            v.push_back(words); // the word being added to the vector
            words = ""; // resetting words back to an empty streing
        }
        else { // if the next character is not an empty space the character will be added to the words
            words += ch;
        }
    }
    v.push_back(words); // adds the last word into the vector, since there is no more empty space
    
    return v; // returns the vector of strings
}

/**
 inputs a string and translates the string into pig latin
 @param str the string to be translated
 @return toPL the string translated to pig latin
 */
string word_to_PL(const string& str) {
    
    size_t n = str.length(); // length of the string
    string toPL; // creates an empty string to be used later
    string temp = str.substr(0, 1); // takes the first character of the string
    
    //if statement to determine if there is a punctuation at the end of the string
    if (is_punc(str[n-1])) {
        // if statement to determine how to translate the string
        if (is_vowel(str[0]) && is_vowel(str[n-2])) {
            toPL = str.substr(0, n-1) + "yay" + str.substr(n-1); // translates for the words that start and end with a vowel
        }
        else if (is_vowel(str[0])) {
            toPL = str.substr(0, n-1) + "ay" + str.substr(n-1); // translates for the words that start with a vowel
        }
        else {
            toPL = str.substr(1, n-2) + temp + "ay" + str.substr(n-1); // translates for the rest of the words (starts with a consosnant)
        }
        return toPL; // returns the translated string
    }
    else { // if there is no punctuation at the end of the string
        //if statement to determine how to translate the string
        if (is_vowel(str[0]) && n == 1) {
            toPL = str + "yay"; // translates for the words that are only one vowel ("i" and "a")
        }
        else if (is_vowel(str[0]) && is_vowel(str[n-1])) {
            toPL = str + "yay"; // translates for the words that start and end with a vowel
        }
        else if (is_vowel(str[0])) {
            toPL = str + "ay"; // translates for the words that start with a vowel and end with a consonant
        }
        else {
            toPL = str.substr(1) + temp + "ay"; // translates for the rest of the words (starts with a consonant)
        }
        return toPL; // returns the translated string
    }
}

/**
 inputs a vector of strings and translates each string into pig latin and outputs a vector of the translated strings
 @param vec the vector of string
 @return trans the vector of translated into pig latin strings
 */
vector<string> vec_to_PL(const vector<string>& vec) {
    size_t N = vec.size(); // gets the vector size
    vector<string> trans; // creates an empty vector
    // for loop to go through each of the strings in the vector
    for (size_t i = 0; i < N; ++i) {
        string toPL = word_to_PL(vec[i]); // takes each string in the vector and uses the word_to_PL function to translate each string into pig latin
        trans.push_back(toPL); // takes the translated word and puts it inside the vector trans
    }
    return trans; // returns a vector of the translated strings
}

/**
 inputs a vector of strings and returns a long single string by inserting a single space in between each word
 @param vec the vector of strings
 @return paragraph the long string of all of the words from the vector combined
 */
string build_paragraph(const vector<string>& vec) {
    // gets the size of the vector
    size_t N = vec.size();
    string paragraph; // create an empty string
    // for loop to go through all the strings stored in the vector
    for (size_t i = 0; i < N; ++i) {
        string temp = vec[i] + " "; // makes a string of the string in the vector with a space after
        paragraph = paragraph + temp; // adds the previous string to the new string from the vector each time
    }
    return paragraph; // returns a long string of all the words from the vector combined
}


int main() {

    //creating an input stream
    ifstream in_file;
    in_file.open("Gettysburg.txt"); // open the gettysburg text
    
    string GettysburgRaw; // creates an empty string
    getline(in_file, GettysburgRaw); // stores the gettyburg text into a long string
    
    make_lower(GettysburgRaw); // makes each of the letters in the text to be lower case
    
    vector<string> GettysburgRawStrings = words(GettysburgRaw); // creates a vector of strings from the long string
    vector<string> GettysburgTransStrings = vec_to_PL(GettysburgRawStrings); // creates a vector of strings that are translated to pig latin
    
    string ettysburggay = build_paragraph(GettysburgTransStrings); // stitches all the strings from the vector back into a long string
    
    // creates an output stream
    ofstream out_file;
    out_file.open("ettysburggay.txt"); // names the new file as ettysburggay.txt
    out_file << ettysburggay << "\n";
     
    return 0;
}
