#pragma once

#ifndef __FILE_FOURIER
#define __FILE_FOURIER

#include<Math/MathConfig.h>
#include<vector>
#include<Windows.h>
#include<opencv2/opencv.hpp>
#include<Eigen/Dense>

#define SHOW_AMPLITUDE 1

#define SHOW_PHASE 2

#define SHOW_AMPLITUDE_PHASE 3

#define SHOW_TRIGONOMETRIC_FIT 4

#define CLOSE_RESULT_WINDOW 1

#define CLOSE_ORIGIN_DATA_WINDOW 2

#define CLOSE_RESULT_ORIGIN 3

#define FIT_DEDUCTING_ERROR_POINT 1

#define FIT_NORMAL 2

namespace ld
{
	namespace math
	{
		struct sort_partical_self
		{
			double position;
			double value;
		};
		/*粒子类*/
		class one_partical {
		public:
			std::vector<sort_partical_self> self_history;//粒子的历史
			double V = 0;//粒子速度
			double position = 0;//粒子位置
			double now_value = 0;//粒子对应函数值
			double self_best_position = 1;//粒子最佳函数取值对应的最佳位置
			double self_best_value = 5000;//粒子最佳函数取值
			double get_self_best_and_update_best();
			double set_position(double input_position) {
				position = input_position;
			}
			/*更新速度*/
			double set_v(double input_v) {
				V = input_v;
			}
			void historey_update(double position, double value) {
				sort_partical_self Input_;
				Input_.position = position;
				Input_.value = value;
				self_history.push_back(Input_);
			}
		};
		/*粒子群类*/
		class partical_swarm {
		public:
			/*放置初始位置的粒子*/
			void put_particals_in_region(double Lower, double Upper);
			/*设置粒子数目*/
			void set_patical_number(int input_partical_number);
			/*设置迭代参数*/
			void set_parameters(int input_partical_number = 20, int input_max_iteration = 100, double input_omiga_begin = 0.9, double input_omiga_end = 0.4, double input_self_index = 2.0, double input_social_index = 2.5);
			/*迭代*/
			void calc_and_update(double(*value_function)(double));
			double get_best_parameter() {
				return best_position;
			}
			partical_swarm();

			partical_swarm(int input_patical_number, int input_max_iteration);

			~partical_swarm() {

			}
		private:
			std::vector<one_partical> Particals;
			std::vector<sort_partical_self> global_value_vector;//所有粒子的位置和函数值
			int iteration_count = 0;//迭代次数
			int max_iteration_number = 10;//最大迭代次数
			int patical_number = 0;
			double lower_ = 0;
			double upper_ = 0;
			double omiga_begin = 0.9;
			double omiga_end = 0.4;
			double self_index = 2.0;
			double social_index = 2.0;
			double global_best_value = 9999999;
			double global_best_position = 0;
			double best_value = 9999999999;
			double best_position = 0;
			double get_omiga(int input_iteration_count) {
				return (omiga_begin - omiga_end) * (double(max_iteration_number) - double(input_iteration_count)) + omiga_end;
			}
			void update_global_best();
		};
		/*三角函数参数类*/
		struct trigonometric_function_paramater {
			double A = 0;//系数A
			double B = 0;//系数B
			double omiga = 0;//角频率
			double C = 0;//系数C
			double error_value = 10000;//目标函数值
		};
		/*用于排序*/
		struct sort_function_value
		{
			double omiga = 0;
			double error_value = 100000;
		};
		struct function_point {
			double x = 0;
			double y = 0;
			bool is_error_point = FALSE;
		};

		struct to_sort {
			int position = 0;//位置
			double amplitude = 0;//幅度
			double phase = 0;//相位
			double frequency = 0;
		};

		class Fourier_parameter {
		public:
			int sample_number = 0;
			std::vector<double> phase;//相位
			std::vector<double> amplitude;//幅值
		private:
		};

