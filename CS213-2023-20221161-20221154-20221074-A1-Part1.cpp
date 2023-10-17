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
        image[i][j] = (image[i][j]+(255-image[i][j]))/2;
    }
}
    } else {
        cout << "Invalid choice. No adjustment performed." << endl;
        return;
    }
    
}
void detectImage()
{
  // Create a new image to store the edges
  unsigned char edges[SIZE][SIZE];
  // Set the background pixels to white
  memset(edges, 255, sizeof(edges));
  
  // Iterate over each pixel in the image
  for (int i = 1; i < SIZE - 1; i++)
  {
    for (int j = 1; j < SIZE - 1; j++)
    {
      // Calculate the gradient magnitude using the Sobel operator
      int gx = image[i - 1][j + 1] + 2 * image[i][j + 1] + image[i + 1][j + 1]
             - image[i - 1][j - 1] - 2 * image[i][j - 1] - image[i + 1][j - 1];
      int gy = image[i + 1][j - 1] + 2 * image[i + 1][j] + image[i + 1][j + 1]
             - image[i - 1][j - 1] - 2 * image[i - 1][j] - image[i - 1][j + 1];
      int gradient = sqrt(gx * gx + gy * gy);
      
      // Set the edge pixel in the edges image as black
      if (gradient > 128) {
         edges[i][j] = 0;
      }
    }
  }
  memcpy(image, edges, sizeof(image));
  }
  void enlargeImage() {
  int region;
  cout << "Enter the region to enlarge (1, 2, 3, or 4): ";
  cin >> region;

  int startX, startY;
  switch (region) {
    case 1:
      startX = 0;
      startY = 0;
      break;
    case 2:
      startX = 0;
      startY = SIZE / 2;
      break;
    case 3:
      startX = SIZE / 2;
      startY = 0;
      break;
    case 4:
      startX = SIZE / 2;
      startY = SIZE / 2;
      break;
    default:
      cout << "Invalid region. Exiting..." << endl;
      return;
  }

  unsigned char enlargedImage[SIZE][SIZE];
  for (int i = startX; i < startX + SIZE / 2; i++) {
    for (int j = startY; j < startY + SIZE / 2; j++) {
      int newX = 2 * (i - startX);
      int newY = 2 * (j - startY);

      enlargedImage[newX][newY] = image[i][j];
      enlargedImage[newX][newY + 1] = image[i][j];
      enlargedImage[newX + 1][newY] = image[i][j];
      enlargedImage[newX + 1][newY + 1] = image[i][j];
    }
  }

  memcpy(image, enlargedImage, sizeof(enlargedImage));
}
 void shrinkImage() 
 {
   int shrinkFactor;
   cout << "Enter the shrink factor (2, 3, or 4): ";
   cin >> shrinkFactor;

   if (shrinkFactor < 2 || shrinkFactor > 4) {
       cout << "Invalid shrink factor! Please choose 2, 3, or 4." << endl;
       return;
   }

   int newSize = SIZE / shrinkFactor;
   unsigned char shrunkImage[newSize][newSize];

   for (int i = 0; i < newSize; i++) {
       for (int j = 0; j < newSize; j++) {
           unsigned int sum = 0;
           for (int x = 0; x < shrinkFactor; x++) {
               for (int y = 0; y < shrinkFactor; y++) {
                   sum += image[i * shrinkFactor + x][j * shrinkFactor + y];
               }
           }
           shrunkImage[i][j] = sum / (shrinkFactor * shrinkFactor);
       }
   }

   // Copy the shrunk image back to the original image array
   for (int i = 0; i < newSize; i++) {
       for (int j = 0; j < newSize; j++) {
           image[i][j] = shrunkImage[i][j];
       }
   }
   // Fill the remaining portion of the image with white pixels
   for (int i = newSize; i < SIZE; i++) {
       for (int j = 0; j < SIZE; j++) {
           image[i][j] = 255; // White pixel value
       }
   }

   for (int j = newSize; j < SIZE; j++) {
       for (int i = 0; i < SIZE; i++) {
           image[i][j] = 255; // White pixel value
       }
   }
 }
   void shuffleImage() {
  int order[4];

  // Get the order of the quarters from the user
  cout << "Enter the order of the quarters (from 0 to 3):" << endl;
  for (int i = 0; i < 4; i++) {
    cout << "Quarter " << i << ": ";
    cin >> order[i];
  }

  // Validate the input order
  bool validOrder = true;
  bool selected[4] = {false};

  for (int i = 0; i < 4; i++) {
    if (order[i] < 0 || order[i] > 3 || selected[order[i]]) {
      validOrder = false;
      break;
    }
    selected[order[i]] = true;
  }

  if (!validOrder) {
    cout << "Invalid order. Exiting..." << endl;
    return;
  }

  // Calculate the size of each quarter
  int quarterSize = SIZE / 2;

  // Create a new image to store the combined quarters
  unsigned char combinedImage[SIZE][SIZE];

  // Combine the quarters based on user-defined order
  for (int i = 0; i < 4; i++) {
    int srcX = (order[i] % 2) * quarterSize;
    int srcY = (order[i] / 2) * quarterSize;

    for (int x = 0; x < quarterSize; x++) {
      for (int y = 0; y < quarterSize; y++) {
        int destX = x + (i % 2) * quarterSize;
        int destY = y + (i / 2) * quarterSize;
        combinedImage[destX][destY] = image[srcX + x][srcY + y];
      }
    }
  }

  // Copy the combined image back to the original image
  memcpy(image, combinedImage, sizeof(combinedImage));
}
void blurImage()
{
    // Make blur image
    // This filter produces a blurry version of the image
    for (int y = 2; y < SIZE - 2; y++)
    {
        for (int x = 2; x < SIZE - 2; x++)
        {
            // Apply average filter to blur the image
            int sum = 0;
            sum += image[y - 2][x - 2];
            sum += image[y - 2][x - 1];
            sum += image[y - 2][x];
            sum += image[y - 2][x + 1];
            sum += image[y - 2][x + 2];
            sum += image[y - 1][x - 2];
            sum += image[y - 1][x - 1];
            sum += image[y - 1][x];
            sum += image[y - 1][x + 1];
            sum += image[y - 1][x + 2];
            sum += image[y][x - 2];
            sum += image[y][x - 1];
            sum += image[y][x];
            sum += image[y][x + 1];
            sum += image[y][x + 2];
            sum += image[y + 1][x - 2];
            sum += image[y + 1][x - 1];
            sum += image[y + 1][x];
            sum += image[y + 1][x + 1];
            sum += image[y + 1][x + 2];
            sum += image[y + 2][x - 2];
            sum += image[y + 2][x - 1];
            sum += image[y + 2][x];
            sum += image[y + 2][x + 1];
            sum += image[y + 2][x + 2];

            image[y][x] = sum / 25; // Divide by 25 (5x5 kernel size)
        }
    }
}
void cropImage() {
  int x, y, l, w;

  // Get cropping parameters from user
  cout << "Enter x position: ";
  cin >> x;
  cout << "Enter y position: ";
  cin >> y;
  cout << "Enter length: ";
  cin >> l;
  cout << "Enter width: ";
  cin >> w;

  // Crop the image
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (i < x || i >= (x + l) || j < y || j >= (y + w)) {
        // Set pixels outside the cropped region to white (255)
        image[i][j] = 255;
      }
    }
  }

}



  
 
