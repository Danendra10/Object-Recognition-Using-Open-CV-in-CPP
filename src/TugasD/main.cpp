// do GLCM

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;
using namespace cv;

char image_path[100];

Mat image;
Mat image_hsv;

// function for glcm
void glcm(Mat &image, Mat &glcm, int distance, int angle, int gray_levels, int symmetric, int normed)
{
    // calculate glcm
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            int x = image.at<Vec3b>(i, j)[0];
            int y = image.at<Vec3b>(i + distance, j + distance)[0];
            glcm.at<float>(x, y) += 1;
        }
    }
    // normalize
    if (normed)
    {
        glcm /= (image.rows * image.cols);
    }
    // symmetrize
    if (symmetric)
    {
        for (int i = 0; i < gray_levels; i++)
        {
            for (int j = 0; j < gray_levels; j++)
            {
                glcm.at<float>(i, j) = (glcm.at<float>(i, j) + glcm.at<float>(j, i)) / 2;
            }
        }
    }
}

int main()
{
    for (uint8_t color_space = 0; color_space < 2; color_space++)
    {
        if (!color_space)
        {
            for (uint8_t i = 1; i <= 10; i++)
            {
                for (uint8_t j = 1; j <= 3; j++)
                {
                    sprintf(image_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/dataset/tugasA/%d/%d_%d.png", i, i, j);
                    cout << image_path << endl;
                    image = imread(image_path);
                    cvtColor(image, image_hsv, COLOR_BGR2HSV);

                    try
                    {
                        // use glcm function
                        Mat glcm_mat;
                        int distance = 1;
                        int angle = 0;
                        int gray_levels = 256;
                        int symmetric = 1;
                        int normed = 1;
                        glcm_mat = Mat::zeros(gray_levels, gray_levels, CV_32FC1);
                        glcm(image_hsv, glcm_mat, distance, angle, gray_levels, symmetric, normed);

                        imshow("image", image);
                        imshow("glcm", glcm_mat);
                        waitKey(0);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    catch (const cv::Exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    catch (...)
                    {
                        std::cerr << "Unknown error" << '\n';
                    }
                }
            }
        }
    }
    // // read image
    // Mat img = imread("/home/dancoeks/Kuliah/DSEC/Tugas Akhir/dataset/tugasA/2/2_1.png", IMREAD_GRAYSCALE);
    // // imshow("image", img);
    // // waitKey(0);

    // // create glcm
    // Mat glcm;
    // int distance = 1;
    // int angle = 0;
    // int gray_levels = 256;
    // int symmetric = 1;
    // int normed = 1;
    // glcm = Mat::zeros(gray_levels, gray_levels, CV_32FC1);
    // // cout << glcm << endl;

    // // calculate glcm
    // for (int i = 0; i < img.rows; i++)
    // {
    //     for (int j = 0; j < img.cols; j++)
    //     {
    //         int x = img.at<uchar>(i, j);
    //         int y = img.at<uchar>(i + distance, j + distance);
    //         glcm.at<float>(x, y) += 1;
    //     }
    // }
    // // cout << glcm << endl;

    // // normalize glcm
    // double sum = 0;
    // for (int i = 0; i < glcm.rows; i++)
    // {
    //     for (int j = 0; j < glcm.cols; j++)
    //     {
    //         sum += glcm.at<float>(i, j);
    //     }
    // }
    // // cout << sum << endl;
    // glcm = glcm / sum;
    // // cout << glcm << endl;

    // // calculate contrast
    // double contrast = 0;
    // for (int i = 0; i < glcm.rows; i++)
    // {
    //     for (int j = 0; j < glcm.cols; j++)
    //     {
    //         contrast += pow(i - j, 2) * glcm.at<float>(i, j);
    //     }
    // }
    // cout << "Contrast: " << contrast << endl;

    // // calculate correlation
    // double mean_x = 0;
    // double mean_y = 0;
    // for (int i = 0; i < glcm.rows; i++)
    // {
    //     for (int j = 0; j < glcm.cols; j++)
    //     {
    //         mean_x += i * glcm.at<float>(i, j);
    //         mean_y += j * glcm.at<float>(i, j);
    //     }
    // }
    // // cout << mean_x << endl;
    // // cout << mean_y << endl;
    // double std_x = 0;
    // double std_y = 0;

    // for (int i = 0; i < glcm.rows; i++)
    // {
    //     for (int j = 0; j < glcm.cols; j++)
    //     {
    //         std_x += pow(i - mean_x, 2) * glcm.at<float>(i, j);
    //         std_y += pow(j - mean_y, 2) * glcm.at<float>(i, j);
    //     }
    // }

    // std_x = sqrt(std_x);
    // std_y = sqrt(std_y);
    // // cout << std_x << endl;
    // // cout << std_y << endl;

    // double correlation = 0;
    // for (int i = 0; i < glcm.rows; i++)
    // {
    //     for (int j = 0; j < glcm.cols; j++)
    //     {
    //         correlation += (i - mean_x) * (j - mean_y) * glcm.at<float>(i, j) / (std_x * std_y);
    //     }
    // }

    // cout << "Correlation: " << correlation << endl;

    // // calculate energy
    // double energy = 0;
    // for (int i = 0; i < glcm.rows; i++)
    // {
    //     for (int j = 0; j < glcm.cols; j++)
    //     {
    //         energy += pow(glcm.at<float>(i, j), 2);
    //     }
    // }
    // cout << "Energy: " << energy << endl;

    // // calculate homogeneity
    // double homogeneity = 0;
    // for (int i = 0; i < glcm.rows; i++)
    // {
    //     for (int j = 0; j < glcm.cols; j++)
    //     {
    //         homogeneity += glcm.at<float>(i, j) / (1 + abs(i - j));
    //     }
    // }

    // cout << "Homogeneity: " << homogeneity << endl;

    // return 0;
}