// CMakeProject2.cpp: 定义应用程序的入口点。
//

#include "CMakeProject2.h"

#define EmptyCheck(x)  if (x.empty())   return Mat();




















int main()
{
	string path = "D:/Vscode_Project/Img/dragon.jpg";


	string SavePath = "D:/Vscode_Project/Img/dragonHalftone.jpg";

	cv::Mat src = imread(path);

	Mat img_Gray;
	cv::cvtColor(src, img_Gray, cv::COLOR_BGR2GRAY);


	Mat img_Gray0 = img_Gray.clone();
	Mat imgDiffuser_Halftone = Diffuser_Halftone(img_Gray0);

	imwrite(SavePath, imgDiffuser_Halftone);

	waitKey(3);

	//int dip_val = 30;


	//SetResolution(SavePath.c_str(), dip_val);
	//waitKey(3);


	//cv::Mat src_SetResolution = imread(SavePath);

	//waitKey(1);


	return 0;
}


bool SetResolution(const char* path, int iResolution)
{
	FILE* file = fopen(path, "rb+");// - 打开图片文件 
	if (!file)return false;
	int len = _filelength(_fileno(file));// - 获取文件大小 
	char* buf = new char[len];
	fread(buf, sizeof(char), len, file);// - 将图片数据读入缓存 
	char* pResolution = (char*)&iResolution;// - iResolution为要设置的分辨率的数值，如72dpi 
	// - 设置JPG图片的分辨率 
	buf[0x0D] = 1;// - 设置使用图片密度单位 
	// - 水平密度，水平分辨率 
	buf[0x0E] = pResolution[1];
	buf[0x0F] = pResolution[0];
	// - 垂直密度，垂直分辨率 
	buf[0x10] = pResolution[1];
	buf[0x11] = pResolution[0];

	// - 将文件指针移动回到文件开头 
	fseek(file, 0, SEEK_SET);
	// - 将数据写入文件，覆盖原始的数据，让修改生效 
	fwrite(buf, sizeof(char), len, file);
	fclose(file);
	return true;
}



















//
//
//
//
//int main()
//{
//	string path = "D:/Vscode_Project/Img/dragon.jpg";
//	cv::Mat src = imread(path);
//
//	Mat img_Gray;
//	cv::cvtColor(src, img_Gray, cv::COLOR_BGR2GRAY);
//
//
//
//
//
//
//
//	//Mat img_Gray0 = img_Gray.clone();
//
//	//Mat imgDiffuserBurkes = Diffuser_Burkes(img_Gray0);
//
//	//Mat img_Gray1 = img_Gray.clone();
//	//Mat imgDiffuserFloydSteinberg = Diffuser_FloydSteinberg(img_Gray1);
//
//	//Mat img_Gray2 = img_Gray.clone();
//	//Mat imgDiffuserJarris = Diffuser_Jarris(img_Gray2);
//
//
//	//Mat img_Gray3 = img_Gray.clone();
//	//Mat imgDiffuserSierra = Diffuser_Sierra(img_Gray3);
//
//
//
//	//Mat img_Gray4 = img_Gray.clone();
//	//Mat imgDiffuser = Diffuser(img_Gray4);
//
//
//	//Mat img_Gray5 = img_Gray.clone();
//	//Mat imgDiffuserTworowSierra = Diffuser_Two_row_Sierra(img_Gray4);
//
//	//Mat img_Gray6 = img_Gray.clone();
//	//Mat imgDiffuser_Sierra_Lite = Diffuser_Sierra_Lite(img_Gray6);
//	//
//
//	//Mat img_Gray7 = img_Gray.clone();
//	//Mat imgDiffuserAtkinson = Diffuser_Atkinson(img_Gray7);
//
//
//
//	//Mat img_Gray8 = img_Gray.clone();
//	//Mat imgDiffuser_Threshold = setDither_Threshold(img_Gray8);
//
//
//
//	//Mat img_Gray9 = img_Gray.clone();
//	//Mat imgsetDither_Screw = setDither_Screw(img_Gray9);
//
//	//Mat img_Gray91 = img_Gray.clone();
//	//Mat imgDiffuser_Halftone = Diffuser_Halftone(img_Gray91);
//
//
//
//	//
//	//Mat img_Gray10 = img_Gray.clone();
//	//Mat imgsetDither_CoarseFatting = setDither_CoarseFatting(img_Gray10);
//
//	//Mat img_Gray11 = img_Gray.clone();
//	//Mat imgsetDither_Screening_Zero = setDither_Screening_Zero(img_Gray11);
//
//
//
//
//
//
//	//Mat img_Gray12 = img_Gray.clone();
//	//Mat imgsetDither_Screening_forty_five = setDither_Screening_forty_five(img_Gray12);
//
//
//	//Mat img_Gray13 = img_Gray.clone();
//	//Mat imgsetDither_Seventy_five = setDither_Seventy_five(img_Gray13);
//
//
//	//Mat img_Gray14 = img_Gray.clone();
//	//Mat imgsetDither_Screening_Fifteen = setDither_Screening_Fifteen(img_Gray14);
//
//
//	imshow("img_Gray", img_Gray);
//	waitKey(1);
//
//
//	return 0;
//}



Mat setDither_Seventy_five(const Mat& mat)
{
	EmptyCheck(mat);
	Mat matDith = getGray(mat);
	// Halftone Ordered Dithering 8*8
	// Screw Ordered Dithering
	int Mask[] = { 
		153,145,136,117,95,81,8,52,93,104,97,86,77,69,59,54,41,29,7,5,36,23,13,18,26,34,
		46,64,67,72,79,25,50,66,90,103,122,128,130,137,134,118,102,82,16,51,96,115,132,147,152,
		148,139,126,105,98,78,15,27,80,73,71,61,53,48,31,14,1,10,17,4,3,6,30,49,60,68,
		75,84,89,106,83,37,35,85,107,119,131,138,146,142,140,129,109,92,32,39,91,111,124,141,144,
		120,101,88,74,63,58,2,20,65,47,43,40,28,11,12,24,38,42,55,21,22,56,62,70,87,100,
		114,121,127,113,99,45,9,57,110,123,135,143,151,150,149,133,112,94,44,19,76,108,116,125,136

	};

	cout << "matDith.cols: " << mat.cols << endl;

	cout << "matDith.rows: " << mat.rows << endl;


	Size dsize = Size(matDith.cols, matDith.rows);

	Mat matGrayResize = Mat::zeros(dsize, CV_8U);
	int nW = matGrayResize.cols;
	int nH = matGrayResize.rows;

	for (int y = 0; y < nH; y++)
	{


		int k = y % 3;

		for (int x = 0; x < nW; x++)
		{
			int l = x % 8;
			int  dPix = matDith.at<uint8_t>(Point(x, y));
			if (((matDith.at<uint8_t>(Point(x, y))) >> 2) > Mask[(k * 51 + l)])
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 255;
			}
			else
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 0;
			}

		}

	}
	return matGrayResize;
}






