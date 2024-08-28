﻿#include<test.h>
#include<Math/Graph.h>

using namespace ld::math;
using namespace Eigen;

int mainx()
{
    // 初始化数据，这里只是示例，实际应用中需要从文件或某种方法获取数据
    VectorXd input(2);
    input << 1, -2;
    VectorXd target(1);
    target << 3;

    // 初始化网络参数
    MatrixXd W1(2, 2);
    W1 << 0, 0,
        0, 0;
    VectorXd b1(2);
    b1 << 0, 0;
    MatrixXd W2(2, 1);
    W2 << 0, 0;
    VectorXd b2(1);
    b2 << 0;

    // 前向传播
    auto temp = W1 * input;
    VectorXd z1 = temp + b1;
    VectorXd a1 = z1.unaryExpr(&sigmoid);
    VectorXd z2 = W2 * a1 + b2;
    VectorXd a2 = z2.unaryExpr(&sigmoid);

    // 计算损失
    double loss = (a2 - target).squaredNorm();
    cout << "Loss: " << loss << endl;

    // 反向传播
    VectorXd dz2 = (a2 - target) * z2.unaryExpr(&dSigmoid);
    VectorXd da1 = W2.transpose() * dz2;
    VectorXd dz1 = da1 * z1.unaryExpr(&dSigmoid);

    // 更新参数
    W2 -= dz2 * a1.transpose();
    b2 -= dz2;
    W1 -= dz1 * input.transpose();
    b1 -= dz1;

    return 0;
}


int main()
{
	console.LogMessage("start"); 
    Perceptron<5, 3> a;
    a.get_ref()(3, 1) = 0.2;
    Perceptron<3, 2> b;
    Perceptron<2, 1> c;
    Matrix<Number, 2, 5> data;
    data << 5, 1, 2, 4, 0,
        1, 2, 5, 10, 99;
    Matrix<Number, 1, 1> test;
    test << 1;
    auto result = predict(data, a);
    cout << result << '\n';
	console.LogMessage("end");
}


