#include<Fourier.h>

namespace ld
{
	namespace math
	{
		clock_t start_c, end_c;
		std::vector<function_point> partical_Function_Points;
		bool sort_comp(to_sort& S1, to_sort& S2) {
			return S1.amplitude > S2.amplitude;
		}

		bool function_value_sort_comp(sort_function_value& S1, sort_function_value& S2) {//从小到大排序
			return S1.error_value < S2.error_value;
		}

		bool one_partical_find_self_best(sort_partical_self& S1, sort_partical_self& S2) {
			return S1.value < S2.value;
		}

		double random_(double a, double b, double precision = 2) {
			int OUTPUT = 0;
			double GAIN = 1;
			int i = 0;
			for (i = 0; i < precision; i++) {
				GAIN = GAIN * 10;
			}
			int A = a * GAIN, B = b * GAIN;
			OUTPUT = (rand() % (B - A + 1)) + A;
			double OUTPUT2 = 0;
			OUTPUT2 = OUTPUT;
			OUTPUT2 = OUTPUT2 / GAIN;
			return OUTPUT2;
		}

		double partical_fit_trigonometric_function_paramater(double aomiga) {
			double sc = 0, c2 = 0, s2 = 0, s = 0, c = 0, y = 0, ys = 0, yc = 0, y2 = 0;//需要计算的取值
			int i = 0;
			double ti = 0, yi = 0;
			double value_ = 0, A = 0, B = 0, C = 0;
			double average = 0, derta = 0;//统计几何参数
			double number_ = 0;
			double judge_value = 0;
			Eigen::MatrixXd A_Matrix(3, 3), B_Matrix(3, 1), a_vector(3, 1);
			trigonometric_function_paramater output_;
			double data_number = double(partical_Function_Points.size());
			for (i = 0; i < partical_Function_Points.size(); i++) {//循环赋值，从fuction points取数据
				ti = partical_Function_Points[i].x * aomiga;
				yi = partical_Function_Points[i].y;
				//std::cout <<"ti"<< Function_Points[i].y << std::endl;
				sc += sin(ti) * cos(ti);
				c2 += cos(ti) * cos(ti);
				s2 += sin(ti) * sin(ti);
				s += sin(ti);
				c += cos(ti);
				y += yi;
				ys += yi * sin(ti);
				yc += yi * cos(ti);
				y2 += yi * yi;
			}
			A_Matrix << c2, sc, c,
				sc, s2, s,
				c, s, double(data_number);
			B_Matrix << yc,
				ys,
				y;
			if (A_Matrix.determinant() != 0) {//安全
				//std::cout << A_Matrix.determinant() << std::endl;
				a_vector = (A_Matrix.inverse()) * B_Matrix;
				A = a_vector(0, 0); B = a_vector(1, 0); C = a_vector(2, 0);
				value_ = y2 + \
					A * A * c2 + \
					B * B * s2 + \
					2.0 * A * B * sc + \
					2.0 * A * C * c + \
					2.0 * B * C * s + \
					double(data_number) * C * C - \
					2.0 * A * yc - \
					2.0 * B * ys - \
					2.0 * C * y;
				output_.A = A; output_.B = B; output_.C = C; output_.omiga = aomiga; output_.error_value = value_;
				//std::cout << "1" << std::endl;
			}
			else {
				output_.error_value = 999999999;
			}
			//std::cout << output_.error_value << std::endl;
			return output_.error_value;
		}

		Fourier_transformer::Fourier_transformer() {
			srand(time(0));//丢随机数
		}

		double Fourier_transformer::DFT_max(double a, double b) {
			if (a > b)
				return a;
			else
				return b;
		}

		double Fourier_transformer::DFT_min(double a, double b) {
			if (a <= b)
				return a;
			else
				return b;
		}

