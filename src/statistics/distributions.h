
///
/// @file distributions.h Probability distribution functions
///

#ifndef THEORETICA_DISTRIBUTIONS
#define THEORETICA_DISTRIBUTIONS

#include "../core/real_analysis.h"
#include "./statistics.h"
#include "../core/function.h"


/// @namespace theoretica
namespace theoretica {


	/// Compute the likelihood of a distribution <f> with the given
	/// parameters <theta> and measures <X>
	inline real likelihood(const vec_buff& X, const vec_buff& theta, stat_function f) {

		real res = 1;

		for (unsigned int i = 0; i < X.size(); ++i) {
			res *= f(X[i], theta);
		}

		return res;
	}


	/// Compute the log likelihood of a distribution <f> with the given
	/// parameters <theta> and measures <X>
	inline real log_likelihood(const vec_buff& X, const vec_buff& theta, stat_function f) {

		real res = 0;

		for (unsigned int i = 0; i < X.size(); ++i) {
			res += ln(f(X[i], theta));
		}

		return res;
	}


	/// @namespace distribution Probability distribution functions
	namespace distribution {
	

		/// Gaussian distribution function
		inline real gaussian(real x, real X, real sigma) {

			return (1.0 / (sigma *
				sqrt(2 * PI))) * exp(-square(x - X) / (2 * square(sigma)));
		}


		/// Wrapper for distribution::gaussian(real, real, real)
		inline real gaussian(real x, const vec_buff& theta) {

			if(theta.size() != 2) {
				UMATH_ERROR("distribution::gaussian", theta.size(), INVALID_ARGUMENT);
				return nan();
			}

			return gaussian(x, theta[0], theta[1]);
		}


		/// Bernoulli distribution
		inline real bernoulli(unsigned int k, real p) {

			return pow(p, k) * pow(1 - p, 1 - k);
		}


		/// Wrapper for distribution::bernoulli(unsigned int, real)
		inline real bernoulli(real k, const vec_buff& theta) {

			if(theta.size() != 1) {
				UMATH_ERROR("distribution::bernoulli", theta.size(), INVALID_ARGUMENT);
				return nan();
			}

			return bernoulli(static_cast<unsigned int>(k), theta[0]);

		}


		/// Poisson distribution
		inline real poisson(unsigned int k, real lambda) {

			return exp(-lambda) * pow(lambda, k) / (real) fact(k);
		}


		/// Wrapper for distribution::poisson(unsigned int, real)
		inline real poisson(real k, const vec_buff& theta) {

			if(theta.size() != 1) {
				UMATH_ERROR("distribution::poisson", theta.size(), INVALID_ARGUMENT);
				return nan();
			}

			return poisson(static_cast<unsigned int>(k), theta[0]);

		}


		/// Binomial distribution function
		inline real binomial(unsigned int nu, unsigned int n, real p) {

			return binomial_coeff(n, nu) *
				pow(p, nu) * pow(1 - p, n - nu);
		}


		/// Wrapper for distribution::binomial(unsigned int, unsigned int, real)
		inline real binomial(real nu, const vec_buff& theta) {

			if(theta.size() != 2) {
				UMATH_ERROR("distribution::binomial", theta.size(), INVALID_ARGUMENT);
				return nan();
			}

			return binomial(static_cast<unsigned int>(nu),
				static_cast<unsigned int>(theta[0]), theta[1]);
		}


		/// Log-normal distribution
		inline real log_normal(real x, real mu, real sigma) {

			return 1.0 / (2.50662827463 * sigma * x) *
				exp(-square(ln(x) - mu) / (2 * square(sigma)));
		}


		/// Wrapper for distribution::log_normal(real, real, real)
		inline real log_normal(real x, const vec_buff& theta) {

			if(theta.size() != 2) {
				UMATH_ERROR("distribution::log_normal", theta.size(), INVALID_ARGUMENT);
				return nan();
			}

			return log_normal(x, theta[0], theta[1]);
		}


		/// Exponential distribution
		inline real exponential(real x, real lambda) {

			if(x < 0)
				return 0;

			return lambda * exp(-lambda * x);
		}


		/// Wrapper for distribution::exponential(real, real)
		inline real exponential(real x, const vec_buff& theta) {

			if(theta.size() != 1) {
				UMATH_ERROR("distribution::exponential", theta.size(), INVALID_ARGUMENT);
				return nan();
			}

			return exponential(x, theta[0]);
		}


		/// Cauchy distribution
		inline real cauchy(real x, real mu, real alpha) {

			return 1.0 / (PI * alpha * (1 + (square(x - mu) / square(alpha))));
		}


		/// Wrapper for distribution::cauchy(real, real, real)
		inline real cauchy(real x, const vec_buff& theta) {

			if(theta.size() != 2) {
				UMATH_ERROR("distribution::cauchy", theta.size(), INVALID_ARGUMENT);
				return nan();
			}

			return cauchy(x, theta[0], theta[1]);
		}


		/// Breit Wigner distribution
		inline real breit_wigner(real x, real M, real Gamma) {

			return Gamma / (2 * PI * (square(x - M) + square(Gamma / 2.0)));
		}


		/// Wrapper for distribution::breit_wigner(real, real, real)
		inline real breit_wigner(real x, const vec_buff& theta) {

			if(theta.size() != 2) {
				UMATH_ERROR("distribution::breit_wigner", theta.size(), INVALID_ARGUMENT);
				return nan();
			}

			return breit_wigner(x, theta[0], theta[1]);
		}


		/// Pareto distribution
		inline real pareto(real x, real x_m, real alpha) {

			if(alpha <= 0) {
				UMATH_ERROR("distribution::pareto", alpha, OUT_OF_DOMAIN);
				return nan();
			}

			if(x < x_m)
				return 0;

			return alpha * powf(x_m, alpha) / powf(x, alpha + 1);
		}


		/// Wrapper for distribution::pareto(real, real, real)
		inline real pareto(real x, const vec_buff& theta) {

			if(theta.size() != 2) {
				UMATH_ERROR("distribution::pareto", theta.size(), INVALID_ARGUMENT);
				return nan();
			}

			return pareto(x, theta[0], theta[1]);
		}

	}
}

#endif
