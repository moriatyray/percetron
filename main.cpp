


//1预测函数 -1.1
//2训练函数 获取数据集大小  获取特征维度    迭代训练    遍历数据集  预测结果
//3生成数据函数 随机数生成器    正态分布     生成数据   计算点积    确定标签    添加标签
//4main
//5


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "math.h"
#include <random>
 
using namespace std;
//-1.1计算特征向量x和权重向量w的点积+偏置b  如果预测值大于0，则返回1，否则返回-1
int predict(vector<double> x, vector<double> w, double b) {
    double wx_add_b = 0;
    for (int i = 0; i < x.size(); i++) {
        wx_add_b += x[i] * w[i];
    }
    double pred = wx_add_b + b;
    return pred > 0 ? 1 : -1;
}

// 训练函数
void train(vector<vector<double>> X, vector<int> y, vector<double> w, double& b, double learning_rate, int epochs) {
    int n = X.size(); // 获取数据集大小
    int m = X[0].size(); // 获取特征维度
    for (int i = 0; i < epochs; i++) { // 迭代训练
        for (int j = 0; j < n; j++) { // 遍历数据集
            int pred = predict(X[j], w, b); // 预测结果
            if (pred != y[j]) // 判断是否需要更新权重和偏置
            { 
                for (int k = 0; k < m; k++) {
                    w[k] += learning_rate * y[j] * X[j][k]; // 新权重
                }
                b += learning_rate * y[j];  // 新偏置
            }
        }
    }
}


// 生成数据函数
void data(int num, vector<vector<double>>& X, vector<int>& y) {
    default_random_engine generator; // 定义随机数生成器
    normal_distribution<double> distribution(0.0, 1.0); // 定义正态分布
    for (int i = 0; i < num; i++) { // 生成数据
        vector<double> feature;
        feature.push_back(distribution(generator));
        feature.push_back(distribution(generator));
        X.push_back(feature);
        double dot_product = feature[0] * 2 + feature[1] * 3; // 计算点积
        int label = dot_product > 0 ? 1 : -1; // 根据点积确定标签
        y.push_back(label); // 添加标签
        
//         cout << "X:" << endl;
//      for (const auto& row : X || const auto& label : y) {
//        for (const auto& element : row) {
//         cout << element << " ";
//          }
//          cout << endl;
//      }

// cout << "y:" << endl;
// for (const auto& label : y) {
//     cout << label << " ";
// }
// cout << endl;

        for (const auto& x : feature) {
            cout << x << " ";
        }
        cout << label << endl;

    }
}


int main() {
    // 生成数据
    vector<vector<double>> X;
    vector<int> y;
    data(10, X, y);
    
    // 初始化权重和偏置
    vector<double> w = {0, 0};
    double b = 0;
    
    double learning_rate = 0.1;
    int epochs = 100;
    // 训练模型
    train(X, y, w, b, learning_rate, epochs);
    // 输出训练结果
    cout << "w: " << w[0] << ", " << w[1] << ", b: " << b << std::endl;
    
    // 随机生成测试数据
    default_random_engine generator;
    normal_distribution<double> distribution(0.0, 1.0);
    vector<double> x_test = {distribution(generator), distribution(generator)};
    // 预测结果
    int pred = predict(x_test, w, b);
    cout<<"x_test "<<x_test[0]<<" "<<x_test[1]<<" pred: "<<pred<<endl;
 
    return 0;
}