Mat setDither_Screening_Zero(const Mat& mat)
{
	EmptyCheck(mat);
	Mat matDith = getGray(mat);
	// Halftone Ordered Dithering 8*8
	// Screw Ordered Dithering
	int Mask[] = { 144,140,132,122,107,63,54,93,106,123,133,142,
	143,137,128,104,94,41,31,65,98,116,120,139,
	135,131,114,97,61,35,24,55,80,103,113,125,
	126,117,88,83,56,29,15,51,68,90,99,111,
	109,100,81,77,48,22,8,28,47,76,85,96,
	91,44,16,12,9,3,5,21,25,33,37,73,
		59,58,30,18,10,1,2,4,11,19,34,42,
	92,64,57,52,26,6,7,14,32,46,53,74,
	101,95,70,67,38,13,20,36,50,75,82,108,
	121,110,86,78,45,17,27,39,69,79,102,119,
	134,129,112,89,49,23,43,60,71,87,115,127,
	141,138,124,118,66,40,62,72,84,105,130,136};

	cout << "matDith.cols: " << mat.cols << endl;

	cout << "matDith.rows: " << mat.rows << endl;


	Size dsize = Size(matDith.cols, matDith.rows);

	Mat matGrayResize = Mat::zeros(dsize, CV_8U);
	int nW = matGrayResize.cols;
	int nH = matGrayResize.rows;

	for (int y = 0; y < nH; y++)
	{


		int k = y % 8;

		for (int x = 0; x < nW; x++)
		{
			int l = x % 8;
			int  dPix = matDith.at<uint8_t>(Point(x, y));
			if (((matDith.at<uint8_t>(Point(x, y))) >> 2) > Mask[(k * 12 + l)])
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 255;
			}
			else
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 0;
			}

		}

	}
	return matGrayResize;
}


Mat setDither_Screening_forty_five(const Mat& mat)
{
	EmptyCheck(mat);
	Mat matDith = getGray(mat);
	// Halftone Ordered Dithering 8*8
	// Screw Ordered Dithering
	int Mask[] = {
		128,120,109,92,74,66,46,8,15,10,64,79,97,111,122,127,
		123,116,87,69,62,38,6,39,42,3,19,55,86,105,115,119,
		107,96,71,59,24,12,28,52,63,47,20,1,58,95,108,112,
		84,73,56,2,18,23,48,78,82,67,35,5,31,61,91,101,
		77,53,32,4,25,43,75,85,100,89,60,30,9,34,68,80,
		51,41,21,27,40,70,94,102,110,103,93,57,26,11,37,65,
		44,29,33,45,72,90,104,121,117,114,106,88,54,17,13,16,
		14,36,49,76,83,98,118,126,125,124,113,99,81,50,22,7

	};

	cout << "matDith.cols: " << mat.cols << endl;

	cout << "matDith.rows: " << mat.rows << endl;


	Size dsize = Size(matDith.cols, matDith.rows);

	Mat matGrayResize = Mat::zeros(dsize, CV_8U);
	int nW = matGrayResize.cols;
	int nH = matGrayResize.rows;

	for (int y = 0; y < nH; y++)
	{


		int k = y % 8;

		for (int x = 0; x < nW; x++)
		{
			int l = x % 8;
			int  dPix = matDith.at<uint8_t>(Point(x, y));
			if (((matDith.at<uint8_t>(Point(x, y))) >> 2) > Mask[(k * 16 + l)])
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 255;
			}
			else
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 0;
			}

		}

	}
	return matGrayResize;
}




Mat setDither_Screening_Fifteen(const Mat& mat)
{
	EmptyCheck(mat);
	Mat matDith = getGray(mat);
	// Halftone Ordered Dithering 8*8
	// Screw Ordered Dithering
	int Mask[] = 
	{ 
		153,148,120,77,53,28,26,60,87,122,131,135,132,124,116,104,73,47,23,6,56,66,85,57,51,39,
		19,8,15,2,7,17,55,79,83,99,102,109,112,117,105,74,54,14,24,64,84,121,137,142,150,
		145,139,101,69,48,11,34,68,100,128,138,143,147,141,125,97,71,43,13,30,62,90,107,110,96,91,
		76,52,27,20,5,4,21,25,37,45,82,92,94,95,98,63,41,1,38,67,89,127,134,140,149,
		136,126,88,59,31,12,46,75,114,130,146,151,152,144,136,86,61,40,18,49,70,103,119,123,115,111,
		108,93,80,65,36,3,22,50,35,9,16,32,44,81,78,58,29,10,42,72,106,113,118,129,133
	};

	cout << "matDith.cols: " << mat.cols << endl;

	cout << "matDith.rows: " << mat.rows << endl;


	Size dsize = Size(matDith.cols, matDith.rows);

	Mat matGrayResize = Mat::zeros(dsize, CV_8U);
	int nW = matGrayResize.cols;
	int nH = matGrayResize.rows;

	for (int y = 0; y < nH; y++)
	{


		int k = y % 3;

		for (int x = 0; x < nW; x++)
		{
			int l = x % 8;
			int  dPix = matDith.at<uint8_t>(Point(x, y));
			if (((matDith.at<uint8_t>(Point(x, y))) >> 2) > Mask[(k * 51 + l)])
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 255;
			}
			else
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 0;
			}

		}

	}
	return matGrayResize;
}















