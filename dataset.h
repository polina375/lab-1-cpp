#pragma once
#include <vector>
#include <fstream>
#include <cstdlib>
#include "types.h"
#include "linear.h"

class Dataset {
public:
    static std::vector<Point2D> generate(int n, float k, float b) {
        std::vector<Point2D> data;
        data.reserve(n);

        for (int i = 0; i < n; i++) {
            float x = -2 + (float)rand() / RAND_MAX * 4;
            float y = -2 + (float)rand() / RAND_MAX * 4;
            float label = (y > k * x + b) ? 1 : 0;
            data.push_back({ x,y,label });
        }

        return data;
    }

    static bool saveCSV(const std::vector<Point2D>& data, const char* filename) {
        std::ofstream file(filename);
        if (!file) return false;

        file << "x,y,label\n";
        for (auto& p : data)
            file << p.x << "," << p.y << "," << p.label << "\n";
        return true;
    }
};
