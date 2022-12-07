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

int main()
{
    for (uint8_t color_space = 0; color_space < 2; color_space++)
    {
        try
        {
            if (!color_space)
            {
                char path_file[100] = "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasD/db_hsv.txt";
                ofstream file;
                file.open(path_file, ios_base::out);
                for (uint8_t i = 1; i <= 10; i++)
                {
                    for (uint8_t j = 1; j <= 3; j++)
                    {
                        // read image
                        sprintf(image_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/dataset/tugasA/%d/%d_%d.png", i, i, j);
                        image = imread(image_path, IMREAD_COLOR);
                        // convert to hsv
                        cvtColor(image, image_hsv, COLOR_BGR2HSV);
                        // do local binary pattern
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
                        // normalize glcm
                        normalize(glcm_image, glcm_image, 0, 1, NORM_MINMAX, -1, Mat());
                        // get contrast
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

                        // print all data
                        cout << "Contrast: " << contrast << endl;
                        cout << "Energy: " << energy << endl;
                        cout << "Homogeneity: " << homogeneity << endl;
                        cout << "Correlation: " << correlation << endl;

                        file << contrast << "," << correlation << "," << (int)i << endl;
                    }
                }
                file.close();
            }
            else
            {
                char path_file[100] = "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasD/db_rgb.txt";
                ofstream file;
                file.open(path_file, ios_base::out);
                for (uint8_t i = 1; i <= 10; i++)
                {
                    for (uint8_t j = 1; j <= 3; j++)
                    {
                        // read image
                        sprintf(image_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/dataset/tugasA/%d/%d_%d.png", i, i, j);
                        image = imread(image_path, IMREAD_COLOR);
                        // do local binary pattern
                        Mat lbp_image;
                        lbp_image = Mat::zeros(image.rows, image.cols, CV_8UC1);
                        // do lbp
                        for (int i = 1; i < image.rows - 1; i++)
                        {
                            for (int j = 1; j < image.cols - 1; j++)
                            {
                                // get 8 pixel
                                int p1 = image.at<Vec3b>(i - 1, j - 1)[0];
                                int p2 = image.at<Vec3b>(i - 1, j)[0];
                                int p3 = image.at<Vec3b>(i - 1, j + 1)[0];
                                int p4 = image.at<Vec3b>(i, j + 1)[0];
                                int p5 = image.at<Vec3b>(i + 1, j + 1)[0];
                                int p6 = image.at<Vec3b>(i + 1, j)[0];
                                int p7 = image.at<Vec3b>(i + 1, j - 1)[0];
                                int p8 = image.at<Vec3b>(i, j - 1)[0];
                                // get center pixel
                                int p9 = image.at<Vec3b>(i, j)[0];
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
                        for (int i = 1; i < image.rows - 1; i++)
                        {
                            for (int j = 1; j < image.cols - 1; j++)
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
                        // normalize glcm
                        normalize(glcm_image, glcm_image, 0, 1, NORM_MINMAX, -1, Mat());
                        // get contrast
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

                        // print all data
                        cout << "Contrast: " << contrast << endl;
                        cout << "Energy: " << energy << endl;
                        cout << "Homogeneity: " << homogeneity << endl;
                        cout << "Correlation: " << correlation << endl;

                        file << contrast << "," << correlation << "," << (int)i << endl;
                    }
                }
                file.close();
            }
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
            std::cerr << "Unknown exception" << '\n';
        }
    }
}