Mat setDither_CoarseFatting(const Mat& mat)
{
	EmptyCheck(mat);
	Mat matDith = getGray(mat);
	// Halftone Ordered Dithering 8*8
	// Screw Ordered Dithering
	int Mask[] = { 4, 14, 52, 58, 56, 45, 20, 6,
				   16, 26, 38, 50, 48, 36, 28, 18,
				   43, 35, 31, 9, 11, 25, 33, 41,
				   61, 46, 23, 1, 3, 13, 55, 60,
				   57, 47, 21, 7, 5, 15, 53, 59,
				   49, 37, 29, 19, 17, 27, 39, 51,
				   10, 24, 32, 40, 42, 34, 30, 8,
				   2, 12, 54, 60, 51, 44, 22, 0 };

	cout << "matDith.cols: " << mat.cols << endl;

	cout << "matDith.rows: " << mat.rows << endl;


	Size dsize = Size(matDith.cols, matDith.rows);

	Mat matGrayResize = Mat::zeros(dsize, CV_8U);
	int nW = matGrayResize.cols;
	int nH = matGrayResize.rows;

	for (int y = 0; y < nH; y++)
	{


		int k = y % 8;

		for (int x = 0; x < nW; x++)
		{
			int l = x % 8;
			int  dPix = matDith.at<uint8_t>(Point(x, y));
			if (((matDith.at<uint8_t>(Point(x, y))) >> 2) > Mask[(k * 8 + l)])
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 255;
			}
			else
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 0;
			}

		}

	}
	return matGrayResize;
}

















Mat setDither_Screw(const Mat& mat)
{
	EmptyCheck(mat);
	Mat matDith = getGray(mat);
	// Halftone Ordered Dithering 8*8
	// Screw Ordered Dithering
	int Mask[] = { 64, 53, 42, 26, 27, 43, 54, 61,
				   60, 41, 25, 14, 15, 28, 44, 55,
				   52, 40, 13, 5, 6, 16, 29, 45,
				   39, 24, 12, 1, 2, 7, 17, 30,
				   38, 23, 11, 4, 3, 8, 18, 31,
				   51, 37, 22, 10, 9, 19, 32, 41,
				   59, 50, 36, 21, 20, 33, 47, 56,
				   63, 58, 49, 35, 34, 48, 57, 62 };

	cout << "matDith.cols: " << mat.cols << endl;

	cout << "matDith.rows: " << mat.rows << endl;


	Size dsize = Size(matDith.cols, matDith.rows);

	Mat matGrayResize = Mat::zeros(dsize, CV_8U);
	int nW = matGrayResize.cols;
	int nH = matGrayResize.rows;

	for (int y = 0; y < nH; y++)
	{


		int k = y % 8;

		for (int x = 0; x < nW; x++)
		{
			int l = x % 8;
			int  dPix = matDith.at<uint8_t>(Point(x, y));
			if (((matDith.at<uint8_t>(Point(x, y))) >> 2) > Mask[(k * 8 + l)])
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 255;
			}
			else
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 0;
			}

		}

	}
	return matGrayResize;
}




















Mat setDither_Threshold(const Mat& mat)
{
	EmptyCheck(mat);

	Mat matDith = getGray(mat);


	int nW = matDith.cols;
	int nH = matDith.rows;


	Mat img_Threshold = Mat::zeros(Size(nW, nH), CV_8U);
	/* Run the 'Rand value Threshold' dithering algorithm ... */

	for (int i = 0; i < nH; i++)
	{
		for (int j = 0; j < nW; j++)
		{

			if (matDith.at<uchar>(i, j) > (rand() % 255))
			{
				img_Threshold.at<uchar>(i, j) = 255;
			}
		}
	}

	matDith = img_Threshold;
	return matDith;
}








cv::Mat Diffuser_Halftone(cv::Mat src)
{

	Mat matDith = getGray(src);
	// Halftone Ordered Dithering 8*8
	int Mask3[] = { 28, 10, 18, 26, 36, 44, 52, 34,
				   22, 2, 4, 12, 48, 58, 60, 42,
				   14, 6, 0, 20, 40, 56, 62, 50,
				   24, 16, 8, 30, 32, 54, 46, 38,
				   37, 45, 53, 35, 29, 11, 19, 27,
				   49, 59, 61, 43, 23, 3, 5, 13,
				   41, 57, 63, 51, 15, 7, 1, 21,
				   33, 55, 47, 39, 25, 17, 9, 31 };

	cout << "matDith.cols: " << matDith.cols << endl;

	cout << "matDith.rows: " << matDith.rows << endl;


	Size dsize = Size(matDith.cols, matDith.rows);

	Mat matGrayResize = Mat::zeros(dsize, CV_8U);

	cout << "matGrayResize.cols: " << matGrayResize.cols << endl;

	cout << "matGrayResize.rows: " << matGrayResize.rows << endl;

	int nW = matGrayResize.cols;
	int nH = matGrayResize.rows;



	for (int y = 0; y < nH; y++)
	{
		

		int k = y % 8;

		for (int x = 0; x < nW; x++)
		{
			int l = x % 8;
			int  dPix = matDith.at<uint8_t>(Point(x, y));
			if (((matDith.at<uint8_t>(Point(x, y))) >> 2) > Mask3[(k * 8 + l)])
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 255;
			}
			else
			{
				matGrayResize.at<uint8_t>(Point(x, y)) = 0;
			}

		}

	}


// Size dsize = Size(matDith.cols * time, matDith.rows * time);

// Mat matGrayResize = Mat::zeros(dsize, CV_8U);

// int nW = matGrayResize.cols;
// int nH = matGrayResize.rows;

// cout<<"matGrayResize.cols: "<<matGrayResize.cols<<endl;

// cout<<"matGrayResize.rows: "<<matGrayResize.rows<<endl;


// for (int y = 0; y < nH; y++)
// {

//     int k = y % K;

//     for (int x = 0; x < nW; x++)
//     {
//         int l = x % L;  
//         double dPix = matDith.at<uint8_t>(Point(x / time, y / time)) / 255.0 * N + 0.5 +0.5;
//         if (dPix > Mask3[(k * L + l)])
//         {
//             matGrayResize.at<uint8_t>(Point(x, y)) = 255;
//         }
//         else
//         {
//             matGrayResize.at<uint8_t>(Point(x, y)) = 0;
//         }
//     }
// }






	return matGrayResize;




}