		double Fourier_transformer::DFT_arctan(double input_value, double eqs_) {
			double start = -Pi / 2.0, end = Pi / 2.0, mid = 0;
			double start_value = 0, end_value = 0, mid_value = 0;
			double output_ = 0;
			int i = 0;;
			if ((tan(start) - input_value) * (tan(end) - input_value) < 0) {
				while (abs(start - end) > eqs_) {
					i++;
					mid = 0.5 * (start + end);
					mid_value = tan(mid) - input_value;
					start_value = tan(start) - input_value;
					end_value = tan(end) - input_value;
					if (abs(mid_value) < eqs_)
						break;
					else if (mid_value * start_value < 0)
						end = mid;
					else
						start = mid;
					if (i > 200)
						break;
				}
			}
			else {
				output_ = atan(input_value);
				return output_;
			}
			output_ = 0.5 * (start + end);
			//std::cout << i << std::endl;
			return output_;
		}

		void Fourier_transformer::Input_data(double input_data, double input_time) {
			function_point this_point;
			The_data_in_time.push_back(input_data);
			time_vector.push_back(input_time);
			this_point.x = input_time;
			this_point.y = input_data;
			Function_Points.push_back(this_point);
			data_number++;//输入的数据计数
		}

		void Fourier_transformer::reset_retain_predictive_ability() {
			data_number = 0;
			The_data_in_time.clear();
			Re_data.clear();
			Im_data.clear();
			Amplitude.clear();
			Phase.clear();
			time_vector.clear();
			frequency_.clear();
			Function_Points.clear();
			DFT_HAVE_SOLVE = FALSE;
		}

		void Fourier_transformer::get_Re_Im_data() {
			int i, k;
			double input_value_Re = 0, input_value_Im = 0;
			for (k = 0; k < data_number; k++) {
				input_value_Re = 0;
				input_value_Im = 0;
				for (i = 0; i < data_number; i++) {
					input_value_Re += The_data_in_time[i] * cos(2.0 * Pi * double(k) * double(i) / double(data_number));
					input_value_Im += -The_data_in_time[i] * sin(2.0 * Pi * double(k) * double(i) / double(data_number));
				}
				Re_data.push_back(input_value_Re);
				Im_data.push_back(input_value_Im);
				frequency_.push_back(2.0 * Pi * double(k) / double(data_number));
			}
		}

		void Fourier_transformer::get_A_p() {
			int k;
			to_sort this_sort;
			Re_data.clear();
			Im_data.clear();
			Amplitude.clear();
			Phase.clear();
			sorting.clear();
			get_Re_Im_data();
			for (k = 0; k < data_number; k++) {/*遍历求解*/
				if (Re_data[k] != 0 && Im_data[k] != 0) {
					Amplitude.push_back(sqrt(Re_data[k] * Re_data[k] + Im_data[k] * Im_data[k]));
					Phase.push_back(DFT_arctan(Im_data[k] / Re_data[k]));
				}
				else {
					Amplitude.push_back(0.0);
					Phase.push_back(0.0);
				}
				this_sort.position = k;
				this_sort.amplitude = Amplitude[k];
				this_sort.phase = Phase[k];
				this_sort.frequency = 2.0 * Pi * double(k) / double(data_number);
				sorting.push_back(this_sort);
			}
			data_number_pre = data_number;
			time_0_position_pre = time_vector[0];
			DFT_HAVE_SOLVE = TRUE;
		}

