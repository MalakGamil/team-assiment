#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char rotate[SIZE][SIZE][RGB];
void loadImage();
void saveImage();
void convertImageToGray();
void convertImageToBlackAndWhiteImage();
void Invert();
void mergeImage();
void loadSecondImage();
void flipImage();
void darkenImage();
void rotateImage(int &degreeOfRotate);  
void rotate_180_degree();  
void rotate_90_degree();  
void rotate_270_degree();  
void saveRotate();
void lightenImage();
void detectImageEdges();
void EnlargeImage(int &quarter); 
void EnlargeImage1();  
void EnlargeImage2();  
void EnlargeImage3();  
void EnlargeImage4();  
void shrinkAhalfImage();
void shrinkAthirdImage();
void shrinkQuarterImage();
void mirrorImage();
void mirrorDownUp();
void mirrorUpDown();
void mirrorRightLeft();
void mirrorLeftRight();
void shuffleImage1(int &a);  
void shuffleImage2(int &b); 
void shuffleImage3(int &c);  
void shuffleImage4(int &d); 
void blurImage();
void cropImage();

int main()
{
    char choose = ' ';
    while (choose != '0')
    {   
        cout << "Please select a filter to apply or 0 to exit: " << endl;
        cout << "1- Black & White Filter" << endl;
        cout << "2- Invert Filter" << endl;
        cout << "3- Merge Filter" << endl;
        cout << "4- Flip Image" << endl;
        cout << "5- Rotate Image" << endl;
        cout << "6- Darken and Lighten Image" << endl;
        cout << "7- Detect Image Edges" << endl;
        cout << "8- Enlarge Image" << endl;
        cout << "9- Shrink Image" << endl;
        cout << "a- Mirror 1/2 Image" << endl;
        cout << "b- Shuffle Image" << endl;
        cout << "c- Blur Image" << endl;
        cout << "d- Crop Image" << endl;
        cout << "s- Save the image to a file" << endl;
        cout << "0- Exit" << endl;
        cin >> choose;
        if (choose == '1')
        {
            loadImage();
            convertImageToBlackAndWhiteImage();
            saveImage();
        } else if (choose == '2')
        {
            loadImage();
            Invert();
            saveImage();
        } else if (choose == '3')
        {
            loadImage();
            loadSecondImage();
            mergeImage();
            saveImage();
        } else if (choose == '4')
        {
            loadImage();
            flipImage();
            saveImage();
        } else if (choose == '5')
        {
            int degreeOfRotate;
            cout << "Rotate (90), (180) or (270) degree? ";
            cin >> degreeOfRotate;
            loadImage();
            rotateImage(degreeOfRotate);
            saveRotate();
        } else if (choose == '6')
        {
            char choose1;
            cout << "do you want to (d)arken or (l)ighten? ";
            cin >> choose1;
            loadImage();
            if (choose1 == 'l')
            {
                lightenImage();
            } else if (choose1 == 'd')
            {
                darkenImage();
            } else
            {
                cout << "invalid";
            }
            saveImage();
        } else if (choose == '7')
        {
            loadImage();
            detectImageEdges();
            saveImage();
            cout << '7' << endl;
        } else if (choose == '8')
        {
            int quarter;
            cout << "which one of the four quarters do you want to get bigger ? ";
            cin >> quarter;
            loadImage();
            EnlargeImage(quarter);
            saveRotate();

        } else if (choose == '9')
        {
            string choose;
            cout << "Shrink to 1/2, 1/3 or 1/4: ";
            cin >> choose;
            loadImage();
            if (choose == "1/2")
            {
                shrinkAhalfImage();
            } else if (choose == "1/3")
            {
                shrinkAthirdImage();
            } else if (choose == "1/4")
            {
                shrinkQuarterImage();
            } else
            {
                cout << "invalid";
            }
            saveRotate();
        } else if (choose == 'a')
        {
            loadImage();
            mirrorImage();
            saveImage();
        } else if (choose == 'b')
        {
            int a, b, c, d;
            cout << "which order do you want : ";
            cin >> a >> b >> c >> d;
            loadImage();
            shuffleImage1(a);
            shuffleImage2(b);
            shuffleImage3(c);
            shuffleImage4(d);
            saveRotate();
        } else if (choose == 'c')
        {
            loadImage();
            blurImage();
            saveImage();
            
        }else if (choose == 'd')
        {
            loadImage();
            cropImage();
            saveImage();
        }else if (choose == 's')
        {
            loadImage();
            saveImage();
        }else
        {
            cout << "See you later" << endl;
            return 0;
        }
    }
    return 0;
}
void loadImage()
{
    char imageFileName[100];
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to image file name .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
void saveImage()
{
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to image file name .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}
// definition of function for convert the image to gray to use it in 2 Filters (1 and 7)
void convertImageToGray()
{
    double gray;
    // 2 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; ++i) // loop for rows
    {
        for (int j = 0; j < SIZE; ++j) // loop for columns
        {
            // equation for percentage of (red, green and blue) in gray image
            // to convert all pixels to gray scale
            gray = (((image[i][j][0]) * 0.3) + ((image[i][j][1]) * 0.59) + ((image[i][j][2]) * 0.11));
            // assign the value of the gray to all pixels
            image[i][j][0] = gray;
            image[i][j][1] = gray;
            image[i][j][2] = gray;
        }
    }
}
void convertImageToBlackAndWhiteImage()
{
    // call the function of convertImageToGray
    // to make the convert easier
    convertImageToGray();
    // nested 3 for loops to loop each pixel
    for (int i = 0; i < SIZE; ++i) // loop for rows
    {
        for (int j = 0; j < SIZE; ++j) // loop for columns
        {
            for (int k = 0; k < RGB; ++k) // loop for colour
            {
                // if the value of pixel greater than 127 (that refer to the level of colour in that pixel is low )
                // else (that refer to the level of colour in that pixel is high )
                if (image[i][j][k] > 127) {
                    // convert the pixel of image to white
                    image[i][j][k] = 255;
                } else {
                    // convert the pixel of image to black
                    image[i][j][k] = 0;
                }
            }
        }
    }
}
void Invert()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; ++i) // loop for rows
    {
        for (int j = 0; j < SIZE; ++j) // loop for columns
        {
            for (int k = 0; k < RGB; ++k) // loop for colour
            {
                // subtract from 255 the value of pixel to invert the image
                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}

// definition of function for load the second image that will use in merge image
void loadSecondImage()
{
    char image2FileName[100];
    cout << "Enter the source image file name of image2: ";
    cin >> image2FileName;
    // Add to image file name .bmp extension and load image
    strcat(image2FileName, ".bmp");
    readRGBBMP(image2FileName, image2);
}
void mergeImage()
{
    // initialize average matrix
    int avg[SIZE][SIZE][RGB];
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; ++i) // loop for rows
    {
        for (int j = 0; j < SIZE; ++j) // loop for columns
        {
            for (int k = 0; k < RGB; ++k)// loop for colour
            {
                // get the average of the pixels of the two images
                avg[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
                image[i][j][k] = avg[i][j][k];
            }
        }
    }
}
void flipImage()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; ++i) // loop for rows
    {
        for (int j = 0, a = SIZE - 1; j < a; j++, a--) // loop for columns
        {
            for (int k = 0; k < RGB; ++k) // loop for colour
            {
                // swap each pixel to get the flip image
                swap(image[j][i][k], image[a][i][k]);
            }
        }
    }
}
void rotate_180_degree()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; i++) // loop for rows
    {
        for (int j = 0; j < SIZE; j++) // loop for columns
        {
            for (int k = 0; k < RGB; k++) // loop for colour
            {
                // subtract elements from the size to flip the image.and save it in new image.
                rotate[SIZE - i][SIZE - j][k] = image[i][j][k];
            }
        }
    }
}
void rotate_90_degree()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; i++) // loop for rows
    {
        for (int j = 0; j < SIZE; j++) // loop for columns
        {
            for (int k = 0; k < RGB; k++) // loop for colour
            {
                // subtract row from the size to rotate image by 90 degree.and save it in new image.
                rotate[i][j][k] = image[SIZE - j][i][k];
            }
        }
    }
}
void rotate_270_degree()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; i++) // loop for rows
    {
        for (int j = 0; j < SIZE; j++) // loop for columns
        {
            for (int k = 0; k < RGB; k++) // loop for colour
            {
                // subtract column from the size to rotate image by 270 degree. and save it in new image.
                rotate[i][j][k] = image[j][SIZE - i][k];
            }
        }
    }
}
// definition of function for rotateImage
void rotateImage(int &degreeOfRotate)
{
    // if the user want to rotate the image 90 degree call the function rotate_90_degree
    // if the user want to rotate 180 degree call the function rotate_180_degree
    // if the user want to rotate 2700 degree call the function rotate_270_degree
    if (degreeOfRotate == 90)
    {
        rotate_90_degree();
    } else if (degreeOfRotate == 180)
    {
        rotate_180_degree();
    } else if (degreeOfRotate == 270)
    {
        rotate_270_degree();
    } else
    {
        cout << "invalid degree" << endl;
    }
}
void saveRotate()
{
    char imageFileName[100];

    // Get coloured image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to image file name .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, rotate);
}
void lightenImage()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; ++i) // loop for rows
    {
        for (int j = 0; j < SIZE; ++j) // loop for columns
        {
            for (int k = 0; k < RGB; ++k) // loop for colour
            {
                // if the value of each pixel not equal to 255 power that pixel with (0.8) and add 150 and
                //   if that value greater than 255 substract 255 and assign the value to the pixel
                //   else assign the value to the pixel
                if(image[i][j][k] != 255){
                    int img = pow(image[i][j][k], 0.8) + 150;
                    if ((img) > 255)
                    {
                        image[i][j][k] = img - 255;
                    } else {
                        image[i][j][k] = img;
                    }
                }
            }
        }
    }
}
void darkenImage()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; ++i) // loop for rows
    {
        for (int j = 0; j < SIZE; ++j) // loop for columns
        {
            for (int k = 0; k < RGB; ++k) // loop for colour
            {
                //multiply each pixel by 0.5(be darken)
                image[i][j][k] *= 0.5;
            }
        }
    }
}
void detectImageEdges()
{
    // call function convertImageToGray
    convertImageToGray();
    // 3 nested loops to loop in each pixel
    int diff = 30;
    for (int i = 0; i < SIZE; ++i) // loop for rows
    {
        for (int j = 0; j < SIZE; ++j) // loop for columns
        {
            for (int k = 0; k < RGB; ++k) // loop for colour
            {
                // comparing each pixel with the pixels arround it
                // if result of subtract two adjecant pixels greater than or equal to 35 (convert the first pixel to black)
                // else (convert the first pixel to white)
                if (image[i][j][k] - image[i + 1][j][k] >= diff || image[i][j][k] - image[i + 1][j][k] <= (diff * (-1)) ||
                     image[i][j][k] - image[i][j + 1][k] >= diff ||
                      image[i][j][k] - image[i][j + 1][k] <= (diff * (-1)))
                {
                    image[i][j][k] = 0;
                }
                else
                {
                    image[i][j][k] = 255;
                }
            }
        }
    }
}
void EnlargeImage1() // definition of function for enlarge first quarter of image
{
    // 3 nested loops to loop in each pixel
    for (int i = 0, k = 0; i < (SIZE / 2), k < SIZE; k += 2, i++) // loop for rows
    {
        for (int j = 0, l = 0; j < (SIZE / 2), l < SIZE; j++, l += 2) // loop for columns
        {
            for (int m = 0; m < RGB; m++) // loop for colour
            {
                // copy every pixel in first quarter 4 time in new image .
                rotate[k][l][m] = image[i][j][m];
                rotate[k][l + 1][m] = image[i][j][m];
                rotate[k + 1][l][m] = image[i][j][m];
                rotate[k + 1][l + 1][m] = image[i][j][m];
            }
        }
    }
}