//int main() {
//	string path = "D:/Vscode_Project/Img/dragon.jpg";
//	cv::Mat src = imread(path);
//
//	Mat img_gray0;
//	cv::cvtColor(src, img_gray0, cv::COLOR_BGR2GRAY);
//	int img_h, img_w;
//	img_h = img_gray0.size().height;
//	img_w = img_gray0.size().width;
//
//	Mat img_dither = Mat::zeros(Size(img_w + 1, img_h + 1), CV_8U);
//	Mat img_undither = Mat::zeros(Size(img_w, img_h), CV_8U);
//	int threshold = 128;
//
//	//@ 给img_dither赋值，对img_undither二值化
//	for (int i = 0; i < img_h; i++)
//	{
//		for (int j = 0; j < img_w; j++)
//		{
//			//cout << img_dither.at<uchar>(i, j) << endl;
//			img_dither.at<uchar>(i, j) = img_gray0.at<uchar>(i, j);
//			if (img_gray0.at<uchar>(i, j) > threshold)
//			{
//				img_undither.at<uchar>(i, j) = 255;
//			}
//			//@ 这里还有一种二值化方式，采用随机阈值进行二值化，这种也很有意思，得到的二值图像有更多的细节
//			if (img_gray0.at<uchar>(i, j) > (rand() % 255))
//			{
//				img_undither.at<uchar>(i, j) = 255;
//			}
//		}
//	}
//
//	for (int i = 0; i < img_h; i++)
//	{
//		for (int j = 0; j < img_w; j++)
//		{
//			int new_pix;
//			int old_pix = img_dither.at<uchar>(i, j);
//			if (img_dither.at<uchar>(i, j) > threshold)
//			{
//				new_pix = 255;
//			}
//			else
//			{
//				new_pix = 0;
//			}
//			//先对img_dither二值化
//			img_dither.at<uchar>(i, j) = new_pix;
//			int quant_err = old_pix - new_pix;
//			if (j > 0)
//			{
//				img_dither.at<uchar>(i + 1, j - 1) = img_dither.at<uchar>(i + 1, j - 1) + quant_err * 3 / 16;
//			}
//			img_dither.at<uchar>(i + 1, j) = img_dither.at<uchar>(i + 1, j) + quant_err * 5 / 16;
//			img_dither.at<uchar>(i, j + 1) = img_dither.at<uchar>(i, j + 1) + quant_err * 7 / 16;
//			img_dither.at<uchar>(i + 1, j + 1) = img_dither.at<uchar>(i + 1, j + 1) + quant_err * 1 / 16;
//		}
//	}
//	imshow("src", img_gray0);
//	imshow("img_undither", img_undither);
//	imshow("img_dither", img_dither);
//	waitKey();
//	return 0;
//}
















cv::Mat Diffuser_Atkinson(cv::Mat src)
{
	Mat mat = src.clone();

	EmptyCheck(mat);


	Mat matDith = getGray(mat);

	int nW = matDith.cols;
	int nH = matDith.rows;

	/* Run the 'Floyd-Steinberg' dithering algorithm ... */
	int err;
	int8_t a, b, c, d, e, f, g, w, s, x, y, z;

	auto saturated_add = [](uint8_t val1, int8_t val2) -> uint8_t
	{
		int16_t val1_int = val1;
		int16_t val2_int = val2;
		int16_t tmp = val1_int + val2_int;

		if (tmp > 255)
			return 255;
		else if (tmp < 0)
			return 0;
		else
			return tmp;
	};

	for (int i = 0; i < nH; i++)
	{
		for (int j = 0; j < nW; j++)
		{
			if (matDith.at<uint8_t>(i, j) > 127)
			{
				err = matDith.at<uint8_t>(i, j) - 255;
				matDith.at<uint8_t>(i, j) = 255;
			}
			else
			{
				err = matDith.at<uint8_t>(i, j) - 0;
				matDith.at<uint8_t>(i, j) = 0;
			}

			a = (err * 1) / 6;
			b = (err * 1) / 6;

			c = (err * 1) / 6;
			d = (err * 1) / 6;
			e = (err * 1) / 6;
			f = (err * 1) / 6;





			if ((i < (nH - 2)) && (j > 1) && (j < (nW - 2)))
			{
				matDith.at<uint8_t>(i + 0, j + 1) = saturated_add(matDith.at<uint8_t>(i + 0, j + 1), a);
				matDith.at<uint8_t>(i + 0, j + 2) = saturated_add(matDith.at<uint8_t>(i + 0, j + 2), b);

				matDith.at<uint8_t>(i + 1, j - 1) = saturated_add(matDith.at<uint8_t>(i + 1, j - 1), c);
				matDith.at<uint8_t>(i + 1, j + 0) = saturated_add(matDith.at<uint8_t>(i + 1, j + 0), d);
				matDith.at<uint8_t>(i + 1, j + 1) = saturated_add(matDith.at<uint8_t>(i + 1, j + 1), e);

				matDith.at<uint8_t>(i + 2, j + 0) = saturated_add(matDith.at<uint8_t>(i + 2, j + 0), f);

			}
		}
	}
	return matDith;

}








cv::Mat Diffuser_Sierra_Lite(cv::Mat src)
{
	Mat mat = src.clone();

	EmptyCheck(mat);


	Mat matDith = getGray(mat);

	int nW = matDith.cols;
	int nH = matDith.rows;

	/* Run the 'Floyd-Steinberg' dithering algorithm ... */
	int err;
	int8_t a, b, c, d, e, f, g, w, s, x, y, z;

	auto saturated_add = [](uint8_t val1, int8_t val2) -> uint8_t
	{
		int16_t val1_int = val1;
		int16_t val2_int = val2;
		int16_t tmp = val1_int + val2_int;

		if (tmp > 255)
			return 255;
		else if (tmp < 0)
			return 0;
		else
			return tmp;
	};

	for (int i = 0; i < nH; i++)
	{
		for (int j = 0; j < nW; j++)
		{
			if (matDith.at<uint8_t>(i, j) > 127)
			{
				err = matDith.at<uint8_t>(i, j) - 255;
				matDith.at<uint8_t>(i, j) = 255;
			}
			else
			{
				err = matDith.at<uint8_t>(i, j) - 0;
				matDith.at<uint8_t>(i, j) = 0;
			}

			a = (err * 2) / 4;
			b = (err * 1) / 4;

			c = (err * 1) / 4;





			if ((i < (nH - 2)) && (j > 1) && (j < (nW - 2)))
			{
				matDith.at<uint8_t>(i + 0, j + 1) = saturated_add(matDith.at<uint8_t>(i + 0, j + 1), a);
				matDith.at<uint8_t>(i + 1, j - 1) = saturated_add(matDith.at<uint8_t>(i + 1, j - 1), b);
				matDith.at<uint8_t>(i + 1, j + 0) = saturated_add(matDith.at<uint8_t>(i + 1, j + 0), c);


			}
		}
	}
	return matDith;

}





