		void Fourier_transformer::show_frequency_domian(int Show_mode, int rows_, int step_) {
			if (data_number > 0) {
				if (DFT_HAVE_SOLVE) {
					int data_number1 = data_number / 2;
					cv::Mat show_mat(rows_, data_number1 * step_, CV_8UC3, cv::Scalar(255, 255, 255));
					cv::Point2d P1;
					cv::Point2d P2;
					cv::Point2d P3;
					cv::Point2d P4;
					double max_amplitude = *std::max_element(Amplitude.begin(), Amplitude.end());
					double max_phase = *std::max_element(Phase.begin(), Phase.end());
					double min_phase = *std::min_element(Phase.begin(), Phase.end());
					int i, position_after = 0;
					int base_line;
					int font_face = cv::FONT_HERSHEY_SIMPLEX;
					std::string text_A_w = "amplitude - w:";
					std::string text_P_w = "Phase - w:";
					max_phase = DFT_max(abs(max_phase), abs(min_phase));
					max_phase = 2.0 * max_phase;
					//cv::putText(show_mat,)
					cv::Size text_1_size = cv::getTextSize(text_A_w, font_face, 1, 1, &base_line);
					cv::Size text_2_size = cv::getTextSize(text_P_w, font_face, 1, 1, &base_line);
					if (Show_mode == SHOW_AMPLITUDE || Show_mode == SHOW_AMPLITUDE_PHASE) {
						cv::putText(show_mat, text_A_w, cv::Point(1, text_1_size.height + 1), font_face, 1, cv::Scalar(0, 0, 0), 2);
						cv::line(show_mat, cv::Point(text_1_size.width + 1, text_1_size.height / 2), cv::Point(text_1_size.width + 1 + 30, text_1_size.height / 2), cv::Scalar(0, 0, 255), 2);
					}
					else if (Show_mode == SHOW_PHASE || Show_mode == SHOW_AMPLITUDE_PHASE) {
						cv::putText(show_mat, text_P_w, cv::Point(1, text_1_size.height + 8 + text_2_size.height), font_face, 1, cv::Scalar(0, 0, 0), 2);
						cv::line(show_mat, cv::Point(text_1_size.width + 1, text_1_size.height + text_2_size.height / 2 + 8), cv::Point(text_1_size.width + 1 + 30, text_1_size.height + text_2_size.height / 2 + 8), cv::Scalar(255, 0, 0), 2);
					}
					for (i = 0; i < data_number1; i++) {
						if (i < data_number1 - 1) {
							position_after = i + 1;
							P1.x = double(i) * double(step_);
							P2.x = (double(i) + 1.0) * double(step_);
							P3.x = P1.x;
							P4.x = P2.x;
							P1.y = -Amplitude[i] * double(0.5 * double(rows_)) / (1.2 * max_amplitude) + 0.5 * double(rows_);
							P2.y = -Amplitude[position_after] * double(0.5 * double(rows_)) / (1.2 * max_amplitude) + 0.5 * double(rows_);
							P3.y = -Phase[i] * double(0.5 * double(rows_)) / (1.2 * max_phase) + 0.5 * double(rows_);
							P4.y = -Phase[position_after] * double(0.5 * double(rows_)) / (1.2 * max_phase) + 0.5 * double(rows_);
							if (Show_mode == SHOW_AMPLITUDE || Show_mode == SHOW_AMPLITUDE_PHASE)
								cv::line(show_mat, P1, P2, cv::Scalar(0, 0, 255), 2);
							if (Show_mode == SHOW_PHASE || Show_mode == SHOW_AMPLITUDE_PHASE)
								cv::line(show_mat, P3, P4, cv::Scalar(255, 0, 0), 2);
						}
					}
					cv::namedWindow("DFT result", cv::WINDOW_NORMAL);
					cv::resizeWindow("DFT result", cv::Size(1100, 400));
					cv::imshow("DFT result", show_mat);
					cv::waitKey(5);
				}
				else {
					std::cout << "数据未求解！" << std::endl;
				}
			}
			else {
				std::cout << "未输入数据！" << std::endl;
			}
		}

