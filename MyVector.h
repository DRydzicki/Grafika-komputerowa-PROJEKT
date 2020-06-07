#pragma once
#include<vector>
class MyVector
{
public:

    static std::vector<double> multMatVec(std::vector<std::vector<double>> matrix, std::vector<double> b) {
        int size = b.size();

        std::vector<double> a;
        a.resize(size);

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                a[i] += matrix[i][j] * b[j];

        return a;
    }

    static std::vector<std::vector<double>> multiply(std::vector<std::vector<double>> matrix, std::vector<std::vector<double>> points) {
        std::vector<double> a;
        a.resize(3);

        for (int i = 0; i < points.size(); i++) {
            a[0] = points[i][0];
            a[1] = points[i][1];
            a[2] = points[i][2];

            a = multMatVec(matrix, a);

            points[i][0] = a[0];
            points[i][1] = a[1];
            points[i][2] = a[2];
        }

        return points;
    }
};