cv::Mat Diffuser_Two_row_Sierra(cv::Mat src)
{

	Mat mat = src.clone();

	EmptyCheck(mat);


	Mat matDith = getGray(mat);

	int nW = matDith.cols;
	int nH = matDith.rows;

	/* Run the 'Floyd-Steinberg' dithering algorithm ... */
	int err;
	int8_t a, b, c, d, e, f, g;

	auto saturated_add = [](uint8_t val1, int8_t val2) -> uint8_t
	{
		int16_t val1_int = val1;
		int16_t val2_int = val2;
		int16_t tmp = val1_int + val2_int;

		if (tmp > 255)
			return 255;
		else if (tmp < 0)
			return 0;
		else
			return tmp;
	};

	for (int i = 0; i < nH; i++)
	{
		for (int j = 0; j < nW; j++)
		{
			if (matDith.at<uint8_t>(i, j) > 127)
			{
				err = matDith.at<uint8_t>(i, j) - 255;
				matDith.at<uint8_t>(i, j) = 255;
			}
			else
			{
				err = matDith.at<uint8_t>(i, j) - 0;
				matDith.at<uint8_t>(i, j) = 0;
			}

			a = (err * 4) / 16;
			b = (err * 3) / 16;

			c = (err * 1) / 16;
			d = (err * 2) / 16;
			e = (err * 3) / 16;
			f = (err * 2) / 16;
			g = (err * 1) / 16;


			if ((i < (nH - 1)) && (j > 1) && (j < (nW - 2)))
			{
				matDith.at<uint8_t>(i + 0, j + 1) = saturated_add(matDith.at<uint8_t>(i + 0, j + 1), a);
				matDith.at<uint8_t>(i + 0, j + 2) = saturated_add(matDith.at<uint8_t>(i + 0, j + 2), b);
				matDith.at<uint8_t>(i + 1, j - 2) = saturated_add(matDith.at<uint8_t>(i + 1, j - 2), c);
				matDith.at<uint8_t>(i + 1, j - 1) = saturated_add(matDith.at<uint8_t>(i + 1, j - 1), d);
				matDith.at<uint8_t>(i + 1, j + 0) = saturated_add(matDith.at<uint8_t>(i + 1, j + 0), e);
				matDith.at<uint8_t>(i + 1, j + 1) = saturated_add(matDith.at<uint8_t>(i + 1, j + 1), f);
				matDith.at<uint8_t>(i + 1, j + 2) = saturated_add(matDith.at<uint8_t>(i + 1, j + 2), g);

			}
		}
	}



	return matDith;
}









cv::Mat Diffuser_Sierra(cv::Mat src)
{
	Mat mat = src.clone();

	EmptyCheck(mat);


	Mat matDith = getGray(mat);

	int nW = matDith.cols;
	int nH = matDith.rows;

	/* Run the 'Floyd-Steinberg' dithering algorithm ... */
	int err;
	int8_t a, b, c, d, e, f, g, w, s, x, y, z;

	auto saturated_add = [](uint8_t val1, int8_t val2) -> uint8_t
	{
		int16_t val1_int = val1;
		int16_t val2_int = val2;
		int16_t tmp = val1_int + val2_int;

		if (tmp > 255)
			return 255;
		else if (tmp < 0)
			return 0;
		else
			return tmp;
	};

	for (int i = 0; i < nH; i++)
	{
		for (int j = 0; j < nW; j++)
		{
			if (matDith.at<uint8_t>(i, j) > 127)
			{
				err = matDith.at<uint8_t>(i, j) - 255;
				matDith.at<uint8_t>(i, j) = 255;
			}
			else
			{
				err = matDith.at<uint8_t>(i, j) - 0;
				matDith.at<uint8_t>(i, j) = 0;
			}

			a = (err * 5) / 32;
			b = (err * 3) / 32;

			c = (err * 2) / 32;
			d = (err * 4) / 32;
			e = (err * 5) / 32;
			f = (err * 4) / 32;
			g = (err * 2) / 32;

			s = (err * 2) / 32;
			x = (err * 3) / 32;
			y = (err * 2) / 32;




			if ((i < (nH - 3)) && (j > 1) && (j < (nW - 2)))
			{
				matDith.at<uint8_t>(i + 0, j + 1) = saturated_add(matDith.at<uint8_t>(i + 0, j + 1), a);
				matDith.at<uint8_t>(i + 0, j + 2) = saturated_add(matDith.at<uint8_t>(i + 0, j + 2), b);

				matDith.at<uint8_t>(i + 1, j - 2) = saturated_add(matDith.at<uint8_t>(i + 1, j - 2), c);
				matDith.at<uint8_t>(i + 1, j - 1) = saturated_add(matDith.at<uint8_t>(i + 1, j - 1), d);
				matDith.at<uint8_t>(i + 1, j + 0) = saturated_add(matDith.at<uint8_t>(i + 1, j + 0), e);
				matDith.at<uint8_t>(i + 1, j + 1) = saturated_add(matDith.at<uint8_t>(i + 1, j + 1), f);
				matDith.at<uint8_t>(i + 1, j + 2) = saturated_add(matDith.at<uint8_t>(i + 1, j + 2), g);



				matDith.at<uint8_t>(i + 2, j - 1) = saturated_add(matDith.at<uint8_t>(i + 2, j - 1), s);
				matDith.at<uint8_t>(i + 2, j + 0) = saturated_add(matDith.at<uint8_t>(i + 2, j + 0), x);
				matDith.at<uint8_t>(i + 2, j + 1) = saturated_add(matDith.at<uint8_t>(i + 2, j + 1), y);

			}
		}
	}
	return matDith;

}

































