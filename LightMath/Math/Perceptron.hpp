#ifndef __FILE_PERCEPTRON
#define __FILE_PERCEPTRON

#include<Math/MathConfig.h>

namespace ld
{
	namespace math
	{
		template<int row, int col>
		Number L1Loss(const Eigen::Matrix<Number, row, col>& mat)
		{
			Number result(0);
			for (size_t i = 0, e = mat.rows(); i < e; i++)
			{
				for (size_t j = 0, ej = mat.cols(); j < ej; j++)
				{
					result += ::abs(mat(i, j));
				}
			}
			return result;
		}

		template<
			size_t InputDimension, size_t OutputDimension
		>
		_LF_C_API(TClass) Perceptron
			Symbol_Push _LF_Inherited(any_class)
			Symbol_Link public instance<Eigen::Matrix<Number, -1, OutputDimension>>
			Symbol_Endl
		{
		public:
			using tag = Perceptron;
			using InputMatrix = Eigen::Matrix<Number, -1, InputDimension>;
			using OutputMatrix = Eigen::Matrix < Number, InputDimension, OutputDimension>;
			using WeightMatrix = Eigen::Matrix<Number, -1, OutputDimension>;

			constexpr static size_t InputDimensionValue = InputDimension;
			constexpr static size_t OutputDimensionValue = OutputDimension;

			using instance = instance<WeightMatrix>;

			using LossFunction = std::function<Number(const OutputMatrix&)>;
			LossFunction lost;
			using ActivateFunction = std::function<Number(Number)>;
			ActivateFunction activate;
		private:

		public:
			Perceptron(_In_ WeightMatrix* from, ActivateFunction activate, LossFunction lost)
				:instance(from), activate(activate), lost(lost) {}
			Perceptron(_In_ WeightMatrix* from, LossFunction lost)
				:instance(from), activate(ld::math::sigmoid), lost(lost) {}
			Perceptron(_In_ WeightMatrix* from, ActivateFunction activate)
				:instance(from), activate(activate), lost(L1Loss<InputDimension, OutputDimension>) {}
			Perceptron(_In_ WeightMatrix* from) :Perceptron(from, ActivateFunction(ld::math::sigmoid), LossFunction(L1Loss<InputDimension, OutputDimension>)) {}
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

			void learning(Number cost)
			{
				this->get_ref().unaryExpr([&cost, this](Number n)
					{
						return n - cost * learning_rate;
					});
			}
		};

		template<
			size_t InputDimension,
			int DataSize,
			size_t OutputDimension
		>
		auto predict(
			const Eigen::Matrix<Number, DataSize, InputDimension>& mat,
			const Perceptron<InputDimension, OutputDimension>& current)
		{
			return (mat * current.get_ref()).unaryExpr(current.activate);
		}
		template<
			size_t InputDimension,
			int DataSize,
			size_t NextInputDimension,
			class... PerceptronArgs
		>
		auto predict(
			const Eigen::Matrix<Number, DataSize, InputDimension>& mat,
			const Perceptron<InputDimension, NextInputDimension>& current,
			PerceptronArgs&... matrixs)
		{
			return Push<NextInputDimension, -1, decltype(matrixs)::InputDimensionValue>(
				(mat * current.get_ref()).unaryExpr(current.activate)
				, matrixs...);
		}
	}
}

#endif // !__FILE_PERCEPTRON
