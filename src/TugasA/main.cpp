#include "histogram_learning/TugasA/main.h"
// include for sleep
#include <unistd.h>

char image_path[100];

vector<uint8_t> nilai_h;
vector<uint8_t> nilai_s;
vector<uint8_t> nilai_v;

int main()
{
    // load image
    for (uint8_t i = 1; i <= 10; i++)
    {
        for (uint8_t j = 1; j <= 3; j++)
        {
            sprintf(image_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/dataset/tugasA/%d/%d_%d.png", i, i, j);
            cout << image_path << endl;
            image = imread(image_path);
            cvtColor(image, image_hsv, COLOR_BGR2HSV);

            // create histogram of H, S, and V
            try
            {
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
                char hist_path[200];
                sprintf(hist_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasA/hist/%d/%d_%d.png", i, i, j);
                imwrite(hist_path, histImage);

                // show image
                imshow("image", image);
                imshow("HSV", image_hsv);
                imshow("histogram", histImage);
                // sleep(5);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
}
