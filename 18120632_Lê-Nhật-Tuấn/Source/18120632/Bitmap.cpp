#include "Bitmap.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <Windows.h>

#pragma warning(disable: 4996)

bool isBMPFile(const Bitmap& bmp)
{
	return (bmp.bitmapHeader.signature[0] == 'B' && bmp.bitmapHeader.signature[1] == 'M');
}

void readBMFHeader(FILE* f, Bitmap& bmp)
{
	fseek(f, 0, SEEK_SET);
	fread(&bmp.bitmapHeader, sizeof(BMFHeader), 1, f);
}

void readDIBHeader(FILE* f, Bitmap& bmp)
{
	fseek(f, sizeof(BMFHeader), SEEK_SET);
	fread(&bmp.dibHeader, sizeof(DIBHeader), 1, f);
}

void readBmpPixelArray(FILE* f, Bitmap& bmp)
{
	int widthSize = bmp.dibHeader.imageWidth * (bmp.dibHeader.colorDepth / 8);
	bmp.pixelArray.paddingSize = (4 - (widthSize % 4)) % 4;
	bmp.pixelArray.lineSize = widthSize + bmp.pixelArray.paddingSize;
	bmp.pixelArray.rawByteSize = bmp.pixelArray.lineSize * bmp.dibHeader.imageHeight;
	bmp.pixelArray.rawBytes = new unsigned char[bmp.pixelArray.rawByteSize];

	fseek(f, bmp.bitmapHeader.pixelArrayAddress, SEEK_SET);
	fread(bmp.pixelArray.rawBytes, bmp.pixelArray.rawByteSize, 1, f);

	initPixels(bmp.pixelArray, bmp.dibHeader.imageWidth, bmp.dibHeader.imageHeight);
}

bool readBitmap(const char* filePath, Bitmap& bmp)
{
	FILE* f = fopen(filePath, "rb");
	if (f == nullptr)
	{
		std::cout << "\tKhong the mo duoc file!!! ";
		return false;
	}
	// read BMFHeader
	readBMFHeader(f, bmp);
	if (!isBMPFile(bmp))
	{
		std::cout << "\tDay khong phai la mot file Bitmap. Hien tai chuong trinh chua duoc cap nhat xu li cac loai file khac";
		return false;
	}
			
	//read DIBHeader
	readDIBHeader(f, bmp);
	if (bmp.dibHeader.colorDepth != 24 || bmp.dibHeader.imageHeight < 0)
	{
		std::cout << "\tKhong dung chuan file xu li";
		return false;
	}

	//Read Pixels
	readBmpPixelArray(f, bmp);
	fclose(f);

	std::cout << "\tDoc File Thanh Cong!!!" << std::endl;
	return true;
}

int saveBitmap(const char* filePath, const Bitmap& bmp)
{
	FILE* f = fopen(filePath, "wb");
	if (f == NULL)
		return 0;

	if (fwrite(&bmp.bitmapHeader, sizeof(BMFHeader), 1, f) == 0)
		return 0;

	if (fwrite(&bmp.dibHeader, sizeof(DIBHeader), 1, f) == 0)
		return 0;

	fwrite(bmp.pixelArray.rawBytes, bmp.pixelArray.rawByteSize, 1, f);
	
	fclose(f);
	return 1;
}

void printBMFHeader(const Bitmap& bmp)
{
	printf("*** BMP Header ***\n");
	printf("- File Size  : %d byte(s)\n", bmp.bitmapHeader.bitmapSize);
	printf("- Reserved   : %d\n", bmp.bitmapHeader.reserved);
	printf("- Data Offset: %d byte(s)\n", bmp.bitmapHeader.pixelArrayAddress);
}