void EnlargeImage2()  // definition of function for enlarge second quarter of image
{
    // 3 nested loops to loop in each pixel
    for (int i = 0, k = 0; i < SIZE, k < SIZE; k += 2, i++)  // loop for rows
    {
        for (int j = SIZE / 2, l = 0; j < SIZE, l < SIZE; j++, l += 2) // loop for columns
        {
            for (int m = 0; m < RGB; m++) // loop for colour
            {
                // copy every pixel in second quarter 4 time in new image .
                rotate[k][l][m] = image[i][j][m];
                rotate[k][l + 1][m] = image[i][j][m];
                rotate[k + 1][l][m] = image[i][j][m];
                rotate[k + 1][l + 1][m] = image[i][j][m];
            }
        }
    }
}
void EnlargeImage3()  // definition of function for enlarge third quarter of image
{
    // 3 nested loops to loop in each pixel
    for (int i = SIZE / 2, k = 0; i < SIZE, k < SIZE; k += 2, i++) // loop for rows
    {
        for (int j = 0, l = 0; j < (SIZE / 2), l < SIZE; j++, l += 2) // loop for columns
        {
            for (int m = 0; m < RGB; m++) // loop for colour
            {
                // copy every pixel in third quarter 4 time in new image .
                rotate[k][l][m] = image[i][j][m];
                rotate[k][l + 1][m] = image[i][j][m];
                rotate[k + 1][l][m] = image[i][j][m];
                rotate[k + 1][l + 1][m] = image[i][j][m];
            }
        }
    }
}
void EnlargeImage4()  // definition of function for enlarge fourth quarter of image
{
    // 3 nested loops to loop in each pixel
    for (int i = SIZE / 2, k = 0; i < SIZE, k < SIZE; k += 2, i++) // loop for rows
    {
        for (int j = SIZE / 2, l = 0; j < (SIZE / 2), l < SIZE; j++, l += 2) // loop for columns
        {
            for (int m = 0; m < RGB; m++) // loop for colour
            {
                // copy every pixel in fourth quarter 4 time in new image .
                rotate[k][l][m] = image[i][j][m];
                rotate[k][l + 1][m] = image[i][j][m];
                rotate[k + 1][l][m] = image[i][j][m];
                rotate[k + 1][l + 1][m] = image[i][j][m];
            }
        }
    }
}

