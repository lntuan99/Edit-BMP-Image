#include <vector>

#include "Bitmap.h"
#pragma once

void frame();

void resizeConsole(int width, int height);
void Nocursortype();
void FixConsoleWindow();
void GetDesktopResolution(int& horizontal, int& vertical);

void RGB2HSI(Bitmap& result);
void HSI2RGB(Bitmap& result);

void createMatrix0(int** matrix, const Bitmap& bmp);
void createMatrixR(int** matrix, const Bitmap& bmp);
void createMatrixG(int** matrix, const Bitmap& bmp);
void createMatrixB(int** matrix, const Bitmap& bmp);

void better(int** Rmatrix, int** Xmatrix, int** Ymatrix, int row, int col, const int T);

Color Bilinear(double x, double y, const Color& p11, const Color& p12, const Color& p21, const Color& p22);

int** newMatrix(int row, int col);
void deleteMatrix(int** Matrix, int row);

//Tinh tich chap
void convolution(int** copyMatrix, int** resultMatrix, std::vector<std::vector<char>> kernel, int L, int maxRow, int maxCol);

//Gán kết quả tích chập lại vào ảnh mới
void ResultRGB(Bitmap& result, int** RMatrix, int factor);
void ResultR(Bitmap& result, int** RMatrix, int factor);
void ResultG(Bitmap& result, int** RMatrix, int factor);
void ResultB(Bitmap& result, int** RMatrix, int factor);

void initPixelsHSI(Bitmap& result);
void getLPCoefficientsButterworth2Pole(const int samplerate, const double cutoff, double* const ax, double* const by);