cv::Mat Diffuser_Jarris(cv::Mat src)
{
	Mat mat = src.clone();

	EmptyCheck(mat);


	Mat matDith = getGray(mat);

	int nW = matDith.cols;
	int nH = matDith.rows;

	/* Run the 'Floyd-Steinberg' dithering algorithm ... */
	int err;
	int8_t a, b, c, d, e, f, g, w, s, x, y, z;

	auto saturated_add = [](uint8_t val1, int8_t val2) -> uint8_t
	{
		int16_t val1_int = val1;
		int16_t val2_int = val2;
		int16_t tmp = val1_int + val2_int;

		if (tmp > 255)
			return 255;
		else if (tmp < 0)
			return 0;
		else
			return tmp;
	};

	for (int i = 0; i < nH; i++)
	{
		for (int j = 0; j < nW; j++)
		{
			if (matDith.at<uint8_t>(i, j) > 127)
			{
				err = matDith.at<uint8_t>(i, j) - 255;
				matDith.at<uint8_t>(i, j) = 255;
			}
			else
			{
				err = matDith.at<uint8_t>(i, j) - 0;
				matDith.at<uint8_t>(i, j) = 0;
			}

			a = (err * 7) / 48;
			b = (err * 5) / 48;

			c = (err * 3) / 48;
			d = (err * 5) / 48;
			e = (err * 7) / 48;
			f = (err * 5) / 48;
			g = (err * 3) / 48;

			w = (err * 1) / 48;
			s = (err * 3) / 48;
			x = (err * 5) / 48;
			y = (err * 3) / 48;
			z = (err * 1) / 48;




			if ((i < (nH - 3)) && (j > 1) && (j < (nW - 2)))
			{
				matDith.at<uint8_t>(i + 0, j + 1) = saturated_add(matDith.at<uint8_t>(i + 0, j + 1), a);
				matDith.at<uint8_t>(i + 0, j + 2) = saturated_add(matDith.at<uint8_t>(i + 0, j + 2), b);

				matDith.at<uint8_t>(i + 1, j - 2) = saturated_add(matDith.at<uint8_t>(i + 1, j - 2), c);
				matDith.at<uint8_t>(i + 1, j - 1) = saturated_add(matDith.at<uint8_t>(i + 1, j - 1), d);
				matDith.at<uint8_t>(i + 1, j + 0) = saturated_add(matDith.at<uint8_t>(i + 1, j + 0), e);
				matDith.at<uint8_t>(i + 1, j + 1) = saturated_add(matDith.at<uint8_t>(i + 1, j + 1), f);
				matDith.at<uint8_t>(i + 1, j + 2) = saturated_add(matDith.at<uint8_t>(i + 1, j + 2), g);


				matDith.at<uint8_t>(i + 2, j - 2) = saturated_add(matDith.at<uint8_t>(i + 2, j - 2), w);
				matDith.at<uint8_t>(i + 2, j - 1) = saturated_add(matDith.at<uint8_t>(i + 2, j - 1), s);
				matDith.at<uint8_t>(i + 2, j + 0) = saturated_add(matDith.at<uint8_t>(i + 2, j + 0), x);
				matDith.at<uint8_t>(i + 2, j + 1) = saturated_add(matDith.at<uint8_t>(i + 2, j + 1), y);
				matDith.at<uint8_t>(i + 2, j + 2) = saturated_add(matDith.at<uint8_t>(i + 2, j + 2), z);
			}
		}
	}
	return matDith;

}
















cv::Mat Diffuser_Burkes(cv::Mat src)
{
	Mat mat = src.clone();

	EmptyCheck(mat);


	Mat matDith = getGray(mat);

	int nW = matDith.cols;
	int nH = matDith.rows;

	/* Run the 'Floyd-Steinberg' dithering algorithm ... */
	int err;
	int8_t a, b, c, d,e,f,g;

	auto saturated_add = [](uint8_t val1, int8_t val2) -> uint8_t
	{
		int16_t val1_int = val1;
		int16_t val2_int = val2;
		int16_t tmp = val1_int + val2_int;

		if (tmp > 255)
			return 255;
		else if (tmp < 0)
			return 0;
		else
			return tmp;
	};

	for (int i = 0; i < nH; i++)
	{
		for (int j = 0; j < nW; j++)
		{
			if (matDith.at<uint8_t>(i, j) > 127)
			{
				err = matDith.at<uint8_t>(i, j) - 255;
				matDith.at<uint8_t>(i, j) = 255;
			}
			else
			{
				err = matDith.at<uint8_t>(i, j) - 0;
				matDith.at<uint8_t>(i, j) = 0;
			}

			a = (err * 8) / 32;
			b = (err * 4) / 32;
			c = (err * 2) / 32;
			d = (err * 4) / 32;
			e = (err * 8) / 32;
			f = (err * 4) / 32;
			g = (err * 2) / 32;
			

			if ((i < (nH - 2)) && (j > 1) && (j < (nW - 2)))
			{
				matDith.at<uint8_t>(i + 0, j + 1) = saturated_add(matDith.at<uint8_t>(i + 0, j + 1), a);
				matDith.at<uint8_t>(i + 0, j + 2) = saturated_add(matDith.at<uint8_t>(i + 0, j + 2), b);
				matDith.at<uint8_t>(i + 1, j - 2) = saturated_add(matDith.at<uint8_t>(i + 1, j - 2), c);
				matDith.at<uint8_t>(i + 1, j - 1) = saturated_add(matDith.at<uint8_t>(i + 1, j - 1), d);
				matDith.at<uint8_t>(i + 1, j + 0) = saturated_add(matDith.at<uint8_t>(i + 1, j + 0), e);
				matDith.at<uint8_t>(i + 1, j + 1) = saturated_add(matDith.at<uint8_t>(i + 1, j + 1), f);
				matDith.at<uint8_t>(i + 1, j + 2) = saturated_add(matDith.at<uint8_t>(i + 1, j + 2), g);
				
			}
		}
	}
	return matDith;

}






Mat getGray(const Mat& mat)
{
	EmptyCheck(mat);

	if (1 == mat.channels())
		return mat;

	// 将图片转换成灰度图片
	Mat matGray;
	if (mat.channels() == 3)
	{
		cvtColor(mat, matGray, COLOR_BGR2GRAY);
		return matGray;
	}
	else if (mat.channels() == 4)
	{
		cvtColor(mat, matGray, COLOR_BGRA2GRAY);
		return matGray;
	}
	else
	{
		return mat;
	}
}
























