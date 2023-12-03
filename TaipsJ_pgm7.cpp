// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Program: The purpose of this program is to play a game called Snowman, which is similar to hangman.
// Process: The program does this, by reading words from an input file, randomly choosing one, then reading inputs from the user as they attempt to guess what letters are in the word. Each wrong guess, the snowman gets more complete. Once completed (after 8 incorrect guesses) the user loses. If the user manages to guess all of the lettersr, then they win.
//
// Class: CS2010
// Section: 1001
// Term: Fall 2023
// Author: Jeffrey Taips
// Reflection: Overall, this program was a challenge, as it was a long, intricate process. The hardest part was creating the snowman itself, as it required the use of unicode/ascii codes, which I did not have prior knowledge about.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Description: Load the dictionary of words from the data file into an array
// Parameters: string dictionary array
//
int loadDictionary(string dict[]) {
	ifstream inFile;
	int count = 0;

	inFile.open("pgm7.txt");

	if (!inFile.is_open()) {
		cout << "Error opening input file" << endl;
		exit(EXIT_FAILURE);
	}
	while (count < 100 && inFile >> dict[count]) {
		++count;
	}
	inFile.close();
	return count;
}
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Description: Bubble sort algorithm is used to sort the array, no other
// functions should be called from this sorting function.
// parameters: string array of words
// int number of elements in the array in descending order
//
void bubbleSort(string dict[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (dict[j] < dict[j + 1]) {
				swap(dict[j], dict[j + 1]);
			}
		}
	}
}
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Description: Randomly select an index to the dictionary array (number
// between 0 and the number of words-1. Load the
// char array representing the secret word with letters of the
// selected randomly secret word.
// Parameters: char array that will hold the secret word
// string array that holds the dictionary
// int how many words are in the dictionary
//
int setSecretWord(char secret[], string dict[], int wordCount) {
	int index;
	string randomWord;
	int length;

	srand(static_cast<unsigned>(time(0)));
	index = rand() % wordCount;
	randomWord = dict[index];
	length = randomWord.length();

	for (int i = 0; i < length; ++i) {
		secret[i] = randomWord[i];
	}

	return length;
}
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Description: Initialize each element of the char array of guessed letters
// Parameters: char array that will contain guessed letters in their correct
// positions within the secret word.
// int length of the secret word.
//
void initGuess(char guesses[], int secretlen) {
	for (int i = 0; i < secretlen; ++i) {
		guesses[i] = '\0';
	}
}
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Description: Draw a snowman figure. The number of body parts shown
// corresponds to the current wrong turn. Wrong turn 1 -> hat,
// 2 -> head, etc.
// Parameters: Current wrong turn (1 -> 8)
//
void drawSnowman(int turn) {
	switch (turn) {
	case 1:
		cout << "     " << "\u250c\u2500\u2500\u2500\u2510" << "     " << endl;
		cout << "     " << "\u2503" << "   " << "\u2503" << "     " << endl;
		cout << "    " << "\u2500\u253f\u2500\u2500\u2500\u253f\u2500" << "    " << endl;
		break;
	case 2:
		cout << "     " << "\u250c\u2500\u2500\u2500\u2510" << "     " << endl;
		cout << "     " << "\u2503" << "   " << "\u2503" << "     " << endl;
		cout << "    " << "\u2500\u253f\u2500\u2500\u2500\u253f\u2500" << "    " << endl;
		cout << "     " << "\u2502" << "*" << " " << "*" << "\u2502" << "     " << endl;
		cout << "     " << "\u2502" << " " << "\u2502" << " " << "\u2502" << "     " << endl;
		cout << "    " << "\u250d\u253b\u2500\u2500\u2500\u253b\u2513" << "    " << endl;
		break;
	case 3:
		cout << "     " << "\u250c\u2500\u2500\u2500\u2510" << "     " << endl;
		cout << "     " << "\u2503" << "   " << "\u2503" << "     " << endl;
		cout << "    " << "\u2500\u253f\u2500\u2500\u2500\u253f\u2500" << "    " << endl;
		cout << "     " << "\u2502" << "*" << " " << "*" << "\u2502" << "     " << endl;
		cout << "     " << "\u2502" << " " << "\u2502" << " " << "\u2502" << "     " << endl;
		cout << "    " << "\u250d\u253b\u2500\u2500\u2500\u253b\u2513" << "    " << endl;
		cout << "    " << "\u2502" << "     " << "\u2502" << "    " << endl;
		cout << "    " << "\u2502" << "  " << "@" << "  " << "\u2502" << "    " << endl;
		cout << "    " << "\u2502" << "     " << "\u2502" << "    " << endl;
		cout << "   " << "\u250d\u253b\u2500\u2500\u2500\u2500\u2500\u253b\u2513" << "   " << endl;
		break;
	case 4:
		cout << "     " << "\u250c\u2500\u2500\u2500\u2510" << "     " << endl;
		cout << "     " << "\u2503" << "   " << "\u2503" << "     " << endl;
		cout << "    " << "\u2500\u253f\u2500\u2500\u2500\u253f\u2500" << "    " << endl;
		cout << "     " << "\u2502" << "*" << " " << "*" << "\u2502" << "     " << endl;
		cout << "     " << "\u2502" << " " << "\u2502" << " " << "\u2502" << "     " << endl;
		cout << "    " << "\u250d\u253b\u2500\u2500\u2500\u253b\u2513" << "    " << endl;
		cout << "   " << "/" << "\u2502" << "     " << "\u2502" << "    " << endl;
		cout << "  " << "/" << " " << "\u2502" << "  " << "@" << "  " << "\u2502" << "    " << endl;
		cout << " " << "/" << "  " << "\u2502" << "     " << "\u2502" << "    " << endl;
		cout << "   " << "\u250d\u253b\u2500\u2500\u2500\u2500\u2500\u253b\u2513" << "   " << endl;
		break;
	case 5:
		cout << "     " << "\u250c\u2500\u2500\u2500\u2510" << "     " << endl;
		cout << "     " << "\u2503" << "   " << "\u2503" << "     " << endl;
		cout << "    " << "\u2500\u253f\u2500\u2500\u2500\u253f\u2500" << "    " << endl;
		cout << "     " << "\u2502" << "*" << " " << "*" << "\u2502" << "     " << endl;
		cout << "     " << "\u2502" << " " << "\u2502" << " " << "\u2502" << "     " << endl;
		cout << "    " << "\u250d\u253b\u2500\u2500\u2500\u253b\u2513" << "    " << endl;
		cout << "   " << "/" << "\u2502" << "     " << "\u2502" << "\\" << "   " << endl;
		cout << "  " << "/" << " " << "\u2502" << "  " << "@" << "  " << "\u2502" << " " << "\\" << "  " << endl;
		cout << " " << "/" << "  " << "\u2502" << "     " << "\u2502" << "  " << "\\" << " " << endl;
		cout << "   " << "\u250d\u253b\u2500\u2500\u2500\u2500\u2500\u253b\u2513" << "   " << endl;
		break;
	case 6:
		cout << "     " << "\u250c\u2500\u2500\u2500\u2510" << "     " << endl;
		cout << "     " << "\u2503" << "   " << "\u2503" << "     " << endl;
		cout << "    " << "\u2500\u253f\u2500\u2500\u2500\u253f\u2500" << "    " << endl;
		cout << "     " << "\u2502" << "*" << " " << "*" << "\u2502" << "     " << endl;
		cout << "     " << "\u2502" << " " << "\u2502" << " " << "\u2502" << "     " << endl;
		cout << "    " << "\u250d\u253b\u2500\u2500\u2500\u253b\u2513" << "    " << endl;
		cout << "   " << "/" << "\u2502" << "     " << "\u2502" << "\\" << "   " << endl;
		cout << "  " << "/" << " " << "\u2502" << "  " << "@" << "  " << "\u2502" << " " << "\\" << "  " << endl;
		cout << " " << "/" << "  " << "\u2502" << "     " << "\u2502" << "  " << "\\" << " " << endl;
		cout << "   " << "\u250d\u253b\u2500\u2500\u2500\u2500\u2500\u253b\u2513" << "   " << endl;
		cout << "   " << "\u2502" << "       " << "\u2502" << "   " << endl;
		cout << "   " << "\u2502" << "   " << "@" << "   " << "\u2502" << "   " << endl;
		cout << "   " << "\u2502" << "       " << "\u2502" << "   " << endl;
		cout << "   " << "\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2514" << "   " << endl;
		break;
	case 7:
		cout << "     " << "\u250c\u2500\u2500\u2500\u2510" << "     " << endl;
		cout << "     " << "\u2503" << "   " << "\u2503" << "     " << endl;
		cout << "    " << "\u2500\u253f\u2500\u2500\u2500\u253f\u2500" << "    " << endl;
		cout << "     " << "\u2502" << "*" << " " << "*" << "\u2502" << "     " << endl;
		cout << "     " << "\u2502" << " " << "\u2502" << " " << "\u2502" << "     " << endl;
		cout << "    " << "\u250d\u253b\u2500\u2500\u2500\u253b\u2513" << "    " << endl;
		cout << "   " << "/" << "\u2502" << "     " << "\u2502" << "\\" << "   " << endl;
		cout << "  " << "/" << " " << "\u2502" << "  " << "@" << "  " << "\u2502" << " " << "\\" << "  " << endl;
		cout << " " << "/" << "  " << "\u2502" << "     " << "\u2502" << "  " << "\\" << " " << endl;
		cout << "   " << "\u250d\u253b\u2500\u2500\u2500\u2500\u2500\u253b\u2513" << "   " << endl;
		cout << "   " << "\u2502" << "       " << "\u2502" << "   " << endl;
		cout << "   " << "\u2502" << "   " << "@" << "   " << "\u2502" << "   " << endl;
		cout << "   " << "\u2502" << "       " << "\u2502" << "   " << endl;
		cout << "   " << "\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2514" << "   " << endl;
		cout << "     " << "\u2551" << "   " << " " << "     " << endl;
		cout << "     " << "\u255d" << "   " << " " << "     " << endl;
		break;
	case 8:
		cout << "     " << "\u250c\u2500\u2500\u2500\u2510" << "     " << endl;
		cout << "     " << "\u2503" << "   " << "\u2503" << "     " << endl;
		cout << "    " << "\u2500\u253f\u2500\u2500\u2500\u253f\u2500" << "    " << endl;
		cout << "     " << "\u2502" << "*" << " " << "*" << "\u2502" << "     " << endl;
		cout << "     " << "\u2502" << " " << "\u2502" << " " << "\u2502" << "     " << endl;
		cout << "    " << "\u250d\u253b\u2500\u2500\u2500\u253b\u2513" << "    " << endl;
		cout << "   " << "/" << "\u2502" << "     " << "\u2502" << "\\" << "   " << endl;
		cout << "  " << "/" << " " << "\u2502" << "  " << "@" << "  " << "\u2502" << " " << "\\" << "  " << endl;
		cout << " " << "/" << "  " << "\u2502" << "     " << "\u2502" << "  " << "\\" << " " << endl;
		cout << "   " << "\u250d\u253b\u2500\u2500\u2500\u2500\u2500\u253b\u2513" << "   " << endl;
		cout << "   " << "\u2502" << "       " << "\u2502" << "   " << endl;
		cout << "   " << "\u2502" << "   " << "@" << "   " << "\u2502" << "   " << endl;
		cout << "   " << "\u2502" << "       " << "\u2502" << "   " << endl;
		cout << "   " << "\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2514" << "   " << endl;
		cout << "     " << "\u2551" << "   " << "\u2551" << "     " << endl;
		cout << "     " << "\u255d" << "   " << "\u255a" << "     " << endl;
		break;
	default:
		break;
	}
}
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Description: Get next guess from the player via the console window
// Returns: The letter guessed by the player.
//
char getGuess() {
	char guess;
	cout << "Enter your guess (a single letter): " << endl;
	cin >> guess;
	guess = tolower(guess);

	while (!isalpha(guess) || (guess == '\n')) {
		cout << "Invalid input, please enter a single letter:" << endl;
		cin >> guess;
		guess = tolower(guess);
	}
	return guess;
}
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Description: Show current game status, i.e., each guessed letter is
// shown in its correct position within the secret word.
// Letters that have not been guessed yet are shown as " _ "
// to indicate missing letters.
// Parameters: Guess array of char containing currently guessed letters
// in their correct positions.
// Length of the secret word
void showStatus(char guesses[], int secretlen) {

	for (int i = 0; i < secretlen; ++i) {
		if (guesses[i] == '\0') {
			cout << " _ ";
		}
		else {
			cout << " " << guesses[i] << " ";
		}
	}
	cout << endl;
}
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Description: Place the correctly guessed letter in the array of guessed
// letters in their correct spot.
// Parameters: char array containing the secret word
// char array containing the correctly guessed letters
// the last guessed letter
// the length of the secret word
// Returns: true if correct guess, false otherwise
//
bool recordGuess(char secret[], char guesses[], char letter, char secretlen) {

	bool correctGuess = false;
	for (int i = 0; i < secretlen; ++i) {
		if (secret[i] == letter) {
			guesses[i] = letter;
			correctGuess = true;
		}
	}
	return correctGuess;
}
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Description: Do we have a winner yet?
// parameters: char array of guessed letters
// the length of the secret word
// Returns: true if the whole word is revealed, false otherwise
//
bool isWin(char guesses[], int secretlen) {
	
	for (int i = 0; i < secretlen; ++i) {
		if (guesses[i] == '\0') {
			return false;
		}
	}
	return true;
}
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Description: Reveal the secret word
// parameters: char array holding secret word
// the length of the secret word
//
void showSecret(char secret[], int secretlen) {

	for (int i = 0; i < secretlen; ++i) {
		cout << secret[i];
	}
}

int main() {

	const int MAX_WORDS = 100; // Creates a constant integer variable for the max amount of words in the file (100)
	const int MAX_LETTERS = 25; // Creates a constant integer variable for the max amount of letters in the words (25)
	string dict[MAX_WORDS]; // Creates a string array that holds the words in the file
	char quizWord[MAX_LETTERS]; // Creates a character array that will hold the secret word
	char guesses[MAX_LETTERS]; // Creates a character array that will hold the users guesses
	int wordCount; // Creates an integer variable that tracks the amount of words
	char againAnswer; // Creates a character variable that will hold the users input if they want to play again (Y/N)
	int wrongGuesses = 0; // Creates an integer variable that tracks wrong guesses, starts at 0
	int quizLength; // Creates an integer variable that tracks the length of the word
	char letter; // Creates a character variable that tracks the letter the user inputs

	wordCount = loadDictionary(dict); // Calls the loadDictionary function to get the word count
	bubbleSort(dict, wordCount); // Calls the bubbleSort function to sort the words

	do { // Starts a do while loop that runs until the user decides not to play anymore
		system("cls"); // Clears the console
		quizLength = setSecretWord(quizWord, dict, wordCount); // Calls the setSecretWord function to get the length of the quiz
		initGuess(guesses, quizLength); // Calls the initGuess function
		wrongGuesses = 0; // Sets wrong guesses to 0 (resets the counter for each game)

		do { // Starts an inner do while loop that runs while the game is being played
			drawSnowman(wrongGuesses); // Calls the drawSnowman function
			showStatus(guesses, quizLength); // Calls the show status function
			letter = getGuess(); // Sets the letter equal to what the user guesses

			if (!recordGuess(quizWord, guesses, letter, quizLength)) { // Uses an if statement that adds 1 to wrong guesses if the users input is not within the word
				++wrongGuesses;
			}
		} while (!isWin(guesses, quizLength) && wrongGuesses < 8);

		system("cls"); // Clears console
		if (isWin(guesses, quizLength)) { // Creates an if else statement, outputs the correct word and if the user won or not
			cout << "Congratulations! You guessed the word! It was: ";
			showSecret(quizWord, quizLength);
			cout << endl;
		}
		else {
			drawSnowman(wrongGuesses);
			cout << "Sorry! The correct word was: ";
			showSecret(quizWord, quizLength);
			cout << endl;
		}

		cout << "Do you want to play again? (Y/N): "; // Asks the user if they want to play again, user inputs Y or N
		cin >> againAnswer;
		if ((againAnswer != 'y') && (againAnswer != 'Y') && (againAnswer != 'n') && (againAnswer != 'N')) {
			cout << "Invalid input, please answer Y/N" << endl;
			cin >> againAnswer;
		}
	} while (againAnswer == 'Y' || againAnswer == 'y');
	cout << "Thanks for playing!" << endl; // Outputs "Thanks for playing!" when the user decides they are done, then ends the program
	return 0;
}