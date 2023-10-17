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
bool isModified = false;

void loadImage();
void saveImage();
void blackAndWhite();
void invertImage();
void mergeImages();
void flipImage();
void rotateImage();
void darkenAndLightenImage();
void detectImage();
void enlargeImage();
void shrinkImage();
void shuffleImage();
void blurImage();
void cropImage();

int main()
{
    int choice;
    
    do
    {
        cout << "Choose a filter to apply to the image:" << endl;
        cout << "1. Black and White Image" << endl;
        cout << "2. Invert Image" << endl;
        cout << "3. Merge Images" << endl;
        cout << "4. Flip Image" << endl;
        cout << "5. Rotate Image" << endl;
        cout << "6. Darken and Lighten Image" << endl;
        cout << "7. Detect Image" << endl;
        cout << "8. Enlarge Image" << endl;
        cout << "9. Shrink Image" << endl;
        cout << "b. Shuffle Image" << endl;
        cout << "c. Blur Image" << endl;
        cout << "d. Crop Image" << endl;
        cout << "0. Exit" << endl;
        
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                blackAndWhite();
                isModified = true;
                break;
            case 2:
                invertImage();
                isModified = true;
                break;
            case 3:
                mergeImages();
                isModified = true;
                break;
            case 4:
                flipImage();
                isModified = true;
                break;
            case 5:
                rotateImage();
                isModified = true;
                break;
            case 6:
                darkenAndLightenImage();
                isModified = true;
                break;
            case 7:
                detectImage();
                isModified = true;
                break;
            case 8:
                enlargeImage();
                isModified = true;
                break;
            case 9:
                shrinkImage();
                isModified = true;
                break;
            case 'b':
                shuffleImage();
                isModified = true;
                break;
            case 'c':
                blurImage();
                isModified = true;
                break;
            case 'd':
                cropImage();
                isModified = true;
                break;
            case 0:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        if (isModified && choice != 0)  // Check if the image is modified and option is not 0
        {
            int filterChoice;

            // Ask if the user wants to apply another filter or save the image
            cout << "Do you want to apply another filter (Enter '1') or save the image (Enter '2')? ";
            cin >> filterChoice;

            if (filterChoice == 2)
            {
                saveImage();
                cout << "Image saved." << endl;
                isModified = false; // Reset the modified flag
            }
        }
        else if (!isModified && choice != 0)  // Check if the image is not modified and option is not 0
        {
            cout << "No modifications made to the image." << endl;
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