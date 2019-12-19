#include <Windows.h>
#include <cmath>
#include <iostream>

#include "myUtility.h"

void frame()
{
	std::cout << "*********************************************************************************\n";
	std::cout << "*                                                                               *\n";
	std::cout << "*                                                                               *\n";
	std::cout << "*                    CHUONG TRINH XU LI ANH - 18120632                          *\n";
	std::cout << "*                                                                               *\n";
	std::cout << "*                                                                               *\n";
	std::cout << "*                                                                               *\n";
	std::cout << "*********************************************************************************\n\n";
}

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void Nocursortype()  //Xóa con trỏ
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

int** newMatrix(int row, int col)
{
	int** tmp = new int*[row];
	for (int i = 0; i < row; ++i)
		tmp[i] = new int[col];

	return tmp;
}

void createMatrix0(int** matrix, const Bitmap& bmp)
{
	int row = bmp.dibHeader.imageHeight;
	int col = bmp.dibHeader.imageWidth;

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			matrix[i][j] = 0;
}

void createMatrixB(int** matrix, const Bitmap& bmp)
{
	int row = bmp.dibHeader.imageHeight;
	int col = bmp.dibHeader.imageWidth;

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			matrix[i][j] = bmp.pixelArray.pixels[i][j].B;
}

void createMatrixG(int** matrix, const Bitmap& bmp)
{
	int row = bmp.dibHeader.imageHeight;
	int col = bmp.dibHeader.imageWidth;

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			matrix[i][j] = bmp.pixelArray.pixels[i][j].G;
}

void createMatrixR(int** matrix, const Bitmap& bmp)
{
	int row = bmp.dibHeader.imageHeight;
	int col = bmp.dibHeader.imageWidth;

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			matrix[i][j] = bmp.pixelArray.pixels[i][j].R;
}

void deleteMatrix(int** Matrix, int row)
{
	for (int i = 0; i < row; ++i)
		delete[] Matrix[i];

	delete[] Matrix;
}

Color Bilinear(double x, double y, const Color& p11, const Color& p12, const Color& p21, const Color& p22)
{
	Color tmp;
	uint32_t x1, y1, x2, y2;
	x1 = floor(x);
	y1 = floor(y);
	x2 = x1 + 1;
	y2 = y1 + 1;

	tmp.R = p11.R*(y2 - y)*(x2 - x) + p21.R*(y2 - y)*(x - x1) + p12.R*(y - y1)*(x2 - x) + p22.R*(y - y1)*(x - x1);
	tmp.G = p11.G*(y2 - y)*(x2 - x) + p21.G*(y2 - y)*(x - x1) + p12.G*(y - y1)*(x2 - x) + p22.G*(y - y1)*(x - x1);
	tmp.B = p11.B*(y2 - y)*(x2 - x) + p21.B*(y2 - y)*(x - x1) + p12.B*(y - y1)*(x2 - x) + p22.B*(y - y1)*(x - x1);

	return tmp;
}

void convolution(int** copyMatrix, int** resultMatrix, std::vector<std::vector<char>> kernel, int L, int maxRow, int maxCol)
{
	int kCenter = (L - 1) / 2;
	unsigned char pixel;

	for (int row = 0; row < maxRow; ++row)
		for (int col = 0; col < maxCol; ++col)
		{
			double sum = 0;
			int i = row + kCenter;

			for (int k_Y = 0; k_Y < L; ++k_Y)
			{
				int j = col + kCenter;

				for (int k_X = 0; k_X < L; ++k_X)
				{
					if (i >= 0 && i < maxRow && j >= 0 && j < maxCol)
					{
						sum += copyMatrix[i][j] * kernel[k_Y][k_X];
					}

					--j;
				}

				--i;
			}

			if (sum > MAXINT)
				sum = MAXINT;

			if (sum < MININT)
				sum = MININT;

			resultMatrix[row][col] = fabs(sum);
		}
}

void ResultRGB(Bitmap& result, int** RMatrix, int factor)
{
	int row = result.dibHeader.imageHeight;
	int col = result.dibHeader.imageWidth;

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			RMatrix[i][j] /= factor;
			result.pixelArray.pixels[i][j].B = result.pixelArray.pixels[i][j].G = result.pixelArray.pixels[i][j].R = RMatrix[i][j] > 255 ? 255 : RMatrix[i][j];
			result.pixelArray.pixels[i][j].B = result.pixelArray.pixels[i][j].G = result.pixelArray.pixels[i][j].R = RMatrix[i][j] < 0 ? 0 : RMatrix[i][j];
		}
}

void ResultR(Bitmap& result, int** RMatrix, int factor)
{
	int row = result.dibHeader.imageHeight;
	int col = result.dibHeader.imageWidth;

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			RMatrix[i][j] /= factor;
			result.pixelArray.pixels[i][j].R = RMatrix[i][j] > 255 ? 255 : RMatrix[i][j];
			result.pixelArray.pixels[i][j].R = RMatrix[i][j] < 0 ? 0 : RMatrix[i][j];
		}
}

void ResultG(Bitmap& result, int** RMatrix, int factor)
{
	int row = result.dibHeader.imageHeight;
	int col = result.dibHeader.imageWidth;

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			RMatrix[i][j] /= factor;
			result.pixelArray.pixels[i][j].G = RMatrix[i][j] > 255 ? 255 : RMatrix[i][j];
			result.pixelArray.pixels[i][j].G = RMatrix[i][j] < 0 ? 0 : RMatrix[i][j];
		}
}