		void Fourier_transformer::show_original_data(int rows_, int step_) {
			if (data_number > 0) {
				cv::Mat show_mat(rows_, data_number * step_, CV_8UC3, cv::Scalar(255, 255, 255));
				cv::Point2d P1, P2;
				int i, i2;
				double max_data = *std::max_element(The_data_in_time.begin(), The_data_in_time.end());
				double min_data = *std::min_element(The_data_in_time.begin(), The_data_in_time.end());
				max_data = DFT_max(abs(max_data), abs(min_data));
				for (i = 0; i < data_number; i++) {
					if (i < data_number - 1) {
						i2 = i + 1;
						P1.x = double(i) * double(step_);
						P2.x = double(i2) * double(step_);
						P1.y = -The_data_in_time[i] * double(0.5 * double(rows_)) / (1.2 * max_data) + 0.5 * double(rows_);
						P2.y = -The_data_in_time[i2] * double(0.5 * double(rows_)) / (1.2 * max_data) + 0.5 * double(rows_);;
					}
					cv::line(show_mat, P1, P2, cv::Scalar(8, 102, 5), 2);
				}
				cv::namedWindow("DFT input data", cv::WINDOW_NORMAL);
				cv::resizeWindow("DFT input data", cv::Size(1100, 400));
				cv::imshow("DFT input data", show_mat);
				cv::waitKey(5);
			}
			else {
				std::cout << "未输入数据！" << std::endl;
			}
		}

		Fourier_parameter Fourier_transformer::get_harmonic_parameters() {
			Fourier_parameter output_;
			get_A_p();
			output_.sample_number = data_number;
			output_.phase = Phase;
			output_.amplitude = Amplitude;
			return output_;
		}

		double Fourier_transformer::Error_prediction_use_DFT(double input_time_position, int frequency_number, double low_frequency_domain) {
			double output_ = 0;
			int i;
			if (!no_prediction_power()) {
				std::vector<to_sort> sort_stay1 = sorting;//sorting只能由solve函数赋值
				std::vector<to_sort>::const_iterator first_ = sort_stay1.begin();
				std::vector<to_sort>::const_iterator end_ = sort_stay1.begin() + ceil(double(data_number_pre) / 2.0);//data_number_pre只能由solve函数赋值
				std::vector<to_sort> sort_stay(first_, end_);
				std::sort(sort_stay.begin(), sort_stay.end(), sort_comp);//排序
				//std::cout << data_number << std::endl;
				if (frequency_number == -1) {
					frequency_number = ceil(double(data_number_pre) / 2.0);
				}
				for (i = 0; i < frequency_number; i++) {
					if (sort_stay[i].amplitude <= 0 || sort_stay[i].frequency > 2.0 * Pi * low_frequency_domain)//只要低频段的数据
						continue;
					output_ += (sort_stay[i].amplitude * 2.0 / double(data_number_pre)) * cos(sort_stay[i].frequency * (double(input_time_position) - double(time_0_position_pre + 2)) + sort_stay[i].phase);
					//std::cout << sort_stay[i].phase << std::endl;
				}
			}
			return output_;
		}

		void Fourier_transformer::Solve_() {
			get_A_p();
		}

		void Fourier_transformer::close_display_window(int window_choose) {
			if (window_choose == CLOSE_RESULT_WINDOW)
				cv::destroyWindow("DFT result");
			if (window_choose == CLOSE_ORIGIN_DATA_WINDOW)
				cv::destroyWindow("DFT input data");
			if (window_choose == CLOSE_RESULT_ORIGIN) {
				cv::destroyWindow("DFT result");
				cv::destroyWindow("DFT input data");
			}
		}

		void Fourier_transformer::printf_data(int show_number) {
			int i;
			if (DFT_HAVE_SOLVE) {
				std::vector<to_sort> sort_stay1 = sorting;
				std::vector<to_sort>::const_iterator first_ = sort_stay1.begin();
				std::vector<to_sort>::const_iterator end_ = sort_stay1.begin() + data_number / 2;
				std::vector<to_sort> sort_stay(first_, end_);
				std::sort(sort_stay.begin(), sort_stay.end(), sort_comp);//排序
				std::cout << "频率    |    幅值    |    相位" << std::endl;
				for (i = 0; i < show_number; i++) {
					std::cout << sort_stay[i].frequency << " | " << sort_stay[i].amplitude * 2.0 / double(data_number) << " | " << sort_stay[i].phase << std::endl;
				}
			}
		}

