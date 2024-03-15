// CS 52 Sound Header
// Copyright (c) 2023 Nathan Greenfield. All rights reserved
// WAV file code from Douglas Thain
// http://www3.nd.edu/~dthain/courses/cse20211/fall2013/wavfile/

#pragma once

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <string>

const int WAVFILE_SAMPLES_PER_SECOND = 44100;
const int VOLUME = 20000;
const int FREQUENCY = 900;
const double PI = 3.14159265358979323846;

static std::string morseMessage;

// Struct representing WAV header
struct wavfile_header
{
	char	riff_tag[4];
	int	riff_length;
	char	wave_tag[4];
	char	fmt_tag[4];
	int	fmt_length;
	short	audio_format;
	short	num_channels;
	int	sample_rate;
	int	byte_rate;
	short	block_align;
	short	bits_per_sample;
	char	data_tag[4];
	int	data_length;
};

// Output File
static FILE* gOutputFile = nullptr;

// Waveform data for short/long waveforms, and pause waveforms
static short gShortWave[WAVFILE_SAMPLES_PER_SECOND / 10];
static short gLongWave[WAVFILE_SAMPLES_PER_SECOND / 4];
static short gPause[WAVFILE_SAMPLES_PER_SECOND / 8];

// For musical notes
// I'm assuming we won't go over 5 second notes!
static short gNoteBuffer[WAVFILE_SAMPLES_PER_SECOND * 5];
static int gBeatsPerMin = 100;

void initSound()
{
	struct wavfile_header header;

	int samples_per_second = WAVFILE_SAMPLES_PER_SECOND;
	int bits_per_sample = 16;

	strncpy(header.riff_tag, "RIFF", 4);
	strncpy(header.wave_tag, "WAVE", 4);
	strncpy(header.fmt_tag, "fmt ", 4);
	strncpy(header.data_tag, "data", 4);

	header.riff_length = 0;
	header.fmt_length = 16;
	header.audio_format = 1;
	header.num_channels = 1;
	header.sample_rate = samples_per_second;
	header.byte_rate = samples_per_second*(bits_per_sample / 8);
	header.block_align = bits_per_sample / 8;
	header.bits_per_sample = bits_per_sample;
	header.data_length = 0;

	gOutputFile = fopen("out.wav", "w+b");

	fwrite(&header, sizeof(header), 1, gOutputFile);

	fflush(gOutputFile);

	// Initialize waveform data
	for (int i = 0; i < sizeof(gShortWave) / 2; i++)
	{
		double t = (double)i / WAVFILE_SAMPLES_PER_SECOND;

		gShortWave[i] = static_cast<short>(VOLUME*sin(FREQUENCY*t * 2 * PI));
	}

	for (int i = 0; i < sizeof(gLongWave) / 2; i++)
	{
		double t = (double)i / WAVFILE_SAMPLES_PER_SECOND;

		gLongWave[i] = static_cast<short>(VOLUME*sin(FREQUENCY*t * 2 * PI));
	}

	for (int i = 0; i < sizeof(gPause) / 2; i++)
	{
		gPause[i] = 0;
	}
}

void writeData(short data[], size_t length)
{
	fwrite(data, sizeof(short), length, gOutputFile);
}

void addMorseDot()
{
	writeData(gShortWave, sizeof(gShortWave) / 2);
	writeData(gPause, sizeof(gPause) / 2);
	morseMessage += ".";
}

void addMorseDash()
{
	writeData(gLongWave, sizeof(gLongWave) / 2);
	writeData(gPause, sizeof(gPause) / 2);
	morseMessage += "_";
}

void addMorsePause()
{
	writeData(gPause, sizeof(gPause) / 2);
	writeData(gPause, sizeof(gPause) / 2);
	morseMessage += " ";
}

std::string getMorseOutput()
{
	return morseMessage;
}

void setBPM(int bpm)
{
	gBeatsPerMin = bpm;
}

void addNote(double freq, double beats)
{
	int numSamples = static_cast<int>(beats / gBeatsPerMin * 60.0 * WAVFILE_SAMPLES_PER_SECOND);

	double theta = freq * 2 * PI;
	for (int i = 0; i < numSamples; i++)
	{
		double t = (double)i / WAVFILE_SAMPLES_PER_SECOND;

		gNoteBuffer[i] = static_cast<short>(VOLUME*sin(theta * t));
	}

	writeData(gNoteBuffer, numSamples);

	// Add a 1/10th of a quarter note pause
	numSamples = static_cast<int>(0.1 / gBeatsPerMin * 60.0 * WAVFILE_SAMPLES_PER_SECOND);
	for (int i = 0; i < numSamples; i++)
	{
		gNoteBuffer[i] = 0;
	}
	writeData(gNoteBuffer, numSamples);
}

