#include "sound.h"
#include "soundLib.h"

#include <cstring>

void playMySong(unsigned int inBpm)
{
    initSound(); // Initiates sound system

    setBPM(inBpm);

    // Playing TNT by ACDC
    addE3(1);
    addE3(1);
    addE3(1);
    addE3(1);
    addE3(1);
    addE3(1);
    addE3(1);
    addE3(1);
    addE4(1);
    addG4(1);
    addA4(1);
    addA4(1);
    addA4(1);
    addA4(1);
    addB4(1);
    addE4(1);
    addRest(1);
    addE4(1);
    addD4(1);
    addE4(1);
    addE4(1);
    addE4(1);
    addE4(1);
    addG4(1);
    addA4(1);
    addG4(1);
    addA4(1);
    addA4(1);
    addB4(1);
    addG4(1);
    addE4(2);
    addE4(1);
    addE4(1);

    playSound(); // Plays the song
}

std::string convertToMorse(const std::string& text)
{
     // String array for Morse alphabet
    std::string morseAlphabet[26] = {
        "._",   // A or a
        "_...", // B or b
        "_._.", // C or c
        "_..",  // D or d
        ".",    // E or e
        ".._.", // F or f
        "__.",  // G or g
        "....", // H or h
        "..",   // I or i
        ".___", // J or j
        "_._",  // K or k
        "._..", // L or l
        "__",   // M or m
        "_.",   // N or n
        "___",  // O or o
        ".__.", // P or p
        "__._", // Q or q
        "._.",  // R or r
        "...",  // S or s
        "_",    // T or t
        ".._",  // U or u
        "..._", // V or v
        ".__",  // W or w
        "_.._", // X or x
        "_.__", // Y or y
        "__.."  // Z or z
    };

    std::string morseOutput = "";

    for (int i = 0; i < text.length(); i++) {
        char textOutput = text[i];
        
        // Converts lowercase to Morse code and adds a space after the digit
        if (textOutput >= 'a' && textOutput <= 'z')
        {
            morseOutput += morseAlphabet[textOutput - 'a'] + " ";
        }
        // Converts uppercase to Morse code and adds a space after the digit
        else if (textOutput >= 'A' && textOutput <= 'Z')
        {
            morseOutput += morseAlphabet[textOutput - 'A'] + " ";
        }
        // Adds double spacing for every single spacing input (word separation in Morse code)
        else if (textOutput == ' ')
        {
            morseOutput += "  ";
        }
    }

    return morseOutput;
}

std::string playMorse(const std::string& morseString)
{ 
    initSound(); // Initiates sound system

    for (int i = 0; i < morseString.length(); i++) {
        char morseTextOutput = morseString[i];

        if (morseTextOutput == '.') {
            addMorseDot();
        } else if (morseTextOutput == '_') {
            addMorseDash();
        } else if (morseTextOutput == ' ') {
            addMorsePause();
        }
    }
    playSound(); // Plays the Morse code
    
	return morseString;
}