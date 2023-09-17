#include <stdio.h>
#include <stdlib.h>
// Structure to hold grayscale pixel data
typedef struct {
    unsigned char value;
} PixelGray;
// Function to read a PGM image into a 2D array
PixelGray** readPGM(const char* filename, int* width, int* height) {
    //write code here
    FILE* file = fopen(filename, "r"); //opens file for reading
    //below handles errors
    if (file == NULL) {
        perror("File does not exist!"); //prints error message to user
        return NULL;
    }
    else {
        printf("File opened successfully");
    }

    //The file looks like this
    //P5
    //3 3
    //255
    //000001111

    //write code to read the pgm file dimensions height and width
    char pgm[3];
    fscanf(file, "%2s", pgm);
    fscanf(file, "%d %d", width, height); //gets the width and height
    int maxGrayVal;
    fscanf(file, "%d", &maxGrayVal);
    //now when we scan again from the file we are at the binary line from above example

    //below dynamically allocates memory for an array of pointers to rows
    PixelGray **lenaMatrix = (PixelGray **)malloc(*height * sizeof(PixelGray *));
    if (lenaMatrix == NULL) {
        printf("Error: Unable to allocate memory for the rows\n");
        //return NULL;
    }
    //now allocate memory for each row to be filled
    for (int i = 0; i < *height; i++) {
        lenaMatrix[i] = (PixelGray*)malloc(*width*sizeof(PixelGray));
        if (lenaMatrix[i] == NULL) {
            printf("Error\n");
            //return NULL;
        }
    }


    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
                unsigned char val;
                fread(&val, sizeof(unsigned char), 1, file);
                lenaMatrix[i][j].value = val;
            }
        }

    // Print the matrix (take out eventually)
/*
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            printf("%3u ", lenaMatrix[i][j].value);
        }
        printf("\n");
    }
*/
    fclose(file);
    return lenaMatrix;

}



//// Function to write a 2D matrix as a PGM image

void writePGM(const char* filename, PixelGray** matrix, int* width, int* height) {
//we need to create a new file
//P5
//width, height
//255
//bits


FILE* file = fopen(filename, "w"); //opens file for writing

//below handles errors
    if (file == NULL) {
        perror("File does not exist!"); //prints error message to user
    }
    else {
        printf("File opened successfully");
    }
//lets make it a PGM file

    fprintf(file, "P5"); //specifies P5
    fprintf(file, "\n"); //new line character
    fprintf(file, "%d %d", *width, *height); //prints width and height
    fprintf(file, "\n"); //new line character
    fprintf(file, "%s", "255");
    fprintf(file, "\n"); //new line character

    //below copies data from matrix to the file

    for (int i = 0; i < *width; i++) {
        for (int j = 0; j < *height; j++) {
            //we should use fwrite to write to a file from memory
            fwrite(&(matrix[i][j].value), sizeof(unsigned char), 1,  file); //write to the file, one byte at a time
        }
    }
    fclose(file); //close file
}
//// Function to threshold the image matrix
PixelGray** threshold(PixelGray** matrix, int* width, int* height) {

    //create a new 2D matrix lenaMatrix2 with dynamically allocated storage
    PixelGray** matrix2 = (PixelGray **)malloc(*height * sizeof(PixelGray *));

    for (int i = 0; i < *height; i++) {
        matrix2[i] = (PixelGray*)malloc(*width*sizeof(PixelGray));
        if (matrix2[i] == NULL) {
            printf("Error\n");
        }
    }

    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {

            if (matrix[i][j].value > 80) { //if original value is greater than threshold
                matrix2[i][j].value = 255; //set new value to black
            }
            else {
                matrix2[i][j].value = 0; //else set to white (0)
            }

            }
        }
    //prints thresholded matrix2 (test)
/*
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            printf("%3u ", matrix2[i][j].value);
        }
        printf("\n");
    }
    */
    return matrix2;

}

//write code here
//
//// Function to rotate the image matrix
//PixelGray** rotate(PixelGray** matrix, int* width, int* height);
PixelGray** rotate(PixelGray** matrix, int* width, int* height) {

    //below dynamically allocates storage for the matrix we want to rotate with swapped rows and columns
    PixelGray** matrix3 = (PixelGray **)malloc(*width * sizeof(PixelGray *));

    for (int i = 0; i < *height; i++) {
        matrix3[i] = (PixelGray*)malloc(*height*sizeof(PixelGray));
        if (matrix3[i] == NULL) {
            printf("Error\n");
        }
    }

    //below conducts matrix transpose (swapping rows and columns)
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
                matrix3[j][i].value = matrix[i][j].value; //swap i and j (row and column) from matrix passed in
            }
        }

    //print matrix3 (test)

    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            printf("%3u ", matrix3[i][j].value);
        }
        printf("\n");
    }

    return matrix3;

}

//main function - DO NOT MODIFY
int main() {
    int width, height; // variable to hold width and height. Use reference in other functions
    PixelGray** image_original = readPGM("lenna.pgm", &width, &height);

// Now you have the grayscale image data in the 'image_original' 2D array
// Access pixel data using image[row][col].value
// For example, to access the pixel at row=2, col=3:
// unsigned char pixel_value = image[2][3].value;
// Create a new 2D array 'image_thresh' to store the threshold image
    PixelGray** image_thresh = threshold(image_original, &width, &height);
//write the image data as "threshold.pgm"
    writePGM("threshold.pgm", image_thresh, &width, &height);
// Create a new 2D array 'image_rotate' to store the rotated image
    PixelGray** image_rotate = rotate(image_original, &width, &height);
//write the image data as "rotate.pgm"
    writePGM("rotate.pgm", image_rotate, &width, &height);
    image_rotate = rotate(image_rotate, &width, &height);
//write the image data as "rotate_again.pgm"
    writePGM("rotate_again.pgm", image_rotate, &width, &height);
// Free the allocated memory when you're done
    for (int i = 0; i < height; ++i) {
        free(image_original[i]);
        free(image_thresh[i]);
        free(image_rotate[i]);
    }
    free(image_original);
    free(image_thresh);
    free(image_rotate);
    return 0;
}