void addA0(double beats)
{
	addNote(27.50000364732528, beats);
}


void addA0flat(double beats)
{
	addNote(25.956547041363212, beats);
}


void addA0sharp(double beats)
{
	addNote(29.135238959087147, beats);
}


void addA1(double beats)
{
	addNote(55.00000729465056, beats);
}


void addA1flat(double beats)
{
	addNote(51.913094082726424, beats);
}


void addA1sharp(double beats)
{
	addNote(58.270477918174294, beats);
}


void addA2(double beats)
{
	addNote(110.00001458930112, beats);
}


void addA2flat(double beats)
{
	addNote(103.82618816545285, beats);
}


void addA2sharp(double beats)
{
	addNote(116.54095583634859, beats);
}


void addA3(double beats)
{
	addNote(220.00002917860223, beats);
}


void addA3flat(double beats)
{
	addNote(207.6523763309057, beats);
}


void addA3sharp(double beats)
{
	addNote(233.08191167269717, beats);
}


void addA4(double beats)
{
	addNote(440.00005835720447, beats);
}


void addA4flat(double beats)
{
	addNote(415.3047526618114, beats);
}


void addA4sharp(double beats)
{
	addNote(466.16382334539435, beats);
}


void addA5(double beats)
{
	addNote(880.0001167144089, beats);
}


void addA5flat(double beats)
{
	addNote(830.6095053236228, beats);
}


void addA5sharp(double beats)
{
	addNote(932.3276466907887, beats);
}


void addA6(double beats)
{
	addNote(1760.0002334288179, beats);
}


void addA6flat(double beats)
{
	addNote(1661.2190106472456, beats);
}


void addA6sharp(double beats)
{
	addNote(1864.6552933815774, beats);
}


void addA7(double beats)
{
	addNote(3520.0004668576357, beats);
}


void addA7flat(double beats)
{
	addNote(3322.438021294491, beats);
}


void addA7sharp(double beats)
{
	addNote(3729.310586763155, beats);
}


void addA8(double beats)
{
	addNote(7040.0009337152715, beats);
}


void addA8flat(double beats)
{
	addNote(6644.876042588982, beats);
}


void addA8sharp(double beats)
{
	addNote(7458.62117352631, beats);
}


void addB0(double beats)
{
	addNote(30.867710422491964, beats);
}


void addB0flat(double beats)
{
	addNote(29.135238959087147, beats);
}


void addB1(double beats)
{
	addNote(61.73542084498393, beats);
}


void addB1flat(double beats)
{
	addNote(58.270477918174294, beats);
}


void addB2(double beats)
{
	addNote(123.47084168996786, beats);
}


void addB2flat(double beats)
{
	addNote(116.54095583634859, beats);
}


void addB3(double beats)
{
	addNote(246.9416833799357, beats);
}


void addB3flat(double beats)
{
	addNote(233.08191167269717, beats);
}


void addB4(double beats)
{
	addNote(493.8833667598714, beats);
}


void addB4flat(double beats)
{
	addNote(466.16382334539435, beats);
}


void addB5(double beats)
{
	addNote(987.7667335197428, beats);
}


void addB5flat(double beats)
{
	addNote(932.3276466907887, beats);
}


void addB6(double beats)
{
	addNote(1975.5334670394857, beats);
}


void addB6flat(double beats)
{
	addNote(1864.6552933815774, beats);
}


void addB7(double beats)
{
	addNote(3951.0669340789714, beats);
}


void addB7flat(double beats)
{
	addNote(3729.310586763155, beats);
}


void addB8(double beats)
{
	addNote(7902.133868157943, beats);
}


void addB8flat(double beats)
{
	addNote(7458.62117352631, beats);
}


void addC0(double beats)
{
	addNote(16.3516, beats);
}


void addC0sharp(double beats)
{
	addNote(17.323916733725454, beats);
}


void addC1(double beats)
{
	addNote(32.7032, beats);
}


void addC1sharp(double beats)
{
	addNote(34.64783346745091, beats);
}


void addC2(double beats)
{
	addNote(65.4064, beats);
}


void addC2sharp(double beats)
{
	addNote(69.29566693490182, beats);
}


void addC3(double beats)
{
	addNote(130.8128, beats);
}


void addC3sharp(double beats)
{
	addNote(138.59133386980363, beats);
}


