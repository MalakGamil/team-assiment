#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage();
void saveImage();
void mirrorImage();
void mirrorLeftRight();
void mirrorRightLeft();
void mirrorUpDown();
void mirrorDownUp();

int main()
{
    loadImage();
    mirrorImage();
    saveImage();
    return 0;
}

void loadImage()
{
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add .bmp extension and load the image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage()
{
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add .bmp extension and save the image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void mirrorLeftRight()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE / 2; j++)
        {
            unsigned char temp = image[i][j];
            image[i][j] = image[i][SIZE - 1 - j];
            image[i][SIZE - 1 - j] = temp;
        }
    }
}

void mirrorRightLeft()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = SIZE - 1; j >= SIZE / 2; j--)
        {
            unsigned char temp = image[i][j];
            image[i][j] = image[i][SIZE - 1 - j];
            image[i][SIZE - 1 - j] = temp;
        }
    }
}

void mirrorUpDown()
{
    for (int i = 0; i < SIZE / 2; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            unsigned char temp = image[i][j];
            image[i][j] = image[SIZE - 1 - i][j];
            image[SIZE - 1 - i][j] = temp;
        }
    }
}

void mirrorDownUp()
{
    for (int i = SIZE - 1; i >= SIZE / 2; i--)
    {
        for (int j = 0; j < SIZE; j++)
        {
            unsigned char temp = image[i][j];
            image[i][j] = image[SIZE - 1 - i][j];
            image[SIZE - 1 - i][j] = temp;
        }
    }
}

void mirrorImage()
{
    char mirrorSide;

    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
    cin >> mirrorSide;

    switch (mirrorSide)
    {
    case 'l':
        mirrorLeftRight();
        break;
    case 'r':
        mirrorRightLeft();
        break;
    case 'u':
        mirrorUpDown();
        break;
    case 'd':
        mirrorDownUp();
        break;
    default:
        cout << "Invalid side" << endl;
    }
}


    