		/*傅里叶变换器*/
		class Fourier_transformer {
		public:
			/** @brief 输入数据
			@param input_data 输入的数据
			@param input_time 数据对应的时间位置
			*/
			void Input_data(double input_data, double input_time);
			/*重置但是保留了针对上一次输入的数据的预测能力*/
			void reset_retain_predictive_ability();
			/** @brief 显示幅频曲线和相频曲线
			@param Show_mode 显示模式，可选：SHOW_AMPLITUDE_PHASE，同时显示幅频曲线和相频曲线；SHOW_AMPLITUDE，只显示幅频曲线；SHOW_PHASE，只显示相频曲线
			@param rows_ 显示图像的行数
			@param step_ 两个频率之间的间隔
			*/
			void show_frequency_domian(int Show_mode = SHOW_AMPLITUDE_PHASE, int rows_ = 800, int step_ = 10);
			/** @brief 显示原始信号
			@param rows_ 显示图像的行数
			@param step_ 两个频率之间的间隔
			*/
			void show_original_data(int rows_ = 800, int step_ = 10);
			/** @brief 显示拟合信号
			@param rows_ 显示图像的行数
			@param step_ 两个频率之间的间隔
			*/
			void show_fit_result(int rows_ = 800, int step_ = 10);
			/** @brief 利用傅里叶变换分离出的周期信号得到误差预测结果
			@param input_time_position 输入的时间
			@param frequency_number 选择使用前几的谐波分量预测误差
			@param low_frequency_domain 定义低频段的系数，该函数只对低频段的周期信号进行预测
			*/
			double Error_prediction_use_DFT(double input_time_position, int frequency_number = 4, double low_frequency_domain = 0.3);
			/** @brief 利用傅里叶变换分离出的周期信号得到误差预测结果
			@param input_time_position 输入的时间
			*/
			double Error_prediction_use_trigonometric_function_fit(double input_time_position);
			/** @brief 离散傅里叶变换求解
			*/
			void Solve_();
			/** @brief 三角函数拟合求解
			@param exquisite_number 精细寻找步长系数
			*/
			void Solve_fit(int exquisite_number = 7000);
			/** @brief 关闭所有显示窗口
			*/
			void close_display_window(int window_choose = CLOSE_RESULT_ORIGIN);
			/** @brief 打印分离出的谐波分量数据
			@param show_number 打印前几个分量
			*/
			void printf_data(int show_number = 5);
			/*傅里叶变换暂时没有能力预测*/
			bool no_prediction_power();
			Fourier_transformer();
		private:
			int data_number = 0;
			int data_number_pre = 0;
			double time_0_position_pre = 0;//初始时刻的时间位置，只能由solve函数赋值
			bool DFT_HAVE_SOLVE = FALSE;
			bool fit_parameter_have_solve = FALSE;
			std::vector<trigonometric_function_paramater> fit_funtion_pre;
			std::vector<double> time_vector;
			std::vector<double> The_data_in_time;//时域离散数据,位置即坐标
			std::vector<double> Re_data;//实部
			std::vector<double> Im_data;//虚部
			std::vector<double> Amplitude;//幅值
			std::vector<double> Phase;//相位
			std::vector<double> frequency_;//频率
			std::vector<to_sort> sorting;//用于预测排序的容器
			std::vector<function_point> Function_Points;//用于拟合的样本点
			/*得到实部和虚部信息*/
			void get_Re_Im_data();
			/*得到频率和相位信息*/
			void get_A_p();
			/*得到最大的前n个谐波分量参数*/
			Fourier_parameter get_harmonic_parameters();
			double DFT_max(double a, double b);
			/*求反正切*/
			double DFT_arctan(double input_value, double eqs_ = 0.00001);
			/** @brief 固定频率拟合三角函数
			@param aomiga 输入的角频率
			@param Fit_mode 拟合模式
			@param error_domain 误差区间，利用正态分布扣除误差
			*/
			trigonometric_function_paramater fit_trigonometric_function_paramater(double aomiga, int Fit_mode = FIT_NORMAL, double error_domain = 3.0);
			/** @brief 判断三角函数是否为空
			@param input_parameter 输入的三角函数
			*/
			bool fit_funtion_pre_empty(trigonometric_function_paramater input_parameter);
			/*随机数*/
			double DFT_random(double a, double b, double precision = 2);
			/*最小值*/
			double DFT_min(double a, double b);
		};
	}
}


#endif // !__FILE_FOURIER

