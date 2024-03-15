#pragma once

#include <string>

// Name: 
//		playMySong
// Input:
//		1. An unsigned integer that indicates song speed by beats per minute
// Output: 
//		None
// Side effects: 
//		Uses sound library to play music
// Summary:
//		Uses the sound library to play a song at whatever speed in BPM
void playMySong(unsigned int inBpm);

// Name: 
//		convertToMorse
// Input:
//		1. A string with text to convert to Morse code
// Output: 
//		A string with "." and "_" that is the Morse version of input
// Side effects: 
//		None
// Summary:
//		Converts the input to Morse code
//		Doesn't encode numbers, symbols. Just text and spacebar
std::string convertToMorse(const std::string& text);

// Name: 
//		playMorse
// Input:
//		1. A string with ".", "_", and " " of Morse code
// Output: 
//		The string returned from playSound from the sound library
// Side effects: 
//		Uses system to play audio Morse code
// Summary:
//		Plays inputted morse code
std::string playMorse(const std::string& morseString);
