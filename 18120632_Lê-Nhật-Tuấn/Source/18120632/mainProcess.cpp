#include <algorithm>
#include <iostream>
#include <string>
#include <conio.h>
#include <cmath>

#include "mainProcess.h"
#include "myUtility.h"

void getSobel(const Bitmap& origiBitmap, Bitmap& result)
{
	int lua_chon = 0;
	
	do
	{
		system("cls");
		frame();

		std::cout << "\t\t1. Sobel theo huong x" << std::endl;
		std::cout << "\t\t2. Sobel theo huong y" << std::endl;
		std::cout << "\t\t3. Sobel theo ca hai huong x va y" << std::endl;

		std::cout << "\n\t\tVui long nhap lua chon >= 1 va <= 3: ";
		std::cin >> lua_chon;
	} while (lua_chon < 1 || lua_chon > 3);

	std::vector<std::vector<char>> sobel_x_matrix = { {-1,0,1},{-2,0,2},{-1,0,1} };
	std::vector<std::vector<char>> sobel_y_matrix = { {-1,-2,-1},{0,0,0},{1,2,1} };

	Bitmap blackwhite;

	copyImage(origiBitmap, blackwhite);

	int maxRow = origiBitmap.dibHeader.imageHeight;
	int maxCol = origiBitmap.dibHeader.imageWidth;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = blackwhite.pixelArray.pixels[i][j];
			int val = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
			pixel.R = pixel.G = pixel.B = val;

			mySetPixel(blackwhite, i, j, pixel);
		}

	if (lua_chon == 1)
	{
		std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n" << std::endl;

		int **CXmatrix = newMatrix(maxRow, maxCol);
		int **Xmatrix = newMatrix(maxRow, maxCol);

		createMatrixB(CXmatrix, blackwhite);
		createMatrix0(Xmatrix, blackwhite);

		convolution(CXmatrix, Xmatrix, sobel_x_matrix, 3, maxRow, maxCol);

		ResultRGB(result, Xmatrix, 1);

		deleteMatrix(CXmatrix, maxRow);
		deleteMatrix(Xmatrix, maxRow);
	}

	else if (lua_chon == 2)
	{
		std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n" << std::endl;

		int **CYmatrix = newMatrix(maxRow, maxCol);
		int **Ymatrix = newMatrix(maxRow, maxCol);

		createMatrixB(CYmatrix, blackwhite);
		createMatrix0(Ymatrix, blackwhite);

		convolution(CYmatrix, Ymatrix, sobel_y_matrix, 3, maxRow, maxCol);

		ResultRGB(result, Ymatrix, 1);

		deleteMatrix(CYmatrix, maxRow);
		deleteMatrix(Ymatrix, maxRow);
	}

	else if (lua_chon == 3)
	{
		int T = -1;
		do
		{
			system("cls");
			frame();
			std::cout << "\tNhap vao nguong can de lay bien anh (0 - 255), Vi du 128: ";
			std::cin >> T;
		} while (T < 0 || T > 255);
		
		std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n";

		int **CXmatrix = newMatrix(maxRow, maxCol);
		int **Xmatrix = newMatrix(maxRow, maxCol);
		int **CYmatrix = newMatrix(maxRow, maxCol);
		int **Ymatrix = newMatrix(maxRow, maxCol);

		createMatrixB(CXmatrix, blackwhite);
		createMatrix0(Xmatrix, blackwhite);
		createMatrixB(CYmatrix, blackwhite);
		createMatrix0(Ymatrix, blackwhite);

		convolution(CXmatrix, Xmatrix, sobel_x_matrix, 3, maxRow, maxCol);
		convolution(CYmatrix, Ymatrix, sobel_y_matrix, 3, maxRow, maxCol);

		int **Rmatrix = newMatrix(maxRow, maxCol);
		better(Rmatrix, Xmatrix, Ymatrix, maxRow, maxCol, T);

		ResultRGB(result, Rmatrix, 1);

		deleteMatrix(CXmatrix, maxRow);
		deleteMatrix(CYmatrix, maxRow);
		deleteMatrix(Xmatrix, maxRow);
		deleteMatrix(Ymatrix, maxRow);
		deleteMatrix(Rmatrix, maxRow);
	}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void BlackWhite(const Bitmap& origiBitmap, Bitmap& result)
{
	uint32_t maxRow = origiBitmap.dibHeader.imageHeight;
	uint32_t maxCol = origiBitmap.dibHeader.imageWidth;

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = origiBitmap.pixelArray.pixels[i][j];
			int val = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
			pixel.R = pixel.G = pixel.B = val;

			mySetPixel(result, i, j, pixel);
		}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Contrast(const Bitmap& origiBitmap, Bitmap& result)
{
	double factor = 0;
	do
	{
		std::cout << "\t\tNhap vao he so tuong phan lon hon 0: ";
		std::cin >> factor;
	} while (factor <= 0);
	
	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	uint32_t maxRow = origiBitmap.dibHeader.imageHeight;
	uint32_t maxCol = origiBitmap.dibHeader.imageWidth;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = origiBitmap.pixelArray.pixels[i][j];

			pixel.R = (pixel.R * factor > 255 ? 255 : pixel.R * factor);
			pixel.G = (pixel.G * factor > 255 ? 255 : pixel.G * factor);
			pixel.B = (pixel.B * factor > 255 ? 255 : pixel.B * factor);

			mySetPixel(result, i, j, pixel);
		}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Negative(const Bitmap& origiBitmap, Bitmap& result)
{
	uint32_t maxRow = origiBitmap.dibHeader.imageHeight;
	uint32_t maxCol = origiBitmap.dibHeader.imageWidth;

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;
	
	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = origiBitmap.pixelArray.pixels[i][j];

			pixel.B = 255 - pixel.B;
			pixel.G = 255 - pixel.G;
			pixel.R = 255 - pixel.R;

			mySetPixel(result, i, j, pixel);
		}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Brightness(const Bitmap& origiBitmap, Bitmap& result)
{
	int factor = 0;
	
	std::cout << "\n\tNhap vao do sang muon thay doi (so duong de tang, so am de giam): ";
	std::cin >> factor;

	uint32_t maxRow = origiBitmap.dibHeader.imageHeight;
	uint32_t maxCol = origiBitmap.dibHeader.imageWidth;

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			double tmp;
			Color pixel = origiBitmap.pixelArray.pixels[i][j];

			tmp = (pixel.R + factor > 255 ? 255 : pixel.R + factor);
			tmp = tmp < 0 ? 0 : tmp;
			pixel.R = tmp;

			tmp = (pixel.G + factor > 255 ? 255 : pixel.G + factor);
			tmp = tmp < 0 ? 0 : tmp;
			pixel.G = tmp;

			tmp = (pixel.B + factor > 255 ? 255 : pixel.B + factor);
			tmp = tmp < 0 ? 0 : tmp;
			pixel.B = tmp;

			mySetPixel(result, i, j, pixel);
		}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Dim(const Bitmap& origiBitmap, Bitmap& result)
{
	int lua_chon = 0;
	std::cout << "\t\t1. Lam mo cap 1" << std::endl;
	std::cout << "\t\t2. Lam mo cap 2" << std::endl;
	std::cout << "\t\t3. Lam mo cap 3" << std::endl;
	std::cout << "\n\tNhap lua chon cua ban: ";
	std::cin >> lua_chon;

	while (lua_chon < 1 || lua_chon > 3)
	{
		std::cout << "\t\tVui long nhap lua chon >= 1 va <= 3: ";
		std::cin >> lua_chon;
	}

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	uint32_t maxRow = origiBitmap.dibHeader.imageHeight;
	uint32_t maxCol = origiBitmap.dibHeader.imageWidth;

	if (lua_chon == 1)
	{
		std::vector<std::vector<char>> kernel = { {1, 1, 1},
												  {1, 1, 1},
												  {1, 1, 1} };
		int **Cmatrix = newMatrix(maxRow, maxCol);
		int **Rmatrix = newMatrix(maxRow, maxCol);

		createMatrixR(Cmatrix, origiBitmap);
		createMatrix0(Rmatrix, origiBitmap);
		convolution(Cmatrix, Rmatrix, kernel, 3, maxRow, maxCol);
		ResultR(result, Rmatrix, 9);

		createMatrixG(Cmatrix, origiBitmap);
		createMatrix0(Rmatrix, origiBitmap);
		convolution(Cmatrix, Rmatrix, kernel, 3, maxRow, maxCol);
		ResultG(result, Rmatrix, 9);

		createMatrixB(Cmatrix, origiBitmap);
		createMatrix0(Rmatrix, origiBitmap);
		convolution(Cmatrix, Rmatrix, kernel, 3, maxRow, maxCol);
		ResultB(result, Rmatrix, 9);

		deleteMatrix(Cmatrix, maxRow);
		deleteMatrix(Rmatrix, maxRow);
	}

	else if (lua_chon == 2)
	{
		std::vector<std::vector<char>> kernel = { {1, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1} };

		int **Cmatrix = newMatrix(maxRow, maxCol);
		int **Rmatrix = newMatrix(maxRow, maxCol);

		createMatrixR(Cmatrix, origiBitmap);
		createMatrix0(Rmatrix, origiBitmap);
		convolution(Cmatrix, Rmatrix, kernel, 5, maxRow, maxCol);
		ResultR(result, Rmatrix, 25);

		createMatrixG(Cmatrix, origiBitmap);
		createMatrix0(Rmatrix, origiBitmap);
		convolution(Cmatrix, Rmatrix, kernel, 5, maxRow, maxCol);
		ResultG(result, Rmatrix, 25);

		createMatrixB(Cmatrix, origiBitmap);
		createMatrix0(Rmatrix, origiBitmap);
		convolution(Cmatrix, Rmatrix, kernel, 5, maxRow, maxCol);
		ResultB(result, Rmatrix, 25);

		deleteMatrix(Cmatrix, maxRow);
		deleteMatrix(Rmatrix, maxRow);
	}

	else if (lua_chon == 3)
	{
		std::vector<std::vector<char>> kernel = { {1, 1, 1, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1, 1, 1} };

		int **Cmatrix = newMatrix(maxRow, maxCol);
		int **Rmatrix = newMatrix(maxRow, maxCol);

		createMatrixR(Cmatrix, origiBitmap);
		createMatrix0(Rmatrix, origiBitmap);
		convolution(Cmatrix, Rmatrix, kernel, 7, maxRow, maxCol);
		ResultR(result, Rmatrix, 49);

		createMatrixG(Cmatrix, origiBitmap);
		createMatrix0(Rmatrix, origiBitmap);
		convolution(Cmatrix, Rmatrix, kernel, 7, maxRow, maxCol);
		ResultG(result, Rmatrix, 49);

		createMatrixB(Cmatrix, origiBitmap);
		createMatrix0(Rmatrix, origiBitmap);
		convolution(Cmatrix, Rmatrix, kernel, 7, maxRow, maxCol);
		ResultB(result, Rmatrix, 49);

		deleteMatrix(Cmatrix, maxRow);
		deleteMatrix(Rmatrix, maxRow);
	}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Blending(const Bitmap& origiBitmap1, const Bitmap& origiBitmap2, Bitmap& result)
{
	int alpha = -1;
	do
	{
		system("cls");
		frame();
		std::cout << "\tHe so cong anh se quyet dinh anh nao noi bat hon anh con lai\n";
		std::cout << "\tNhap vao he so cong anh (0 - 255), Vi du 128: ";
		std::cin >> alpha;
	} while (alpha < 0 || alpha > 255);

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n";

	uint32_t height1, width1, height2, width2;

	height1 = origiBitmap1.dibHeader.imageHeight;
	width1 = origiBitmap1.dibHeader.imageWidth;

	height2 = origiBitmap2.dibHeader.imageHeight;
	width2 = origiBitmap2.dibHeader.imageWidth;

	if (width1 < width2)
	{
		int scale = width2 / width1;

		Bitmap tmp;
		double x, y;
		uint32_t newWidth, newHeight, i, j, x1, y1, x2, y2;

		newImage(origiBitmap1, tmp);

		uint32_t width = origiBitmap1.dibHeader.imageWidth;
		uint32_t height = origiBitmap1.dibHeader.imageHeight;

		newWidth = (uint32_t)(width * scale);
		newHeight = (uint32_t)(height * scale);

		tmp.dibHeader.imageWidth = newWidth;
		tmp.dibHeader.imageHeight = newHeight;

		delete[] tmp.pixelArray.rawBytes;

		int widthSize = tmp.dibHeader.imageWidth * (tmp.dibHeader.colorDepth / 8);
		tmp.pixelArray.paddingSize = (4 - (widthSize % 4)) % 4;
		tmp.pixelArray.lineSize = widthSize + tmp.pixelArray.paddingSize;
		tmp.pixelArray.rawByteSize = tmp.pixelArray.lineSize * tmp.dibHeader.imageHeight;
		tmp.pixelArray.rawBytes = new unsigned char[tmp.pixelArray.rawByteSize];

		for (int i = 0; i < tmp.pixelArray.rawByteSize; ++i)
			tmp.pixelArray.rawBytes[i] = 0;

		initPixels(tmp.pixelArray, tmp.dibHeader.imageWidth, tmp.dibHeader.imageHeight);

		for (int i = 0; i < newHeight; i++)
			for (int j = 0; j < newWidth; j++)
			{
				x = i / scale;
				y = j / scale;
				x1 = floor(x);
				y1 = floor(y);

				if (x1 < height - 1)
					x2 = x1 + 1;
				else
					x2 = x1;

				if (y1 < width - 1)
					y2 = y1 + 1;
				else
					y2 = y1;

				Color p11 = origiBitmap1.pixelArray.pixels[x1][y1];
				Color p12 = origiBitmap1.pixelArray.pixels[x1][y2];
				Color p21 = origiBitmap1.pixelArray.pixels[x2][y1];
				Color p22 = origiBitmap1.pixelArray.pixels[x2][y2];

				tmp.pixelArray.pixels[i][j] = Bilinear(x, y, p11, p12, p21, p22);
			}

		uint32_t maxRow = std::min(origiBitmap2.dibHeader.imageHeight, tmp.dibHeader.imageHeight);
		uint32_t maxCol = std::min(origiBitmap2.dibHeader.imageWidth, tmp.dibHeader.imageWidth);

		result.dibHeader.imageWidth = maxCol;
		result.dibHeader.imageHeight = maxRow;

		delete[] result.pixelArray.rawBytes;

		widthSize = result.dibHeader.imageWidth * (result.dibHeader.colorDepth / 8);
		result.pixelArray.paddingSize = (4 - (widthSize % 4)) % 4;
		result.pixelArray.lineSize = widthSize + result.pixelArray.paddingSize;
		result.pixelArray.rawByteSize = result.pixelArray.lineSize * result.dibHeader.imageHeight;
		result.pixelArray.rawBytes = new unsigned char[result.pixelArray.rawByteSize];

		for (int i = 0; i < result.pixelArray.rawByteSize; ++i)
			result.pixelArray.rawBytes[i] = 0;

		initPixels(result.pixelArray, result.dibHeader.imageWidth, result.dibHeader.imageHeight);

		for (int i = 0; i < maxRow; ++i)
			for (int j = 0; j < maxCol; ++j)
			{
				result.pixelArray.pixels[i][j].R = blend(tmp.pixelArray.pixels[i][j].R, origiBitmap2.pixelArray.pixels[i][j].R, alpha);
				result.pixelArray.pixels[i][j].G = blend(tmp.pixelArray.pixels[i][j].G, origiBitmap2.pixelArray.pixels[i][j].G, alpha);
				result.pixelArray.pixels[i][j].B = blend(tmp.pixelArray.pixels[i][j].B, origiBitmap2.pixelArray.pixels[i][j].B, alpha);
			}
	}

	else
	{
		int scale = width1 / width2;

		Bitmap tmp;
		double x, y;
		uint32_t newWidth, newHeight, i, j, x1, y1, x2, y2;

		newImage(origiBitmap2, tmp);

		uint32_t width = origiBitmap2.dibHeader.imageWidth;
		uint32_t height = origiBitmap2.dibHeader.imageHeight;

		newWidth = (uint32_t)(width * scale);
		newHeight = (uint32_t)(height * scale);

		tmp.dibHeader.imageWidth = newWidth;
		tmp.dibHeader.imageHeight = newHeight;

		delete[] tmp.pixelArray.rawBytes;

		int widthSize = tmp.dibHeader.imageWidth * (tmp.dibHeader.colorDepth / 8);
		tmp.pixelArray.paddingSize = (4 - (widthSize % 4)) % 4;
		tmp.pixelArray.lineSize = widthSize + tmp.pixelArray.paddingSize;
		tmp.pixelArray.rawByteSize = tmp.pixelArray.lineSize * tmp.dibHeader.imageHeight;
		tmp.pixelArray.rawBytes = new unsigned char[tmp.pixelArray.rawByteSize];

		for (int i = 0; i < tmp.pixelArray.rawByteSize; ++i)
			tmp.pixelArray.rawBytes[i] = 0;

		initPixels(tmp.pixelArray, tmp.dibHeader.imageWidth, tmp.dibHeader.imageHeight);

		for (int i = 0; i < newHeight; i++)
			for (int j = 0; j < newWidth; j++)
			{
				x = i / scale;
				y = j / scale;
				x1 = floor(x);
				y1 = floor(y);

				if (x1 < height - 1)
					x2 = x1 + 1;
				else
					x2 = x1;

				if (y1 < width - 1)
					y2 = y1 + 1;
				else
					y2 = y1;

				Color p11 = origiBitmap2.pixelArray.pixels[x1][y1];
				Color p12 = origiBitmap2.pixelArray.pixels[x1][y2];
				Color p21 = origiBitmap2.pixelArray.pixels[x2][y1];
				Color p22 = origiBitmap2.pixelArray.pixels[x2][y2];

				tmp.pixelArray.pixels[i][j] = Bilinear(x, y, p11, p12, p21, p22);
			}

		uint32_t maxRow = std::min(origiBitmap1.dibHeader.imageHeight, tmp.dibHeader.imageHeight);
		uint32_t maxCol = std::min(origiBitmap1.dibHeader.imageWidth, tmp.dibHeader.imageWidth);

		result.dibHeader.imageWidth = maxCol;
		result.dibHeader.imageHeight = maxRow;

		delete[] result.pixelArray.rawBytes;

		widthSize = result.dibHeader.imageWidth * (result.dibHeader.colorDepth / 8);
		result.pixelArray.paddingSize = (4 - (widthSize % 4)) % 4;
		result.pixelArray.lineSize = widthSize + result.pixelArray.paddingSize;
		result.pixelArray.rawByteSize = result.pixelArray.lineSize * result.dibHeader.imageHeight;
		result.pixelArray.rawBytes = new unsigned char[result.pixelArray.rawByteSize];

		for (int i = 0; i < result.pixelArray.rawByteSize; ++i)
			result.pixelArray.rawBytes[i] = 0;

		initPixels(result.pixelArray, result.dibHeader.imageWidth, result.dibHeader.imageHeight);

		for (int i = 0; i < maxRow; ++i)
			for (int j = 0; j < maxCol; ++j)
			{
				result.pixelArray.pixels[i][j].R = blend(origiBitmap1.pixelArray.pixels[i][j].R, tmp.pixelArray.pixels[i][j].R, alpha);
				result.pixelArray.pixels[i][j].G = blend(origiBitmap1.pixelArray.pixels[i][j].G, tmp.pixelArray.pixels[i][j].G, alpha);
				result.pixelArray.pixels[i][j].B = blend(origiBitmap1.pixelArray.pixels[i][j].B, tmp.pixelArray.pixels[i][j].B, alpha);
			}
	}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}
	
unsigned char blend(const unsigned char& A, const unsigned char& B, const int& alpha)
{
	return ((A * alpha + B * (255 - alpha) + 127) / 255);
}

void Scaling(const Bitmap& origiBitmap, Bitmap& result)
{
	double scale = 0;

	do
	{
		std::cout << "\tNhap vao he so ti le thay doi kich thuoc anh (lon hon 0): ";
		std::cin >> scale;
	} while (scale <= 0);
	
	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	uint32_t newWidth, newHeight, i, j, x1, y1, x2, y2;
	double x, y;

	uint32_t width = origiBitmap.dibHeader.imageWidth;
	uint32_t height = origiBitmap.dibHeader.imageHeight;

	newWidth = (uint32_t)(width * scale);
	newHeight = (uint32_t)(height * scale);

	result.dibHeader.imageWidth = newWidth;
	result.dibHeader.imageHeight = newHeight;
	
	delete[] result.pixelArray.rawBytes;

	int widthSize = result.dibHeader.imageWidth * (result.dibHeader.colorDepth / 8);
	result.pixelArray.paddingSize = (4 - (widthSize % 4)) % 4;
	result.pixelArray.lineSize = widthSize + result.pixelArray.paddingSize;
	result.pixelArray.rawByteSize = result.pixelArray.lineSize * result.dibHeader.imageHeight;
	result.pixelArray.rawBytes = new unsigned char[result.pixelArray.rawByteSize];

	for (int i = 0; i < result.pixelArray.rawByteSize; ++i)
		result.pixelArray.rawBytes[i] = 0;

	initPixels(result.pixelArray, result.dibHeader.imageWidth, result.dibHeader.imageHeight);

	for(i = 0; i < newHeight; i++)
		for(j = 0; j < newWidth; j++) 
		{
			x = i / scale;
			y = j / scale;
			x1 = floor(x);
			y1 = floor(y);

			if (x1 < height - 1)
				x2 = x1 + 1;
			else
				x2 = x1;

			if (y1 < width - 1)
				y2 = y1 + 1;
			else
				y2 = y1;
			
			Color p11 = origiBitmap.pixelArray.pixels[x1][y1];
			Color p12 = origiBitmap.pixelArray.pixels[x1][y2];
			Color p21 = origiBitmap.pixelArray.pixels[x2][y1];
			Color p22 = origiBitmap.pixelArray.pixels[x2][y2];

			result.pixelArray.pixels[i][j] = Bilinear(x, y, p11, p12, p21, p22);
		}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Rotating(const Bitmap& origiBitmap, Bitmap& result)
{
	uint32_t width, height; 
	width = origiBitmap.dibHeader.imageWidth;
	height = origiBitmap.dibHeader.imageHeight;

	double angle = 0;
	
	do 
	{
		std::cout << "\tNhap vao goc quay anh lon hon 0 (don vi do - vi du: 90): ";
		std::cin >> angle;
	} while (angle <= 0);

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;
	
	int centerx, centery, centerx1, centery1, xi, yi, x1, y1, x2, y2, x3, y3, x4, y4, Max, Min;
	uint32_t newWidth, newHeight; 

	double sine, cosine, x, y;

	centerx = width / 2;
	centery = height / 2;

	while (angle > 360)
		angle = angle - 360;
	angle *= 3.14159 / 180.0;

	cosine = cos(angle);
	sine = sin(angle);

	x1 = (width - centerx) * cosine - (height - centery) * sine;
	y1 = (width - centerx) * sine + (height - centery) * cosine;
	x2 = (width - centerx) * cosine + centery * sine;
	y2 = (width - centerx) * sine - centery * cosine;
	x3 = -x1; y3 = -y1;
	x4 = -x2; y4 = -y2;
	x1 += centerx; y1 += centery;
	x2 += centerx; y2 += centery;
	x3 += centerx; y3 += centery;
	x4 += centerx; y4 += centery;
	
	Max = x1;
	if (x2 > Max) Max = x2;
	if (x3 > Max) Max = x3;
	if (x4 > Max) Max = x4;

	Min = x1;
	if (x2 < Min) Min = x2;
	if (x3 < Min) Min = x3;
	if (x4 < Min) Min = x4;

	newWidth = Max - Min;

	Max = y1;
	if (y2 > Max) Max = y2;
	if (y3 > Max) Max = y3;
	if (y4 > Max) Max = y4;

	Min = y1;
	if (y2 < Min) Min = y2;
	if (y3 < Min) Min = y3;
	if (y4 < Min) Min = y4;

	newHeight = Max - Min;

	centerx1 = newWidth / 2;
	centery1 = newHeight / 2;

	result.dibHeader.imageWidth = newWidth;
	result.dibHeader.imageHeight = newHeight;

	delete[] result.pixelArray.rawBytes;

	int widthSize = result.dibHeader.imageWidth * (result.dibHeader.colorDepth / 8);
	result.pixelArray.paddingSize = (4 - (widthSize % 4)) % 4;
	result.pixelArray.lineSize = widthSize + result.pixelArray.paddingSize;
	result.pixelArray.rawByteSize = result.pixelArray.lineSize * result.dibHeader.imageHeight;
	result.pixelArray.rawBytes = new unsigned char[result.pixelArray.rawByteSize];

	for (int i = 0; i < result.pixelArray.rawByteSize; ++i)
		result.pixelArray.rawBytes[i] = 0;

	initPixels(result.pixelArray, result.dibHeader.imageWidth, result.dibHeader.imageHeight);

	for (yi = 0; yi < newHeight; yi++)
		for (xi = 0; xi < newWidth; xi++) {
			x = (xi - centerx1) * cosine + (yi - centery1) * sine;
			x += centerx;
			y = (yi - centery1) * cosine - (xi - centerx1) * sine;
			y += centery;
			if (x < 0 || x >= width - 1 || y < 0 || y >= height - 1)
				result.pixelArray.pixels[yi][xi].R = result.pixelArray.pixels[yi][xi].G = result.pixelArray.pixels[yi][xi].B = 0;
			else 
			{
				x1 = floor(x);
				y1 = floor(y);

				Color p11 = origiBitmap.pixelArray.pixels[y1][x1];
				Color p12 = origiBitmap.pixelArray.pixels[y1][x1 + 1];
				Color p21 = origiBitmap.pixelArray.pixels[y1 + 1][x1];
				Color p22 = origiBitmap.pixelArray.pixels[y1 + 1][x1 + 1];

				result.pixelArray.pixels[yi][xi] = Bilinear(x, y, p11, p12, p21, p22);
			}
		}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Vertical(const Bitmap& origiBitmap, Bitmap& result)
{
	uint32_t width, height;
	width = origiBitmap.dibHeader.imageWidth;
	height = origiBitmap.dibHeader.imageHeight;

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	uint32_t i, j, k;

	for (i = 0; i < height; i++)
		for (j = 0, k = width - 1; j <= k; j++, k--)
		{
			result.pixelArray.pixels[i][k] = origiBitmap.pixelArray.pixels[i][j];
			result.pixelArray.pixels[i][j] = origiBitmap.pixelArray.pixels[i][k];
		}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Horizontal(const Bitmap& origiBitmap, Bitmap& result)
{
	uint32_t width, height;
	width = origiBitmap.dibHeader.imageWidth;
	height = origiBitmap.dibHeader.imageHeight;

	uint32_t i, j, k;

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	for (i = 0; i < width; i++)
		for (j = 0, k = height - 1; j <= k; j++, k--)
		{
			result.pixelArray.pixels[k][i] = origiBitmap.pixelArray.pixels[j][i];
			result.pixelArray.pixels[j][i] = origiBitmap.pixelArray.pixels[k][i];
		}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Robert(const Bitmap& origiBitmap, Bitmap& result)
{
	std::vector<std::vector<char>> Robert_kernel_x = { {1, 0, 0}, {0, -1, 0}, {0, 0, 0} };
	std::vector<std::vector<char>> Robert_kernel_y = { {0, 1, 0}, {-1, 0, 0}, {0, 0, 0} };

	int lua_chon = 0;

	do
	{
		system("cls");
		frame();

		std::cout << "\t\t1. Robert theo huong x" << std::endl;
		std::cout << "\t\t2. Robert theo huong y" << std::endl;
		std::cout << "\t\t3. Robert theo ca hai huong x va y" << std::endl;

		std::cout << "\n\t\tVui long nhap lua chon >= 1 va <= 3: ";
		std::cin >> lua_chon;
	} while (lua_chon < 1 || lua_chon > 3);

	Bitmap blackwhite;

	copyImage(origiBitmap, blackwhite);

	int maxRow = origiBitmap.dibHeader.imageHeight;
	int maxCol = origiBitmap.dibHeader.imageWidth;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = blackwhite.pixelArray.pixels[i][j];
			int val = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
			pixel.R = pixel.G = pixel.B = val;

			mySetPixel(blackwhite, i, j, pixel);
		}

	if (lua_chon == 1)
	{
		std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n" << std::endl;

		int **CXmatrix = newMatrix(maxRow, maxCol);
		int **Xmatrix = newMatrix(maxRow, maxCol);

		createMatrixB(CXmatrix, blackwhite);
		createMatrix0(Xmatrix, blackwhite);

		convolution(CXmatrix, Xmatrix, Robert_kernel_x, 3, maxRow, maxCol);

		ResultRGB(result, Xmatrix, 1);

		deleteMatrix(CXmatrix, maxRow);
		deleteMatrix(Xmatrix, maxRow);
	}

	else if (lua_chon == 2)
	{
		std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n" << std::endl;

		int **CYmatrix = newMatrix(maxRow, maxCol);
		int **Ymatrix = newMatrix(maxRow, maxCol);

		createMatrixB(CYmatrix, blackwhite);
		createMatrix0(Ymatrix, blackwhite);

		convolution(CYmatrix, Ymatrix, Robert_kernel_y, 3, maxRow, maxCol);

		ResultRGB(result, Ymatrix, 1);

		deleteMatrix(CYmatrix, maxRow);
		deleteMatrix(Ymatrix, maxRow);
	}

	else if (lua_chon == 3)
	{
		int T = -1;
		do
		{
			system("cls");
			frame();
			std::cout << "\tNhap vao nguong can de lay bien anh (0 - 255), Vi du 128: ";
			std::cin >> T;
		} while (T < 0 || T > 255);

		std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n";

		int **CXmatrix = newMatrix(maxRow, maxCol);
		int **Xmatrix = newMatrix(maxRow, maxCol);
		int **CYmatrix = newMatrix(maxRow, maxCol);
		int **Ymatrix = newMatrix(maxRow, maxCol);

		createMatrixB(CXmatrix, blackwhite);
		createMatrix0(Xmatrix, blackwhite);
		createMatrixB(CYmatrix, blackwhite);
		createMatrix0(Ymatrix, blackwhite);

		convolution(CXmatrix, Xmatrix, Robert_kernel_x, 3, maxRow, maxCol);
		convolution(CYmatrix, Ymatrix, Robert_kernel_y, 3, maxRow, maxCol);

		int **Rmatrix = newMatrix(maxRow, maxCol);
		better(Rmatrix, Xmatrix, Ymatrix, maxRow, maxCol, T);

		ResultRGB(result, Rmatrix, 1);

		deleteMatrix(CXmatrix, maxRow);
		deleteMatrix(CYmatrix, maxRow);
		deleteMatrix(Xmatrix, maxRow);
		deleteMatrix(Ymatrix, maxRow);
		deleteMatrix(Rmatrix, maxRow);
	}

	int flag = 0;
	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Prewitt(const Bitmap& origiBitmap, Bitmap& result)
{
	std::vector<std::vector<char>> Prewitt_kernel_x = { {1, 0, -1}, {1, 0, -1}, {1, 0, -1} };
	std::vector<std::vector<char>> Prewitt_kernel_y = { {-1, -1, -1}, {0, 0, 0}, {1, 1, 1} };

	int lua_chon = 0;

	do
	{
		system("cls");
		frame();

		std::cout << "\t\t1. Prewitt theo huong x" << std::endl;
		std::cout << "\t\t2. Prewitt theo huong y" << std::endl;
		std::cout << "\t\t3. Prewitt theo ca hai huong x va y" << std::endl;

		std::cout << "\n\t\tVui long nhap lua chon >= 1 va <= 3: ";
		std::cin >> lua_chon;
	} while (lua_chon < 1 || lua_chon > 3);

	Bitmap blackwhite;

	copyImage(origiBitmap, blackwhite);

	int maxRow = origiBitmap.dibHeader.imageHeight;
	int maxCol = origiBitmap.dibHeader.imageWidth;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = blackwhite.pixelArray.pixels[i][j];
			int val = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
			pixel.R = pixel.G = pixel.B = val;

			mySetPixel(blackwhite, i, j, pixel);
		}

	if (lua_chon == 1)
	{
		std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n";

		int **CXmatrix = newMatrix(maxRow, maxCol);
		int **Xmatrix = newMatrix(maxRow, maxCol);

		createMatrixB(CXmatrix, blackwhite);
		createMatrix0(Xmatrix, blackwhite);

		convolution(CXmatrix, Xmatrix, Prewitt_kernel_x, 3, maxRow, maxCol);

		ResultRGB(result, Xmatrix, 1);

		deleteMatrix(CXmatrix, maxRow);
		deleteMatrix(Xmatrix, maxRow);
	}

	else if (lua_chon == 2)
	{
		std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n";

		int **CYmatrix = newMatrix(maxRow, maxCol);
		int **Ymatrix = newMatrix(maxRow, maxCol);

		createMatrixB(CYmatrix, blackwhite);
		createMatrix0(Ymatrix, blackwhite);

		convolution(CYmatrix, Ymatrix, Prewitt_kernel_y, 3, maxRow, maxCol);

		ResultRGB(result, Ymatrix, 1);

		deleteMatrix(CYmatrix, maxRow);
		deleteMatrix(Ymatrix, maxRow);
	}

	else if (lua_chon == 3)
	{
		int T = -1;
		do
		{
			system("cls");
			frame();
			std::cout << "\tNhap vao nguong can de lay bien anh (0 - 255), Vi du 128: ";
			std::cin >> T;
		} while (T < 0 || T > 255);

		std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n";

		int **CXmatrix = newMatrix(maxRow, maxCol);
		int **Xmatrix = newMatrix(maxRow, maxCol);
		int **CYmatrix = newMatrix(maxRow, maxCol);
		int **Ymatrix = newMatrix(maxRow, maxCol);

		createMatrixB(CXmatrix, blackwhite);
		createMatrix0(Xmatrix, blackwhite);
		createMatrixB(CYmatrix, blackwhite);
		createMatrix0(Ymatrix, blackwhite);

		convolution(CXmatrix, Xmatrix, Prewitt_kernel_x, 3, maxRow, maxCol);
		convolution(CYmatrix, Ymatrix, Prewitt_kernel_y, 3, maxRow, maxCol);

		int **Rmatrix = newMatrix(maxRow, maxCol);
		better(Rmatrix, Xmatrix, Ymatrix, maxRow, maxCol, T);

		ResultRGB(result, Rmatrix, 1);

		deleteMatrix(CXmatrix, maxRow);
		deleteMatrix(CYmatrix, maxRow);
		deleteMatrix(Xmatrix, maxRow);
		deleteMatrix(Ymatrix, maxRow);
		deleteMatrix(Rmatrix, maxRow);
	}

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Homogeneity_Edge_Detector(const Bitmap& origiBitmap, Bitmap& result)
{
	uint32_t maxRow, maxCol;

	copyImage(origiBitmap, result);
	maxRow = origiBitmap.dibHeader.imageHeight;
	maxCol = origiBitmap.dibHeader.imageWidth;

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = result.pixelArray.pixels[i][j];
			int val = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
			pixel.R = pixel.G = pixel.B = val;

			mySetPixel(result, i, j, pixel);
		}

	int i, j, k;
	short int** T, diff[8], max;

	T = new short int* [maxRow];

	for (i = 0; i < maxRow; i++)
		T[i] = new short int[maxCol];
	
	initPixelsHSI(result);

	RGB2HSI(result);

	colorHSI** p = result.pixelHSI.pixels;

	for (i = 1; i < maxRow - 1; i++)
		for (j = 1; j < maxCol - 1; j++) 
		{
			diff[0] = abs(p[i][j].I - p[i - 1][j - 1].I);
			diff[1] = abs(p[i][j].I - p[i - 1][j].I);
			diff[2] = abs(p[i][j].I - p[i - 1][j + 1].I);
			diff[3] = abs(p[i][j].I - p[i][j - 1].I);
			diff[4] = abs(p[i][j].I - p[i][j + 1].I);
			diff[5] = abs(p[i][j].I - p[i + 1][j - 1].I);
			diff[6] = abs(p[i][j].I - p[i + 1][j].I);
			diff[7] = abs(p[i][j].I - p[i + 1][j + 1].I);

			max = diff[0];
			for (k = 1; k <= 7; k++)
				if (max < diff[k])                                                                                              
					max = diff[k];
			T[i][j] = max + 64;
		}

	for (i = 1; i < maxRow - 1; i++)
		for (j = 1; j < maxCol - 1; j++)
			if (T[i][j] > 255)
				p[i][j].I = 255;
			else
				p[i][j].I = (unsigned char)T[i][j];

	HSI2RGB(result);

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Difference_Edge_Detector(const Bitmap& origiBitmap, Bitmap& result)
{
	uint32_t maxRow, maxCol;
	copyImage(origiBitmap, result);

	maxRow = origiBitmap.dibHeader.imageHeight;
	maxCol = origiBitmap.dibHeader.imageWidth;

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = result.pixelArray.pixels[i][j];
			int val = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
			pixel.R = pixel.G = pixel.B = val;

			mySetPixel(result, i, j, pixel);
		}

	int i, j, k;
	short int** T, diff[4], max;

	T = new short int*[maxRow];

	for (i = 0; i < maxRow; i++)
		T[i] = new short int[maxCol];

	initPixelsHSI(result);

	RGB2HSI(result);

	colorHSI** p = result.pixelHSI.pixels;

	for (i = 1; i < maxRow - 1; i++)
		for (j = 1; j < maxCol - 1; j++) {
			diff[0] = abs(p[i + 1][j + 1].I - p[i - 1][j - 1].I);
			diff[1] = abs(p[i][j + 1].I - p[i][j - 1].I);
			diff[2] = abs(p[i + 1][j - 1].I - p[i - 1][j + 1].I);
			diff[3] = abs(p[i + 1][j].I - p[i - 1][j].I);

			max = diff[0];
			for (k = 1; k <= 3; k++)
				if (max < diff[k]) max = diff[k];

			T[i][j] = max + 64;
		}
	for (i = 1; i < maxRow - 1; i++)
		for (j = 1; j < maxCol - 1; j++)
			if (T[i][j] > 255)
				p[i][j].I = 255;
			else
				p[i][j].I = (unsigned char)T[i][j];

	HSI2RGB(result);

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Canny(const Bitmap& origiBitmap, Bitmap& result)
{
	std::vector<std::vector<char>> gaussien = { {2, 4, 5, 4, 2},
												{4, 9, 12, 9 ,4},
												{5, 12, 15, 12, 5},
												{4, 9, 12, 9 ,4},
												{2, 4, 5, 4, 2} };

	std::vector<std::vector<char>> sobel_x_matrix = { {-1, 0, 1},
													  {-2, 0, 2},
													  {-1, 0, 1} };

	std::vector<std::vector<char>> sobel_y_matrix = { {-1, -2, -1},
													  {0, 0, 0},
													  {1, 2, 1} };

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	Bitmap blackwhite;

	copyImage(origiBitmap, blackwhite);

	int maxRow = origiBitmap.dibHeader.imageHeight;
	int maxCol = origiBitmap.dibHeader.imageWidth;

	int **Cmatrix = newMatrix(maxRow, maxCol);
	int **Rmatrix = newMatrix(maxRow, maxCol);

	createMatrixR(Cmatrix, blackwhite);
	createMatrix0(Rmatrix, blackwhite);
	convolution(Cmatrix, Rmatrix, gaussien, 5, maxRow, maxCol);
	ResultR(blackwhite, Rmatrix, 159);

	createMatrixG(Cmatrix, blackwhite);
	createMatrix0(Rmatrix, blackwhite);
	convolution(Cmatrix, Rmatrix, gaussien, 5, maxRow, maxCol);
	ResultG(blackwhite, Rmatrix, 159);

	createMatrixB(Cmatrix, blackwhite);
	createMatrix0(Rmatrix, blackwhite);
	convolution(Cmatrix, Rmatrix, gaussien, 5, maxRow, maxCol);
	ResultB(blackwhite, Rmatrix, 159);

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = blackwhite.pixelArray.pixels[i][j];
			int val = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
			pixel.R = pixel.G = pixel.B = val;

			mySetPixel(blackwhite, i, j, pixel);
		}

	int **CXmatrix = newMatrix(maxRow, maxCol);
	int **Xmatrix = newMatrix(maxRow, maxCol);
	int **CYmatrix = newMatrix(maxRow, maxCol);
	int **Ymatrix = newMatrix(maxRow, maxCol);

	createMatrixB(CXmatrix, blackwhite);
	createMatrix0(Xmatrix, blackwhite);

	createMatrixB(CYmatrix, blackwhite);
	createMatrix0(Ymatrix, blackwhite);

	convolution(CXmatrix, Xmatrix, sobel_x_matrix, 3, maxRow, maxCol);
	convolution(CYmatrix, Ymatrix, sobel_y_matrix, 3, maxRow, maxCol);

	double **theta = new double*[maxRow];
	for (int i = 0; i < maxRow; ++i)
		theta[i] = new double[maxCol];

	const double PI = 3.14159265;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Rmatrix[i][j] = Xmatrix[i][j] + Ymatrix[i][j];
			theta[i][j] = atan2(Ymatrix[i][j], Xmatrix[i][j]) * 180 / PI;
		}

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			int S1, S2;

			if (theta[i][j] <= 22.5 || theta[i][j] > 157.5)
			{
				if (i - 1 >= 0)
					S1 = Rmatrix[i - 1][j];
				else
					S1 = 0;

				if (i + 1 < maxRow)
					S2 = Rmatrix[i + 1][j];
				else
					S2 = 0;
			}

			else if (theta[i][j] > 22.5 && theta[i][j] <= 67.5)
			{
				if (i - 1 >= 0 && j - 1 <= 0)
					S1 = Rmatrix[i - 1][j - 1];
				else
					S1 = 0;

				if (i + 1 < maxRow && j + 1 < maxCol)
					S2 = Rmatrix[i + 1][j + 1];
				else
					S2 = 0;
			}

			else if (theta[i][j] > 67.5 && theta[i][j] <= 112.5)
			{
				if (j - 1 >= 0)
					S1 = Rmatrix[i][j - 1];
				else
					S1 = 0;
				if (j + 1 < maxCol)
					S2 = Rmatrix[i][j + 1];
				else
					S2 = 0;
			}

			else if (theta[i][j] > 112.5 && theta[i][j] <= 157.5)
			{
				if (i + 1 < maxRow && j - 1 >= 0)
					S1 = Rmatrix[i + 1][j - 1];
				else
					S1 = 0;

				if (i - 1 >= 0 && j + 1 < maxCol)
					S2 = Rmatrix[i - 1][j + 1];
				else
					S2 = 0;
			}

			int Max = S1;

			if (Max < S2)
				Max = S2;

			if (Max < Rmatrix[i][j])
				Max = Rmatrix[i][j];

			if (Max != Rmatrix[i][j])
				Rmatrix[i][j] = 0;
		}

	int Tl = 30, Th = 100;
	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			if (Rmatrix[i][j] >= Th)
				Rmatrix[i][j] = 255;

			else if (Rmatrix[i][j] < Tl)
				Rmatrix[i][j] = 0;

			else if (Rmatrix[i][j] <= Tl && Rmatrix[i][j] < Th)
			{
				int S1, S2, S3, S4, S5, S6, S7, S8;

				if (i - 1 >= 0 && j - 1 >= 0)
					S1 = Rmatrix[i - 1][j - 1];
				else
					S1 = 0;

				if (i - 1 >= 0)
					S2 = Rmatrix[i - 1][j];
				else
					S2 = 0;

				if (i - 1 >= 0 && j + 1 < maxCol)
					S3 = Rmatrix[i - 1][j + 1];
				else
					S3 = 0;

				if (j - 1 >= 0)
					S4 = Rmatrix[i][j - 1];
				else
					S4 = 0;

				if (j + 1 < maxCol)
					S5 = Rmatrix[i][j];
				else
					S5 = 0;

				if (i + 1 < maxRow && j - 1 >= 0)
					S6 = Rmatrix[i + 1][j - 1];
				else
					S6 = 0;

				if (i + 1 < maxRow)
					S7 = Rmatrix[i + 1][j];
				else
					S7 = 0;

				if (i + 1 < maxRow && j + 1 < maxCol)
					S8 = Rmatrix[i][j];
				else
					S8 = 0;

				if (S1 >= Th || S2 >= Th || S3 >= Th || S4 >= Th || S5 >= Th || S6 >= Th || S7 >= Th || S8 >= Th)
					Rmatrix[i][j] = 255;
				else
					Rmatrix[i][j] = 0;
			}
		}

	ResultRGB(result, Rmatrix, 1);

	for (int i = 0; i < maxRow; ++i)
		delete[] theta[i];
	delete[] theta;

	deleteMatrix(Rmatrix, maxRow);
	deleteMatrix(CXmatrix, maxRow);
	deleteMatrix(Xmatrix, maxRow);
	deleteMatrix(CYmatrix, maxRow);
	deleteMatrix(Ymatrix, maxRow);
	deleteMatrix(Cmatrix, maxRow);

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Laplacian_Of_Gaussian(const Bitmap& origiBitmap, Bitmap& result)
{
	std::vector<std::vector<char>> gaussien = { {2, 4, 5, 4, 2},
												{4, 9, 12, 9 ,4},
												{5, 12, 15, 12, 5},
												{4, 9, 12, 9 ,4},
												{2, 4, 5, 4, 2} };

	std::vector<std::vector<char>> laplace1 = { { -1, -1, -1},
											    { -1,  8, -1},
										   	    { -1, -1, -1} };

	std::vector<std::vector<char>> laplace2 = { {  0, -1,  0},
											    { -1,  4, -1},
											    {  0, -1,  0} };

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	Bitmap blackwhite;

	copyImage(origiBitmap, blackwhite);

	int maxRow = origiBitmap.dibHeader.imageHeight;
	int maxCol = origiBitmap.dibHeader.imageWidth;

	int **Cmatrix = newMatrix(maxRow, maxCol);
	int **Rmatrix = newMatrix(maxRow, maxCol);

	createMatrixR(Cmatrix, blackwhite);
	createMatrix0(Rmatrix, blackwhite);
	convolution(Cmatrix, Rmatrix, gaussien, 5, maxRow, maxCol);
	ResultR(blackwhite, Rmatrix, 159);

	createMatrixG(Cmatrix, blackwhite);
	createMatrix0(Rmatrix, blackwhite);
	convolution(Cmatrix, Rmatrix, gaussien, 5, maxRow, maxCol);
	ResultG(blackwhite, Rmatrix, 159);

	createMatrixB(Cmatrix, blackwhite);
	createMatrix0(Rmatrix, blackwhite);
	convolution(Cmatrix, Rmatrix, gaussien, 5, maxRow, maxCol);
	ResultB(blackwhite, Rmatrix, 159);

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = blackwhite.pixelArray.pixels[i][j];
			int val = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
			pixel.R = pixel.G = pixel.B = val;

			mySetPixel(blackwhite, i, j, pixel);
		}

	int **CXmatrix = newMatrix(maxRow, maxCol);
	int **Xmatrix = newMatrix(maxRow, maxCol);

	createMatrixB(CXmatrix, blackwhite);
	createMatrix0(Xmatrix, blackwhite);

	convolution(CXmatrix, Xmatrix, laplace1, 3, maxRow, maxCol);

	int **CYmatrix = newMatrix(maxRow, maxCol);
	int **Ymatrix = newMatrix(maxRow, maxCol);

	createMatrixB(CYmatrix, blackwhite);
	createMatrix0(Ymatrix, blackwhite);

	convolution(CYmatrix, Ymatrix, laplace2, 3, maxRow, maxCol);

	better(Rmatrix, Xmatrix, Ymatrix, maxRow, maxCol, 20);

	ResultRGB(result, Rmatrix, 1);

	deleteMatrix(Cmatrix, maxRow);
	deleteMatrix(Rmatrix, maxRow);
	deleteMatrix(CXmatrix, maxRow);
	deleteMatrix(Xmatrix, maxRow);
	deleteMatrix(CYmatrix, maxRow);
	deleteMatrix(Ymatrix, maxRow);

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Histogram_GrayScale(const Bitmap& origiBitmap, Bitmap& result) 
{
	float Pi[256], SumPi[256], H[256], sum;
	unsigned char LUT[256];

	uint32_t maxRow, maxCol;

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	copyImage(origiBitmap, result);
	maxRow = origiBitmap.dibHeader.imageHeight;
	maxCol = origiBitmap.dibHeader.imageWidth;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = result.pixelArray.pixels[i][j];
			int val = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
			pixel.R = pixel.G = pixel.B = val;

			mySetPixel(result, i, j, pixel);
		}

	initPixelsHSI(result);

	RGB2HSI(result);

	colorHSI** p = result.pixelHSI.pixels;

	for (int i = 0; i <= 255; i++)
		H[i] = 0;
	for (int i = 0; i < maxRow; i++)
		for (int j = 0; j < maxCol; j++)
			H[p[i][j].I]++;

	for (int i = 0; i <= 255; i++)
		Pi[i] = H[i] / (maxRow * maxCol);

	sum = 0;
	for (int i = 0; i <= 255; i++) 
	{
		sum += Pi[i];
		SumPi[i] = sum;
	}

	for (int i = 0; i <= 255; i++)
		LUT[i] = (unsigned char)(255 * SumPi[i]);

	for (int i = 0; i < maxRow; i++)
		for (int j = 0; j < maxCol; j++)
			p[i][j].I = LUT[p[i][j].I];

	HSI2RGB(result);

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Histogram_RGB(const Bitmap& origiBitmap, Bitmap& result)
{
	float Pi[256], SumPi[256], H[256], sum;
	unsigned char LUT[256];

	uint32_t maxRow, maxCol;

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	copyImage(origiBitmap, result);
	maxRow = origiBitmap.dibHeader.imageHeight;
	maxCol = origiBitmap.dibHeader.imageWidth;

	Color** p = result.pixelArray.pixels;

	for (int i = 0; i <= 255; i++)
		H[i] = 0;
	for (int i = 0; i < maxRow; i++)
		for (int j = 0; j < maxCol; j++)
			H[p[i][j].R]++;

	//R
	for (int i = 0; i <= 255; i++)
		Pi[i] = H[i] / (maxRow * maxCol);

	sum = 0;
	for (int i = 0; i <= 255; i++)
	{
		sum += Pi[i];
		SumPi[i] = sum;
	}

	for (int i = 0; i <= 255; i++)
		LUT[i] = (unsigned char)(255 * SumPi[i]);

	for (int i = 0; i < maxRow; i++)
		for (int j = 0; j < maxCol; j++)
			p[i][j].R = LUT[p[i][j].R];

	//G
	for (int i = 0; i <= 255; i++)
		H[i] = 0;
	for (int i = 0; i < maxRow; i++)
		for (int j = 0; j < maxCol; j++)
			H[p[i][j].G]++;

	for (int i = 0; i <= 255; i++)
		Pi[i] = H[i] / (maxRow * maxCol);

	sum = 0;
	for (int i = 0; i <= 255; i++)
	{
		sum += Pi[i];
		SumPi[i] = sum;
	}

	for (int i = 0; i <= 255; i++)
		LUT[i] = (unsigned char)(255 * SumPi[i]);

	for (int i = 0; i < maxRow; i++)
		for (int j = 0; j < maxCol; j++)
			p[i][j].G = LUT[p[i][j].G];

	//B
	for (int i = 0; i <= 255; i++)
		H[i] = 0;
	for (int i = 0; i < maxRow; i++)
		for (int j = 0; j < maxCol; j++)
			H[p[i][j].B]++;

	for (int i = 0; i <= 255; i++)
		Pi[i] = H[i] / (maxRow * maxCol);

	sum = 0;
	for (int i = 0; i <= 255; i++)
	{
		sum += Pi[i];
		SumPi[i] = sum;
	}

	for (int i = 0; i <= 255; i++)
		LUT[i] = (unsigned char)(255 * SumPi[i]);

	for (int i = 0; i < maxRow; i++)
		for (int j = 0; j < maxCol; j++)
			p[i][j].B = LUT[p[i][j].B];

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Median_Filter(const Bitmap& origiBitmap, Bitmap& result) 
{
	unsigned char *M, ik, jk, c, dem, tg;
	unsigned int i, j;

	uint32_t width, height;
	width = origiBitmap.dibHeader.imageWidth;
	height = origiBitmap.dibHeader.imageHeight;

	int size = -1;
	do
	{
		system("cls");
		frame();
		std::cout << "\n\tVui long nhap vao kich thuoc cua cua so loc > 0 (Vi du: 3)\n\tVoi moi kich thuoc cua so khac nhau se co ket qua khac nhau: ";
		std::cin >> size;
	} while (size < 0);

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	copyImage(origiBitmap, result);

	initPixelsHSI(result);

	RGB2HSI(result);

	c = size / 2;
	M = new unsigned char[size * size];

	colorHSI** p = result.pixelHSI.pixels;

	for (i = c; i < height - c; i++)
		for (j = c; j < width - c; j++) 
		{
			dem = 0;
			for (ik = 0; ik < size; ik++)
				for (jk = 0; jk < size; jk++) 
				{
					M[dem] = p[i + ik - c][j + jk - c].I;
					dem++;
				}

			for (ik = 0; ik < dem - 1; ik++)
				for (jk = ik + 1; jk < dem; jk++)
					if (M[ik] < M[jk]) 
					{
						tg = M[ik];
						M[ik] = M[jk];
						M[jk] = tg;
					}
			p[i][j].I = M[dem / 2];
		}

	HSI2RGB(result);

	std::cout << "\tXu li thanh cong!!! " << std::endl;

	delete[] M;
}

void Mean_Filter(const Bitmap& origiBitmap, Bitmap& result)
{
	uint32_t width, height;

	width = origiBitmap.dibHeader.imageWidth;
	height = origiBitmap.dibHeader.imageHeight;

	copyImage(origiBitmap, result);

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat....." << std::endl;

	initPixelsHSI(result);

	RGB2HSI(result);

	colorHSI** p = result.pixelHSI.pixels;

	for (int i = 1; i < height - 1; ++i)
		for (int j = 1; j < width - 1; ++j)
		{
			int sum = p[i - 1][j - 1].I + p[i - 1][j].I + p[i - 1][j + 1].I + p[i][j - 1].I + p[i][j].I + p[i][j + 1].I + p[i + 1][j - 1].I + p[i + 1][j].I + p[i + 1][j + 1].I;

			p[i][j].I = sum / 9;
		}

	HSI2RGB(result);

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}

void Kirsh(const Bitmap& origiBitmap, Bitmap& result)
{
	int lua_chon = 0;

	do
	{
		system("cls");
		frame();

		std::cout << "\t\t1. North" << std::endl;
		std::cout << "\t\t2. North-East" << std::endl;
		std::cout << "\t\t3. East" << std::endl;
		std::cout << "\t\t4. South-East" << std::endl;
		std::cout << "\t\t5. South" << std::endl;
		std::cout << "\t\t6. South-West" << std::endl;
		std::cout << "\t\t7. West" << std::endl;
		std::cout << "\t\t8. North-West" << std::endl;

		std::cout << "\n\t\tVui long nhap lua chon >= 1 va <= 8: ";
		std::cin >> lua_chon;
	} while (lua_chon < 1 || lua_chon > 8);

	std::vector<std::vector<char>> North = { {5, 5, 5},{-3, 0, -3},{-3, -3, -3} };
	std::vector<std::vector<char>> North_East = { {-3, 5, 5},{-3, 0, 5},{-3, -3, -3} };
	std::vector<std::vector<char>> East = { {-3, -3, 5},{-3, 0, 5},{-3, -3, 5} };
	std::vector<std::vector<char>> South_East = { {-3, -3, -3},{-3, 0, 5},{-3, 5, 5} };
	std::vector<std::vector<char>> South = { {-3, -3, -3},{-3, 0, -3},{5, 5, 5} };
	std::vector<std::vector<char>> South_West = { {-3, -3, -3},{5, 0, -3},{5, 5, -3} };
	std::vector<std::vector<char>> West = { {5, -3, -3},{5, 0, -3},{5, -3, -3} };
	std::vector<std::vector<char>> North_West = { {5, 5, -3},{5, 0, -3},{-3, -3, -3} };

	Bitmap blackwhite;

	copyImage(origiBitmap, blackwhite);

	int maxRow = origiBitmap.dibHeader.imageHeight;
	int maxCol = origiBitmap.dibHeader.imageWidth;

	for (int i = 0; i < maxRow; ++i)
		for (int j = 0; j < maxCol; ++j)
		{
			Color pixel = blackwhite.pixelArray.pixels[i][j];
			int val = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
			pixel.R = pixel.G = pixel.B = val;

			mySetPixel(blackwhite, i, j, pixel);
		}

	std::cout << "\n\tDang xu li. Xin vui long cho trong giay lat.....\n" << std::endl;

	int **Cmatrix = newMatrix(maxRow, maxCol);
	int **Rmatrix = newMatrix(maxRow, maxCol);

	createMatrixB(Cmatrix, blackwhite);
	createMatrix0(Rmatrix, blackwhite);

	if (lua_chon == 1)
		convolution(Cmatrix, Rmatrix, North, 3, maxRow, maxCol);
	else if (lua_chon == 2)
		convolution(Cmatrix, Rmatrix, North_East, 3, maxRow, maxCol);
	else if (lua_chon == 3)
		convolution(Cmatrix, Rmatrix, East, 3, maxRow, maxCol);
	else if (lua_chon == 4)
		convolution(Cmatrix, Rmatrix, South_East, 3, maxRow, maxCol);
	else if (lua_chon == 5)
		convolution(Cmatrix, Rmatrix, South, 3, maxRow, maxCol);
	else if (lua_chon == 6)
		convolution(Cmatrix, Rmatrix, South_West, 3, maxRow, maxCol);
	else if (lua_chon == 7)
		convolution(Cmatrix, Rmatrix, West, 3, maxRow, maxCol);
	else if (lua_chon == 8)
		convolution(Cmatrix, Rmatrix, North_West, 3, maxRow, maxCol);

	ResultRGB(result, Rmatrix, 1);

	deleteMatrix(Cmatrix, maxRow);
	deleteMatrix(Rmatrix, maxRow);

	std::cout << "\tXu li thanh cong!!! " << std::endl;
}