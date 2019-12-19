#include "GUI.h"
#include <string.h>
#pragma warning(disable: 4996)

bool getFile(Bitmap& bmp)
{
	char filePath[1000];
	
	fflush(stdin);
	std::cout << "\tNhap vao duong dan cua file anh : ";
	
	gets_s(filePath);

	FILE* fi;
	Bitmap temp;

	const char* exit = "0";

	bool canOpenFile = readBitmap(filePath, temp);
	while (!canOpenFile)
	{
		fflush(stdin);
		system("cls");
		frame(); 

		std::cout << "\tDoc file khong thanh cong" << std::endl;
		std::cout << "\tNhap lai duong dan khac neu ban muon tiep tuc, nhap 0 de thoat chuong trinh!!" << std::endl;
		std::cout << "\tDuong dan moi: ";

		gets_s(filePath);
		
		if (strcmp(filePath, exit) == 0)
			break;

		else 
			canOpenFile = readBitmap(filePath, temp);
	}

	if (strcmp(filePath, exit) != 0)
	{
		system("cls");
		bmp = temp;

		frame();
		std::cout << "\t\t  Doc File Thanh Cong" << std::endl;
		std::cout << "\t\tThong tin File vua nhan:" << std::endl;
		printBMFHeader(bmp);
		printDIBHeader(bmp);

		std::cout << "\n\n\t\tNHAN PHIM BAT KI DE TIEP TUC" << std::endl;
		_getch();
		system("cls");

		return true;
	}

	return false;
}

