 #include "stdio.h" // 4 Libraries imported
 #include "stdlib.h"
 #include "string.h"
 #include <time.h>

int main() {

    srand(time(NULL));
	
	char guessWords[][16] = {
		"green",
		"yellow",
		"purple",
		"windows",
		"linux",
		"apple"
	};
	
	// Index for random word
	int randomIndex = rand() % 6; // Divides number by 6, giving remainder
	
	int numLives = 5; // User has 5 guesses
	int numCorrect = 0; // How many guesses are correct
	int oldCorrect = 0;

	int lengthOfWord = strlen(guessWords[randomIndex]); // Length of the word selected
	// Positions of the characters to tell if they have been guessed or not
	// This will be 0 or 1, 0 being not guessed, 1 being guessed
	int letterGuessed[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	int quit = 0; // Quit used to break out of the loop

	int loopIndex = 0;
	
	// User inputs go into this guess array
	// used to display which characters have already been guessed
	char guess[16];
	char letterEntered;

	// Prints out which word is being selected randomly
	// Which index is it at
	// What is the length of the word
	printf("guessWords: %s randomIndex: %d lengthOfWord: %d\n\n",
		guessWords[randomIndex],
		randomIndex,
		lengthOfWord);


	// ---------------------- GAME LOOP ---------------------------
	// Keep running while number of correct letters guessed is less than the length of the word chosen
	while (numCorrect < lengthOfWord) {

		printf("\n\nNew Turn...\nHangman Word:\n");
		for (loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
			// If letterGuessed at this index is already guessed, continue the for loop without incrementing
			if (letterGuessed[loopIndex] == 1){
				printf("%c", guessWords[randomIndex][loopIndex]);
			} else {
				printf("-");
			}
		}
		printf("\n");

		printf("Number of correct guesses so far: %d\n", numCorrect);
		printf("Enter a guess letter (Type 'quit' to leave): ");
		// Gets input, stores it into the guess array
		// 16 characters AT MOST, from the standard input (stdin)
		fgets(guess, 16, stdin);

		// Checks if user wants to leave the game/quit
		if (strncmp(guess, "quit", 4) == 0) {
			quit = 1;
			break;
		}

		letterEntered = guess[0];

		printf("Letter entered: %c\n", letterEntered);

		oldCorrect = numCorrect; // Set oldCorrect to numCorrect, to determine in the for loop if this value has changed, if not changed, lose 1 life

		for (loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
			// If letterGuessed at this index is already guessed, continue the for loop without incrementing
			if (letterGuessed[loopIndex] == 1){
				continue;
			}
			if (letterEntered == guessWords[randomIndex][loopIndex]) { // If letterEntered is the same as the letter at the current index
			                                                           // set that index to 1 and increment numCorrect
				letterGuessed[loopIndex] = 1;
				numCorrect++;
			}
		}

		// oldCorrect remained the same, so user lost 1 life
		if (oldCorrect == numCorrect){
			numLives--;
			printf("WRONG GUESS, YOU HAVE LOST 1 OF YOUR LIVES\n");
			if (numLives == 0){ // No more lives, so break out of while loop and end game
				break;
			}
		} else {
			printf("Correct guess!!!\n");
		}
	}

	// If user wanted to quit, output this msg
	if(quit == 1) {
		printf("\nYou have quit early!!! \n");
	} else if (numLives == 0){ // If user lost all their lives, output this
		printf("\nYOU LOSE! The word was: %s\n",
		guessWords[randomIndex]);
	} else { // User has won the game, output this
		printf("\nYOU WON!\n");
		printf("\nThe word was: %s\n",
		guessWords[randomIndex]);
	}
	return 0; // Return 0, to exit main method
}