//Floyd - Steinberg算法
//int main()
//{
//
//
//	string path1 = "D:/Vscode_Project/Img/dragon_out.png";
//	cv::Mat src_out = imread(path1);
//
//
//	string path = "D:/Vscode_Project/Img/dragon.jpg";
// 	cv::Mat src = imread(path);
//
//
//
//
//
//	Mat img_Gray;
//	cv::cvtColor(src, img_Gray, cv::COLOR_BGR2GRAY);
//
//	Mat img_Gray0 = img_Gray.clone();
//	Mat img_Gray1 = img_Gray.clone();
//
//	Mat img_dither = Diffuser(img_Gray0);
//
//	Mat img_dither1 = Diffuser(img_Gray1,1);
//
//	imshow("src_out", src_out);
//	imshow("img_dither", img_dither);
//	waitKey();
//	return 0;
//}
















cv::Mat Diffuser_FloydSteinberg(cv::Mat src)
{

	Mat matDith = src.clone();

	int nW = matDith.cols;
	int nH = matDith.rows;

	/* Run the 'Floyd-Steinberg' dithering algorithm ... */
	int err;
	int8_t a, b, c, d;

	auto saturated_add = [](uint8_t val1, int8_t val2) -> uint8_t
	{
		int16_t val1_int = val1;
		int16_t val2_int = val2;
		int16_t tmp = val1_int + val2_int;

		if (tmp > 255)
			return 255;
		else if (tmp < 0)
			return 0;
		else
			return tmp;
	};

	for (int i = 0; i < nH; i++)
	{
		for (int j = 0; j < nW; j++)
		{
			if (matDith.at<uint8_t>(i, j) > 127)
			{
				err = matDith.at<uint8_t>(i, j) - 255;
				matDith.at<uint8_t>(i, j) = 255;
			}
			else
			{
				err = matDith.at<uint8_t>(i, j) - 0;
				matDith.at<uint8_t>(i, j) = 0;
			}

			a = (err * 7) / 16;
			b = (err * 1) / 16;
			c = (err * 5) / 16;
			d = (err * 3) / 16;

			if ((i != (nH - 1)) && (j != 0) && (j != (nW - 1)))
			{
				matDith.at<uint8_t>(i + 0, j + 1) = saturated_add(matDith.at<uint8_t>(i + 0, j + 1), a);
				matDith.at<uint8_t>(i + 1, j + 1) = saturated_add(matDith.at<uint8_t>(i + 1, j + 1), b);
				matDith.at<uint8_t>(i + 1, j + 0) = saturated_add(matDith.at<uint8_t>(i + 1, j + 0), c);
				matDith.at<uint8_t>(i + 1, j - 1) = saturated_add(matDith.at<uint8_t>(i + 1, j - 1), d);
			}
		}
	}


	return matDith;
}



int get_Value(int value)
{
	if (value > 255)
	{
		value = 255;
		return value;
	}
	if (value < 0)
	{
		value = 0;
		return value;
	}
	else
	{
		return value;
	}
}


cv::Mat Diffuser(cv::Mat src)
{
	Mat img_gray0 = src.clone();
	int img_h, img_w;
	img_h = img_gray0.size().height;
	img_w = img_gray0.size().width;

	Mat img_dither = img_gray0.clone();

	int threshold = 128;


	//Mat img_undither = Mat::zeros(Size(img_w, img_h), CV_8U);
	////@ 给img_dither赋值，对img_undither二值化
	//for (int i = 0; i < img_h; i++)
	//{
	//	for (int j = 0; j < img_w; j++)
	//	{
	//		//cout << img_dither.at<uchar>(i, j) << endl;
	//		img_dither.at<uchar>(i, j) = img_gray0.at<uchar>(i, j);
	//		if (img_gray0.at<uchar>(i, j) > threshold)
	//		{
	//			img_undither.at<uchar>(i, j) = 255;
	//		}
	//		//@ 这里还有一种二值化方式，采用随机阈值进行二值化，这种也很有意思，得到的二值图像有更多的细节
	//		if (img_gray0.at<uchar>(i, j) > (rand() % 255))
	//		{
	//			img_undither.at<uchar>(i, j) = 255;
	//		}
	//	}
	//}


	for (int i = 0; i < img_h; i++)
	{
		for (int j = 0; j < img_w; j++)
		{
			int new_pix;
			int old_pix = img_dither.at<uchar>(i, j);
			if (img_dither.at<uchar>(i, j) > threshold)
			{
				new_pix = 255;
			}
			else
			{
				new_pix = 0;
			}
			//先对img_dither二值化
			img_dither.at<uchar>(i, j) = new_pix;
			int quant_err = old_pix - new_pix;
			if ((i != (img_h - 1)) && (j != 0) && (j != (img_w - 1)))
			{
				img_dither.at<uchar>(i + 1, j - 1) = get_Value(img_dither.at<uchar>(i + 1, j - 1) + quant_err * 3 / 16);
				img_dither.at<uchar>(i + 1, j + 0) = get_Value(img_dither.at<uchar>(i + 1, j + 0) + quant_err * 5 / 16);
				img_dither.at<uchar>(i + 1, j + 1) = get_Value(img_dither.at<uchar>(i + 1, j + 1) + quant_err * 1 / 16);
				img_dither.at<uchar>(i + 0, j + 1) = get_Value(img_dither.at<uchar>(i + 0, j + 1) + quant_err * 7 / 16);
			}
		}
	}


	return img_dither;
}


































//浮雕自定义探索

