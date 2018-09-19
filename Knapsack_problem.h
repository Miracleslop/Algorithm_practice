//
// Created by l on 18-9-19.
// 本程序模拟01背包问题的推导过程，并提供测试程序

#ifndef ALGORITHM_PRACTICE_PACKSACK_QUESTION_H
#define ALGORITHM_PRACTICE_PACKSACK_QUESTION_H

#endif //ALGORITHM_PRACTICE_PACKSACK_QUESTION_H

#include <iostream>
#include <cmath>

using namespace std;

struct Good {
    Good(const int _weight, const int _value) : weight(_weight), value(_value) {}

    const int weight;
    const int value;
};

int knapsack01(const int gn, const int bw, Good *(&gs)[30]) {
    //  推导记录矩阵， 最大价值
    int deduce[100][100], maxValue = -1;

    //  初始化最后一排数据
    for (int i = 0; i < bw; ++i) {
        int tw = i + 1;
        deduce[gn - 1][i] = gs[gn - 1]->weight > tw ? 0 : gs[gn - 1]->value;
        if (deduce[gn - 1][i] > maxValue) {
            maxValue = deduce[gn - 1][i];
        }
    }

    //  从倒数第二行开始推导
    for (int n = gn - 2; n >= 0; --n) {
        Good *good = gs[n];
        for (int w = 0; w < bw; ++w) {
            int tw = w + 1;
            deduce[n][w] = good->weight > tw ?
                           deduce[n + 1][w] : max(deduce[n + 1][w], deduce[n + 1][w - good->weight] + good->value);
            if (deduce[n][w] > maxValue) {
                maxValue = deduce[n][w];
            }
        }
    }

    //  输出推导矩阵
    for (int i = 0; i < gn; ++i) {
        for (int j = 0; j < bw; ++j) {
            printf("%d, ", deduce[i][j]);
        }
        printf("\n");
    }
    //  返回最大价值
    return maxValue;
}


void test() {
    std::cout << "Hello, World!" << std::endl;


    const int good_N = 5, bag_W = 10;
    Good *goods[30];
    goods[0] = new Good(2, 6);
    goods[1] = new Good(2, 3);
    goods[2] = new Good(6, 5);
    goods[3] = new Good(5, 4);
    goods[4] = new Good(4, 6);

    //  动态规划，开始推导
    knapsack01(good_N - 1, bag_W, goods);
}