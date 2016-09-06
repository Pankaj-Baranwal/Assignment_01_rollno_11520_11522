/*

*/

#include <iostream>		//header for handling standard input-output.
#include <string.h>		//header for string functionality.
#include <fstream>		//header for file-handling.
#include <stdlib.h>		//header for program exit.


using namespace std;

/*
	global variables.
*/
// File name. Repalce this with your txt file.

string g_file_name = "sample.txt";

//Prototypes of functions defined in the code.
void display_options();
void process_option(char a);
void count_probability(string search_string);
void find_words_using_dictionary_search(string search_string);
void clear_screen();
void count_paragraphs();
void find_words_using_dictionary_search(string search_string);
void KMPMainAlgo(string search_string, string main_string);
bool single_kmp(string search_string, string main_string);
void computeLPSArray(string search_string, int string_size, int lps[]);


/*
	Main function
*/
int main()
{
	display_options();
	return 0;
}

/*
	function for displaying menu.
*/
void display_options(){

	char input_choice;		// variable to store user choice
	cout << "Menu Options: " << endl;
	cout << "0.) Clear Screen" << endl;
	cout << "1.) KMP Search" << endl;
	cout << "2.) Count number of paragraphs" << endl;
	cout << "3.) Dictionary Search" << endl;
	cout << "4.) Probability of word in document" << endl;
	cout << "5.) Exit" << endl;
	cout << "Enter your choice: ";
	cin >> input_choice;
	string futile_string;		// useless. Just to capture extra \n
	getline(cin, futile_string);
	process_option(input_choice);
}

/*
	function for implementing menu.
*/
void process_option(char a){
	string search_string;		// string to be searched
	string main_string;			// Main text on which processing is being done
	switch (a){
		case '0':
			clear_screen();
			display_options();
			break;
		case '1':
			cout << "Options chosen: KMP Search." << endl;
			cout << "Enter main string" << endl;
			getline(cin, main_string);
			cout << "Enter sub string to be searched" << endl;
			getline(cin, search_string);
			KMPMainAlgo(search_string, main_string);
			cout << endl;
			cout << endl;
			display_options();
			break;
		case '2':
			cout << endl;
			cout << "Options chosen: Count paragraphs." << endl;
			count_paragraphs();
			cout << endl;
			cout << endl;
			display_options();
			break;
		case '3':
			cout << endl;
			cout << "Options chosen: Dictionary search." << endl;
			cout << "Enter the string you want to use for dictionary search" << endl;
			cin >> search_string;
			find_words_using_dictionary_search(search_string);
			cout << endl;
			cout << endl;
			display_options();
			break;
		case '4':
			cout << endl;
			cout << "Options chosen: Dictionary search." << endl;
			cout << "Enter the string you want to get probability of" << endl;
			cin >> search_string;
			count_probability(search_string);
			cout << endl;
			cout << endl;
			display_options();
			break;
		case '5':
			clear_screen();
			cout << endl;
			cout << endl;
			cout << "Thank you for using our program!" << endl;
			cout << endl;
			cout << endl;
			exit(0);
			break;
	}
}


/**
	Counts the probability of a certain word in the text file.
	@implements a function which reads through
     the file and counts probability of a word
     in the given text.

*/
void count_probability(string search_string){
	ifstream file (g_file_name.c_str());		// Read file.
	int count_words = 0;				// number of words mathcing criteria.
	if (file.is_open()){				// Check if file is open.
	string word;						// To store each new word from file.
    char x ;							// Stores character from file.
    word.clear();						// Clear existing word.
    int total_words = 0;				// Stores number of words in file.
    bool found_char = false;
    while ((x = file.get()) != EOF)
    {
        while ( x != ' ' && x !='\n')
        {
        	found_char = true;
            word = word + x;
            if ((x = file.get()) == EOF){
	            break;
	        }
        }
        if (found_char)
        {
        	total_words++;
        	found_char = false;
        }
        if (word.length()>0){
	        if (single_kmp(search_string, word)){
	        	count_words++;
	        }
	    }
        word.clear();
    }
	file.close();
	cout << "Total words = " << total_words << endl;
	cout << "Total occurances of selected string = " << count_words << endl;
	cout << "Probability = " << (count_words*100 / total_words) << " percent" <<endl;
	}else{
		cout << "Unable to open file" << endl;
	}
}