//int main()
//{
//
//	Mat src = Mat::zeros(Size(400, 400), CV_8UC1);
//	Mat src_one = Mat::zeros(Size(400, 400), CV_8UC1);
//	Point FirstPoint, SecondPoint, ThirdlyPoint;
//	FirstPoint = Point(100, 200);
//	SecondPoint = Point(200, 200);
//	ThirdlyPoint = Point(150, 100);
//
//
//	line(src, FirstPoint, SecondPoint, Scalar(255), 1);
//	line(src, FirstPoint, ThirdlyPoint, Scalar(255), 1);
//	line(src, SecondPoint, ThirdlyPoint, Scalar(255), 1);
//	// imshow("src",src);
//	// waitKey(0);
//	vector<vector<cv::Point>> contours;
//	vector<Vec4i> hierarchy;
//	//CV_CHAIN_APPROX_NONE  CV_CHAIN_APPROX_SIMPLE
//	findContours(src, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point());
//	drawContours(src_one, contours, 1, Scalar(255), -1, 8, hierarchy);
//
//
//	int value_px = 255;
//
//	vector<int> valueList;
//	valueList.clear();
//	valueList.push_back(value_px);
//	Mat src_Two = src_one.clone();
//
//	
//
//	while (true)
//	{
//		value_px = value_px - 20;
//
//		if (value_px < 0)
//		{
//			break;
//		}
//
//
//		src_one = Diffuser(src_Two, valueList, value_px);
//	}
//
//
//
//	Mat result0 = Relief_Gray(src_one);
//
//
//
//	imshow("src_one", result0);
//	//imshow("result0", result0);
//	//waitKey(0);
//
//	return 0;
//}







cv::Mat Diffuser(cv::Mat src, vector<int>& value_List, int value)
{
	if (value_List.size() == 0)
	{
		cout << "please push the num to value_List " << endl;;
		return Mat();
	}
	
	int findValue = value_List.back();

	cout << "findValue "<< findValue<<endl;

	cout << "value_List.size()  " << value_List.size() << endl;


	int row = src.rows;
	int col = src.cols;
	cv::Mat temp = src.clone();
	for (int i = 1; i < row - 1; ++i)
	{
		uchar* s1 = src.ptr<uchar>(i - 1);
		uchar* s2 = src.ptr<uchar>(i);
		uchar* s3 = src.ptr<uchar>(i + 1);
		uchar* t = temp.ptr<uchar>(i);
		for (int j = 1; j < (col - 1); ++j)
		{
			int Num = 0;

			for (int k = 0; k < value_List.size(); k++)
			{

				if ((int)s2[j] != value_List[k])
				{
					
					Num++;
					//cout << "Num  get Num  "<< Num << endl;
				}
			}


			if (Num == (int)value_List.size())
			{


				

				if ((s2[j - 1] == findValue) || (s2[j + 1] == findValue)|| (s1[j] == findValue) || (s3[j] == findValue))
				{
					t[j] = value;
				}
			}
		}
	}
	value_List.push_back(value);
	return temp;
}



































//单纯的视差的浮雕

// int main()
// {
//     string path = "D:/Vscode_Project/Img/dragon.jpg";
// 	cv::Mat src = imread(path);
//     cv::Mat src_gray;
// 	cvtColor(src,src_gray,CV_BGR2GRAY);

// 	Mat result0 = Relief_Gray(src_gray);
// 	Mat result_one = Relief_Gray_one(src_gray);
// 	cv::imshow("src_gray", src_gray);
// 	cv::imshow("Relief_Gray", result0);
// 	cv::imshow("result_one", result_one);
// 	waitKey(0);

// 	// cv::Mat result1 = Relief(src);
// 	// cv::Mat result2 = Sculpture(src);
// 	// cv::imshow("original", src);
// 	// cv::imshow("relief", result1);
// 	// cv::imshow("sculpture", result2);
// 	// waitKey(0);
// 	return 0;
// }





cv::Mat Relief_Gray_one(cv::Mat src)
{
	int row = src.rows;
	int col = src.cols;
	cv::Mat temp = src.clone();
	for (int i = 1; i < row - 1; ++i)
	{
		uchar* s1 = src.ptr<uchar>(i - 1);
		uchar* s2 = src.ptr<uchar>(i + 1);
		uchar* t = temp.ptr<uchar>(i);
		for (int j = 1; j < (col - 1) / 3; ++j)
		{

			int RGB = s1[3 * (j - 1)] - s2[3 * (j + 1)] + 128;
			if (RGB < 0)RGB = 0;
			if (RGB > 255)RGB = 255;
			t[3 * j] = (uchar)RGB;

		}
	}
	return temp;
}


cv::Mat Relief_Gray(cv::Mat src)
{
	int row = src.rows;
	int col = src.cols;
	cv::Mat temp = src.clone();
	for (int i = 1; i < row - 1; ++i)
	{
		uchar* s1 = src.ptr<uchar>(i - 1);
		uchar* s2 = src.ptr<uchar>(i + 1);
		uchar* t = temp.ptr<uchar>(i);
		for (int j = 1; j < (col - 1); ++j)
		{

			int RGB = s1[(j - 1)] - s2[(j + 1)] + 128;
			if (RGB < 0)RGB = 0;
			if (RGB > 255)RGB = 255;
			t[j] = (uchar)RGB;

		}
	}
	return temp;
}







// 浮雕
cv::Mat Relief(cv::Mat src)
{
	CV_Assert(src.channels() == 3);
	int row = src.rows;
	int col = src.cols;
	cv::Mat temp = src.clone();
	for (int i = 1; i < row - 1; ++i)
	{
		uchar* s1 = src.ptr<uchar>(i - 1);
		uchar* s2 = src.ptr<uchar>(i + 1);
		uchar* t = temp.ptr<uchar>(i);
		for (int j = 1; j < col - 1; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				int RGB = s1[3 * (j - 1) + k] - s2[3 * (j + 1) + k] + 128;
				if (RGB < 0)RGB = 0;
				if (RGB > 255)RGB = 255;
				t[3 * j + k] = (uchar)RGB;
			}
		}
	}
	return temp;
}

// 雕刻
cv::Mat Sculpture(cv::Mat src)
{
	CV_Assert(src.channels() == 3);
	int row = src.rows;
	int col = src.cols;




	cv::Mat temp = src.clone();
	for (int i = 1; i < row - 1; ++i)
	{
		uchar* s1 = src.ptr<uchar>(i - 1);
		uchar* s2 = src.ptr<uchar>(i + 1);
		uchar* t = temp.ptr<uchar>(i);
		for (int j = 1; j < col - 1; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				int RGB = s2[3 * (j + 1) + k] - s1[3 * (j - 1) + k] + 128;
				if (RGB < 0)RGB = 0;
				if (RGB > 255)RGB = 255;
				t[3 * j + k] = (uchar)RGB;
			}
		}
	}
	return temp;
}