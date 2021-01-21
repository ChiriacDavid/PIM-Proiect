#include "opencv2/objdetect.hpp" 
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include <iostream> 

using namespace std;
using namespace cv;

string numeImagine = "";

void detectAndDraw(Mat& img, CascadeClassifier& cascade);

int main(int argc, const char** argv)
{
    cout << "Inserati numele imaginii dorite: ";
    cin >> numeImagine;

    //Memoreaza imaginea pe care se aplica detectia fetelor
    Mat image;

    image = imread("Imagini\\"+numeImagine, 1);

    //Se verifica daca imaginea a fost incarcata cu succes
    //Daca incarcarea esueaza vom parasi programul
    if (image.empty()) 
    {
        cout << "Imaginea nu poate fi incarcata!!!";
    }
    else
    {
        // Vom folosi clasificatorii Haar care contin trasaturi faciale
        CascadeClassifier cascade;

        // Vom incarca trasaturile din opencv
        cascade.load("haarcascade_frontalface_alt.xml");

        detectAndDraw(image, cascade);
    }
    return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade)
{
    vector<Rect> faces;

    Mat small_Img;

    //Vom folosi imaginea cu dimensiunile originale
    double width, height;

    width = img.cols;
    height = img.rows;

    while (width > 1400 || height > 800) {
        width /= 2;
        height /= 2;
    }

    //Modifica dimensiunile imaginii astfel incat sa se poata incadra cat mai bine in ecran
    resize(img, small_Img, Size(width, height), (0.0), (0.0), 1);

    // Detecteaza fetele de diferite dimensiuni, folosindu-se de cascada de clasificatori 
    cascade.detectMultiScale(small_Img, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));

    // Parcurgem toate fetele detectate
    for (size_t i = 0; i < faces.size(); i++)
    {
        //Se marcheaza fata detectata cu un dreptunghi
        rectangle(small_Img, faces[i], Scalar(255),3,8,0);        
    }

    //Salveaza imaginea in fisier
    imwrite("Imagini procesate\\"+numeImagine, small_Img);

    // Afiseaza imaginea procesata
    imshow("Face Detection", small_Img);
    waitKey(0);
}