//Lichkovaha Daniil
//st129351@student.spbu.ru
//LabWork1
#include "BMP.h"

// BMP files usually have a header, followed by the array of pixels
BMP::BMP(const char* filename)
{
    std::ifstream inp(filename, std::ios_base::binary); // create input stream; also bin mode, because BMP files is binary data, no text
    if (!inp)
    {
        throw std::runtime_error("File isn't open!"); // method "throw" throws me an exception, which i'll catch later in "try-catch"
    }

    inp.read((char*)&header, sizeof(header)); // (char*)&header - casting to pointer to char; points to the beginning of "header" in memory
    std::cout << sizeof(header) + sizeof(info_header) + sizeof(color_header) << std::endl;
    std::cout << header.offset_data << std::endl;
    // (std::ifstream) read() - read bytes from file and write it in inp
    // 1st arg give info, where do i need to write data (memory area)
    // 2nd arg "says" take all bytes from header (quantity of bytes, which read() must read in memory area);
    // read only "header", which is in *filename (around 14 bytes) and take it in data about &header
    // method read() expect 1st arg pointer to char!!!
    if (header.file_type != 0x4D42)
    {
        throw std::runtime_error("File isn't BMP");
    }

    inp.read((char*)&info_header, sizeof(info_header));
    // read from "inp" needs data (volume sizeof(i_h)) to info_header
    std::cout << info_header.bit_count << std::endl;

    if (info_header.bit_count == 24)
    {
        inp.read((char*)&color_header, sizeof(color_header));
    }
    // now, if my image is 24-bytes, i'm also going to read inf about img's color to container("color_header")
    inp.seekg(header.offset_data, inp.beg);
    // cursor offset by "offset_data" from begin of pixels in inp
    // because now i have inf about bytes, from which begin pixels (66 string)
    data.resize(info_header.size_image);
    // resize in data-vector quantity of bytes, which need to store all pixels
    inp.read((char*)data.data(), data.size());
    // &data return adress of vector-data, data.data() return adress of 1st data-item for next writing bytes in vector
    // but 1st data-item is uint8_t, not poiter to char, which expect .read()
    // and i use .size(), because sizeof(data) is data about bytes, which occupy vector
    // .size() return data about quantity of item in "data", info_header.size_image()
}
// about cursor and inp.read()
/*
the cursor save its position after each read(), so we read from the BMP file
the headers specified in it, but at the same time we need to move the cursor to
the value specified in the headers in order to proceed to reading pixels
*/

void BMP::Rotate90Clockwise()
{
    int row_size = (info_header.width * 3 + 3) & (~3);
    std::vector<uint8_t> rotated_data(info_header.size_image);

    for (int y = 0; y < info_header.height; ++y)
    {
        for (int x = 0; x < info_header.width; ++x)
        {
            int oldIndex = y * row_size + x * 3;
            int newIndex = (info_header.width - x - 1) * ((info_header.height * 3 + 3) & (~3)) + y * 3;

            rotated_data[newIndex]     = data[oldIndex];
            rotated_data[newIndex + 1] = data[oldIndex + 1];
            rotated_data[newIndex + 2] = data[oldIndex + 2];
        }
    }

    std::swap(info_header.width, info_header.height);
    data = rotated_data;
}


void BMP::Rotate90CounterClockwise()
{
    int row_size = (info_header.width * 3 + 3) & (~3);
    std::vector<uint8_t> rotated_data(info_header.size_image);

    for (int y = 0; y < info_header.height; ++y)
    {
        for (int x = 0; x < info_header.width; ++x)
        {
            int oldIndex = y * row_size + x * 3;
            int newIndex = x * ((info_header.height * 3 + 3) & (~3)) + (info_header.height - y - 1) * 3;

            rotated_data[newIndex]     = data[oldIndex];
            rotated_data[newIndex + 1] = data[oldIndex + 1];
            rotated_data[newIndex + 2] = data[oldIndex + 2];
        }
    }

    std::swap(info_header.width, info_header.height);
    data = rotated_data;
}

void BMP::GaussianBlur()
{
    const float kernel[3][3] =
    {
        {1/16.0f, 2/16.0f, 1/16.0f},
        {2/16.0f, 4/16.0f, 2/16.0f},
        {1/16.0f, 2/16.0f, 1/16.0f}
    }; // just value for blur for each pixel; 0f - type float (in the center max weight, so the brightness of the center has more influence on the blur)
    // matrix for each pixel, and his neighbour; the more weight, the more in new pixel this color from "old pixel" (considered the color of all neighbors in the matrix)
    std::vector<uint8_t> blurred_data(data.size());
    int channels = info_header.bit_count / 8;

    for (int y = 1; y < info_header.height - 1; y++)   // some neighbours of this pixel may extend beyond the image boundaries, (matrix 3*3)
    {
        for (int x = 1; x < info_header.width - 1; x++)   // kernel should not extend beyond the boundaries of the image
        {
            for (int c = 0; c < channels; c++)
            {
                float color = 0.0f; // used to accumulate the color value after applying a GaussianBlur

                for (int ky = -1; ky <= 1; ky++)
                {
                    for (int kx = -1; kx <= 1; kx++)   // runs through all pixels in neighborhood 3*3
                    {
                        int pixel_x = x + kx;
                        int pixel_y = y + ky; // the coordinates of neighbours pixels (-1;-1) = (x-1, y-1), (0;1) = (x,y+1), ...
                        color += data[(pixel_y * info_header.width + pixel_x) * channels + c] * kernel[ky + 1][kx + 1];
                        // for each pixel, i multiply it's value by the weight
                        //from the Gaussian kernel and add result to the "color"; new color of pixel
                    }
                }
                blurred_data[(y * info_header.width + x) * channels + c] = static_cast<uint8_t>(color);
                // type of "color" isn't suitable for storage in BMP --> convert to uint8
            }
        }
    }
    data = blurred_data;
}

void BMP::Save(const char* filename)
{
    std::ofstream out(filename, std::ios_base::binary);
    if (!out)
    {
        throw std::runtime_error("Error when opening a file for writing");
    }

    out.write((char*)&header, sizeof(header));
    out.write((char*)&info_header, sizeof(info_header));

    if (info_header.bit_count == 24)
    {
        out.write((char*)&color_header, sizeof(color_header)); // update color if image has additional info about colors (f.e. alpgha-channel)
    }

    out.write((char*)data.data(), data.size()); // END!!!
}






