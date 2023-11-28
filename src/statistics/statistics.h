
///
/// @file statistics.h Statistical functions
///

#ifndef THEORETICA_STATISTICS_H
#define THEORETICA_STATISTICS_H

#include "../core/constants.h"
#include "../algebra/vec.h"
#include "../core/vec_buff.h"
#include "../core/real_analysis.h"
#include "../core/special.h"
#include "../calculus/integration.h"
#include "../calculus/gauss.h"


namespace theoretica {


	/// Compute the arithmetic mean of a set of values
	inline real arithmetic_mean(const vec_buff& data) {

		if(!data.size()) {
			TH_MATH_ERROR("arithmetic_mean", data.size(), DIV_BY_ZERO);
			return nan();
		}

		// Sum of x_i / N
		return sum(data) / (real) data.size();
	}


	/// Compute the arithmetic mean of a set of values
	/// Alias for arithmetic_mean
	inline real mean(const vec_buff& data) {
		return arithmetic_mean(data);
	}


	/// Compute the harmonic mean of a set of values
	inline real harmonic_mean(const vec_buff& data) {

		if(!data.size()) {
			TH_MATH_ERROR("harmonic_mean", data.size(), DIV_BY_ZERO);
			return nan();
		}

		real res = 0;

		for (unsigned int i = 0; i < data.size(); ++i) {

			if(data[i] == 0) {
				TH_MATH_ERROR("harmonic_mean", data[i], DIV_BY_ZERO);
				return nan();
			}

			res += 1.0 / data[i];
		}

		return static_cast<real>(data.size()) / res;
	}


	/// Compute the geometric mean of a set of values
	/// as \f$\sqrt[n]{\Pi_i x_i}\f$
	inline real geometric_mean(const vec_buff& data) {
		return root(product(data), data.size());
	}


	/// Compute the weighted mean of a set of values
	/// <data> and <weights> must have the same size
	inline real weighted_mean(const vec_buff& data, const vec_buff& weights) {

		// Sum of x_i * w_i / Sum of w_i
		return product_sum(data, weights) / sum(weights);
	}


	/// Compute the quadratic mean (Root Mean Square) of a set of values
	/// m_q = sqrt(x1^2 + x2^2 + ...)
	inline real quadratic_mean(const vec_buff& data) {

		if(!data.size()) {
			TH_MATH_ERROR("quadratic_mean", data.size(), INVALID_ARGUMENT);
			return nan();
		}

		return sqrt(sum_squares(data) / data.size());
	}


	/// Compute the quadratic mean (Root Mean Square) of a set of values
	/// m_q = sqrt(x1^2 + x2^2 + ...)
	/// @see quadratic_mean
	inline real rms(const vec_buff& data) {

		return quadratic_mean(data);
	}


	/// Computes the range of a data set
	/// defined as x_max - x_min
	inline real range(const vec_buff& data) {

		return max(data) - min(data);
	}


	/// Computes the maximum semidispersion of a data set
	/// defined as (x_max - x_min) / 2
	inline real semidispersion(const vec_buff& data) {

		return range(data) / 2.0;
	}


	/// Propagate error of a sum of values
	/// as sqrt(sigma_x^2 + sigma_y^2 + ...)
	inline real propagate_sum(const vec_buff& sigma) {

		return sqrt(sum_squares(sigma));
	}


	/// Propagate error of a product (or quotient) of values
	/// as sqrt((sigma_x / x_mean)^2 + (sigma_y / y_mean)^2 + ...)
	/// The result is the propagated relative error
	inline real propagate_product(const vec_buff& sigma, const vec_buff& mean) {

		if(sigma.size() != mean.size()) {
			TH_MATH_ERROR("propagate_product", sigma.size(), INVALID_ARGUMENT);
			return nan();
		}

		// Compute sum of squares of (i_sigma / i_mean)
		real s = 0;
		for (unsigned int i = 0; i < sigma.size(); ++i) {

			if(mean[i] == 0) {
				TH_MATH_ERROR("propagate_product", mean[i], DIV_BY_ZERO);
				return nan();
			}

			s += square(sigma[i] / abs(mean[i]));
		}

		return sqrt(s);
	}


	/// Total sum of squares (TSS)
	/// Computed as sum(square(x_i - x_mean))
	inline real total_sum_squares(const vec_buff& X) {

		if(!X.size()) {
			TH_MATH_ERROR("total_sum_squares", X.size(), INVALID_ARGUMENT);
			return nan();
		}

		real res = 0;
		real x_m = mean(X);
		
		for (unsigned int i = 0; i < X.size(); ++i)
			res += square(X[i] - x_m);

		return res;
	}

	/// Total sum of squares (TSS)
	/// Computed as sum(square(x_i - x_mean))
	/// @see total_sum_squares
	inline real tss(const vec_buff& X) {
		return total_sum_squares(X);
	}