		bool Fourier_transformer::no_prediction_power() {
			if (sorting.size() <= 2 || data_number_pre <= 0 || fit_parameter_have_solve == FALSE)
				return TRUE;
			else
				return FALSE;
		}

		bool Fourier_transformer::fit_funtion_pre_empty(trigonometric_function_paramater input_parameter) {
			if (input_parameter.A == 0 && input_parameter.B == 0 && input_parameter.C == 0)
				return TRUE;
			else
				return FALSE;
		}

		trigonometric_function_paramater Fourier_transformer::fit_trigonometric_function_paramater(double aomiga, int Fit_mode, double error_domain) {
			double sc = 0, c2 = 0, s2 = 0, s = 0, c = 0, y = 0, ys = 0, yc = 0, y2 = 0;//需要计算的取值
			int i = 0;
			double ti = 0, yi = 0;
			double value_ = 0, A = 0, B = 0, C = 0;
			double average = 0, derta = 0;//统计几何参数
			double number_ = 0;
			double judge_value = 0;
			Eigen::MatrixXd A_Matrix(3, 3), B_Matrix(3, 1), a_vector(3, 1);
			trigonometric_function_paramater output_;
			for (i = 0; i < Function_Points.size(); i++) {//循环赋值，从fuction points取数据
				ti = Function_Points[i].x * aomiga;
				yi = Function_Points[i].y;
				//std::cout <<"ti"<< Function_Points[i].y << std::endl;
				sc += sin(ti) * cos(ti);
				c2 += cos(ti) * cos(ti);
				s2 += sin(ti) * sin(ti);
				s += sin(ti);
				c += cos(ti);
				y += yi;
				ys += yi * sin(ti);
				yc += yi * cos(ti);
				y2 += yi * yi;
			}
			A_Matrix << c2, sc, c,
				sc, s2, s,
				c, s, double(data_number);
			B_Matrix << yc,
				ys,
				y;
			if (A_Matrix.determinant() != 0) {//安全
				//std::cout << A_Matrix.determinant() << std::endl;
				a_vector = (A_Matrix.inverse()) * B_Matrix;
				A = a_vector(0, 0); B = a_vector(1, 0); C = a_vector(2, 0);
				value_ = y2 + \
					A * A * c2 + \
					B * B * s2 + \
					2.0 * A * B * sc + \
					2.0 * A * C * c + \
					2.0 * B * C * s + \
					double(data_number) * C * C - \
					2.0 * A * yc - \
					2.0 * B * ys - \
					2.0 * C * y;
				output_.A = A; output_.B = B; output_.C = C; output_.omiga = aomiga; output_.error_value = value_;
			}
			else {
				output_.error_value = 99999999;
			}
			if (Fit_mode == FIT_DEDUCTING_ERROR_POINT) {//求统计学参数扣除坏点
				for (i = 0; i < Function_Points.size(); i++) {
					ti = Function_Points[i].x * aomiga;
					yi = Function_Points[i].y;
					average += yi - A * cos(ti) - B * sin(ti) - C;
					number_ = number_ + 1.0;
				}
				average /= number_;
				for (i = 0; i < Function_Points.size(); i++) {
					ti = Function_Points[i].x * aomiga;
					yi = Function_Points[i].y;
					derta += (yi - A * cos(ti) - B * sin(ti) - C - average) * (yi - A * cos(ti) - B * sin(ti) - C - average);
				}
				derta /= number_ - 1.0;
				derta = sqrt(derta);
				for (i = 0; i < Function_Points.size(); i++) {
					ti = Function_Points[i].x * aomiga;
					yi = Function_Points[i].y;
					judge_value = sqrt((yi - A * cos(ti) - B * sin(ti) - C) * (yi - A * cos(ti) - B * sin(ti) - C));
					if (judge_value > error_domain * derta) {
						Function_Points[i].is_error_point = TRUE;
						//std::cout << "error" << std::endl;
					}
				}
				number_ = 0;
				for (i = 0; i < Function_Points.size(); i++) {//循环赋值，从fuction points取数据
					if (Function_Points[i].is_error_point)
						continue;
					ti = Function_Points[i].x * aomiga;
					yi = Function_Points[i].y;
					sc += sin(ti) * cos(ti);
					c2 += cos(ti) * cos(ti);
					s2 += sin(ti) * sin(ti);
					s += sin(ti);
					c += cos(ti);
					y += yi;
					ys += yi * sin(ti);
					yc += yi * cos(ti);
					y2 += yi * yi;
					number_ = number_ + 1;
				}
				A_Matrix << c2, sc, c,
					sc, s2, s,
					c, s, number_;
				B_Matrix << yc,
					ys,
					y;
				if (A_Matrix.determinant() != 0) {//安全
					a_vector = (A_Matrix.inverse()) * B_Matrix;
					A = a_vector(0, 0); B = a_vector(1, 0); C = a_vector(2, 0);
					value_ = y2 + \
						A * A * c2 + \
						B * B * s2 + \
						2.0 * A * B * sc + \
						2.0 * A * C * c + \
						2.0 * B * C * s + \
						double(data_number) * C * C - \
						2.0 * A * yc - \
						2.0 * B * ys - \
						2.0 * C * y;
					output_.A = A; output_.B = B; output_.C = C; output_.omiga = aomiga; output_.error_value = value_;
				}
				else {
					output_.error_value = 99999999;
				}
			}
			return output_;
		}

