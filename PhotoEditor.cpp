#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];


void loadImage () {
    char imageFileName[100];


    cout << "Enter the source image file name: ";
    cin >> imageFileName;



    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage () {
    char imageFileName[100];


    cout << "Enter the target image file name: ";
    cin >> imageFileName;



    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void doSomethingForImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {



            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;

        }
    }
}


int main(){

    loadImage();
    doSomethingForImage();
    saveImage();
    return 0;
}