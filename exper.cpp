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
        
        //Switch statement to choose the appropriate filter
        cin >> choice;
        
        switch (choice)
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
            case 7:
                detectImage();
                break;
            case 8:
                enlargeImage();
                break;
            case 9:
                shrinkImage();
                break;
            case 'b':
                shuffleImage();
                break;
            case 'c':
                blurImage();
                break;
            case 'd':
                cropImage();
                break;
            case 0:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        if (choice != 0)
        {
            // Ask if the user wants to apply another filter or save the image
            cout << "Do you want to apply another filter (Enter '1') or save the image (Enter '2')? ";
            cin >> choice;
            
            if (choice == 2)
            {
                saveImage();
                cout << "Image saved." << endl;
            }
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
    
    // Get output image file name
    cout << "Enter the name of the output image file: ";
    cin >> filename;
    
    // Add .bmp extension and save image
    strcat(filename, ".bmp");
    writeGSBMP(filename, image);
}

void blackAndWhite()
{
    loadImage();

    // Convert image to black and white
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int average = (image[i][j] + image[i][j] + image[i][j]) / 3;
            image[i][j] = average;
        }
    }

    cout << "Black and white filter applied." << endl;
}

void invertImage()
{
    loadImage();

    // Invert image colors
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = 255 - image[i][j];
        }
    }

    cout << "Invert filter applied." << endl;
}

// Implement the remaining filter functions in a similar manner

void mergeImages()
{
    loadImage();
    unsigned char image2[SIZE][SIZE];
    
    cout << "Enter the name of the second image file to load: ";
    char filename[100];
    cin >> filename;
    strcat(filename, ".bmp");
    readGSBMP(filename, image2);
    
    // Merge the two images
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int mergedValue = (image[i][j] + image2[i][j]) / 2;
            image[i][j] = mergedValue;
        }
    }
    
    cout << "Image merged." << endl;
}

void flipImage()
{
    loadImage();
    
    // Flip the image horizontally
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE / 2; j++)
        {
            unsigned char temp = image[i][j];
            image[i][j] = image[i][SIZE - 1 - j];
            image[i][SIZE - 1 - j] = temp;
        }
    }
    
    cout << "Image flipped." << endl;
}

void rotateImage()
{
    loadImage();
    unsigned char rotatedImage[SIZE][SIZE];
    
    // Rotate the image 90 degrees counter-clockwise
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            rotatedImage[j][SIZE - 1 - i] = image[i][j];
        }
    }
    
    // Copy the rotated image back to the original image array
    memcpy(image, rotatedImage, SIZE * SIZE * sizeof(unsigned char));
    
    cout << "Image rotated." << endl;
}

void darkenAndLightenImage()
{
    loadImage();
    int choice;
    cout << "Do you want to darken (Enter '1') or lighten (Enter '2') the image? ";
    cin >> choice;
    
    int factor;
    cout << "Enter the factor value (from 1 to 100): ";
    cin >> factor;
    
    // Adjust the image brightness based on the chosen factor
    if (choice == 1)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                int newValue = max(0, int(image[i][j]) - factor);
                image[i][j] = static_cast<unsigned char>(newValue);
            }
        }
        
        cout << "Image darkened." << endl;
    }
    else if (choice == 2)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                int newValue = min(255, int(image[i][j]) + factor);
                image[i][j] = static_cast<unsigned char>(newValue);
            }
        }
        
        cout << "Image lightened." << endl;
    }
    else
    {
        cout << "Invalid choice." << endl;
    }
}

void detectImage()
{
    loadImage();
    
    // Apply image edge detection algorithm
    unsigned char detectedImage[SIZE][SIZE];
    
    for (int i = 1; i < SIZE - 1; i++)
    {
        for (int j = 1; j < SIZE - 1; j++)
        {
            int gx = image[i - 1][j + 1] + 2 * image[i][j + 1] + image[i + 1][j + 1] - image[i - 1][j - 1] - 2 * image[i][j - 1] - image[i + 1][j - 1];
            int gy = image[i - 1][j - 1] + 2 * image[i - 1][j] + image[i - 1][j + 1] - image[i + 1][j - 1] - 2 * image[i + 1][j] - image[i + 1][j + 1];
            int gradient = sqrt(gx * gx + gy * gy);
            
            detectedImage[i][j] = static_cast<unsigned char>(gradient);
        }
    }
    
    // Copy the detected image back to the original image array
    memcpy(image, detectedImage, SIZE * SIZE * sizeof(unsigned char));
    
    cout << "Image edges detected." << endl;
}