	/// Compute the variance of a population
	inline real variance(const vec_buff& data) {

		if(!data.size()) {
			TH_MATH_ERROR("variance", data.size(), INVALID_ARGUMENT);
			return nan();
		}

		return total_sum_squares(data) / (real) data.size();
	}


	/// Compute the variance of a sample
	/// This function uses Bessel correction
	inline real sample_variance(const vec_buff& data) {

		if(!data.size()) {
			TH_MATH_ERROR("sample_variance", data.size(), INVALID_ARGUMENT);
			return nan();
		}

		// Bessel correction (N - 1)
		return total_sum_squares(data) / (real) (data.size() - 1);
	}


	/// Compute the standard deviation of a population
	inline real standard_deviation(const vec_buff& data) {
		return sqrt(variance(data));
	}


	/// Compute the standard deviation of a population
	inline real stdev(const vec_buff& data) {
		return standard_deviation(data);
	}


	/// Compute the standard deviation of a sample
	inline real sample_standard_deviation(const vec_buff& data) {
		return sqrt(sample_variance(data));
	}


	/// Compute the standard deviation of a sample
	inline real smpl_stdev(const vec_buff& data) {
		return sample_standard_deviation(data);
	}


	/// Compute the relative error on a population measure
	/// using standard deviation
	inline real standard_relative_error(const vec_buff& X) {

		real x_mean = mean(X);

		if(x_mean == 0) {
			TH_MATH_ERROR("standard_relative_error", x_mean, DIV_BY_ZERO);
			return nan();
		}

		return standard_deviation(X) / abs(x_mean);
	}


	/// Compute the relative error on a sample measure
	/// using standard deviation
	inline real sample_standard_relative_error(const vec_buff& X) {

		real x_mean = mean(X);

		if(x_mean == 0) {
			TH_MATH_ERROR("standard_relative_error", x_mean, DIV_BY_ZERO);
			return nan();
		}

		return sample_standard_deviation(X) / abs(x_mean);
	}


	/// Compute the standard deviation on the mean of a set of values
	inline real mean_standard_deviation(const vec_buff& data) {
		return sqrt(variance(data)) / sqrt(data.size());
	}


	/// Compute the standard deviation on the mean of a set of values
	inline real stdom(const vec_buff& data) {
		return mean_standard_deviation(data);
	}


	/// Compute the standard deviation on the mean of a set of measures
	/// Bessel correction is used in the calculation of the variance
	inline real sample_mean_standard_deviation(const vec_buff& data) {
		return sqrt(sample_variance(data)) / sqrt(data.size());
	}


	/// Compute the standard deviation on the mean of a set of measures
	/// Bessel correction is used in the calculation of the variance
	inline real smpl_stdom(const vec_buff& data) {
		return sample_mean_standard_deviation(data);
	}


	/// Compute the covariance of two sets of measures
	inline real covariance(const vec_buff& X, const vec_buff& Y) {

		if(X.size() != Y.size()) {
			TH_MATH_ERROR("covariance", X.size(), INVALID_ARGUMENT);
			return nan();
		}

		real s = 0;
		real X_mean = mean(X);
		real Y_mean = mean(Y);

		for (unsigned int i = 0; i < X.size(); ++i)
			s += (X[i] - X_mean) * (Y[i] - Y_mean);

		return s / (real) X.size();
	}


	/// Compute the covariance between two sets of sample measures
	/// This function uses Bessel correction
	inline real sample_covariance(const vec_buff& X, const vec_buff& Y) {

		if(X.size() != Y.size()) {
			TH_MATH_ERROR("sample_covariance", X.size(), INVALID_ARGUMENT);
			return nan();
		}

		real s = 0;
		real X_mean = mean(X);
		real Y_mean = mean(Y);

		for (unsigned int i = 0; i < X.size(); ++i)
			s += (X[i] - X_mean) * (Y[i] - Y_mean);

		// Bessel correction (N - 1)
		return s / (real) (X.size() - 1);
	}


	/// Pearson's correlation coefficient R for a population
	inline real correlation_coefficient(const vec_buff& X, const vec_buff& Y) {
		return covariance(X, Y) / (stdev(X) * stdev(Y));
	}


	/// Pearson's correlation coefficient r for a sample
	inline real sample_correlation_coefficient(const vec_buff& X, const vec_buff& Y) {
		return sample_covariance(X, Y) / (smpl_stdev(X) * smpl_stdev(Y));
	}


	/// Lag-n autocorrelation of a dataset
	/// @param X The dataset
	/// @param n The lag (defaults to lag-1)
	/// @return The lag-n autocorrelation of the given dataset
	inline real autocorrelation(const vec_buff& X, unsigned int n = 1) {

		if(X.size() < n) {
			TH_MATH_ERROR("autocorrelation", X.size(), INVALID_ARGUMENT);
			return nan();
		}

		const real mu = mean(X);
		real num = 0;
		real den = square(X[0] - mu);

		for (unsigned int i = n; i < X.size(); ++i) {

			const real delta = X[i] - mu;
			num += delta * (X[i - n] - mu);
			den += square(delta);
		}

		return num / den;
	}


