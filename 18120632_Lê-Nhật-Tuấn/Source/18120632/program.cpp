#include "Bitmap.h"
#include "myUtility.h"
#include "mainProcess.h"
#include "GUI.h"

#include <cstdio>
#include <conio.h>
#include <cstdlib>

#pragma warning(disable: 4996)

int main()
{
	Nocursortype();
 	int horizontal = 0;
	int vertical = 0;

	GetDesktopResolution(horizontal, vertical);
	resizeConsole(horizontal, vertical);

	menuProcess();

	system("pause");
	return 0;
}
