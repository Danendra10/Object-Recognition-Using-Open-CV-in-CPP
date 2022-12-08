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

struct KnnPoint
{
    float x;
    float y;
    int label;
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
            // put cs_1 to x, cs_2 to y, and label to label
            KnnPoint p;
            p.x = cs_1.at(i);
            p.y = cs_2.at(i);
            p.label = label.at(i);
            this->data.push_back(p);
        }
        cout << "Dataset created" << endl;
    }

    vector<KnnPoint> GetData()
    {
        return this->data;
    }

private:
    vector<KnnPoint> data;
};

class KNN
{
private:
    Dataset data;
    int k;

public:
    KNN(Dataset data, int k)
    {
        this->data = data;
        this->k = k;
    }

    int Predict(KnnPoint p)
    {
        // get data
        vector<KnnPoint> data = this->data.GetData();
        // get distance
        vector<double> distance;
        for (int i = 0; i < data.size(); i++)
        {
            double d = sqrt(pow(p.x - data.at(i).x, 2) + pow(p.y - data.at(i).y, 2));
            distance.push_back(d);
        }
        // get k nearest neighbor
        vector<int> k_nearest_neighbor;
        for (int i = 0; i < this->k; i++)
        {
            // get min distance
            double min = distance.at(0);
            int min_index = 0;
            for (int j = 0; j < distance.size(); j++)
            {
                if (distance.at(j) < min)
                {
                    min = distance.at(j);
                    min_index = j;
                }
            }
            // add to k nearest neighbor
            k_nearest_neighbor.push_back(data.at(min_index).label);
            // remove from distance
            distance.erase(distance.begin() + min_index);
        }
        // get prediction
        int prediction = 0;
        int max = 0;
        for (int i = 0; i < k_nearest_neighbor.size(); i++)
        {
            int count = 0;
            for (int j = 0; j < k_nearest_neighbor.size(); j++)
            {
                if (k_nearest_neighbor.at(i) == k_nearest_neighbor.at(j))
                {
                    count++;
                }
            }
            if (count > max)
            {
                max = count;
                prediction = k_nearest_neighbor.at(i);
            }
        }
        return prediction;
    }
};