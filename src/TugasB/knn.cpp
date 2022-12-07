#include "histogram_learning/TugasB/knn.h"
#include "opencv4/opencv2/opencv.hpp"
#include <fstream>
#include "histogram_learning/matplotlibcpp.h"

using namespace cv;

#define USE_RGB 1
#define USE_HSV 0

void LoadParam(int label);

vector<int> h_save, s_save, label_hsv;
vector<int> g_save, b_save, label_rgb;

char image_path[100];
Mat image;
Mat image_hsv;
int h_fix = 0, s_fix = 0, v_fix = 0;
int h_buff, s_buff, v_buff;

int r_fix = 0, g_fix = 0, b_fix = 0;
int r_buff, g_buff, b_buff;

int correct_guess = 0;
int wrong_guess = 0;
int total_guess = 0;

vector<int> pred;
vector<int> index_plot;
int index_plt = 0;

namespace plt = matplotlibcpp;

int main()
{
    for (uint8_t color_space = 0; color_space < 2; color_space++)
    {
        if (!color_space)
        {
            index_plt = 0, correct_guess = 0;
            ofstream file;
            file.open("/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasB/detection_result_hsv.txt");
            file << "Real | Pred" << endl;
            LoadParam(USE_HSV);
            // print
            for (int i = 0; i < h_save.size(); i++)
            {
                cout << h_save.at(i) << "," << s_save.at(i) << "," << label_hsv.at(i) << endl;
            }

            for (int i = 1; i <= 10; i++)
            {
                for (int j = 1; j <= 2; j++)
                {
                    h_fix = 0, s_fix = 0, v_fix = 0;
                    sprintf(image_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/dataset/tugasB/test/%d/%d_%d.png", i, i, j);
                    cout << image_path << endl;
                    image = imread(image_path, IMREAD_COLOR);
                    cvtColor(image, image_hsv, COLOR_BGR2HSV);
                    // get the mode of h and s value from image
                    vector<int> h_vec, s_vec;
                    for (int i = 0; i < image_hsv.rows; i++)
                    {
                        for (int j = 0; j < image_hsv.cols; j++)
                        {
                            h_vec.push_back(image_hsv.at<Vec3b>(i, j)[0]);
                            s_vec.push_back(image_hsv.at<Vec3b>(i, j)[1]);
                        }
                    }
                    int biggest_mode_h = 0;
                    vector<double> mode_h, numbers_h;
                    numbers_h.push_back(h_vec.at(0));
                    mode_h.push_back(1);
                    int count_h = 0;
                    for (int i = 0; i < h_vec.size(); i++)
                    {
                        if (h_vec.at(i) > 0)
                        {
                            if (h_vec.at(i) == numbers_h.at(count_h))
                                mode_h.at(count_h)++;
                            else
                            {
                                if (biggest_mode_h < mode_h.at(count_h))
                                    biggest_mode_h = mode_h.at(count_h);

                                count_h++;
                                mode_h.push_back(1);
                                numbers_h.push_back(h_vec.at(i));
                            }
                        }
                    }

                    for (int i = 0; i < mode_h.size(); i++)
                    {
                        if (mode_h.at(i) == biggest_mode_h)
                        {
                            cout << numbers_h.at(i) << " ";
                            h_buff = numbers_h.at(i);
                        }
                    }
                    if (h_buff > h_fix)
                        h_fix = h_buff;
                    cout << endl;

                    int biggest_mode_s = 0;
                    vector<double> mode_s, numbers_s;
                    numbers_s.push_back(s_vec.at(0));
                    mode_s.push_back(1);
                    int count_s = 0;
                    for (int i = 0; i < s_vec.size(); i++)
                    {
                        if (s_vec.at(i) > 0)
                        {
                            if (s_vec.at(i) == numbers_s.at(count_s))
                                mode_s.at(count_s)++;
                            else
                            {
                                if (biggest_mode_s < mode_s.at(count_s))
                                    biggest_mode_s = mode_s.at(count_s);

                                count_s++;
                                mode_s.push_back(1);
                                numbers_s.push_back(s_vec.at(i));
                            }
                        }
                    }

                    for (int i = 0; i < mode_s.size(); i++)
                    {
                        if (mode_s.at(i) == biggest_mode_s)
                        {
                            cout << numbers_s.at(i) << " ";
                            s_buff = numbers_s.at(i);
                        }
                    }

                    if (s_buff > s_fix)
                        s_fix = s_buff;

                    cout << endl;

                    cout << endl
                         << "Final : " << h_fix << " " << s_fix << " " << v_fix << endl;

                    // knn
                    Dataset data_hsv(h_save, s_save, label_hsv);
                    KNN knn_hsv(data_hsv, 3);

                    KnnPoint p;
                    p.x = h_fix;
                    p.y = s_fix;
                    int label = knn_hsv.Predict(p);
                    cout << "Label : " << label << endl;

                    file << i << " | " << label << endl;

                    // check correct guess
                    if (label == i)
                        correct_guess++;
                    else
                        wrong_guess++;

                    index_plt++;
                    pred.push_back(correct_guess);
                    index_plot.push_back(index_plt);
                }
            }
            file.close();
            plt::plot(index_plot, pred);
            plt::xlabel("data");
            plt::ylabel("correct guess");
            plt::title("KNN HSV K: 3");
            plt::show();
            pred.clear();
            index_plot.clear();
        }
        else
        {
            index_plt = 0, correct_guess = 0;
            ofstream file;
            file.open("/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasB/detection_result_rgb.txt");
            file << "Real | Pred" << endl;
            LoadParam(USE_RGB);

            for (int i = 1; i <= 10; i++)
            {
                for (int j = 1; j <= 2; j++)
                {
                    r_fix = 0, g_fix = 0, b_fix = 0;
                    sprintf(image_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/dataset/tugasB/test/%d/%d_%d.png", i, i, j);
                    cout << image_path << endl;
                    image = imread(image_path, IMREAD_COLOR);
                    // get the mode of r, g, and b value from image
                    vector<int> r_vec, g_vec, b_vec;
                    for (int i = 0; i < image.rows; i++)
                    {
                        for (int j = 0; j < image.cols; j++)
                        {
                            r_vec.push_back(image.at<Vec3b>(i, j)[2]);
                            g_vec.push_back(image.at<Vec3b>(i, j)[1]);
                            b_vec.push_back(image.at<Vec3b>(i, j)[0]);
                        }
                    }
                    int biggest_mode_r = 0;
                    vector<double> mode_r, numbers_r;
                    numbers_r.push_back(r_vec.at(0));
                    mode_r.push_back(1);
                    int count_r = 0;
                    for (int i = 0; i < r_vec.size(); i++)
                    {
                        if (r_vec.at(i) > 0)
                        {
                            if (r_vec.at(i) == numbers_r.at(count_r))
                                mode_r.at(count_r)++;
                            else
                            {
                                if (biggest_mode_r < mode_r.at(count_r))
                                    biggest_mode_r = mode_r.at(count_r);

                                count_r++;
                                mode_r.push_back(1);
                                numbers_r.push_back(r_vec.at(i));
                            }
                        }
                    }

                    for (int i = 0; i < mode_r.size(); i++)
                    {
                        if (mode_r.at(i) == biggest_mode_r)
                        {
                            cout << numbers_r.at(i) << " ";
                            r_buff = numbers_r.at(i);
                        }
                    }
                    if (r_buff > r_fix)
                        r_fix = r_buff;
                    cout << endl;

                    int biggest_mode_g = 0;
                    vector<double> mode_g, numbers_g;
                    numbers_g.push_back(g_vec.at(0));
                    mode_g.push_back(1);
                    int count_g = 0;
                    for (int i = 0; i < g_vec.size(); i++)
                    {
                        if (g_vec.at(i) > 0)
                        {
                            if (g_vec.at(i) == numbers_g.at(count_g))
                                mode_g.at(count_g)++;
                            else
                            {
                                if (biggest_mode_g < mode_g.at(count_g))
                                    biggest_mode_g = mode_g.at(count_g);

                                count_g++;
                                mode_g.push_back(1);
                                numbers_g.push_back(g_vec.at(i));
                            }
                        }
                    }

                    for (int i = 0; i < mode_g.size(); i++)
                    {
                        if (mode_g.at(i) == biggest_mode_g)
                        {
                            cout << numbers_g.at(i) << " ";
                            g_buff = numbers_g.at(i);
                        }
                    }

                    if (g_buff > g_fix)
                        g_fix = g_buff;

                    cout << endl;

                    int biggest_mode_b = 0;
                    vector<double> mode_b, numbers_b;
                    numbers_b.push_back(b_vec.at(0));
                    mode_b.push_back(1);
                    int count_b = 0;
                    for (int i = 0; i < b_vec.size(); i++)
                    {
                        if (b_vec.at(i) > 0)
                        {
                            if (b_vec.at(i) == numbers_b.at(count_b))
                                mode_b.at(count_b)++;
                            else
                            {
                                if (biggest_mode_b < mode_b.at(count_b))
                                    biggest_mode_b = mode_b.at(count_b);

                                count_b++;
                                mode_b.push_back(1);
                                numbers_b.push_back(b_vec.at(i));
                            }
                        }
                    }

                    for (int i = 0; i < mode_b.size(); i++)
                    {
                        if (mode_b.at(i) == biggest_mode_b)
                        {
                            cout << numbers_b.at(i) << " ";
                            b_buff = numbers_b.at(i);
                        }
                    }

                    if (b_buff > b_fix)
                        b_fix = b_buff;

                    cout << endl;

                    Dataset data_rgb(g_save, b_save, label_rgb);
                    KNN knn_rgb(data_rgb, 3);
                    KnnPoint p;
                    p.x = g_fix;
                    p.y = b_fix;

                    int label = knn_rgb.Predict(p);
                    cout << "Label : " << label << endl;

                    file << i << " | " << label << endl;

                    // check correct guess
                    if (label == i)
                        correct_guess++;
                    else
                        wrong_guess++;

                    index_plt++;
                    pred.push_back(correct_guess);
                    index_plot.push_back(index_plt);
                }
            }
            file.close();
            plt::plot(index_plot, pred);
            plt::xlabel("data");
            plt::ylabel("correct guess");
            plt::title("KNN RGB  K: 3");
            plt::show();
        }
    }
}
void LoadParam(int label)
{
    if (label == USE_HSV)
    { // read file
        char path_file[100] = "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasB/db_obj_hsv.txt";
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
                    h_save.push_back(stoi(token));
                }
                else if (i == 1)
                {
                    s_save.push_back(stoi(token));
                }
                else
                {
                    label_hsv.push_back(stoi(token));
                }
                i++;
            }
        }
    }
    else
    {
        char path_file[100] = "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasB/db_obj_rgb.txt";
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
                    g_save.push_back(stoi(token));
                }
                else if (i == 1)
                {
                    b_save.push_back(stoi(token));
                }
                else
                {
                    label_rgb.push_back(stoi(token));
                }
                i++;
            }
        }
    }
}