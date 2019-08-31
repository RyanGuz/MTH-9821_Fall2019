#pragma once

// stl
#include <iostream>
#include <algorithm>

// user defined
#include "Black_Scholes.h"

class European_Option
{

public:

	double k; // strike
	double s0; // spot
	double r; // risk free rate
	double sigma; // implied volatility
	double q; // dividends rate
	double t; // time to maturity

	European_Option(
		double k,
		double s0,
		double r,
		double q,
		double sigma,
		double t)
		: k(k)
		, s0(s0)
		, r(r)
		, q(q)
		, sigma(sigma)
		, t(t)
	{
		// init
	}

	virtual double intrinsic_value(double s) = 0;

	virtual double bs_price() = 0;

	virtual double bs_delta() = 0;
};

class European_Call : public European_Option
{

public:

	European_Call(
		double k,
		double s0,
		double r,
		double q,
		double sigma,
		double t)
		: European_Option(k, s0, r, q, sigma, t)
	{}

	double intrinsic_value(double s)
	{
		return std::max<double>(s - k, 0);
	}

	double bs_price()
	{
		return bs_call_price(k, s0, r, q, sigma, t);
	}

	double bs_delta()
	{
		return bs_call_delta(k, s0, r, q, sigma, t);
	}
};

class European_Put : public European_Option
{

public:

	European_Put(
		double k,
		double s0,
		double r,
		double q,
		double sigma,
		double t)
		: European_Option(k, s0, r, q, sigma, t)
	{}

	double intrinsic_value(double s)
	{
		return std::max<double>(k - s, 0);
	}

	double bs_price()
	{
		return bs_put_price(k, s0, r, q, sigma, t);
	}

	double bs_delta()
	{
		return bs_put_delta(k, s0, r, q, sigma, t);
	}
};

void test_european_put()
{
	European_Put put(50, 50, .05, .02, .3, 1.2);

	std::cout << "Intrinsic val: " << put.intrinsic_value(48) << "\n";
	std::cout << "Price: " << put.bs_price() << "\n";
}
