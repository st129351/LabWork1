//Lichkovaha Daniil
//st129351@student.spbu.ru
//LabWork1
#include "BMP.h"

int main() 
{
	try 
	{
		BMP image("start.bmp");

		image.Rotate90Clockwise();
		image.Save("Rotated90Clockwise.bmp");

		image.Rotate90CounterClockwise();
		image.Save("Rotate90CounterClockwise.bmp");

		image.GaussianBlur();
		image.Save("GaussianBlur.bmp");

		std::cout << "Image procecssing was successful!" << std::endl;
		std::cout << "All modified files were created!" << std::endl;
	}
	catch(const std::exception &ex)
	{
		std::cout << "ERROR:" << std::endl;
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}