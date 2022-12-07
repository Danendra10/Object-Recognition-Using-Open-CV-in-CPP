#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include "opencv4/opencv2/opencv.hpp"
#include <vector>
#include <fstream>

#define USE_RGB 1
#define USE_HSV 0

using namespace std;
using namespace cv;

Mat image;
Mat image_hsv;
Mat image_hls;
Mat image_gray;

char image_path[100];

int h_fix = 0, s_fix = 0, v_fix = 0;
int h_buff, s_buff, v_buff;
// for saving data
vector<int> h_save, s_save, label_hsv;

int r_fix = 0, g_fix = 0, b_fix = 0;
int r_buff, g_buff, b_buff;
// for saving data
vector<int> g_save, b_save, label_rgb;

void SortMatrix(int *matrix)
{
    int temp;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            if (matrix[i] > matrix[j])
            {
                temp = matrix[i];
                matrix[i] = matrix[j];
                matrix[j] = temp;
            }
        }
    }
}

/**
 * @param first_data: vector of first data
 * @param second_data: vector of second data
 * @param label: vector of label
 * @param cs: color space
 */
void SaveData(vector<int> first_data, vector<int> second_data, vector<int> label, int cs)
{
    if (cs == USE_RGB)
    {
        char path_file[100] = "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasB/db_obj_rgb.txt";
        ofstream file;
        file.open(path_file, ios_base::out);
        for (int i = 0; i < first_data.size(); i++)
        {
            file << first_data.at(i) << "," << second_data.at(i) << "," << label.at(i) << endl;
        }
        file.close();
    }
    else
    {
        char path_file[100] = "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasB/db_obj_hsv.txt";
        ofstream file;
        file.open(path_file, ios_base::out);
        for (int i = 0; i < first_data.size(); i++)
        {
            file << first_data.at(i) << "," << second_data.at(i) << "," << label.at(i) << endl;
        }
        file.close();
    }
}

#endif