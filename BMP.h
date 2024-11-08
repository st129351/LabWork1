//Lichkovaha Daniil
//st129351@student.spbu.ru
//LabWork1
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
#pragma pack(pop) // no longer required single-byte alignment

struct BMPColorHeader
{
	uint32_t red_mask{0x00ff0000}; // the color of red mask
	uint32_t blue_mask{0x000000ff}; // the color of blue mask
	uint32_t green_mask{0x0000ff00}; // the color of green mask
	uint32_t alpha_mask{0xff000000}; // the alpha channel (transparency)
	uint32_t color_space_type{0x73524742}; // the color space
	uint32_t unused[16]{0}; // reserved data for sRGB color space (massive with 16 '0')
};

class BMP
{
public:
	BMPFileHeader header;
	BMPInfoHeader info_header;
	BMPColorHeader color_header;
	std::vector<uint8_t> data; 

	BMP(const char* filename); // constructor; "char* filename" point to 1-st symbol from string, which i assign filename
	// this allow me use char* like a string (const string in my case)
	// compiler read char* like a string, while symbol != '\0' (end of each str)
	void Rotate90Clockwise();
	void Rotate90CounterClockwise();
	void GaussianBlur();
	void Save(const char* filename);
};

#endif
