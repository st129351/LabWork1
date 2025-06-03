//Lichkovaha Daniil
//st129351@student.spbu.ru
//Parallel
#include "BMP.h"
#include <iostream>
#include <stdexcept>
#include <omp.h>
#include "testParal.h"


int main()
{
    try
    {
        BMP image1("pictures/start1.bmp");
        BMP image2("pictures/start2.bmp");

        std::cout << "------" << std::endl;
        std:: cout << "1st image: " << std::endl;
        std:: cout << "1 thread: " << std::endl;

        omp_set_num_threads(1);
        testParal(image1, "rotateC");
        testParal(image1, "rotateCC");
        testParal(image1, "blur");

        std::cout << "------" << std::endl;
        std:: cout << "2nd image: " << std::endl;
        std:: cout << "1 thread: " << std::endl;
        omp_set_num_threads(1);
        testParal(image2, "rotateC");
        testParal(image2, "rotateCC");
        testParal(image2, "blur");


        std::cout << "------" << std::endl;
        std::cout << "------" << std::endl;
        std:: cout << "1st image: " << std::endl;
        std:: cout << "4 thread: " << std::endl;

        omp_set_num_threads(4);
        testParal(image1, "rotateC");
        testParal(image1, "rotateCC");
        testParal(image1, "blur");

        std::cout << "------" << std::endl;
        std:: cout << "2nd image: " << std::endl;
        std:: cout << "4 thread: " << std::endl;
        omp_set_num_threads(4);
        testParal(image2, "rotateC");
        testParal(image2, "rotateCC");
        testParal(image2, "blur");
    }
    catch(const std::exception &ex)
    {
        std::cout << "ERROR:" << std::endl;
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}