void addC4(double beats)
{
	addNote(261.6256, beats);
}


void addC4sharp(double beats)
{
	addNote(277.18266773960727, beats);
}


void addC5(double beats)
{
	addNote(523.2512, beats);
}


void addC5sharp(double beats)
{
	addNote(554.3653354792145, beats);
}


void addC6(double beats)
{
	addNote(1046.5024, beats);
}


void addC6sharp(double beats)
{
	addNote(1108.730670958429, beats);
}


void addC7(double beats)
{
	addNote(2093.0048, beats);
}


void addC7sharp(double beats)
{
	addNote(2217.461341916858, beats);
}


void addC8(double beats)
{
	addNote(4186.0096, beats);
}


void addC8sharp(double beats)
{
	addNote(4434.922683833716, beats);
}


void addD0(double beats)
{
	addNote(18.354050429135544, beats);
}


void addD0flat(double beats)
{
	addNote(17.323916733725454, beats);
}


void addD0sharp(double beats)
{
	addNote(19.445439061678496, beats);
}


void addD1(double beats)
{
	addNote(36.70810085827109, beats);
}


void addD1flat(double beats)
{
	addNote(34.64783346745091, beats);
}


void addD1sharp(double beats)
{
	addNote(38.89087812335699, beats);
}


void addD2(double beats)
{
	addNote(73.41620171654218, beats);
}


void addD2flat(double beats)
{
	addNote(69.29566693490182, beats);
}


void addD2sharp(double beats)
{
	addNote(77.78175624671398, beats);
}


void addD3(double beats)
{
	addNote(146.83240343308435, beats);
}


void addD3flat(double beats)
{
	addNote(138.59133386980363, beats);
}


void addD3sharp(double beats)
{
	addNote(155.56351249342796, beats);
}


void addD4(double beats)
{
	addNote(293.6648068661687, beats);
}


void addD4flat(double beats)
{
	addNote(277.18266773960727, beats);
}


void addD4sharp(double beats)
{
	addNote(311.12702498685593, beats);
}


void addD5(double beats)
{
	addNote(587.3296137323374, beats);
}


void addD5flat(double beats)
{
	addNote(554.3653354792145, beats);
}


void addD5sharp(double beats)
{
	addNote(622.2540499737119, beats);
}


void addD6(double beats)
{
	addNote(1174.6592274646748, beats);
}


void addD6flat(double beats)
{
	addNote(1108.730670958429, beats);
}


void addD6sharp(double beats)
{
	addNote(1244.5080999474237, beats);
}


void addD7(double beats)
{
	addNote(2349.3184549293496, beats);
}


void addD7flat(double beats)
{
	addNote(2217.461341916858, beats);
}


void addD7sharp(double beats)
{
	addNote(2489.0161998948474, beats);
}


void addD8(double beats)
{
	addNote(4698.636909858699, beats);
}


void addD8flat(double beats)
{
	addNote(4434.922683833716, beats);
}


void addD8sharp(double beats)
{
	addNote(4978.032399789695, beats);
}


void addE0(double beats)
{
	addNote(20.60172503946101, beats);
}


void addE0flat(double beats)
{
	addNote(19.445439061678496, beats);
}


void addE1(double beats)
{
	addNote(41.20345007892202, beats);
}


void addE1flat(double beats)
{
	addNote(38.89087812335699, beats);
}


void addE2(double beats)
{
	addNote(82.40690015784403, beats);
}


void addE2flat(double beats)
{
	addNote(77.78175624671398, beats);
}


void addE3(double beats)
{
	addNote(164.81380031568807, beats);
}


void addE3flat(double beats)
{
	addNote(155.56351249342796, beats);
}


void addE4(double beats)
{
	addNote(329.62760063137614, beats);
}


void addE4flat(double beats)
{
	addNote(311.12702498685593, beats);
}


void addE5(double beats)
{
	addNote(659.2552012627523, beats);
}


void addE5flat(double beats)
{
	addNote(622.2540499737119, beats);
}


void addE6(double beats)
{
	addNote(1318.5104025255046, beats);
}


void addE6flat(double beats)
{
	addNote(1244.5080999474237, beats);
}


void addE7(double beats)
{
	addNote(2637.020805051009, beats);
}


void addE7flat(double beats)
{
	addNote(2489.0161998948474, beats);
}


void addE8(double beats)
{
	addNote(5274.041610102018, beats);
}


void addE8flat(double beats)
{
	addNote(4978.032399789695, beats);
}


void addF0(double beats)
{
	addNote(21.826767359446734, beats);
}


