// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: assigment.cpp
// Last Modification Date: 10/10/2023
// Author1 and ID and Group: Malak Mahmoud Gamil ID:20221161 Email:malakgami098@gmail.com
// Author2 and ID and Group: Mostafa Mohamed Fathy ID:20221154 Email:mostafa528999@gmail.com
// Author3 and ID and Group: Salma Mohamed Mostafa ID:20221074 Email:salmaalhewehy@gmail.com
// Purpose:Solving assigment 1
 #include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage();
void saveImage();
void blackAndWhite();
void invertImage();
void mergeImages();
void flipImage();
void rotateImage();
void darkenAndLightenImage();
int main()
{
    int choice;
    bool imageLoaded = false;

    do
    {
        cout << "Choose an option:" << endl;
        cout << "1. Load image" << endl;
        cout << "2. Apply filter" << endl;
        cout << "3. Save image" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            loadImage();
            imageLoaded = true;
            break;
        case 2:
            if (!imageLoaded)
            {
                cout << "Error: No image loaded. Please load an image first." << endl;
            }
            else
            {
                int filterChoice;
                cout << "Choose a filter to apply to the image:" << endl;
                cout << "1. Black and White" << endl;
                cout << "2. Invert" << endl;
                cout << "3. Merge with another image" << endl;
                cout << "4. Flip" << endl;
                cout << "5. Rotate" << endl;
                cout << "6. Darken and Lighten" << endl;
                cin >> filterChoice;

                switch (filterChoice)
                {
                case 1:
                    blackAndWhite();
                    break;
                case 2:
                    invertImage();
                    break;
                case 3:
                    mergeImages();
                    break;
                case 4:
                    flipImage();
                    break;
                case 5:
                    rotateImage();
                    break;
                case 6:
                    darkenAndLightenImage();
                    break;
                default:
                    cout << "Invalid filter choice. Please try again." << endl;
                    break;
                }
            }
            break;
        case 3:
            if (!imageLoaded)
            {
                cout << "Error: No image loaded. Please load an image first." << endl;
            }
            else
            {
                saveImage();
                cout << "Image saved." << endl;
            }
            break;
        case 0:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}

void loadImage()
{
    char filename[100];
    // Get gray scale image file name
    cout << "Enter the name of the image file to load: ";
    cin >> filename;
    // Add to it .bmp extension and load image
    strcat(filename, ".bmp");
    readGSBMP(filename, image);
}

void saveImage()
{
    char filename[100];
    // Get gray scale image target file name
    cout << "Enter the name of the file to save the image to: ";
    cin >> filename;
    // Add to it .bmp extension and load image
    strcat(filename, ".bmp");
    writeGSBMP(filename, image);
}
//This function converts to BW the image by using the average of the pixels and sets each pixel to either black or white depending on whether its value is above or below the average
void blackAndWhite()
{
    loadImage();
    int sum = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            sum += image[i][j];
        }
    }
    int average = sum / (SIZE * SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (image[i][j] > average)
            {
                image[i][j] = 255;
            }
            else
            {
                image[i][j] = 0;
            }
        }
    }
    
}
// this function inverts the colors of the image by subtracting each pixel value from 255 to obtain the inverted color value
void invertImage()
{
    loadImage();
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = 255 - image[i][j];
        }
    }
    
}
// this function merges two images by calculating the average of the two pixel values for each corresponding pixel. It then sets the pixel value of the current image to this average
void mergeImages()
{
    loadImage();
    char filename[100];
    // Get gray scale image file name to merge with
    cout << "Enter the name of the image file to merge with: ";
    cin >> filename;
    // Add to it .bmp extension
    strcat(filename, ".bmp");
    unsigned char otherImage[SIZE][SIZE];
    readGSBMP(filename, otherImage);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = (image[i][j] + otherImage[i][j]) / 2;
        }
    }
    
}
// this function flips the image  horizontally or vertically. It prompts the user to choose a flip direction (horizontal or vertical) and flips the image accordingly by swapping the pixel values of corresponding pixels on either side of the image
void flipImage()
{
    loadImage();
    int choice;
    cout << "Choose a flip direction:" << endl;
    cout << "1. Horizontal" << endl;
    cout << "2. Vertical" << endl;
    cin >> choice;
    if (choice == 1)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                int temp = image[i][j];
                image[i][j] = image[i][SIZE - j - 1];
                image[i][SIZE - j - 1] = temp;
            }
        }
    }
    else if (choice == 2)
    {
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                int temp = image[i][j];
                image[i][j] = image[SIZE - i - 1][j];
                image[SIZE - i - 1][j] = temp;
            }
        }
    }
    else
    {
        cout << "Invalid choice. No flip performed." << endl;
        return;
    }
    
}
// this function rotates the image by 90, 180, or 270 degrees clockwise. It prompts the user to choose a rotation angle and rotates the image accordingly by copying the pixel values to a temporary array and then copying them back to the original array in the rotated positions.
void rotateImage()
{
    loadImage();
    int choice;
    cout << "Choose a rotation angle:" << endl;
    cout << "1. 90 degrees clockwise" << endl;
    cout << "2. 180 degrees clockwise" << endl;
    cout << "3. 270 degrees clockwise" << endl;
    cin >> choice;
    unsigned char temp[SIZE][SIZE];
    if (choice == 1)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                temp[j][SIZE - i - 1] = image[i][j];
            }
        }
    }
    else if (choice == 2)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                temp[SIZE - i - 1][SIZE - j - 1] = image[i][j];
            }
        }
    }
    else if (choice == 3)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                temp[SIZE - j - 1][i] = image[i][j];
            }
        }
    }
    else
    {
        cout << "Invalid choice. No rotation performed." << endl;
        return;
    }
    memcpy(image, temp, sizeof(temp));
    
}
// this function  allows the user to darken or lighten the loaded image by 50%.
void darkenAndLightenImage()
{
    loadImage();
    // it displays a menu with two options: "1. Darken by 50%" and "2. Lighten by 50%". The user can choose an option by entering the corresponding number.
    int choice;
    cout << "Choose a brightness adjustment:" << endl;
    cout << "1. Darken by 50%" << endl;
    cout << "2. Lighten by 50%" << endl;
    cin >> choice;
    // he function loops through every pixel in the image and divides its value by 2, effectively reducing its brightness by 50%
    if (choice == 1)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] /= 2;
            }
        }
    }
    // the function loops through every pixel in the image and multiplies its value by 2, but caps the maximum value at 255 to prevent overflow. This effectively increases the brightness of the image by 50%.
    else if (choice == 2)
    {
        for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
        image[i][j] = min(image[i][j] * 2, 255);
    }
}
    } else {
        cout << "Invalid choice. No adjustment performed." << endl;
        return;
    }
    
}