void printDIBHeader(const Bitmap& bmp)
{
	printf("*** BMP Dib ***\n");
	printf("- DIB Size               : %d byte(s)\n", bmp.dibHeader.dibSize);
	printf("- Image Width            : %d\n", bmp.dibHeader.imageWidth);
	printf("- Image Height           : %d\n", bmp.dibHeader.imageHeight);
	printf("- Number of Color Planes : %d\n", bmp.dibHeader.colorPlaneCount);
	printf("- Pixel Size             : %d bit(s)\n", bmp.dibHeader.colorDepth);
	printf("- Compress Method        : %d\n", bmp.dibHeader.compressMethod);
	printf("- Bitmap Size            : %d byte(s)\n", bmp.dibHeader.imageSize);
	printf("- Horizontal Resolution  : %d\n", bmp.dibHeader.X_Pixel);
	printf("- Vertical Resolution    : %d\n", bmp.dibHeader.Y_Pixel);
	printf("- Number of Colors       : %d\n", bmp.dibHeader.numberOfColor);
	printf("- Number of Impt Colors  : %d\n", bmp.dibHeader.importantColor);
}

void drawBmp(const Bitmap& bmp)
{
	HWND console = GetConsoleWindow();
	HDC hdc = GetDC(console);

	for (int row = 0; row < bmp.dibHeader.imageHeight; ++row)
		for (int col = 0; col < bmp.dibHeader.imageWidth; ++col)
		{
			Color pixel = bmp.pixelArray.pixels[row][col];
			SetPixel(hdc, col, row, RGB(pixel.R, pixel.G, pixel.B));
		}

	ReleaseDC(console, hdc);
}

void DisposeBitmap(Bitmap& bmp)
{
	delete[]bmp.pixelArray.rawBytes;
	delete[]bmp.pixelArray.pixels;
}

void mySetPixel(const Bitmap& bmp, int row, int col, Color color)
{
	int offset = (bmp.dibHeader.imageHeight - 1 - row) * bmp.pixelArray.lineSize + col * 3;
	bmp.pixelArray.rawBytes[offset] = color.B;
	bmp.pixelArray.rawBytes[offset + 1] = color.G;
	bmp.pixelArray.rawBytes[offset + 2] = color.R;
}

void newImage(const Bitmap& bmp, Bitmap& tmp)
{
	tmp.bitmapHeader = bmp.bitmapHeader;
	tmp.dibHeader = bmp.dibHeader;

	tmp.pixelArray.rowCount = bmp.pixelArray.rowCount;
	tmp.pixelArray.columnCount = bmp.pixelArray.columnCount;
	tmp.pixelArray.lineSize = bmp.pixelArray.lineSize;
	tmp.pixelArray.paddingSize = bmp.pixelArray.paddingSize;
	tmp.pixelArray.rawByteSize = bmp.pixelArray.rawByteSize;
	tmp.pixelArray.rawBytes = new unsigned char[tmp.pixelArray.rawByteSize];

	for (int i = 0; i < tmp.pixelArray.rawByteSize; ++i)
		tmp.pixelArray.rawBytes[i] = 0;

	initPixels(tmp.pixelArray, tmp.dibHeader.imageWidth, tmp.dibHeader.imageHeight);
}

void copyImage(const Bitmap& bmp, Bitmap& tmp)
{
	tmp.bitmapHeader = bmp.bitmapHeader;
	tmp.dibHeader = bmp.dibHeader;

	tmp.pixelArray.rowCount = bmp.pixelArray.rowCount;
	tmp.pixelArray.columnCount = bmp.pixelArray.columnCount;
	tmp.pixelArray.lineSize = bmp.pixelArray.lineSize;
	tmp.pixelArray.paddingSize = bmp.pixelArray.paddingSize;
	tmp.pixelArray.rawByteSize = bmp.pixelArray.rawByteSize;
	tmp.pixelArray.rawBytes = new unsigned char[tmp.pixelArray.rawByteSize];

	for (int i = 0; i < tmp.pixelArray.rawByteSize; ++i)
		tmp.pixelArray.rawBytes[i] = bmp.pixelArray.rawBytes[i];

	initPixels(tmp.pixelArray, tmp.dibHeader.imageWidth, tmp.dibHeader.imageHeight);
}

void initPixels(PixelArray& pa, int width, int height)
{
	pa.rowCount = height;
	pa.columnCount = width;

	pa.pixels = new Color*[pa.rowCount];
	for (int i = 0; i < pa.rowCount; i++)
		pa.pixels[pa.rowCount - 1 - i] = (Color*)(pa.rawBytes + pa.lineSize * i);
}