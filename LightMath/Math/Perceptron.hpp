#ifndef __FILE_PERCEPTRON
#define __FILE_PERCEPTRON

#include<Math/MathConfig.h>

namespace ld
{
	namespace math
	{
		template<int row, int col>
		auto L1Loss(
			const Eigen::Matrix<Number, row, col>& predict_data,
			const Eigen::Matrix<Number, row, col>& teacher_data)
		{
			return teacher_data - predict_data;
		}

		template<
			size_t InputDimension, size_t OutputDimension
		>
		_LF_C_API(TClass) Perceptron
			Symbol_Push _LF_Inherited(any_class)
			Symbol_Link public instance<Eigen::Matrix<Number, InputDimension, OutputDimension>>
			Symbol_Endl
		{
		public:
			using tag = Perceptron;
			using base_tag = instance<Eigen::Matrix<Number, InputDimension, OutputDimension>>;
			using InputMatrix = Eigen::Matrix<Number, -1, InputDimension>;
			using OutputMatrix = Eigen::Matrix < Number, -1, OutputDimension>;
			using WeightMatrix = Eigen::Matrix<Number, InputDimension, OutputDimension>;

			constexpr static size_t InputDimensionValue = InputDimension;
			constexpr static size_t OutputDimensionValue = OutputDimension;

			using instance = instance<WeightMatrix>;

			//predict_data,teacher_data
			using LossFunction = std::function<OutputMatrix(const OutputMatrix&, const OutputMatrix&)>;
			LossFunction lost;
			using ActivateFunction = std::function<Number(Number)>;
			ActivateFunction activate;
		private:

		public:
			Perceptron(_In_ WeightMatrix* from, ActivateFunction activate, LossFunction lost)
				:instance(from), activate(activate), lost(lost) 
			{
				this->get_ref().setZero();
			}
			Perceptron(_In_ WeightMatrix* from, LossFunction lost)
				:Perceptron(from, ld::math::sigmoid, lost) {}
			Perceptron(_In_ WeightMatrix* from, ActivateFunction activate)
				:Perceptron(from,activate,L1Loss<InputDimension, OutputDimension>) {}
			Perceptron(_In_ WeightMatrix* from) :Perceptron(from, ld::math::sigmoid, L1Loss<InputDimension, OutputDimension>) {}
			Perceptron() :Perceptron(new WeightMatrix()) {}
			Perceptron(instance& from) :instance(from) {}
			Perceptron(instance&& from) :instance(std::move(from)) {}
			Perceptron(const WeightMatrix& from) :Perceptron()
			{
				this->get_ref() = from;
			}
			Perceptron(Perceptron& from) :instance(from) {}
			Perceptron(Perceptron&& from) :instance(std::move(from)) {}
			Perceptron& operator=(Perceptron& from)
			{
				instance::operator=(from);
				return *this;
			}
			Perceptron& operator=(Perceptron&& from)
			{
				instance::operator=(std::move(from));
				return *this;
			}

			Number learning_rate = 0.1;

			/// <summary>
			/// 更新权重,返回更新权重后对应的真实值的输入
			/// </summary>
			/// <param name="input_data">当前输入</param>
			/// <param name="predict_data">预测输出</param>
			/// <param name="teacher_data">真实值</param>
			auto learning(
				const InputMatrix& input_data,
				const OutputMatrix& predict_data,
				const OutputMatrix& teacher_data
				)
			{
				//获取当前前向输入
				//auto front_input = teacher_data * this->get_ref().inverse();
				//计算可能的正确权重与当前权重的误差
				WeightMatrix back_cost = lost(input_data.inverse() * predict_data, input_data.inverse() * teacher_data);
				//与学习率相乘
				//back_cost.unaryExpr([this](const Number& from)
				//	{
				//		return from * learning_rate;
				//	});
				back_cost *= learning_rate;
				//更新权重
				this->get_ref() = this->get_ref() + back_cost;
				//返回真实值的前向输入
				//TODO
				return teacher_data * this->get_ref().inverse();
			}

			Number& operator()(const size_t& row, const size_t& col) const
			{
				return this->get_ref()(row, col);
			}
		};

#pragma region Predict

		//返回预测结果
		template<
			typename _In_Matrix,
			size_t InputDimension,
			size_t OutputDimension
		>
		auto _predict(
			const _In_Matrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current)
		{
			return (mat * current.get_ref()).unaryExpr(current.activate);
		}
		//返回预测结果
		template<
			typename _In_Matrix,
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron
		>
		//返回预测结果
		auto _predict(
			const _In_Matrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current,
			const NextPerceptron& next)
		{
			return _predict(
				_predict(mat, current),
				next);
		}
		//返回预测结果
		template<
			typename _In_Matrix,
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron,
			typename... Perceptrons
		>
		auto _predict(
			const _In_Matrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current,
			const NextPerceptron& next,
			const Perceptrons&... args)
		{
			return _predict(
				_predict(mat, current),
				next,
				args...);
		}
		//返回预测结果
		template<
			typename _In_Matrix,
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron,
			typename... Perceptrons
		>
		Eigen::MatrixXd predict(
			const _In_Matrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current,
			const NextPerceptron& next,
			const Perceptrons&... args)
		{
			return _predict(mat, current, next, args...);
		}
		//返回预测结果
		template<
			typename _In_Matrix,
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron
		>
		typename NextPerceptron::OutputMatrix predict(
			const _In_Matrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current,
			const NextPerceptron& next)
		{
			return _predict(mat, current, next);
		}
		//返回预测结果
		template<
			typename _In_Matrix,
			size_t InputDimension,
			size_t OutputDimension
		>
		typename Perceptron<InputDimension, OutputDimension>::OutputMatrix predict(
			const _In_Matrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current)
		{
			return _predict(mat, current);
		}

#pragma endregion

#pragma region Fit

		//返回真实值在学习后权重下的输入
		template<
			typename _In_Matrix,
			size_t InputDimension,
			size_t OutputDimension
		>
		auto fit(
			const typename Perceptron<InputDimension, OutputDimension>::OutputMatrix& label,
			const _In_Matrix& mat,
			Perceptron<InputDimension, OutputDimension>& current
		)
		{
			return current.learning(mat, _predict(mat, current), label);
		}
		// 返回真实值在学习后权重下的输入
		// 对于current而言,由next学习后返回的矩阵即为current的真实值
		template<
			typename _In_Matrix,
			typename _Label_Matrix,
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron
		>
		auto fit(
			const _Label_Matrix& label,
			const _In_Matrix& mat,
			Perceptron<InputDimension, OutputDimension>& current,
			NextPerceptron& next
		)
		{
			typename Perceptron<InputDimension, OutputDimension>::OutputMatrix current_predict_data = _predict(mat, current); 
			return current.learning(mat, current_predict_data, fit(label, current_predict_data, next));
		}
		// 返回真实值在学习后权重下的输入
		// 对于current而言,由next学习后返回的矩阵即为current的真实值
		template<
			typename _In_Matrix,
			typename _Label_Matrix,
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron,
			typename... Perceptrons
		>
		auto fit(
			const _Label_Matrix& label,
			const _In_Matrix& mat,
			Perceptron<InputDimension, OutputDimension>& current,
			NextPerceptron& next,
			Perceptrons&... args
		)
		{
			typename Perceptron<InputDimension, OutputDimension>::OutputMatrix current_predict_data = _predict(mat, current);
			return current.learning(mat, current_predict_data, fit(label, current_predict_data, next, args...));
		}

#pragma endregion

	}
}

#endif // !__FILE_PERCEPTRON