// definition of function enlarge quarter the image like the user want (1), (2), (3) or (4)
void EnlargeImage(int &quarter)
{
    if (quarter == 1)
    {
        EnlargeImage1();
    } else if (quarter == 2)
    {
        EnlargeImage2();
    } else if (quarter == 3)
    {
        EnlargeImage3();
    } else if (quarter == 4)
    {
        EnlargeImage4();
    } else
    {
        cout << "invalid quarter " << endl;
    }
}
// definition of function for shrink an Image to (a half)
void shrinkAhalfImage()
{
    int sum = 0;
    // 3 nested loops to loop in each pixel
    //convert each pixel to white
    for (int i = 0; i < SIZE; i++) // loop for rows
    {
        for (int j = 0; j < SIZE; j++) // loop for columns
        {
            for (int n = 0; n < RGB; n++) // loop for colour
            {
                rotate[i][j][n] = 255;
            }
        }
    }
    // 3 nested loops to loop in each pixel
    for (int i = 0, k = 0; i < SIZE; i += 2, k++) // loop for rows
    {
        for (int j = 0, l = 0; j < SIZE; j += 2, l++) // loop for columns
        {
            for (int n = 0; n < RGB; n++) // loop for colour
            {
                //get the average of 4 pixels (square)
                // take this average and put it in the rotate
                sum = (image[i][j][n] + image[i][j + 1][n] + image[i + 1][j][n] + image[i + 1][j + 1][n]) / 4;
                rotate[k][l][n] = sum;
            }
        }
    }
}
// definition of function for shrink an Image to (a third)
void shrinkAthirdImage()
{
    int sum = 0;
    // 3 nested loops to loop in each pixel
    //convert each pixel to white
    for (int i = 0; i < SIZE; i++) // loop for rows
    {
        for (int j = 0; j < SIZE; j++) // loop for columns
        {
            for (int n = 0; n < RGB; n++) // loop for colour
            {
                rotate[i][j][n] = 255;
            }
        }
    }
    // 3 nested loops to loop in each pixel
    for (int i = 0, k = 0; i < SIZE; i += 3, k++) // loop for rows
    {
        for (int j = 0, l = 0; j < SIZE; j += 3, l++) // loop for columns
        {
            for (int n = 0; n < RGB; n++) // loop for colour
            {
                //get the average of 9 pixels
                // take this average and put it in the rotate
                sum = (image[i][j][n] + image[i][j + 1][n] + image[i][j + 2][n] + image[i + 1][j][n] +
                       image[i + 1][j + 1][n]
                       + image[i + 1][j + 2][n] + image[i + 2][j][n] + image[i + 2][j + 1][n] +
                       image[i + 2][j + 2][n]) / 9;
                rotate[k][l][n] = sum;
            }
        }

    }
}
// definition of function for shrink an Image to (a Quarter)
void shrinkQuarterImage()
{
    int sum = 0;
    // 3 nested loops to loop in each pixel
    //convert each pixel to white
    for (int i = 0; i < SIZE; i++) // loop for rows
    {
        for (int j = 0; j < SIZE; j++) // loop for columns
        {
            for (int n = 0; n < RGB; n++)  // loop for colour
            {
                rotate[i][j][n] = 255;
            }
        }
    }
    // 3 nested loops to loop in each pixel
    for (int i = 0, k = 0; i < SIZE; i += 4, k++) // loop for rows
    {
        for (int j = 0, l = 0; j < SIZE; j += 4, l++) // loop for columns
        {
            for (int n = 0; n < RGB; n++) // loop for colour
            {
                //get the average of 16 pixels
                // take this average and put it in the rotate
                sum = (image[i][j][n] + image[i][j + 1][n] + image[i][j + 2][n] + image[i][j + 3][n] +
                       image[i + 1][j][n] + image[i + 1][j + 1][n] + image[i + 1][j + 2][n] + image[i + 1][j + 3][n] +
                       image[i + 2][j][n] + image[i + 2][j + 1][n]
                       + image[i + 2][j + 2][n] + image[i + 2][j + 3][n] + image[i + 3][j][n] + image[i + 3][j + 1][n] +
                       image[i + 3][j + 2][n] + image[i + 3][j + 3][n]) / 16;
                rotate[k][l][n] = sum;
            }
        }

    }
}
// definition of function for mirror the half of image (left to right)
void mirrorLeftRight()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; i++) // loop for rows
    {
        for (int j = 0; j < SIZE / 2; j++)// we loop in columns to (SIZE / 2) because to mirror half of image
        {
            for (int k = 0; k < RGB; ++k) // loop for colour
            {
                // mirror each pixel
                // ex: the pixel [0][0][0] will mirror in pixel [0][255][0]
                // the pixel [0][1][0] will mirror in pixel [0][254][0] and so on
                image[i][SIZE - 1 - j][k] = image[i][j][k];
            }
        }
    }
}
// definition of function for mirror the half of image (right to left)
void mirrorRightLeft()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; i++) // loop for rows
    {
        for (int j = 256; j > SIZE / 2; --j)// we loop in columns to (SIZE / 2) because to mirror half of image
            // we inverse the count to start from the end
        {
            for (int k = 0; k < RGB; ++k)// loop for colour
            {
                // mirror each pixel
                // ex: the pixel [0][0][0] will mirror in pixel [0][255][0]
                // the pixel [0][1][0] will mirror in pixel [0][254][0] and so on
                image[i][SIZE - 1 - j][k] = image[i][j][k];
            }
        }
    }
}
// definition of function for mirror the half of image (up to down)
void mirrorUpDown()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE / 2; ++i)// we loop in rows to (SIZE / 2) because to mirror half of image
    {
        for (int j = 0; j < SIZE; ++j) // loop for columns
        {
            for (int k = 0; k < RGB; ++k) // loop for colour
            {
                // mirror each pixel
                // ex: the pixel [0][0][0] will mirror in pixel [255][0][0]
                // the pixel [1][0][0] will mirror in pixel [254][0][0] and so on
                image[SIZE - 1 - i][j][k] = image[i][j][k];
            }
        }
    }
}
// definition of function for mirror the half of image (down to up)
void mirrorDownUp()
{
    // 3 nested loops for loop to each pixel
    for (int i = 255; i > SIZE / 2; --i)// we loop in rows to (SIZE / 2) because to mirror half of image
        // we inverse the count to start from the end
    {
        for (int j = 0; j < SIZE; ++j) // loop for columns
        {
            for (int k = 0; k < RGB; ++k) // loop for colour
            {
                // mirror each pixel
                // ex: the pixel [0][0][0] will mirror in pixel [255][0][0]
                // the pixel [1][0][0] will mirror in pixel [254][0][0] and so on
                image[SIZE - 1 - i][j][k] = image[i][j][k];
            }
        }
    }
}
// definition of function for mirror half an image
void mirrorImage()
{
    char mirrorSide;
    // give the user choice of mirror side
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
    cin >> mirrorSide;
    // if mirrorSide == l --> call mirrorLeftRight
    // else if mirrorSide == r --> call mirrorRightLeft
    // else if mirrorSide == u --> call mirrorUpDown
    // else if mirrorSide == d --> call mirrorDownUp
    // else invalid side
    if (mirrorSide == 'l')
    {
        // call mirrorLeftRight function
        mirrorLeftRight();
    } else if (mirrorSide == 'r')
    {
        // call mirrorRightLeft function
        mirrorRightLeft();
    } else if (mirrorSide == 'u')
    {
        // call mirrorUpDown function
        mirrorUpDown();
    } else if (mirrorSide == 'd')
    {
        // call mirrorDownUp function
        mirrorDownUp();
    } else
    {
        cout << "invalid side" << endl;
    }
}
// declaration of function for put any quarter of the image in the first quarter of the image.
void shuffleImage1(int &a)
{
    if (a == 1)  //if user choose 1  ,put first quarter in first quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = 0; i < SIZE / 2; i++) // loop for rows
        {
            for (int j = 0; j < SIZE / 2; j++) // loop for columns
            {
                for (int m = 0; m < RGB; m++) // loop for colour
                {
                    rotate[i][j][m] = image[i][j][m];
                }
            }
        }
    } else if (a == 2)  //if user choose 2 ,put second quarter in first quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = 0, k = 0; i < SIZE / 2; i++, k++) // loop for rows
        {
            for (int j = SIZE / 2, l = 0; j < SIZE; j++, l++) // loop for columns
            {
                for (int m = 0; m < RGB; m++) // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (a == 3)   //if user choose 3 ,put third quarter in first quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = SIZE / 2, k = 0; i < SIZE; i++, k++) // loop for rows
        {
            for (int j = 0, l = 0; j < SIZE / 2; j++, l++) // loop for columns
            {
                for (int m = 0; m < RGB; m++) // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (a == 4)  //if user choose 4 ,put fourth quarter in first quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = SIZE / 2, k = 0; i < SIZE; i++, k++) // loop for rows
        {
            for (int j = SIZE / 2, l = 0; j < SIZE; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++) // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    }
}
// declaration of function for put any quarter of the image in the second quarter of the image.
void shuffleImage2(int &b)
{
    if (b == 1)  //if user choose 1 ,put first quarter in second quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = 0, k = 0; i < SIZE / 2; i++, k++)  // loop for rows
        {
            for (int j = 0, l = SIZE / 2; j < SIZE / 2; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (b == 2)  //if user choose 2 ,put second quarter in second quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = 0, k = 0; i < SIZE / 2; i++, k++)  // loop for rows
        {
            for (int j = SIZE / 2, l = SIZE / 2; j < SIZE; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (b == 3)  //if user choose 3 ,put third quarter in second quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = SIZE / 2, k = 0; i < SIZE; i++, k++)  // loop for rows
        {
            for (int j = 0, l = SIZE / 2; j < SIZE / 2; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (b == 4)  //if user choose 4 ,put fourth quarter in second quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = SIZE / 2, k = 0; i < SIZE; i++, k++)  // loop for rows
        {
            for (int j = SIZE / 2, l = SIZE / 2; j < SIZE; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    }
}
// declaration of function for put any quarter of the image in the third quarter of the image.
void shuffleImage3(int &c)
{
    if (c == 1)  //if user choose 1 ,put first quarter in third quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = 0, k = SIZE / 2; i < SIZE / 2; i++, k++)  // loop for rows
        {
            for (int j = 0, l = 0; j < SIZE / 2; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (c == 2)  //if user choose 2 ,put second quarter in third quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = 0, k = SIZE / 2; i < SIZE / 2; i++, k++)  // loop for rows
        {
            for (int j = SIZE / 2, l = 0; j < SIZE; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (c == 3)  //if user choose 3 ,put third quarter in third quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = SIZE / 2, k = SIZE / 2; i < SIZE; i++, k++)  // loop for rows
        {
            for (int j = 0, l = 0; j < SIZE / 2; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (c == 4)  //if user choose 4 ,put fourth quarter in third quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = SIZE / 2, k = SIZE / 2; i < SIZE; i++, k++)  // loop for rows
        {
            for (int j = SIZE / 2, l = 0; j < SIZE; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    }
}
// declaration of function for put any quarter of the image in the fourth quarter of the image.
void shuffleImage4(int &d)
{
    if (d == 1)  //if user choose 1 ,put first quarter in fourth quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = 0, k = SIZE / 2; i < SIZE / 2; i++, k++)  // loop for rows
        {
            for (int j = 0, l = SIZE / 2; j < SIZE / 2; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (d == 2)  //if user choose 2 ,put second quarter in fourth quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = 0, k = SIZE / 2; i < SIZE / 2; i++, k++)  // loop for rows
        {
            for (int j = SIZE / 2, l = SIZE / 2; j < SIZE; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (d == 3)  //if user choose 3 ,put third quarter in fourth quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = SIZE / 2, k = SIZE / 2; i < SIZE; i++, k++)  // loop for rows
        {
            for (int j = 0, l = SIZE / 2; j < SIZE / 2; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    } else if (d == 4)  //if user choose 4 ,put fourth quarter in fourth quarter of new image
    {
        // 3 nested loops to loop in each pixel
        for (int i = SIZE / 2, k = SIZE / 2; i < SIZE; i++, k++)  // loop for rows
        {
            for (int j = SIZE / 2, l = SIZE / 2; j < SIZE; j++, l++)  // loop for columns
            {
                for (int m = 0; m < RGB; m++)  // loop for colour
                {
                    rotate[k][l][m] = image[i][j][m];
                }
            }
        }
    }
}
void blurImage()
{
    // 3 nested loops to loop in each pixel
    for (int i = 0; i < SIZE; ++i) // loop for rows
    {
        for (int j = 0; j < SIZE; ++j) // loop for columns
        {
            for (int m = 0; m < RGB; ++m) // loop for colour
            {
                // 3 nested loops to loop in each pixel
                //this loop will make a cube of pixels (7rows, 7columns, 7channels)
                int sum = 0;
                for (int k = 0; k < 7; ++k) // loop for rows
                {
                    for (int l = 0; l < 7; ++l) // loop for columns
                    {
                        for (int n = 0; n < 7; ++n)
                        {
                            //sum of this pixels
                            sum += image[i + k][j + l][m];
                        }
                    }
                }
                //put the average of this pixels in the middle of the cube
                image[i + 3][j + 3][m + 3] = sum / 343;
            }
        }
    }
}
const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;

void cropImage()
{
    int x, y, l, w;

    // Get cropping parameters from the user
    cout << "Enter x position: ";
    cin >> x;
    cout << "Enter y position: ";
    cin >> y;
    cout << "Enter length: ";
    cin >> l;
    cout << "Enter width: ";
    cin >> w;

    // Crop the image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i < x || i >= (x + l) || j < y || j >= (y + w))
            {
                // Set pixels outside the cropped region to white (255) for each color channel
                image[i][j][RED] = 255;
                image[i][j][GREEN] = 255;
                image[i][j][BLUE] = 255;
            }
        }
    }
}