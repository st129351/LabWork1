//Lichkovaha Daniil
//st129351@student.spbu.ru
//Parallel
#include "BMP.h"
#include "testParal.h"
#include <iostream>
#include <string>
#include <chrono>

void testParal(BMP& img, const std::string& task) {
    auto start = std::chrono::high_resolution_clock::now(); // start

    if (task == "rotateC") {
        img.Rotate90Clockwise();
        img.Save("Rotated90Clockwise.bmp");
    } else if (task == "rotateCC") {
        img.Rotate90CounterClockwise();
        img.Save("Rotate90CounterClockwise.bmp");
    } else if (task == "blur") {
        img.GaussianBlur();
        img.Save("GaussianBlur.bmp");
    }

    auto end = std::chrono::high_resolution_clock::now(); // end
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // duration
    
    std::cout << "for " << task << " took " << dur.count() << " ms" << std::endl;
}