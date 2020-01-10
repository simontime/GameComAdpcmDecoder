#include <stdio.h>

static short newSample = 0, index1 = 0, index2 = 0;

static unsigned short slopeTable[64] =
{
	0x0000, 0x0100, 0x0200, 0x0400, 0x0610, 0x0810, 0x0C18, 0x1020,
	0x0100, 0x0300, 0x0508, 0x0908, 0x0D18, 0x1118, 0x1920, 0x2128,
	0x0208, 0x0508, 0x0810, 0x0E10, 0x1420, 0x1A20, 0x2628, 0x3230,
	0x0310, 0x0710, 0x0B18, 0x1318, 0x1B28, 0x2328, 0x2930, 0x4338,
	0x0418, 0x0918, 0x0E20, 0x1820, 0x2230, 0x2C30, 0x4038, 0x5438,
	0x0520, 0x0B20, 0x1128, 0x1D28, 0x2938, 0x3538, 0x4D38, 0x6F38,
	0x0628, 0x0D28, 0x1430, 0x2230, 0x3038, 0x3E38, 0x5A38, 0x7638,
	0x0730, 0x0F30, 0x1738, 0x2738, 0x3738, 0x4738, 0x6738, 0x7D38
};

unsigned char decodeSample(unsigned char nibble)
{
	unsigned char s = index2 | (nibble >> 1);
	
	index1 = slopeTable[s] >> 8;
	index2 = slopeTable[s] & 0xff;
	
	newSample += (nibble & 1) ? -index1 : index1;
	
	if (newSample < 0)
		newSample = 0;
	
	if (newSample > 0xff)
		newSample = 0xff;
	
	return newSample;
}

int main(int argc, char **argv)
{
	FILE *in, *out;
	
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
		return -1;
	}

	if ((in = fopen(argv[1], "rb")) == NULL)
	{
		perror(argv[1]);
		return -1;
	}

	if ((out = fopen(argv[2], "wb")) == NULL)
	{
		perror(argv[2]);
		return -1;
	}

	printf("Decoding %s to %s...\n", argv[1], argv[2]);

	for (;;)
	{
		int c = fgetc(in);

		if (c == EOF)
			break;
		
		fputc(decodeSample(c & 0xf), out);
		fputc(decodeSample(c >> 4), out);
	}

	puts("Done!");

	fclose(in);
	fclose(out);

	return 0;
}