/**
   	Finds words using dictionary search.
    
    @param search_string pattern to be searched in the file.
    @implements a function which reads through
     the file and finds the word using KMP string
     search algorithm.
*/

void find_words_using_dictionary_search(string search_string){
	ifstream file (g_file_name.c_str());
	cout << endl;
	cout << endl;
	cout << "If any word is found, it will be mentioned below: " << endl;
	int counter = 0;
	if (file.is_open()){
		string word = "";
	    char x ;
	    while ((x = file.get()) != EOF)
	    {
	        while ( x != ' ' && x !='\n')
	        {
	            word = word + x;
	            if ((x = file.get()) == EOF){
	            	break;
	            }
	        }
	        if (word.length()>0){
	        	if (single_kmp(search_string, word)){
	        		counter ++;
	        		cout << word << endl;
	        	}
	        }
	        word = "";
	    }
	    file.close();
	    if (counter == 0){
	    	cout << endl;
	    	cout << "No word found." << endl;
	    }else{
	    	cout << endl;
	    	cout << "Total words found: " << counter << endl;
	    }
	}
	else{
		cout << "Unable to open file" << endl;
	}
}


void clear_screen(){
	cout << string( 100, '\n' );
}

/**
   	Counts number of paragraphs in a text file.
    
    @implements a function which reads through
     the file and counts number of paragraphs
     which have been defined as a seperation with
     a blank line.
*/

void count_paragraphs(){
	string line;
	bool found_something = false;
	ifstream file (g_file_name.c_str());
	if (file.is_open())
	{
		int count = 1;
		int internal_count = 0;
		char ch;
		bool char_found = false;
		while((ch = file.get()) != EOF)
		{
			if (ch != '\n' && ch != ' ' && ch != '\t')
			{
				found_something = true;
				char_found = true;
			}else{
				if (char_found)
				{
					if (internal_count == 1)
					{
						count += 1;
						internal_count = 0;
						char_found = false;
					}else{
						internal_count += 1;
					}
				}
			}
		}
		file.close();
		if (found_something) cout << "Total paragraph count = " << count<< endl;
		else cout << "No paragraphs found" << endl;
	}else{
		cout << "Unable to open file" << endl;
	}
}

/**
    Implements KMP algorithm for string matching.

    @param search_string is the pattern to find in text.
    @param main_string is the text.
  
*/
void KMPMainAlgo(string search_string, string main_string){
	int string_size = search_string.length();	//size of pattern.
	int N = main_string.length();				//size of text.

	int lps[string_size];						//declaring array to pass through prefix function.
	int j = 0;									//counter variable for pattern.
	computeLPSArray(search_string, string_size, lps);

	int i = 0;									//counter variable for text.

	while (i < N){
		if (search_string[j] == main_string[i])
		{
			j++;
			i++;
		}
		if (j == string_size)
		{
			cout << "Found given search string at index " << (i - j) << endl;
			j = lps[j-1];
		}
		else if (i < N && search_string[j] != main_string[i]){
			if (j != 0)
			{
				j = lps[j-1];
			}else{
				i = i + 1;
			}
		}
	}
}

bool single_kmp(string search_string, string main_string){
	int string_size = search_string.length();
	int N = main_string.length();

	int lps[string_size];
	int j = 0;

	computeLPSArray(search_string, string_size, lps);

	int i = 0;

	while (i < N){
		if (search_string[j] == main_string[i])
		{
			j++;
			i++;
		}
		if (j == string_size)
		{
			return true;
		}
		else if (i < N && search_string[j] != main_string[i]){
			if (j != 0)
			{
				j = lps[j-1];
			}else{
				i = i + 1;
			}
		}
	}

	return false;
}
/**
    Computes prefix array for a given pattern.

    @param search_string which is the pattern to be searched in the text.
    @param string_size which is size of pattern.
    @param  lps[] passing a array to store the prefix array.
    @implements building of prefix array.

*/

void computeLPSArray(string search_string, int string_size, int lps[]){
	int len = 0; //counter to be placed at the start of the pattern.
	int i;      //counter to be placed at position '1' of index.


	lps[0] = 0;
	i = 1;

	while (i < string_size){
		if (search_string[i] == search_string[len])
		{
			len++;
			lps[i] = len;
			i++;
		}else{
			if (len != 0)
			{
				len = lps[len - 1]; // checks whether prefix and suffix are same and we can bypass characters.
			}
			else{
				lps[i] = 0;		     
				i++;
				}
		}
	}
}