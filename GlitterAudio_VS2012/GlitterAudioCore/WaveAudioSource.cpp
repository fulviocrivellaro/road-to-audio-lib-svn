#include "WaveAudioSource.h"
#include <iostream>

WaveAudioSource::WaveAudioSource(void)
{
}


WaveAudioSource::~WaveAudioSource(void)
{
}

void WaveAudioSource::fillChunk(double* buffer, unsigned int channel, unsigned int chunkSize)
{

}

void WaveAudioSource::setFile(const std::string path)
{
	pFile = fopen(path.c_str(), "r");
	if (pFile == NULL)
	{
		std::cout << "Error opening file: " << path << std::endl;
	} else {
		char id[5];
		id[4] = '\0';
		fread(id, sizeof(char), 4, pFile); //read in bytes
		if (strcmp(id, "RIFF"))
		{
			std::cout << "Error opening file: not a WAVE file" << std::endl;
		} else {
			fread(&mFileSize, sizeof(int), 1, pFile);
			std::cout << "Available bytes: " << mFileSize << std::endl;
			fread(id, sizeof(char), 4, pFile); //read in bytes
			if (strcmp(id, "WAVE"))
			{
				std::cout << "Error opening file: not a WAVE file" << std::endl;
			} else {
				int size;
				fread(id, sizeof(char), 4, pFile); //read in bytes
				while (strcmp(id, "fmt "))
				{
					fread(&size, sizeof(int), 1, pFile);
					std::cout << "Found header: " << id << " of declared size: " << size << " - skip." << std::endl;
					fseek(pFile, size, SEEK_CUR);
					fread(id, sizeof(char), 4, pFile); //read in bytes
				}
				if (strcmp(id, "fmt "))
				{
					std::cout << "Error opening file: ""fmt "" header not found." << std::endl;
				} else {
					int fmtChunkSize;
					short format;
					fread(&fmtChunkSize, sizeof(int), 1, pFile); // should always be 16
					fread(&format, sizeof(short), 1, pFile); // should always be 1 (PCM)
					if (format != 1)
					{
						std::cout << "Error opening file: PCM wave file supported only." << std::endl;
					} else {
						int byteRate;
						short blockAlign;
						fread(&mNumChannels, sizeof(short), 1, pFile);
						fread(&mSampleRate, sizeof(int), 1, pFile);
						fread(&byteRate, sizeof(int), 1, pFile);
						fread(&blockAlign, sizeof(short), 1, pFile);
						fread(&mBitsPerSample, sizeof(short), 1, pFile);

						// print stats
						std::cout << std::endl << "WAVE FILE SUCCESSFULLY OPENED - Stats:" << std::endl;
						std::cout << "           Size: " << mFileSize << std::endl;
						std::cout << "    Sample Rate: " << mSampleRate << std::endl;
						std::cout << "       Channels: " << mNumChannels << std::endl;
						std::cout << "Bits Per Sample: " << mBitsPerSample << std::endl;
						std::cout << "      Byte Rate: " << byteRate << std::endl << std::endl;

						// set up conversion constants
						mSignPreservationVerifier = 0x80 << (mBitsPerSample - 8);
						mSignPreservationMask = ~(0xFFFFFFFF >> (32 - mBitsPerSample));
						mNormalizationFactor = 1.0 / ~(0xFFFFFF80 << (mBitsPerSample - 8));
						/*
						int n = 1024;
						double** buf = new double*[2];
						buf[0] = new double[1024];
						buf[1] = new double[1024];
						this->readNextChunk(buf, 1024);

						std::cout << "\nDUMP\n\n";
						for (unsigned int c=0; c<mNumChannels; c++)
						{
							std::cout << "Chan1\n";
							for (unsigned int i=0; i<n; i++)
							{
								std::cout << (i+1) << ": " << buf[c][i] << "\n";
							}
						}
						delete buf[0];
						delete buf[1];
						delete[] buf;
						*/
						return;
					}
				}
			}
		}
		fclose(pFile);
		pFile = NULL;
	}
}

int WaveAudioSource::readNextChunk(double** buffer, unsigned int chunkLength)
{
	if (pFile != NULL)
	{
		char id[5];
		id[4] = '\0';
		int fileSeek = fread(id, sizeof(char), 4, pFile);
		while (fileSeek != 0 && strcmp(id, "data"))
		{
			int size;
			fread(&size, sizeof(int), 1, pFile);
			std::cout << "Found header: " << id << " of declared size: " << size << " - skip." << std::endl;
			fseek(pFile, size, SEEK_CUR);
			fileSeek = fread(id, sizeof(char), 4, pFile); //read in bytes
		}
		if (fileSeek == 0)
		{
			std::cout << "No more data chunks available." << std::endl;
		} else {
			int availableBytes;
			fread(&availableBytes, sizeof(int), 1, pFile);
			std::cout << "Chunk size in bytes is: " << availableBytes << std::endl;
			int bytesPerSample = mBitsPerSample / 8;
			int availableSamples = availableBytes / mNumChannels / bytesPerSample;
			std::cout << "Available samples are: " << availableSamples << std::endl;
			
			if (availableSamples < chunkLength)
			{
				chunkLength = availableSamples;
			}

			int toBeReadBytes = chunkLength * bytesPerSample * mNumChannels;
			char* bytes = (char*)malloc(toBeReadBytes * sizeof(char));
			int actuallyReadBytes;
			std::cout << "Byte size is " << sizeof(char) << "\n";
			fread(bytes, sizeof(char), toBeReadBytes, pFile);

			int p = 0;
			for (unsigned int c=0; c<mNumChannels; c++)
			{
				for (unsigned int i=0; i<chunkLength; i++)
				{
					int bitSample = 0;
					double sample;
					for (unsigned int b=0; b<mBitsPerSample; b+=8)
					{
						bitSample |= (bytes[p++] << b);
					}
					if (bitSample & mSignPreservationVerifier)
					{
						bitSample |= mSignPreservationMask;
					}
					buffer[c][i] = bitSample * mNormalizationFactor;
				}
			}

			free(bytes);

			return chunkLength;
		}
	}

	return 0;
}