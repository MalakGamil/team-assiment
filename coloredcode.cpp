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
