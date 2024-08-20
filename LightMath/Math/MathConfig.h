﻿#pragma once

#ifndef __FILE_MATHCONFIG
#define __FILE_MATHCONFIG

#include <Eigen/Eigen>
#include <Eigen/Eigenvalues>

#include <LightDiagram.h>

namespace ld
{
	namespace math
	{
		using ArithmeticBasicType = double;
		using Number = ArithmeticBasicType;
		using Integer = int;
		using uInteger = std::make_unsigned_t<Integer>;
		using exNumber = long double;
		using exInteger = long long;
		using uexInteger = std::make_unsigned_t<exInteger>;

		constexpr const char* Error_Aligned = "The size cannot be aligned";
		constexpr const char* Error_Empty = "The data cannot be empty";

		//直观的对应关系是,transpose打印的是硬编码时的转置
		//Eigen::MatrixXd.transpose:
		//		row_1	row_2
		//col_1	a11		a21
		//col_1	a12		a22
		//实际上vec<vec<>>中的初始化则是
		//		col_1	col_1
		//row_1	{{a11,	a12},
		//row_2	{a21,	a22}}
		Eigen::MatrixXd _LF_C_API(Func) MatrixToMatrix(const std::vector<std::vector<ld::math::Number>>& from);
		std::vector<std::vector<ld::math::Number>> _LF_C_API(Func) MatrixToMatrix(const Eigen::MatrixXd& from);
	}
}

#endif // !__FILE_MATHCONFIG