		double Fourier_transformer::DFT_random(double a, double b, double precision) {
			int OUTPUT = 0;
			double GAIN = 1;
			int i = 0;
			for (i = 0; i < precision; i++) {
				GAIN = GAIN * 10;
			}
			int A = a * GAIN, B = b * GAIN;
			OUTPUT = (rand() % (B - A + 1)) + A;
			double OUTPUT2 = 0;
			OUTPUT2 = OUTPUT;
			OUTPUT2 = OUTPUT2 / GAIN;
			return OUTPUT2;
		}

		void Fourier_transformer::Solve_fit(int exquisite_number) {
			trigonometric_function_paramater this_function_parameters;
			//partical_swarm Q;
			double a = 0.5, b = 1;
			double now_position = DFT_random(a, b), new_position = DFT_random(a, b);
			double value_now = 0, value_new = 0;
			double d_value = 0;
			double best_aomiga = 0;
			int i = 0;
			int max_number = exquisite_number;
			int max_count = 0;
			double step = 0;
			a = 2.0 * Pi / double(data_number);
			b = 2.0 * Pi;
			step = abs(b - a) / max_number;
			value_now = fit_trigonometric_function_paramater(a).error_value;
			value_new = value_now;
			new_position = a;
			//partical_Function_Points = Function_Points;
			//start_c = clock();
			//Q.set_parameters(20, 1000);
			//Q.put_particals_in_region(a, b);
			//Q.calc_and_update(partical_fit_trigonometric_function_paramater);
			//best_aomiga = Q.get_best_parameter();
			//start_c = clock();
			max_count = ceil(0.5 * double(max_number));
			for (i = 0; i <= max_count; i++) {//利用梯度下降法
				value_new = fit_trigonometric_function_paramater(new_position).error_value;
				if (value_new < value_now) {
					value_now = value_new;
					best_aomiga = new_position;
				}
				new_position += step;
			}
			/*end_c = clock();
			std::cout <<"耗时："<< end_c - start_c <<"毫秒" <<std::endl;*/
			this_function_parameters = fit_trigonometric_function_paramater(best_aomiga, FIT_DEDUCTING_ERROR_POINT);
			fit_parameter_have_solve = TRUE;
			fit_funtion_pre.push_back(this_function_parameters);
			/*fit_funtion_pre.resize(1);
			fit_funtion_pre[0] = this_function_parameters;*/
		}

