// Copyright ©2023 Nathan Greenfield. All rights reserved

#include <iostream>
#include <string>

#include "sound.h"

int main()
{
	std::string userChoice = "0";

	// Do-while loop for user input
	do
	{
		// Menu of options
		std::cout << "Select an option:" << std::endl;
		std::cout << "\t0. Quit" << std::endl;
		std::cout << "\t1. Play a song" << std::endl;
		std::cout << "\t2. Convert to morse code" << std::endl;
		std::cout << "> ";

		std::getline(std::cin, userChoice); // Get user input

		if (userChoice == "0") // If user chooses '0', the program will quit
		{
			std::cout << "Quitting!" << std::endl;
			break;
		}
		else if (userChoice == "1") // If user chooses '1', user will be requested to provide a BPM, and a new window will open to play the song
		{
			std::cout << "Enter BPM: ";
			std::string userBpm;
			std::getline(std::cin, userBpm); // Get user BPM input
			int userBpmInt = std::stoi(userBpm);

			std::cout << "Playing TNT by AC/DC" << std::endl;
			playMySong(userBpmInt);

			std::cout << "Done!" << std::endl; // After playing the song, the program will return to the menu of options 
		}
		else if (userChoice == "2") // If user chooses '2', user will be asked to input a message that can be translated and then played
		{
			std::cout << "Input a message to translate into Morse code: ";
			std::string line;
			std::getline(std::cin, line); // Get user message input

			std::string morseOutput = convertToMorse(line); // Conversion of letters to Morse code
			std::cout << "Your message translated into Morse code is: " << morseOutput << std::endl; // Will display the translated version

			std::cout << "Would you like to hear the Morse code message (Y/N)? ";
			std::string morseChoice;
			std::getline(std::cin, morseChoice);

			if (morseChoice == "Y" || morseChoice == "y") // Any other input other than 'Y' or 'y' will make the program to return to the menu of options
			{
				playMorse(morseOutput);
			}
		}

	} while (userChoice != "0"); // Will keep looping until user chooses '0' to quit the program

	return 0;
}