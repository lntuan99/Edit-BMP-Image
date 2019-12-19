#ifndef _BITMAP_H_
#define _BITMAP_H_
#include <cstdint>
#include <cstdio>
#pragma pack(1)

struct BMFHeader
{
	unsigned char signature[2];
	uint32_t bitmapSize;
	uint32_t reserved;
	uint32_t pixelArrayAddress;
};

struct DIBHeader
{
	uint32_t dibSize;
	uint32_t imageWidth;
	uint32_t imageHeight;
	uint16_t colorPlaneCount;
	uint16_t colorDepth;
	uint32_t compressMethod;
	uint32_t imageSize;
	uint32_t X_Pixel;
	uint32_t Y_Pixel;
	uint32_t numberOfColor;
	uint32_t importantColor;
};

struct Color
{
	unsigned char B, G, R; //Red - Green - Blue
};

struct colorHSI
{
	short int H, S, I; 
};

struct PixelHSI
{
	short int* rawBytes;
	int rawByteSize;
	int lineSize;
	char paddingSize;

	colorHSI** pixels;
	uint32_t rowCount;
	uint32_t columnCount;
};

struct PixelArray
{
	unsigned char* rawBytes;
	int rawByteSize;
	int lineSize;
	char paddingSize;

	Color** pixels;
	uint32_t rowCount;
	uint32_t columnCount;
};

struct Bitmap
{
	BMFHeader bitmapHeader;
	DIBHeader dibHeader;
	PixelArray pixelArray;
	PixelHSI pixelHSI;
};

//Doc File ban dau
bool isBMPFile(const Bitmap& bmp);
void readBMFHeader(FILE* f, Bitmap& bmp);
void readDIBHeader(FILE* f, Bitmap& bmp);
void readBmpPixelArray(FILE* f, Bitmap& bmp);
void initPixels(PixelArray& pa, int width, int height);
bool readBitmap(const char* filePath, Bitmap& bmp);
int saveBitmap(const char* filePath, const Bitmap& bmp);

//Xuat thong tin File
void printBMFHeader(const Bitmap& bmp);
void printDIBHeader(const Bitmap& bmp);

void mySetPixel(const Bitmap& bmp, int row, int col, Color color);

//Ve hinh ra console
void drawBmp(const Bitmap& bmp);

//Tao File ket qua moi
void newImage(const Bitmap& bmp, Bitmap& tmp);

//Copy File cu
void copyImage(const Bitmap& bmp, Bitmap& tmp);

void DisposeBitmap(Bitmap& bmp);

#endif // !_BITMAP_H