		double Fourier_transformer::Error_prediction_use_trigonometric_function_fit(double input_time_position) {
			double A = 0, B = 0, C = 0, w = 0;
			int i;
			double output_ = 0;
			if (!fit_parameter_have_solve) {//求解
				Solve_fit();
				A = fit_funtion_pre[0].A;
				B = fit_funtion_pre[0].B;
				C = fit_funtion_pre[0].C;
				w = fit_funtion_pre[0].omiga;
				output_ = A * cos(w * input_time_position) + B * sin(w * input_time_position) + C;
			}
			else {
				for (i = 0; i < fit_funtion_pre.size(); i++) {//谐波叠加
					A = fit_funtion_pre[i].A;
					B = fit_funtion_pre[i].B;
					C = fit_funtion_pre[i].C;
					w = fit_funtion_pre[i].omiga;
					output_ += A * cos(w * input_time_position) + B * sin(w * input_time_position) + C;
				}
			}
			return output_;
		}

		void Fourier_transformer::show_fit_result(int rows_, int step_) {
			if (data_number > 0) {
				cv::Mat show_mat(rows_, data_number * step_, CV_8UC3, cv::Scalar(255, 255, 255));
				cv::Point2d P1, P2, P3, P4;
				int i, i2;
				double max_data = *std::max_element(The_data_in_time.begin(), The_data_in_time.end());
				double min_data = *std::min_element(The_data_in_time.begin(), The_data_in_time.end());
				double A, B, C, w;
				double value_, value_1;
				max_data = DFT_max(abs(max_data), abs(min_data));
				A = fit_funtion_pre[0].A;
				B = fit_funtion_pre[0].B;
				C = fit_funtion_pre[0].C;
				w = fit_funtion_pre[0].omiga;
				for (i = 0; i < data_number; i++) {
					if (i < data_number - 1) {
						i2 = i + 1;
						value_ = A * cos(w * time_vector[i]) + B * sin(w * time_vector[i]) + C;
						value_1 = A * cos(w * time_vector[i2]) + B * sin(w * time_vector[i2]) + C;
						P1.x = double(i) * double(step_);
						P2.x = double(i2) * double(step_);
						P3.x = P1.x;
						P4.x = P2.x;
						P1.y = -The_data_in_time[i] * double(0.5 * double(rows_)) / (1.2 * max_data) + 0.5 * double(rows_);
						P2.y = -The_data_in_time[i2] * double(0.5 * double(rows_)) / (1.2 * max_data) + 0.5 * double(rows_);
						P3.y = -value_ * double(0.5 * double(rows_)) / (1.2 * max_data) + 0.5 * double(rows_);
						P4.y = -value_1 * double(0.5 * double(rows_)) / (1.2 * max_data) + 0.5 * double(rows_);
					}

					cv::line(show_mat, P3, P4, cv::Scalar(0, 0, 255), 4);
					cv::line(show_mat, P1, P2, cv::Scalar(255, 102, 5), 2);
				}
				cv::namedWindow("DFT input data", cv::WINDOW_NORMAL);
				cv::resizeWindow("DFT input data", cv::Size(1100, 400));
				cv::imshow("DFT input data", show_mat);
				//cv::imwrite("E:\\Fit_pic.jpg", show_mat);
				cv::waitKey(5);
			}
			else {
				std::cout << "未输入数据！" << std::endl;
			}
		}

		/****************************************************************************************************************/

		double one_partical::get_self_best_and_update_best() {
			std::vector<sort_partical_self> STAY;
			STAY = self_history;
			std::sort(STAY.begin(), STAY.end(), one_partical_find_self_best);
			self_best_value = STAY[0].value;
			self_best_position = STAY[0].position;
			return STAY[0].position;
		}

		void partical_swarm::set_patical_number(int input_partical_number) {
			patical_number = input_partical_number;
		}

