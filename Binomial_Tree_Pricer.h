#pragma once

// stl
#include <algorithm>
#include <memory>
#include <vector>
#include <cmath>

// eigen
#include <Eigen/Dense>

// user defined
#include "European_Option.h"


class Binomial_Tree_Pricer
{
private:

	std::shared_ptr<European_Option> option;
	int n;
	Eigen::MatrixXd tree;
	double price, delta, gamma, theta;
	double del_t, u, d;

	void calc_price(int n)
	{
		tree = Eigen::MatrixXd::Zero(n + 1, n + 1);

		del_t = option->t / n;
		u = std::exp(option->sigma * std::sqrt(del_t));
		d = 1 / u;

		double disc = std::exp(-option->r * del_t);
		double p_rn = (std::exp((option->r - option->q) * del_t) - d) / (u - d);
		double q_rn = 1 - p_rn;

		for (int k = 0; k <= n; ++k)
		{
			// stock price at this terminal node
			double s = option->s0 * std::pow(u, n - k) * std::pow(d, k);

			tree(k, n) = option->intrinsic_value(s);
		}

		for (int i = n - 1; i >= 0; --i)
		{
			for (int k = 0; k <= i; ++k)
			{
				tree(k, i) = disc * (p_rn * tree(k, i + 1) + q_rn * tree(k + 1, i + 1));
			}
		}

		price = tree(0, 0);
	}

	void calc_delta()
	{
		double v_u = tree(0, 1);
		double v_d = tree(1, 1);

		double s_u = option->s0 * u;
		double s_d = option->s0 * d;

		delta = (v_u - v_d) / (s_u - s_d);
	}

	void calc_gamma()
	{
		double v_uu = tree(0, 2);
		double v_ud = tree(1, 2);
		double v_dd = tree(2, 2);

		double s_uu = option->s0 * std::pow(u, 2);
		double s_ud = option->s0 * u * d;
		double s_dd = option->s0 * std::pow(d, 2);

		double delta_u = (v_uu - v_ud) / (s_uu - s_ud);
		double delta_d = (v_ud - v_dd) / (s_ud - s_dd);

		gamma = (delta_u - delta_d) / ((s_uu - s_dd) / 2);
	}

	void calc_theta()
	{
		double v = tree(0, 0);
		double v_ud = tree(1, 1);

		theta = (v_ud - v) / (2 * del_t);
	}

public:

	Binomial_Tree_Pricer(
		std::shared_ptr<European_Option> option,
		int n = 2)
		: option(option)
		, n(n)
	{
		calc_price(n);
		calc_delta();
		calc_gamma();
		calc_theta();
	}

	void change_timesteps(int n)
	{
		calc_price(n);
		calc_delta();
		calc_gamma();
		calc_theta();
	}

	double get_price()
	{
		return price;
	}

	void print()
	{
		std::cout << "Price: " << price << "\n";
		std::cout << "Delta: " << delta << "\n";
		std::cout << "Gamma: " << gamma << "\n";
		std::cout << "Theta: " << theta << "\n";
	}

};