	/// Absolute deviation from the mean
	inline real absolute_deviation(const vec_buff& X) {

		real mu = mean(X);
		real res = 0;

		for (real x : X)
			res += abs(x - mu);

		return res / X.size();
	}


	/// Absolute deviation from the mean
	inline real absdev(const vec_buff& X) {
		return absolute_deviation(X);
	}


	/// Skewness of a dataset
	inline real skewness(const vec_buff& X) {

		const real mu = mean(X);
		const real sigma = smpl_stdev(X);
		real res = 0;

		for (real x : X)
			res += cube((x - mu) / sigma);

		return res / X.size();
	}


	/// Normalized Kurtosis of a dataset
	inline real kurtosis(const vec_buff& X) {

		const real mu = mean(X);
		const real sigma = smpl_stdev(X);
		real res = 0;

		for (real x : X)
			res += pow((x - mu) / sigma, 4);

		return (res / X.size()) - 3;
	}


	/// Compute the chi-square from the set of observed
	/// quantities, expected quantities and errors.
	/// The provided sets should all have the same size.
	///
	/// @param O The set of observed values
	/// @param E The set of expected values
	/// @param sigma The set of standard deviations on the observations
	/// @return The computed Chi-squared
	inline real chi_square(
		const vec_buff& O,
		const vec_buff& E,
		const vec_buff& sigma) {

		if(O.size() != E.size() || E.size() != sigma.size()) {
			TH_MATH_ERROR("chi_square", E.size(), INVALID_ARGUMENT);
			return nan();
		}

		real c_sqr = 0;

		for (unsigned int i = 0; i < O.size(); ++i) {

			if(abs(sigma[i]) < MACH_EPSILON) {
				TH_MATH_ERROR("chi_square", sigma[i], DIV_BY_ZERO);
				return nan();
			}

			c_sqr += square((O[i] - E[i]) / sigma[i]);
		}

		return c_sqr;
	}


	/// Compute the (right-tailed) p-value associated to a computed
	/// Chi-square value as the integral of the Chi-squared
	/// distribution from the given value to infinity (right-tailed).
	/// An equivalent integral is computed using Gauss-Laguerre quadrature: 
	/// \f$ p = \frac{e^{-X^2}}{2 \Gamma (k/2)} \int_0^{+\infty} (\sqrt{x + X^2})^{k - 2} e^{-x} dx \f$
	///
	/// @param chi_sqr The computed Chi-squared
	/// @param ndf Number of Degrees of Freedom
	/// @result The computed p-value
	/// @note The current implementation works up to ndf = 36
	inline real pvalue_chi_squared(real chi_sqr, unsigned int ndf) {

		const real coeff = exp(-chi_sqr / 2) / special::half_gamma(ndf);

		return coeff * integral_gauss(
			[=](real x) {
				return pow(sqrt(x + chi_sqr / 2), ndf - 2);
		}, tables::laguerre_roots_16, tables::laguerre_weights_16, 16);
	}


	/// Compute the chi-square on a linearization
	template<typename Dataset1, typename Dataset2, typename Dataset3>
	inline real chi_square_linearization(
		const Dataset1& X, const Dataset2& Y,
		const Dataset3& sigma, real intercept, real slope) {

		if(X.size() != Y.size() || X.size() != sigma.size()) {
			TH_MATH_ERROR(
				"chi_square_linearization",
				X.size(), INVALID_ARGUMENT);
			return nan();
		}

		real chi_squared = 0;
		for (unsigned int i = 0; i < X.size(); ++i) {

			if(abs(sigma[i]) <= MACH_EPSILON) {
				TH_MATH_ERROR("chi_square_linearization", sigma[i], DIV_BY_ZERO);
				return nan();
			}

			chi_squared += square((Y[i] - intercept - slope * X[i]) / sigma[i]);
		}

		return chi_squared;
	}


	/// Compute the reduced chi-squared on a linearization
	template<typename Dataset1, typename Dataset2, typename Dataset3>
	inline real reduced_chi_square_linearization(
		const Dataset1& X, const Dataset2& Y,
		const Dataset3& sigma, real intercept, real slope) {

		if(Y.size() <= 2) {
			TH_MATH_ERROR("reduced_chi_square_linearization",
				Y.size(), INVALID_ARGUMENT);
			return nan();
		}

		// Divide by degrees of freedom (N - 2)
		return chi_square_linearization(X, Y, sigma, intercept, slope)
			/ (real) (Y.size() - 2);
	}

}

#endif
