
///
/// @file complex_types.h Complex data types definitions
///

#ifndef THEORETICA_COMPLEX_TYPES_H
#define THEORETICA_COMPLEX_TYPES_H


namespace theoretica {


	/// A bi-complex number
	template<typename Type = real>
	using bicomplex = complex<complex<Type>>;

}


#endif
