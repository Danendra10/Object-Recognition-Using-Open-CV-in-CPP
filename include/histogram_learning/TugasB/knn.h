#pragma once
#ifndef KNN_H
#define KNN_H
#include <ctime>

#endif // BLOGS_DATASET_H
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
// using namespace cv;

/*
h/g
l
l
l
l
l
l
l
l
l
l
l           .(titik prediksi)
l       .(h, s, dengan label)
l   .(h,s dengan label)
l_______________________________________________________________________________ s/b
*/

struct Point
{
    int x;
    int y;
};

class Dataset
{
public:
    Dataset() = default;
    Dataset(vector<int> cs_1, vector<int> cs_2, vector<int> label)
    {
        cout << "Creating dataset..." << endl;
        for (int i = 0; i < cs_1.size(); i++)
        {
            this->data.push_back({cs_1.at(i), cs_2.at(i)});
            this->label.push_back(label.at(i));
        }
        cout << "Dataset created" << endl;
    }

    vector<Point> GetData()
    {
        return this->data;
    }

    vector<int> GetLabel()
    {
        return this->label;
    }

private:
    vector<Point> data;
    vector<int> label;
};

class KNN
{
public:
    KNN() = default;
    KNN(Dataset dataset, int k)
    {
        this->dataset = dataset;
        this->k = k;
    }

    int Predict(Point p)
    {
        vector<int> label = this->dataset.GetLabel();
        vector<Point> data = this->dataset.GetData();

        vector<int> distance;
        for (int i = 0; i < data.size(); i++)
        {
            distance.push_back(this->EuclideanDistance(p, data.at(i)));
        }

        vector<int> sorted_distance = this->SortDistance(distance);
        vector<int> k_nearest_label = this->GetKNearestLabel(sorted_distance);

        return this->GetMostFrequentLabel(k_nearest_label);
    }

private:
    Dataset dataset;
    int k;

    int EuclideanDistance(Point p1, Point p2)
    {
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    }

    vector<int> SortDistance(vector<int> distance)
    {
        vector<int> sorted_distance = distance;
        for (int i = 0; i < sorted_distance.size(); i++)
        {
            for (int j = 0; j < sorted_distance.size(); j++)
            {
                if (sorted_distance.at(i) < sorted_distance.at(j))
                {
                    int temp = sorted_distance.at(i);
                    sorted_distance.at(i) = sorted_distance.at(j);
                    sorted_distance.at(j) = temp;
                }
            }
        }

        return sorted_distance;
    }

    vector<int> GetKNearestLabel(vector<int> sorted_distance)
    {
        vector<int> k_nearest_label;
        for (int i = 0; i < this->k; i++)
        {
            k_nearest_label.push_back(this->dataset.GetLabel().at(i));
        }

        return k_nearest_label;
    }

    int GetMostFrequentLabel(vector<int> k_nearest_label)
    {
        int most_frequent_label = k_nearest_label.at(0);
        int max_count = 0;
        for (int i = 0; i < k_nearest_label.size(); i++)
        {
            int count = 0;
            for (int j = 0; j < k_nearest_label.size(); j++)
            {
                if (k_nearest_label.at(i) == k_nearest_label.at(j))
                {
                    count++;
                }
            }

            if (count > max_count)
            {
                max_count = count;
                most_frequent_label = k_nearest_label.at(i);
            }
        }

        return most_frequent_label;
    }
};