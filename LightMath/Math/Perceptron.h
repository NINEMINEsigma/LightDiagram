#ifndef __FILE_PERCEPTRON
#define __FILE_PERCEPTRON

#include "MathConfig.h"

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

		//每一个Perceptron类其实是一整层神经元
		//多个Perceptron通过连接后即可形成网络
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
			using InputMatrix = Eigen::Matrix<Number, 1, InputDimension>;
			using OutputMatrix = Eigen::Matrix < Number, 1, OutputDimension>;
			using BiasMatrix = Eigen::Matrix < Number, 1, OutputDimension>;
			using WeightMatrix = Eigen::Matrix<Number, InputDimension, OutputDimension>;

			constexpr static size_t InputDimensionValue = InputDimension;
			constexpr static size_t OutputDimensionValue = OutputDimension;

			using instance = instance<WeightMatrix>;

			//predict_data,teacher_data
			using LossFunction = std::function<OutputMatrix(const OutputMatrix&, const OutputMatrix&)>;
			LossFunction lost;
			using ActivateFunction = std::function<Number(Number)>;
			ActivateFunction activate;
			ActivateFunction dActivate;
		private:

		public:
			Perceptron(_In_ WeightMatrix* from, ActivateFunction activate, ActivateFunction dActivate, LossFunction lost)
				:instance(from), activate(activate), dActivate(dActivate), lost(lost)
			{
				this->get_ref().setZero();
				bias.setZero();
			}
			Perceptron(_In_ WeightMatrix* from) :Perceptron(from, ld::math::sigmoid, ld::math::dSigmoid, L1Loss<1, OutputDimension>) {}
			Perceptron() :Perceptron(new WeightMatrix()) {}
			Perceptron(instance& from) :instance(from) {}
			Perceptron(instance&& from) :instance(std::move(from)) {}
			Perceptron(const WeightMatrix& from) :Perceptron()
			{
				this->get_ref() = from;
			}
			Perceptron(Perceptron& from) noexcept:instance(from) , bias(from.bias){}
			Perceptron(Perceptron&& from) noexcept :instance(std::move(from)), bias(std::move(from.bias)) {}
			Perceptron& operator=(Perceptron& from) noexcept
			{
				instance::operator=(from);
				this->bias = from.bias;
				return *this;
			}
			Perceptron& operator=(Perceptron&& from) noexcept
			{
				instance::operator=(std::move(from));
				this->bias = from.bias;
				return *this;
			}

			Number learning_rate = 0.1;
			BiasMatrix bias;

			Number& operator()(const size_t& row, const size_t& col) const
			{
				return this->get_ref()(row, col);
			}

			Number& operator()(const size_t& index) const
			{
				return this->get_ref()(index);
			}
		};

		template<
			size_t InputDimension, size_t OutputDimension
		>
		std::ostream& operator<<(std::ostream& st, const Perceptron<InputDimension, OutputDimension>& from)
		{
			st << "Weight Matrix:\n" << from.get_ref() << "\n"
				<< "Bias Matrix:\n" << from.bias;
			return st;
		}

#pragma region Predict

		//返回预测结果
		template<
			size_t InputDimension,
			size_t OutputDimension
		>
		auto _predict(
			const typename Perceptron<InputDimension, OutputDimension>::InputMatrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current)
		{
			return (mat * current.get_ref() + current.bias).unaryExpr(current.activate);
		}
		//返回预测结果
		template<
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron
		>
		//返回预测结果
		auto _predict(
			const typename Perceptron<InputDimension, OutputDimension>::InputMatrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current,
			const NextPerceptron& next)
		{
			return _predict(
				_predict(mat, current),
				next);
		}
		//返回预测结果
		template<
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron,
			typename... Perceptrons
		>
		auto _predict(
			const typename Perceptron<InputDimension, OutputDimension>::InputMatrix& mat,
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
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron,
			typename... Perceptrons
		>
		Eigen::MatrixXd predict(
			const typename Perceptron<InputDimension, OutputDimension>::InputMatrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current,
			const NextPerceptron& next,
			const Perceptrons&... args)
		{
			return _predict(mat, current, next, args...);
		}
		//返回预测结果
		template<
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron
		>
		typename NextPerceptron::OutputMatrix predict(
			const typename Perceptron<InputDimension, OutputDimension>::InputMatrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current,
			const NextPerceptron& next)
		{
			return _predict(mat, current, next);
		}
		//返回预测结果
		template<
			size_t InputDimension,
			size_t OutputDimension
		>
		typename Perceptron<InputDimension, OutputDimension>::OutputMatrix predict(
			const typename Perceptron<InputDimension, OutputDimension>::InputMatrix& mat,
			const Perceptron<InputDimension, OutputDimension>& current)
		{
			return _predict(mat, current);
		}

#pragma endregion

#pragma region Fit

		template<
			size_t InputDimension,
			size_t OutputDimension
		>
		auto fit(
			const typename Perceptron<InputDimension, OutputDimension>::OutputMatrix& label,
			const typename Perceptron<InputDimension, OutputDimension>::InputMatrix& mat,
			Perceptron<InputDimension, OutputDimension>& current
		)
		{
			auto p = predict(mat, current);
			decltype(p) d_p = p.unaryExpr(current.dActivate);
			decltype(p) d_b = (p - label) * 2;
			for (size_t index = 0, e = OutputDimension; index < e; index++)
			{
				d_b(index) *= d_p(index);
			}
			current.bias -= current.learning_rate * d_b;
			typename Perceptron<InputDimension, OutputDimension>::WeightMatrix d_w = mat.transpose() * d_b;
			current.get_ref() -= current.learning_rate * d_w;
		}
		template<
			size_t InputDimension,
			size_t OutputDimension,
			typename NextPerceptron
		>
		auto fit(
			const typename Perceptron<InputDimension, OutputDimension>::OutputMatrix& label,
			const typename Perceptron<InputDimension, OutputDimension>::InputMatrix& mat,
			Perceptron<InputDimension, OutputDimension>& current,
			NextPerceptron& next
		)
		{
			auto p = predict(mat, current);
			decltype(p) d_p = p.unaryExpr(current.dActivate);
			decltype(p) d_b = (p - label) * 2;
			for (size_t index = 0, e = OutputDimension; index < e; index++)
			{
				d_b(index) *= d_p(index);
			}
			current.bias -= current.learning_rate * d_b;
			typename Perceptron<InputDimension, OutputDimension>::WeightMatrix d_w = mat.transpose() * d_b;
			current.get_ref() -= current.learning_rate * d_w;
		}

#pragma endregion

	}
}

#endif // !__FILE_PERCEPTRON