		partical_swarm::partical_swarm(int input_patical_number, int input_max_iteration) {
			Particals.resize(input_patical_number);
			patical_number = input_patical_number;
			max_iteration_number = input_max_iteration;
			srand(time(0));
		}

		partical_swarm::partical_swarm() {
			srand(time(0));
		}

		void partical_swarm::put_particals_in_region(double Lower, double Upper) {
			double step = 0;
			int i;
			if (patical_number <= 2) {
				patical_number = 10;
			}
			lower_ = Lower; upper_ = Upper;
			step = (Upper - Lower) / (double(patical_number) - 1.0);
			for (i = 0; i < patical_number; i++) {//等距放位置、速度
				Particals[i].position = double(i) * step;
				Particals[i].V = random_(Lower, 0.8 * Upper);
				Particals[i].self_best_position = double(i) * step;
				Particals[i].self_best_value = 99999999;
				Particals[i].now_value = 999999999;
				//std::cout << Particals[i].V << std::endl;
			}
		}

		void partical_swarm::set_parameters(int input_partical_number, int input_max_iteration, double input_omiga_begin, double input_omiga_end, double input_self_index, double input_social_index) {
			omiga_begin = input_omiga_begin;
			omiga_end = input_omiga_end;
			self_index = input_self_index;
			social_index = input_social_index;
			max_iteration_number = input_max_iteration;
			patical_number = input_partical_number;
			Particals.resize(input_partical_number);
		}

		void partical_swarm::calc_and_update(double (*value_function)(double)) {
			int i;
			/*更新位置和速度*/
			for (iteration_count = 0; iteration_count < max_iteration_number; iteration_count++) {
				//std::cout << iteration_count << std::endl;
				if (iteration_count <= 0) {
					global_best_position = Particals[1].position;
					global_best_value = value_function(global_best_position);
				}
				for (i = 0; i < patical_number; i++) {//更新位置和速度
					Particals[i].position += get_omiga(iteration_count) * Particals[i].V + \
						self_index * random_(0, 1) * (Particals[i].self_best_position - Particals[i].position) + \
						social_index * random_(0, 1) * (global_best_position - Particals[i].position);
					if (iteration_count > 7 * max_iteration_number / 10)
						Particals[i].position += 0.1 * random_(lower_, upper_);
					if (Particals[i].position > upper_ || Particals[i].position < lower_) {
						Particals[i].position = random_(lower_, upper_);
					}
					Particals[i].V = get_omiga(iteration_count) * Particals[i].V + \
						self_index * random_(0, 1) * (Particals[i].self_best_position - Particals[i].position) + \
						social_index * random_(0, 1) * (global_best_position - Particals[i].position);
				}
				for (i = 0; i < patical_number; i++) {//计算每个点的函数值，以及自身最优值更新
					Particals[i].now_value = value_function(Particals[i].position);
					Particals[i].historey_update(Particals[i].position, Particals[i].now_value);
					if (iteration_count <= 0) {
						Particals[i].self_best_position = Particals[i].position;
						Particals[i].self_best_value = Particals[i].now_value;
					}
					else {
						Particals[i].get_self_best_and_update_best();
					}
				}
				update_global_best();//更新全局最优值
			}
		}

		void partical_swarm::update_global_best() {
			int i;
			sort_partical_self INpu;
			global_value_vector.clear();
			for (i = 0; i < patical_number; i++) {
				INpu.position = Particals[i].position;
				INpu.value = Particals[i].now_value;
				global_value_vector.push_back(INpu);
			}
			std::sort(global_value_vector.begin(), global_value_vector.end(), one_partical_find_self_best);
			global_best_position = global_value_vector[0].position;
			global_best_value = global_value_vector[0].value;
			/*std::cout << global_value_vector[0].value << std::endl;
			std::cout << global_value_vector[1].value << std::endl;*/
			if (global_best_value < best_value) {
				best_value = global_best_value;
				best_position = global_best_position;
			}
		}
	}
}

