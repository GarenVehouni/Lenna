# Lenna
The readPGM function reads a PGM image file and stores it in a 2D array of PixelGray structures. It also returns the width and height of the image.
PixelGray** readPGM(const char* filename, int* width, int* height);
----------------------
The writePGM function writes a 2D array of PixelGray structures as a PGM image to a file.
void writePGM(const char* filename, PixelGray** matrix, int* width, int* height);
----------------------
The threshold function takes a grayscale image and creates a new binary image by setting pixels above a threshold value to 255 (black) and pixels below the threshold to 0 (white)
PixelGray** threshold(PixelGray** matrix, int* width, int* height);
----------------------
The rotate function rotates a grayscale image by 90 degrees by swapping rows and columns.
PixelGray** rotate(PixelGray** matrix, int* width, int* height);
----------------------
This code is licensed under the MIT License - see the LICENSE file for details.
