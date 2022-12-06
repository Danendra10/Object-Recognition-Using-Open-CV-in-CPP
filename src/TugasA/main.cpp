#include "histogram_learning/TugasA/main.h"

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
            // put H , V and S data to a variable
            // for (int row = 0; row < image_hsv.rows; row++)
            // {
            //     for (int cols = 0; cols < image_hsv.cols; cols++)
            //     {
            //         nilai_h.push_back(image_hsv.at<Vec3b>(row, cols)[0]);
            //         nilai_s.push_back(image_hsv.at<Vec3b>(row, cols)[1]);
            //         nilai_v.push_back(image_hsv.at<Vec3b>(row, cols)[2]);
            //     }
            // }

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

                // // normalize histogram
                // normalize(hist_h, hist_h, 0, 1, NORM_MINMAX, -1, Mat());
                // normalize(hist_s, hist_s, 0, 1, NORM_MINMAX, -1, Mat());
                // normalize(hist_v, hist_v, 0, 1, NORM_MINMAX, -1, Mat());

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
                sprintf(hist_path, "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/result/tugasA/%d/%d_%d_hist.png", i, i, j);
                imwrite(hist_path, histImage);

                // show image
                imshow("image", image);
                imshow("HSV", image_hsv);
                imshow("histogram", histImage);
                waitKey(0);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            /////////////////////////////////////////////////////////

            // // conver 3 channel hsv to 1 channel
            // cvtColor(image_hsv, image_gray, COLOR_BGR2GRAY);

            // // histogram
            // int histSize = 256;
            // float range[] = {0, 256};
            // const float *histRange = {range};
            // bool uniform = true;
            // bool accumulate = false;
            // Mat hist;

            // calcHist(&image_hsv, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

            // // normalize
            // normalize(hist, hist, 0, 1, NORM_MINMAX, -1, Mat());

            // // print
            // for (int i = 0; i < histSize; i++)
            // {
            //     cout << hist.at<float>(i) << endl;
            // }

            // // show
            // int hist_w = 512;
            // int hist_h = 400;
            // int bin_w = cvRound((double)hist_w / histSize);

            // Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

            // normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

            // for (int i = 1; i < histSize; i++)
            // {
            //     line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
            //          Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
            //          Scalar(255, 0, 0), 2, 8, 0);
            // }

            // imshow("calcHist Demo", histImage);

            // waitKey(0);
        }
    }
    // for (uint8_t i = 1; i <= 5; i++)
    // {
    //     sprintf(image_path, "/home/andreas/Documents/Programming/Cpp/opencv_learning/histogram_learning/TugasA/images/%d.jpg", i);
    //     Mat image = imread(image_path, IMREAD_GRAYSCALE);
    //     if (image.empty())
    //     {
    //         cout << "Could not read the image: " << image_path << endl;
    //         return 1;
    //     }

    //     // show image
    //     imshow("Image", image);
    //     waitKey(0);

    //     // calculate histogram
    //     Mat histogram;
    //     int channels[] = {0};
    //     int histSize[] = {256};
    //     float range[] = {0, 256};
    //     const float *ranges[] = {range};
    //     calcHist(&image, 1, channels, Mat(), histogram, 1, histSize, ranges, true, false);

    //     // show histogram
    //     int hist_w = 512, hist_h = 400;
    //     int bin_w = cvRound((double)hist_w / histSize[0]);
    //     Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    //     normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    //     for (int i = 1; i < histSize[0]; i++)
    //     {
    //         line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
    //              Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
    //              Scalar(255, 0, 0), 2, 8, 0);
    //     }
    //     imshow("Histogram", histImage);
    //     waitKey(0);
    // }
}