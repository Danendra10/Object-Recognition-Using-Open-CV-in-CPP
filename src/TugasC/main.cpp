#include <string.h>
#include <iostream>
#include "histogram_learning/TugasB/knn.h"
#include "opencv4/opencv2/opencv.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include <fstream>

using namespace std;
using namespace cv;

#define USE_RGB 1
#define USE_HSV 0

vector<int> contrast_hsv_save, correlation_hsv_save, label_hsv_save;

const size_t BUFFER_SIZE = 1024;
char command[BUFFER_SIZE];
char label_char[BUFFER_SIZE];

int found_state = 0;

using namespace cv;

Mat image, image_hsv;

void LoadParam();

char image_path[100];

int index_pertama;
int index_kedua;

int asked_label;
int main()
{
    LoadParam();
    while (true)
    {
        cout << "What do you want? ";
        scanf("%s %s", command, label_char);

        cout << "Command: " << command << endl;
        cout << "Label: " << label_char << endl;
        /*
        else if per condition of label_char
        Parfum
        STM
        Ukulele
        Korek
        Charger
        Li-Po
        Tang
        Tipe-X
        Masker
        Baterai
        */
        if (strcmp(label_char, "Parfum") == 0)
        {
            asked_label = 1;
        }
        else if (strcmp(label_char, "STM") == 0)
        {
            asked_label = 2;
        }
        else if (strcmp(label_char, "Ukulele") == 0)
        {
            asked_label = 3;
        }
        else if (strcmp(label_char, "Korek") == 0)
        {
            asked_label = 4;
        }
        else if (strcmp(label_char, "Charger") == 0)
        {
            asked_label = 5;
        }
        else if (strcmp(label_char, "Li-Po") == 0)
        {
            asked_label = 6;
        }
        else if (strcmp(label_char, "Tang") == 0)
        {
            asked_label = 7;
        }
        else if (strcmp(label_char, "Tipe-X") == 0)
        {
            asked_label = 8;
        }
        else if (strcmp(label_char, "Masker") == 0)
        {
            asked_label = 9;
        }
        else if (strcmp(label_char, "Baterai") == 0)
        {
            asked_label = 10;
        }
        else
        {
            cout << "Label not found" << endl;
            continue;
        }
        cout << "Asked label: " << asked_label << endl;

        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 2; j++)
            {
                if (!found_state)
                {
                    sprintf(image_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/dataset/tugasB/test/%d/%d_%d.png", i, i, j);
                    cout << image_path << endl;
                    image = imread(image_path, IMREAD_COLOR);
                    cvtColor(image, image_hsv, COLOR_BGR2HSV);

                    Mat lbp_image;
                    lbp_image = Mat::zeros(image_hsv.rows, image_hsv.cols, CV_8UC1);
                    // do lbp
                    for (int i = 1; i < image_hsv.rows - 1; i++)
                    {
                        for (int j = 1; j < image_hsv.cols - 1; j++)
                        {
                            // get 8 pixel
                            int p1 = image_hsv.at<Vec3b>(i - 1, j - 1)[0];
                            int p2 = image_hsv.at<Vec3b>(i - 1, j)[0];
                            int p3 = image_hsv.at<Vec3b>(i - 1, j + 1)[0];
                            int p4 = image_hsv.at<Vec3b>(i, j + 1)[0];
                            int p5 = image_hsv.at<Vec3b>(i + 1, j + 1)[0];
                            int p6 = image_hsv.at<Vec3b>(i + 1, j)[0];
                            int p7 = image_hsv.at<Vec3b>(i + 1, j - 1)[0];
                            int p8 = image_hsv.at<Vec3b>(i, j - 1)[0];
                            // get center pixel
                            int p9 = image_hsv.at<Vec3b>(i, j)[0];
                            // compare
                            int lbp = 0;
                            if (p1 > p9)
                            {
                                lbp += 1;
                            }
                            if (p2 > p9)
                            {
                                lbp += 2;
                            }
                            if (p3 > p9)
                            {
                                lbp += 4;
                            }
                            if (p4 > p9)
                            {
                                lbp += 8;
                            }
                            if (p5 > p9)
                            {
                                lbp += 16;
                            }
                            if (p6 > p9)
                            {
                                lbp += 32;
                            }
                            if (p7 > p9)
                            {
                                lbp += 64;
                            }
                            if (p8 > p9)
                            {
                                lbp += 128;
                            }
                            // set lbp value
                            lbp_image.at<uchar>(i, j) = lbp;
                        }
                    }

                    // get glcm
                    Mat glcm_image;
                    glcm_image = Mat::zeros(256, 256, CV_32FC1);
                    for (int i = 1; i < image_hsv.rows - 1; i++)
                    {
                        for (int j = 1; j < image_hsv.cols - 1; j++)
                        {
                            // get 8 pixel
                            int p1 = lbp_image.at<uchar>(i - 1, j - 1);
                            int p2 = lbp_image.at<uchar>(i - 1, j);
                            int p3 = lbp_image.at<uchar>(i - 1, j + 1);
                            int p4 = lbp_image.at<uchar>(i, j + 1);
                            int p5 = lbp_image.at<uchar>(i + 1, j + 1);
                            int p6 = lbp_image.at<uchar>(i + 1, j);
                            int p7 = lbp_image.at<uchar>(i + 1, j - 1);
                            int p8 = lbp_image.at<uchar>(i, j - 1);
                            // get center pixel
                            int p9 = lbp_image.at<uchar>(i, j);
                            // set glcm value
                            glcm_image.at<float>(p9, p1) += 1;
                            glcm_image.at<float>(p9, p2) += 1;
                            glcm_image.at<float>(p9, p3) += 1;
                            glcm_image.at<float>(p9, p4) += 1;
                            glcm_image.at<float>(p9, p5) += 1;
                            glcm_image.at<float>(p9, p6) += 1;
                            glcm_image.at<float>(p9, p7) += 1;
                            glcm_image.at<float>(p9, p8) += 1;
                        }
                    }
                    // // normalize glcm
                    normalize(glcm_image, glcm_image, 0, 1, NORM_MINMAX, -1, Mat());
                    // // get contrast
                    float contrast = 0;
                    for (int i = 0; i < 256; i++)
                    {
                        for (int j = 0; j < 256; j++)
                        {
                            contrast += pow(i - j, 2) * glcm_image.at<float>(i, j);
                        }
                    }
                    // get energy
                    float energy = 0;
                    for (int i = 0; i < 256; i++)
                    {
                        for (int j = 0; j < 256; j++)
                        {
                            energy += pow(glcm_image.at<float>(i, j), 2);
                        }
                    }
                    // get homogeneity
                    float homogeneity = 0;
                    for (int i = 0; i < 256; i++)
                    {
                        for (int j = 0; j < 256; j++)
                        {
                            homogeneity += glcm_image.at<float>(i, j) / (1 + abs(i - j));
                        }
                    }
                    // get correlation
                    float correlation = 0;
                    float mean_x = 0;
                    float mean_y = 0;
                    float std_x = 0;
                    float std_y = 0;
                    for (int i = 0; i < 256; i++)
                    {
                        for (int j = 0; j < 256; j++)
                        {
                            mean_x += i * glcm_image.at<float>(i, j);
                            mean_y += j * glcm_image.at<float>(i, j);
                        }
                    }
                    for (int i = 0; i < 256; i++)
                    {
                        for (int j = 0; j < 256; j++)
                        {
                            std_x += pow(i - mean_x, 2) * glcm_image.at<float>(i, j);
                            std_y += pow(j - mean_y, 2) * glcm_image.at<float>(i, j);
                        }
                    }
                    std_x = sqrt(std_x);
                    std_y = sqrt(std_y);
                    for (int i = 0; i < 256; i++)
                    {
                        for (int j = 0; j < 256; j++)
                        {
                            correlation += (i - mean_x) * (j - mean_y) * glcm_image.at<float>(i, j) / (std_x * std_y);
                        }
                    }

                    Dataset data(contrast_hsv_save, correlation_hsv_save, label_hsv_save);

                    KNN knn_hsv(data, 3);

                    // cout << contrast << " | " << correlation << endl;

                    KnnPoint p;
                    p.x = contrast;
                    p.y = correlation;
                    int label = knn_hsv.Predict(p);

                    // check correct guess
                    if (label == asked_label)
                    {
                        found_state = 1;
                        index_pertama = i;
                        index_kedua = j;
                        break;
                    }
                    else
                        found_state = 0;
                }
            }
        }

        if (found_state == 1)
        {
            cout << "Found" << endl;
            cout << "Index pertama : " << index_pertama << endl;
            cout << "Index kedua : " << index_kedua << endl;

            sprintf(image_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/dataset/tugasB/test/%d/%d_%d.png", index_pertama, index_pertama, index_kedua);
            char text[100];
            sprintf(text, "Ini %s untuk anda", label_char);
            Mat image = imread(image_path, IMREAD_COLOR);
            // give text to img
            putText(image, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);
            imshow("Image", image);
            waitKey(0);
            break;
        }
        else
        {
            cout << "Not Found" << endl;
            break;
        }
    }
}

void LoadParam()
{

    char path_file[100] = "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasD/db_hsv.txt";
    ifstream file;
    file.open(path_file, ios_base::in);

    // read data
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        int i = 0;
        while (getline(ss, token, ','))
        {
            if (i == 0)
            {
                contrast_hsv_save.push_back(stoi(token));
            }
            else if (i == 1)
            {
                correlation_hsv_save.push_back(stoi(token));
            }
            else
            {
                label_hsv_save.push_back(stoi(token));
            }
            i++;
        }
    }
}