#pragma once

// stl
#include <algorithm>
#include <memory>
#include <vector>
#include <cmath>

// user defined
#include "European_Option.h"


class Binomial_Tree_Pricer
{
private:

	std::shared_ptr<European_Put> put_ptr;

public:

	Binomial_Tree_Pricer(
		std::shared_ptr<European_Put> put_ptr);
	{
		std::cout << "hi" << "\n";
	}

	double binomial_tree_price(int n)
	{
		//double del_t = put_ptr->t / n;

		//double u = std::exp(put_ptr->sigma * std::sqrt(del_t));
		//double d = 1 / u;

		//double p_rn = (std::exp((put_ptr->r - put_ptr->q) * del_t) - d) / (u - d);
		//double q_rn = 1 - p_rn;

		//double disc = std::exp(put_ptr->r * del_t);

		//std::vector<double> v;
		//double s;

		//for (int k = 0; k < n; ++k)
		//{
		//	std::cout << k << "\n";
		//	// stock price at this terminal node
		//	s = (put_ptr->s0) * std::pow(u, n - k) * std::pow(d, k);

		//	v.push_back(put_ptr->intrinsic_value(s));
		//}

		//for (int i = n - 1; i >= 0; --i)
		//{
		//	for (int k = 0; k <= i; ++k)
		//	{
		//		v[k] = disc * (p_rn * v[k] + q_rn * v[k + 1]);
		//	}
		//}

		return 0.0;
	}

};