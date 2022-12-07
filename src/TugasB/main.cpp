#include "histogram_learning/TugasA/main.h"
#include <fstream>

char image_path[100];

void SortMatrix(int *matrix);

/**
 * @param first_data: vector of first data
 * @param second_data: vector of second data
 * @param label: vector of label
 * @param cs: color space
 */
void SaveData(vector<int> first_data, vector<int> second_data, vector<int> label, int cs);
#define USE_RGB 1
#define USE_HSV 0

int h_fix = 0, s_fix = 0, v_fix = 0;
int h_buff, s_buff, v_buff;
// for saving data
vector<int> h_save, s_save, label_hsv;

int r_fix = 0, g_fix = 0, b_fix = 0;
int r_buff, g_buff, b_buff;
// for saving data
vector<int> g_save, b_save, label_rgb;

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
                        h_fix = 0, s_fix = 0, v_fix = 0;
                        vector<Mat> hsv_planes;
                        split(image_hsv, hsv_planes);
                        int histSize = 256;
                        float range[] = {0, 256};
                        const float *histRange = {range};
                        bool uniform = true;
                        bool accumulate = false;
                        Mat hist_h, hist_s, hist_v;
                        calcHist(&hsv_planes[0], 1, 0, Mat(), hist_h, 1, &histSize, &histRange, uniform, accumulate);
                        calcHist(&hsv_planes[1], 1, 0, Mat(), hist_s, 1, &histSize, &histRange, uniform, accumulate);
                        calcHist(&hsv_planes[2], 1, 0, Mat(), hist_v, 1, &histSize, &histRange, uniform, accumulate);

                        // show hist
                        int hist_width = 1920;
                        int hist_height = 1080;
                        int bin_w = cvRound((double)hist_width / histSize);
                        Mat histImage(hist_height, hist_width, CV_8UC3, Scalar(0, 0, 0));

                        normalize(hist_h, hist_h, 0, histImage.rows, NORM_MINMAX, -1, Mat());
                        normalize(hist_s, hist_s, 0, histImage.rows, NORM_MINMAX, -1, Mat());
                        normalize(hist_v, hist_v, 0, histImage.rows, NORM_MINMAX, -1, Mat());

                        // draw histogram
                        for (int i = 1; i < histSize; i++)
                        {
                            line(histImage, Point(bin_w * (i - 1), hist_height - cvRound(hist_h.at<float>(i - 1) * hist_height)),
                                 Point(bin_w * (i), hist_height - cvRound(hist_h.at<float>(i) * hist_height)),
                                 Scalar(255, 0, 0), 2, 8, 0);
                            line(histImage, Point(bin_w * (i - 1), hist_height - cvRound(hist_s.at<float>(i - 1) * hist_height)),
                                 Point(bin_w * (i), hist_height - cvRound(hist_s.at<float>(i) * hist_height)),
                                 Scalar(0, 255, 0), 2, 8, 0);
                            line(histImage, Point(bin_w * (i - 1), hist_height - cvRound(hist_v.at<float>(i - 1) * hist_height)),
                                 Point(bin_w * (i), hist_height - cvRound(hist_v.at<float>(i) * hist_height)),
                                 Scalar(0, 0, 255), 2, 8, 0);
                        }

                        // save histogram
                        char hist_path[100];
                        sprintf(hist_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasA/%d/%d_%d_hist_hsv.png", i, i, j);
                        imwrite(hist_path, histImage);

                        // convert hsv to vector
                        vector<int> h_vec, s_vec, v_vec;
                        for (int i = 0; i < image.rows; i++)
                        {
                            for (int j = 0; j < image.cols; j++)
                            {
                                h_vec.push_back(image.at<Vec3b>(i, j)[0]);
                                s_vec.push_back(image.at<Vec3b>(i, j)[1]);
                                v_vec.push_back(image.at<Vec3b>(i, j)[2]);
                            }
                        }

                        // Get the most frequent value of H

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

                        // Get the most frequent value of S

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

                        // Get the most frequent value of V

                        int biggest_mode_v = 0;
                        vector<double> mode_v, numbers_v;
                        numbers_v.push_back(v_vec.at(0));
                        mode_v.push_back(1);
                        int count_v = 0;

                        for (int i = 0; i < v_vec.size(); i++)
                        {
                            if (v_vec.at(i) > 0)
                            {
                                if (v_vec.at(i) == numbers_v.at(count_v))
                                    mode_v.at(count_v)++;
                                else
                                {
                                    if (biggest_mode_v < mode_v.at(count_v))
                                        biggest_mode_v = mode_v.at(count_v);

                                    count_v++;
                                    mode_v.push_back(1);
                                    numbers_v.push_back(v_vec.at(i));
                                }
                            }
                        }

                        for (int i = 0; i < mode_v.size(); i++)
                        {
                            if (mode_v.at(i) == biggest_mode_v)
                            {
                                cout << numbers_v.at(i) << " ";
                                v_buff = numbers_v.at(i);
                            }
                        }

                        if (v_buff > v_fix)
                            v_fix = v_buff;

                        cout << endl
                             << "Final : " << h_fix << " " << s_fix << " " << v_fix << endl;

                        // save object identification
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }

                h_save.push_back(h_fix);
                s_save.push_back(s_fix);
                label_hsv.push_back(i);
                SaveData(h_save, s_save, label_hsv, USE_HSV);
            }
        }
        else
        {
            for (uint8_t i = 1; i <= 10; i++)
            {
                for (uint8_t j = 1; j <= 3; j++)
                {
                    // do the same as above but in RGB
                    sprintf(image_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/dataset/tugasA/%d/%d_%d.png", i, i, j);
                    cout << image_path << endl;
                    image = imread(image_path);

                    try
                    {
                        r_fix = 0, g_fix = 0, b_fix = 0;
                        vector<Mat> rgb_planes;
                        split(image, rgb_planes);
                        int histSize = 256;
                        float range[] = {0, 256};
                        const float *histRange = {range};
                        bool uniform = true;
                        bool accumulate = false;
                        Mat hist_r, hist_g, hist_b;
                        calcHist(&rgb_planes[0], 1, 0, Mat(), hist_r, 1, &histSize, &histRange, uniform, accumulate);
                        calcHist(&rgb_planes[1], 1, 0, Mat(), hist_g, 1, &histSize, &histRange, uniform, accumulate);
                        calcHist(&rgb_planes[2], 1, 0, Mat(), hist_b, 1, &histSize, &histRange, uniform, accumulate);

                        // show hist
                        int hist_width = 1920;
                        int hist_height = 1080;
                        int bin_w = cvRound((double)hist_width / histSize);
                        Mat histImage(hist_height, hist_width, CV_8UC3, Scalar(0, 0, 0));

                        normalize(hist_r, hist_r, 0, histImage.rows, NORM_MINMAX, -1, Mat());
                        normalize(hist_g, hist_g, 0, histImage.rows, NORM_MINMAX, -1, Mat());
                        normalize(hist_b, hist_b, 0, histImage.rows, NORM_MINMAX, -1, Mat());

                        // draw histogram
                        for (int i = 1; i < histSize; i++)
                        {
                            line(histImage, Point(bin_w * (i - 1), hist_height - cvRound(hist_r.at<float>(i - 1) * hist_height)),
                                 Point(bin_w * (i), hist_height - cvRound(hist_r.at<float>(i) * hist_height)),
                                 Scalar(255, 0, 0), 2, 8, 0);
                            line(histImage, Point(bin_w * (i - 1), hist_height - cvRound(hist_g.at<float>(i - 1) * hist_height)),
                                 Point(bin_w * (i), hist_height - cvRound(hist_g.at<float>(i) * hist_height)),
                                 Scalar(0, 255, 0), 2, 8, 0);
                            line(histImage, Point(bin_w * (i - 1), hist_height - cvRound(hist_b.at<float>(i - 1) * hist_height)),
                                 Point(bin_w * (i), hist_height - cvRound(hist_b.at<float>(i) * hist_height)),
                                 Scalar(0, 0, 255), 2, 8, 0);
                        }

                        // save histogram
                        char hist_path[100];
                        sprintf(hist_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasA/%d/%d_%d_hist_rgb.png", i, i, j);
                        imwrite(hist_path, histImage);
                        // convert image to vector
                        vector<int> r_vec, g_vec, b_vec;

                        for (int i = 0; i < image.rows; i++)
                        {
                            for (int j = 0; j < image.cols; j++)
                            {
                                r_vec.push_back(image.at<Vec3b>(i, j)[0]);
                                g_vec.push_back(image.at<Vec3b>(i, j)[1]);
                                b_vec.push_back(image.at<Vec3b>(i, j)[2]);
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

                        // do the same for g_vec
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

                        // do the same for b_vec
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
                        cout << "Final data: ";
                        cout << r_fix << " " << g_fix << " " << b_fix << endl;
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                g_save.push_back(g_fix);
                b_save.push_back(b_fix);
                label_rgb.push_back(i);
                SaveData(g_save, b_save, label_rgb, USE_RGB);
            }
        }
    }
}
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