#include "histogram_learning/TugasB/knn.h"

#define USE_RGB 1
#define USE_HSV 0

void LoadParam(int label);

vector<int> h_save, s_save, label_hsv;

int main()
{
    LoadParam(USE_HSV);
    // print
    for (int i = 0; i < h_save.size(); i++)
    {
        cout << h_save.at(i) << "," << s_save.at(i) << "," << label_hsv.at(i) << endl;
    }
    Dataset data_hsv(h_save, s_save, label_hsv);

    KNN knn(data_hsv, 3);
    Point p;
    p.x = 100;
    p.y = 176;
    knn.Predict(p);

    // print the prediction
    cout << "Prediction: " << knn.Predict(p) << endl;
}

void LoadParam(int label)
{
    // read file
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