void ResultB(Bitmap& result, int** RMatrix, int factor)
{
	int row = result.dibHeader.imageHeight;
	int col = result.dibHeader.imageWidth;

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			RMatrix[i][j] /= factor;
			result.pixelArray.pixels[i][j].B = RMatrix[i][j] > 255 ? 255 : RMatrix[i][j];
			result.pixelArray.pixels[i][j].B = RMatrix[i][j] < 0 ? 0 : RMatrix[i][j];
		}
}

void RGB2HSI(Bitmap& result) 
{
	double min, angle, r, g, b, h, s, tam, rgb;
	const double pi = 3.141592654;
	
	int row = result.dibHeader.imageHeight;
	int col = result.dibHeader.imageWidth;
		
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			r = result.pixelArray.pixels[i][j].R;
			g = result.pixelArray.pixels[i][j].G;
			b = result.pixelArray.pixels[i][j].B;

			rgb = r + g + b;

			tam = rgb / 3 / 255;
			r = r / rgb;
			g = g / rgb;
			b = b / rgb;

			min = r;
			if (min > g)
				min = g;

			if (min > b)
				min = b;

			if (r == g && g == b)
				h = s = 0;
			else 
			{
				s = 1 - 3 * min;
				angle = (r - g / 2 - b / 2) / sqrt((r - g) * (r - g) + (r - b) *
					(g - b));
				h = acos(angle);
			}

			if (b > g)
				h = 2 * pi - h;

			result.pixelHSI.pixels[i][j].H = h * 180 / pi;
			result.pixelHSI.pixels[i][j].S = s * 100;
			result.pixelHSI.pixels[i][j].I = tam * 255;
		}
}

void HSI2RGB(Bitmap& result) 
{
	double r, g, b, h, s, tam;
	const double pi = 3.141592654;
	
	colorHSI** p = result.pixelHSI.pixels;

	int row = result.dibHeader.imageHeight;
	int col = result.dibHeader.imageWidth;

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			h = p[i][j].H * pi / 180;
			s = p[i][j].S / 100.0;
			tam = p[i][j].I / 255.0;

			if (tam == 0)
				r = g = b = 0;
			else
				if (s == 0)
					r = g = b = tam;
				else
					if (h <= 2 * pi / 3) 
					{
						b = tam * (1 - s);
						r = tam * (1 + s * cos(h) / cos(pi / 3 - h));
						g = 3 * tam - r - b;
					}

					else if (h <= 4 * pi / 3) 
					{
						h = h - 2 * pi / 3;
						g = tam * (1 + s * cos(h) / cos(pi / 3 - h));
						r = tam * (1 - s);
						b = 3 * tam - r - g;
					}

					else 
					{
						h = h - 4 * pi / 3;
						b = tam * (1 + s * cos(h) / cos(pi / 3 - h));
						g = tam * (1 - s);
						r = 3 * tam - g - b;
					}

			result.pixelArray.pixels[i][j].R = r * 255;
			result.pixelArray.pixels[i][j].G = g * 255;
			result.pixelArray.pixels[i][j].B = b * 255;
		}
}

void better(int** Rmatrix, int** Xmatrix, int** Ymatrix, int row, int col, const int T)
{
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			Rmatrix[i][j] = Xmatrix[i][j] + Ymatrix[i][j];

			if (Rmatrix[i][j] > T)
				Rmatrix[i][j] = 255;
			else
				Rmatrix[i][j] = 0;
		}
}

void initPixelsHSI(Bitmap& result)
{
	result.pixelHSI.columnCount = result.pixelArray.columnCount;
	result.pixelHSI.rowCount = result.pixelArray.rowCount;
	result.pixelHSI.paddingSize = result.pixelArray.paddingSize;
	result.pixelHSI.lineSize = result.pixelArray.lineSize;
	result.pixelHSI.rawByteSize = result.pixelArray.lineSize * result.dibHeader.imageHeight;

	result.pixelHSI.rawBytes = new short int[result.pixelHSI.rawByteSize];

	result.pixelHSI.pixels = new colorHSI*[result.pixelHSI.rowCount];

	for (int i = 0; i < result.pixelHSI.rowCount; i++)
		result.pixelHSI.pixels[result.pixelHSI.rowCount - 1 - i] = (colorHSI*)(result.pixelHSI.rawBytes + result.pixelHSI.lineSize * i);

	RGB2HSI(result);
}

void getLPCoefficientsButterworth2Pole(const int samplerate, const double cutoff, double* const ax, double* const by)
{
	double PI = 3.1415926535897932385;
	double sqrt2 = 1.4142135623730950488;

	double QcRaw = (2 * PI * cutoff) / samplerate; // Find cutoff frequency in [0..PI]
	double QcWarp = tan(QcRaw); // Warp cutoff frequency

	double gain = 1 / (1 + sqrt2 / QcWarp + 2 / (QcWarp*QcWarp));
	by[2] = (1 - sqrt2 / QcWarp + 2 / (QcWarp*QcWarp)) * gain;
	by[1] = (2 - 2 * 2 / (QcWarp*QcWarp)) * gain;
	by[0] = 1;
	ax[0] = 1 * gain;
	ax[1] = 2 * gain;
	ax[2] = 1 * gain;
}