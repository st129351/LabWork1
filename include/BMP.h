//Lichkovaha Daniil
//st129351@student.spbu.ru
//Parallel
#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <vector> // dinamic array
#include <fstream>
#include <stdexcept>
#include <cstdint>

#pragma pack(push, 1) // must be single-byte alignment
struct BMPFileHeader
{
    uint16_t file_type{0x4D42}; // _t means, this isn't variable, but data type (0x4D42 the type of bmp images)
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0}; // default value for correct work
    uint32_t offset_data{0}; // image data offset from the beginning of the file
}; // first default header

struct BMPInfoHeader // must be single-byte alignment
{
    uint32_t size{0}; // size of this header in bytes
    int32_t width{0}; // width of bitmap in pixels
    int32_t height{0}; // also height
    // if positive, bottom-up, with origin in lower left corner
    // if negative, top-down, with origin in upper left corner
    uint16_t planes{1}; // the number of color planes (always 1)
    uint16_t bit_count{0}; // the number of bit per pixel
    uint32_t compression{0}; // the type of compression 0-3 no compression (i do without compression)
    uint32_t size_image{0}; // the size of image in bytes
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{0}; // the num of using colors, i want use max number of colors (use 0)
    uint32_t colors_important{0}; // if 0, all colors are required
}; // second default header

struct BMPColorHeader
{
    uint32_t red_mask{0x00ff0000}; // the color of red mask
    uint32_t blue_mask{0x000000ff}; // the color of blue mask
    uint32_t green_mask{0x0000ff00}; // the color of green mask
    uint32_t alpha_mask{0xff000000}; // the alpha channel (transparency)
    uint32_t color_space_type{0x73524742}; // the color space
    uint32_t unused[16] {0}; // reserved data for sRGB color space (massive with 16 '0')
};
#pragma pack(pop) // no longer required single-byte alignment

/**
 * @class BMP
 * @brief Class for working with BMP image files
 * 
 * Provides functionality to read, write and process BMP images.
 * Supports rotation and Gaussian blur operations with OpenMP parallelization.
 */
class BMP
{
public:
    BMPFileHeader header;
    BMPInfoHeader info_header;
    BMPColorHeader color_header;
    std::vector<uint8_t> data;
    
    /**
     * @class BMP
     * @brief Class for working with BMP image files
     * 
     * This class provides functionality to read, write and process BMP images.
     * The processing includes rotation and Gaussian blur operations.
     */
    BMP(const char* filename); // constructor; "char* filename" point to 1-st symbol from string, which i assign filename
    // this allow me use char* like a string (const string in my case)
    // compiler read char* like a string, while symbol != '\0' (end of each str)
    /**
     * @brief Rotates the image 90 degrees clockwise
     * 
     * This method rotates the image using parallel processing of rows.
     * The rotation is optimized with OpenMP for multi-core CPUs.
     * 
     * @note The method modifies the image data in-place
     */
    void Rotate90Clockwise();
    /**
     * @brief Rotates the image 90 degrees counter clockwise
     * 
     * This method rotates the image using parallel processing of rows.
     * The rotation is optimized with OpenMP for multi-core CPUs.
     * 
     * @note The method modifies the image data in-place
     */
    void Rotate90CounterClockwise();

    /**
     * @brief Applies Gaussian blur to the image
     * 
     * This method applies a 3x3 Gaussian blur filter to the image.
     * The processing is parallelized using OpenMP for better performance
     * on multi-core systems.
     * 
     * @note Edge pixels are not processed to avoid out-of-bounds access
     */
    void GaussianBlur();

    void Save(const char* filename);
};

#endif
