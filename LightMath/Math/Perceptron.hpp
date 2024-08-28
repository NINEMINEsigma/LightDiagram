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

			void learning(
				const InputMatrix& input_data,
				const OutputMatrix& predict_data,
				const OutputMatrix& teacher_data
				)
			{
				WeightMatrix back_cost = lost(predict_data, teacher_data) * input_data.inverse();
				back_cost.unaryExpr([this](const Number& from)
					{
						return from * learning_rate;
					});
				this->get_ref() = this->get_ref() + back_cost;
			}

			Number& operator()(const size_t& row, const size_t& col)
			{
				return this->get_ref()(row, col);
			}
		};

#pragma region Predict

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
		template<
			typename _In_Matrix,
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron
		>
		auto _predict(
			const _In_Matrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current,
			const NextPerceptron& next)
		{
			return _predict(
				_predict(mat, current),
				next);
		}
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

		template<
			typename _In_Matrix,
			size_t InputDimension,
			size_t OutputDimension
		>
		auto fit(
			const typename Perceptron<InputDimension, OutputDimension>::OutputMatrix& label,
			const _In_Matrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current
		)
		{
			using _Out_Matrix = typename Perceptron<InputDimension, OutputDimension>::OutputMatrix;
			_Out_Matrix predict_data = _predict(mat, current);
			current.learning(mat, predict_data, label);
			return predict_data;
		}
		template<
			typename _In_Matrix,
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron
		>
		void fit(
			const typename Perceptron<InputDimension, OutputDimension>::OutputMatrix& label,
			const _In_Matrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current,
			const NextPerceptron& next
		)
		{
			using _Out_Matrix = typename Perceptron<InputDimension, OutputDimension>::OutputMatrix;
			//_Out_Matrix predict_data = _predict(mat, current);
			current.learning(mat, _predict(mat, current), label);
		}

#pragma endregion

	}
}

#endif // !__FILE_PERCEPTRON
