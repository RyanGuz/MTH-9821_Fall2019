#pragma once

// stl
#include <cmath>

double abramowitz_stegun_cum_dist_normal(double t)
{
	double z = fabs(t);
	double y = 1. / (1 + .2316419 * z);
	double a1 = .319381530;
	double a2 = -.356563782;
	double a3 = 1.781477937;
	double a4 = -1.821255978;
	double a5 = 1.330274429;
	double pi = atan(1) * 4;
	double m = 1 - exp(-pow(t, 2) / 2) * (a1 * y + a2 * pow(y, 2) + a3 * pow(y, 3)
		+ a4 * pow(y, 4) + a5 * pow(y, 5)) / sqrt(2 * pi);
	double nn;

	if (t > 0)
	{
		nn = m;
	}
	else
	{
		nn = 1 - m;
	}

	return nn;
}

double d1_val(
	double k, 
	double s,
	double r, 
	double q, 
	double sigma,
	double t)
{
	double num = std::log(s / k) + (r - q + std::pow(sigma, 2) / 2) * t;

	double denom = sigma * std::sqrt(t);

	return num / denom;
}

double d2_val(
	double k,
	double s,
	double r,
	double q,
	double sigma,
	double t)
{
	return d1_val(k, s, r, q, sigma, t) - sigma * std::sqrt(t);
}

double bs_call_price(
	double k, 
	double s,
	double r, 
	double q, 
	double sigma,
	double t)
{
	double Nd1 = abramowitz_stegun_cum_dist_normal(d1_val(k, s, r, q, sigma, t));
	double Nd2 = abramowitz_stegun_cum_dist_normal(d2_val(k, s, r, q, sigma, t));

	return s * exp(-q * t) * Nd1 - k * exp(-r * t) * Nd2;
}

double bs_put_price(
	double k, 
	double s,
	double r, 
	double q, 
	double sigma,
	double t)
{
	double Nd1 = abramowitz_stegun_cum_dist_normal(d1_val(k, s, r, q, sigma, t));
	double Nd2 = abramowitz_stegun_cum_dist_normal(d2_val(k, s, r, q, sigma, t));

	return k * exp(-r * t) * (1 - Nd2) - s * exp(-q * t) * (1 - Nd1);
}

double bs_call_delta(
	double k, 
	double s,
	double r, 
	double q, 
	double sigma,
	double t)
{
	double Nd1 = abramowitz_stegun_cum_dist_normal(d1_val(k, s, r, q, sigma, t));

	return exp(-q * t) * Nd1;
}

double bs_put_delta(
	double k, 
	double s,
	double r, 
	double q, 
	double sigma,
	double t)
{
	double Nd1 = abramowitz_stegun_cum_dist_normal(d1_val(k, s, r, q, sigma, t));

	return -exp(-q * t) * (1 - Nd1);
}