void addF0sharp(double beats)
{
	addNote(23.124654486499903, beats);
}


void addF1(double beats)
{
	addNote(43.65353471889347, beats);
}


void addF1sharp(double beats)
{
	addNote(46.249308972999806, beats);
}


void addF2(double beats)
{
	addNote(87.30706943778694, beats);
}


void addF2sharp(double beats)
{
	addNote(92.49861794599961, beats);
}


void addF3(double beats)
{
	addNote(174.61413887557387, beats);
}


void addF3sharp(double beats)
{
	addNote(184.99723589199922, beats);
}


void addF4(double beats)
{
	addNote(349.22827775114774, beats);
}


void addF4sharp(double beats)
{
	addNote(369.99447178399845, beats);
}


void addF5(double beats)
{
	addNote(698.4565555022955, beats);
}


void addF5sharp(double beats)
{
	addNote(739.9889435679969, beats);
}


void addF6(double beats)
{
	addNote(1396.913111004591, beats);
}


void addF6sharp(double beats)
{
	addNote(1479.9778871359938, beats);
}


void addF7(double beats)
{
	addNote(2793.826222009182, beats);
}


void addF7sharp(double beats)
{
	addNote(2959.9557742719876, beats);
}


void addF8(double beats)
{
	addNote(5587.652444018364, beats);
}


void addF8sharp(double beats)
{
	addNote(5919.911548543975, beats);
}


void addG0(double beats)
{
	addNote(24.49971799825675, beats);
}


void addG0flat(double beats)
{
	addNote(23.124654486499903, beats);
}


void addG0sharp(double beats)
{
	addNote(25.956547041363212, beats);
}


void addG1(double beats)
{
	addNote(48.9994359965135, beats);
}


void addG1flat(double beats)
{
	addNote(46.249308972999806, beats);
}


void addG1sharp(double beats)
{
	addNote(51.913094082726424, beats);
}


void addG2(double beats)
{
	addNote(97.998871993027, beats);
}


void addG2flat(double beats)
{
	addNote(92.49861794599961, beats);
}


void addG2sharp(double beats)
{
	addNote(103.82618816545285, beats);
}


void addG3(double beats)
{
	addNote(195.997743986054, beats);
}


void addG3flat(double beats)
{
	addNote(184.99723589199922, beats);
}


void addG3sharp(double beats)
{
	addNote(207.6523763309057, beats);
}


void addG4(double beats)
{
	addNote(391.995487972108, beats);
}


void addG4flat(double beats)
{
	addNote(369.99447178399845, beats);
}


void addG4sharp(double beats)
{
	addNote(415.3047526618114, beats);
}


void addG5(double beats)
{
	addNote(783.990975944216, beats);
}


void addG5flat(double beats)
{
	addNote(739.9889435679969, beats);
}


void addG5sharp(double beats)
{
	addNote(830.6095053236228, beats);
}


void addG6(double beats)
{
	addNote(1567.981951888432, beats);
}


void addG6flat(double beats)
{
	addNote(1479.9778871359938, beats);
}


void addG6sharp(double beats)
{
	addNote(1661.2190106472456, beats);
}


void addG7(double beats)
{
	addNote(3135.963903776864, beats);
}


void addG7flat(double beats)
{
	addNote(2959.9557742719876, beats);
}


void addG7sharp(double beats)
{
	addNote(3322.438021294491, beats);
}


void addG8(double beats)
{
	addNote(6271.927807553728, beats);
}


void addG8flat(double beats)
{
	addNote(5919.911548543975, beats);
}


void addG8sharp(double beats)
{
	addNote(6644.876042588982, beats);
}


void addRest(double beats)
{
	addNote(0.0, beats);
}

std::string playSound()
{
	// Close the file
	int file_length = static_cast<int>(ftell(gOutputFile));

	int data_length = file_length - sizeof(struct wavfile_header);
	fseek(gOutputFile, sizeof(struct wavfile_header) - sizeof(int), SEEK_SET);
	fwrite(&data_length, sizeof(data_length), 1, gOutputFile);

	int riff_length = file_length - 8;
	fseek(gOutputFile, 4, SEEK_SET);
	fwrite(&riff_length, sizeof(riff_length), 1, gOutputFile);

	fclose(gOutputFile);

	// Play the file
#if _WIN32
	// On windows
	system("start out.wav");
#elif __APPLE__
// Mac version needs no change
	system("afplay out.wav");
#else
	// Linux version, do nothing
#endif
	return getMorseOutput();
}