void menuProcess()
{
	frame();

	Bitmap origiBitmap, result;
	bool doing = getFile(origiBitmap);
	int flag2 = 0;

	while (doing)
	{
		frame();

		if (flag2 == 1)
		{
			int flag3 = 0;
			std::cout << "\tBan co muon thuc hien tren file hinh anh khac hay khong? " << std::endl
					  << "\n\t\t1. Co" << std::endl
					  << "\t\t2. Khong\n" << std::endl;
			do{
				std::cout << "\tNhap vao lua chon cua ban: ";
				std::cin >> flag3;
			} while (flag3 != 1 && flag3 != 2);

			if (flag3 == 1)
			{
				fflush(stdin);
				std::cin.ignore(1000, '\n');
				getFile(origiBitmap);
			}
				

			system("cls");
			frame();
		}
	
		Bitmap result;
		newImage(origiBitmap, result);

		std::cout << "\t\t\tCAC THAO TAC XU LI \n\n";
		std::cout << "\t\t----XU LI DIEM ANH-----" << std::endl
			<< "\t\t1.  Tang/Giam do sang" << std::endl
			<< "\t\t2.  Tang/Giam do tuong phan" << std::endl
			<< "\t\t3.  Tao hinh anh am ban" << std::endl
			<< "\t\t4.  Tao hinh anh trang den" << std::endl
			<< "\n\t\t----TIM BIEN CANH----" << std::endl
			<< "\t\t5.  Tim bien canh bang phuong phap Sobel" << std::endl
			<< "\t\t6.  Tim bien canh bang phuong phap Prewitt" << std::endl
			<< "\t\t7.  Tim bien canh bang phuong phap Robert" << std::endl
			<< "\t\t8.  Tim bien canh bang phuong phap Kirsh" << std::endl
			<< "\t\t9.  Tim bien canh bang phuong phap Canny" << std::endl
			<< "\t\t10. Tim bien canh bang phuong phap Laplacian Of Gaussian" << std::endl
			<< "\t\t11. Tim bien canh bang phuong phap Dong Hinh" << std::endl
			<< "\t\t12. Tim bien canh bang phuong phap Sai Phan" << std::endl
			<< "\n\t\t----XU LI CO BAN----" << std::endl
			<< "\t\t13. Xoay hinh anh" << std::endl
			<< "\t\t14. Phong to/Thu nho hinh anh" << std::endl
			<< "\t\t15. Lat hinh anh theo chieu ngang" << std::endl
			<< "\t\t16. Lat hinh anh theo chieu doc" << std::endl
			<< "\t\t17. Cong hai anh" << std::endl
			<< "\n\t\t----XU LI HISTOGRAM----" << std::endl
			<< "\t\t18. Can bang histogram anh xam" << std::endl
			<< "\t\t19. Can bang histogram anh mau" << std::endl
			<< "\n\t\t----LOC HINH ANH---- " << std::endl
			<< "\t\t20. Loc trung vi voi kich thuoc cua so loc nhap tu ban phim" << std::endl
			<< "\t\t21. Loc trung binh" << std::endl
			<< "\t\t22. Lam mo hinh anh" << std::endl
			<< "\n\t\t0. Thoat chuong trinh";
			
		int lua_chon = -1;
		do {
			std::cout << "\n\n\t\tNhap vao lua chon cua ban: ";
			std::cin >> lua_chon;
		} while (lua_chon < 0 || lua_chon > 22);

		system("cls");
		frame();

		switch (lua_chon)
		{
		case 1: 
		{
			Brightness(origiBitmap, result);
			break;
		}
		case 2:
		{
			Contrast(origiBitmap, result);
			break;
		}
		case 3:
		{
			Negative(origiBitmap, result);
			break;
		}
		case 4:
		{
			BlackWhite(origiBitmap, result);
			break;
		}
		case 5:
		{
			getSobel(origiBitmap, result);
			break;
		}
		case 6:
		{
			Prewitt(origiBitmap, result);
			break;
		}
		case 7:
		{
			Robert(origiBitmap, result);
			break;
		}
		case 8:
		{
			Kirsh(origiBitmap, result);
			break;
		}
		case 9:
		{
			Canny(origiBitmap, result);
			break;
		}
		case 10:
		{
			Laplacian_Of_Gaussian(origiBitmap, result);
			break;
		}
		case 11:
		{
			Homogeneity_Edge_Detector(origiBitmap, result);
			break;
		}
		case 12:
		{
			Difference_Edge_Detector(origiBitmap, result);
			break;
		}
		case 13:
		{
			Rotating(origiBitmap, result);
			break;
		}
		case 14:
		{
			Scaling(origiBitmap, result);
			break;
		}
		case 15:
		{
			Horizontal(origiBitmap, result);
			break;
		}
		case 16:
		{
			Vertical(origiBitmap, result);
			break;
		}
		case 17:
		{
			Bitmap origiBitmap2;
			fflush(stdin);
			std::cin.ignore(1000, '\n');

			std::cout << "\tCan them file anh thu 2\n";
			getFile(origiBitmap2);

			Blending(origiBitmap, origiBitmap2, result);
			break;
		}
		case 18:
		{
			Histogram_GrayScale(origiBitmap, result);
			break;
		}
		case 19:
		{
			Histogram_RGB(origiBitmap, result);
			break;
		}
		case 20:
		{
			Median_Filter(origiBitmap, result);
			break;
		}
		case 21:
		{
			Mean_Filter(origiBitmap, result);
			break;
		}
		case 22:
		{
			Dim(origiBitmap, result);
			break;
		}
		}
		 
		if (lua_chon == 0)
			break;

		std::cout << "\n\t\t\tNHAN PHIM BAT KI DE TIEP TUC";
		_getch();
		fflush(stdin);

		system("cls");
		frame();

		std::cin.ignore(256, '\n');
		std::string filePath;
		std::cout << "\n\tNhap vao duong dan ban muon luu ket qua: ";
		fflush(stdin);
		getline(std::cin, filePath);

		if (saveBitmap(filePath.c_str(), result))
		{
			system("cls");
			frame();
			std::cout << "\tLuu file thanh cong!!!\n\n";
			std::cout << "\tBan co muon tiep tuc hay khong? " << std::endl
				<< "\n\t\t1. Co" << std::endl
				<< "\t\t2. Khong" << std::endl;

			do {
				std::cout << "\n\tNhap vao lua chon cua ban: ";
				std::cin >> flag2;
			} while (flag2 != 1 && flag2 != 2);
		}
	
		else
		{
			int flag = 0;
			do
			{
				system("cls");
				frame();
				std::cout << "\tLuu file KHONG thanh cong!!! Vui long thu lai" << std::endl;
				std::cout << "\tVui long nhap vao duong dan khac: ";
				fflush(stdin);
				getline(std::cin, filePath);

				flag = saveBitmap(filePath.c_str(), result);

				if (flag)
				{
					std::cout << "\tDa luu file thanh cong!!!\n\n";
					std::cout << "\tBan co muon tiep tuc hay khong? " << std::endl
						<< "\n\t\t1. Co" << std::endl
						<< "\t\t2. Khong" << std::endl;

					do {
						std::cout << "\n\tNhap vao lua chon cua ban: ";
						std::cin >> flag2;
					} while (flag2 != 1 && flag2 != 2);
				}
			} while (flag == 0);
		}

		if (flag2 == 2)
			break;

		system("cls");
	}
}