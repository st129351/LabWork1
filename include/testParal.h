//Lichkovaha Daniil
//st129351@student.spbu.ru
//Parallel

#ifndef TESTPARAL_H
#define TESTPARAL_H

#include <string>

/**
 * @brief Tests performance of different image processing operations
 * 
 * This function measures and reports execution time for various image processing tasks
 * including rotation and Gaussian blur. It supports the following operations:
 * - "rotateC": 90-degree clockwise rotation
 * - "rotateCC": 90-degree counter-clockwise rotation
 * - "blur": Gaussian blur effect
 * 
 * @param img Reference to BMP image object to process
 * @param task String specifying the operation to perform. Valid values:
 *             "rotateC", "rotateCC", "blur"
 * 
 * @note The processed image is automatically saved to a new file with operation-specific name:
 *       - "Rotated90Clockwise.bmp"
 *       - "Rotate90CounterClockwise.bmp" 
 *       - "GaussianBlur.bmp"
 * 
 * @throws std::runtime_error if the task parameter is invalid or if file operations fail
 * 
 * @example
 * BMP image("test.bmp");
 * testParal(image, "rotateC"); // Rotates and measures time
 * testParal(image, "blur");    // Applies blur and measures time
 */
void testParal(BMP& img, const std::string& task);

#endif