void enlargeImage()
{
    loadImage();
    unsigned char enlargedImage[SIZE * 2][SIZE * 2];
    
    // Enlarge the image by doubling its size
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            enlargedImage[i * 2][j * 2] = image[i][j];
            enlargedImage[i * 2][j * 2 + 1] = image[i][j];
            enlargedImage[i * 2 + 1][j * 2] = image[i][j];
            enlargedImage[i * 2 + 1][j * 2 + 1] = image[i][j];
        }
    }
    
    // Copy the enlarged image back to the original image array
    memcpy(image, enlargedImage, SIZE * 2 * SIZE * 2 * sizeof(unsigned char));
    
    cout << "Image enlarged." << endl;
}

void shrinkImage()
{
    loadImage();
    unsigned char shrunkenImage[SIZE / 2][SIZE / 2];
    
    // Shrink the image by half its size
    for (int i = 0; i < SIZE / 2; i++)
    {
        for (int j = 0; j < SIZE / 2; j++)
        {
            unsigned char pixel1 = image[i * 2][j * 2];
            unsigned char pixel2 = image[i * 2][j * 2 + 1];
            unsigned char pixel3 = image[i * 2 + 1][j * 2];
            unsigned char pixel4 = image[i * 2 + 1][j * 2 + 1];
            
            shrunkenImage[i][j] = max(max(pixel1, pixel2), max(pixel3, pixel4));
        }
    }
    
    // Copy the shrunken image back to the original image array
    memcpy(image, shrunkenImage, SIZE / 2 * SIZE / 2 * sizeof(unsigned char));
    
    cout << "Image shrunk." << endl;
}

void shuffleImage()
{
    loadImage();
    
    // Shuffle the image pixels
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int randI = rand() % SIZE;
            int randJ = rand() % SIZE;
            
            unsigned char temp = image[i][j];
            image[i][j] = image[randI][randJ];
            image[randI][randJ] = temp;
        }
    }
    
    cout << "Image shuffled." << endl;
}

void blurImage()
{
    loadImage();
    unsigned char blurredImage[SIZE][SIZE];
    
    // Apply image blur filter
    for (int i = 1; i < SIZE - 1; i++)
    {
        for (int j = 1; j < SIZE - 1; j++)
        {
            int sum = 0;
            sum += image[i - 1][j - 1];
            sum += image[i - 1][j];
            sum += image[i - 1][j + 1];
            sum += image[i][j - 1];
            sum += image[i][j];
            sum += image[i][j + 1];
            sum += image[i + 1][j - 1];
            sum += image[i + 1][j];
            sum += image[i + 1][j + 1];
            
            blurredImage[i][j] = static_cast<unsigned char>(sum / 9);
        }
    }
    
    // Copy the blurred image back to the original image array
    memcpy(image, blurredImage, SIZE * SIZE * sizeof(unsigned char));
    
    cout << "Image blurred." << endl;
}

void cropImage()
{
    loadImage();
    int startX, startY, endX, endY;
    
    cout << "Enter the starting X coordinate of the crop area: ";
    cin >> startX;
    
    cout << "Enter the starting Y coordinate of the crop area: ";
    cin >> startY;
    
    cout << "Enter the ending X coordinate of the crop area: ";
    cin >> endX;
    
    cout << "Enter the ending Y coordinate of the crop area: ";
    cin >> endY;
    
    // Crop the image within the specified area
    unsigned char croppedImage[SIZE][SIZE];
    
    for (int i = startX; i <= endX; i++)
    {
        for (int j = startY; j <= endY; j++)
        {
            croppedImage[i - startX][j - startY] = image[i][j];
        }
    }
    
    // Copy the cropped image back to the original image array
    memcpy(image, croppedImage, (endX - startX + 1) * (endY - startY + 1) * sizeof(unsigned char));
    
    cout << "Image cropped." << endl;
}

