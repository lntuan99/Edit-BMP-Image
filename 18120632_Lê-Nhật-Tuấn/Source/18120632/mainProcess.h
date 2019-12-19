#include <vector>
#include "Bitmap.h"

//Cac thao tac tren File
void BlackWhite(const Bitmap& origiBitmap, Bitmap& result);
void Contrast(const Bitmap& origiBitmap, Bitmap& result);
void Negative(const Bitmap& origiBitmap, Bitmap& result);
void Blending(const Bitmap& origiBitmap1, const Bitmap& origiBitmap2, Bitmap& result);
void Brightness(const Bitmap& origiBitmap, Bitmap& result);
void Dim(const Bitmap& origiBitmap, Bitmap& result);
void Scaling(const Bitmap& origiBitmap, Bitmap& result);
void Rotating(const Bitmap& origiBitmap, Bitmap& result);
void Vertical(const Bitmap& origiBitmap, Bitmap& result);
void Horizontal(const Bitmap& origiBitmap, Bitmap& result);
void Robert(const Bitmap& origiBitmap, Bitmap& result);
void Prewitt(const Bitmap& origiBitmap, Bitmap& result);
void Homogeneity_Edge_Detector(const Bitmap& origiBitmap, Bitmap& result);
void Difference_Edge_Detector(const Bitmap& origiBitmap, Bitmap& result);
void Canny(const Bitmap& origiBitmap, Bitmap& result);
void Laplacian_Of_Gaussian(const Bitmap& origiBitmap, Bitmap& result);
void getSobel(const Bitmap& origiBitmap, Bitmap& result);
void Histogram_GrayScale(const Bitmap& origiBitmap, Bitmap& result);
void Histogram_RGB(const Bitmap& origiBitmap, Bitmap& result);
void Median_Filter(const Bitmap& origiBitmap, Bitmap& result);
void Mean_Filter(const Bitmap& origiBitmap, Bitmap& result);
void Kirsh(const Bitmap& origiBitmap, Bitmap& result);

unsigned char blend(const unsigned char& A, const unsigned char& B, const int& alpha);
