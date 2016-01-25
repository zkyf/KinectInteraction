#ifndef _MTL_MATRIX_TRAITS_
#define _MTL_MATRIX_TRAITS_

#include "mtl_complex.h"
#include "mtl_config.h"

namespace mtl {

  enum 
  { 
	  MAT_RECT, MAT_BAND, MAT_TRI, MAT_SYMM, MAT_HERM, MAT_ROW_MAJOR, MAT_COL_MAJOR, MAT_DIAG, MAT_DENSE,
	  MAT_PACKED, MAT_BAND_VIEW, MAT_SPARSE, MAT_ARRAY, MAT_ENVELOPE,
	  MAT_COMPRESSED, MAT_SPARSE_PAIR, MAT_TREE, MAT_LINKED_LIST,
	  MAT_upper, MAT_lower, MAT_unit_upper, MAT_unit_lower, MAT_dynamic_uplo,
	  MAT_internal = 0, MAT_external,
	  MAT_index_from_one = -1, MAT_index_from_zero = 0 
  };


//:  The "traits" class for MTL matrices.
//!component: type
//!category: containers, tags
template <class Matrix>
struct matrix_traits {

  //: The shape of the matrix, either rectangle_tag, banded_tag, diagonal_tag, triangle_tag, or symmetric_tag
  typedef typename Matrix::shape shape;
  //: The orientation, either row_tag or column_tag
  typedef typename Matrix::orientation orientation;
  //: The sparsity, either dense_tag or sparse_tag
  typedef typename Matrix::sparsity sparsity;

  //: Used by the trans helper function
  typedef typename Matrix::transpose_type transpose_type;
  //: Used by the rows and columns helper functions
  typedef typename Matrix::strided_type strided_type;
  //: Whether the rows and columns functions can be used with this Matrix
  typedef typename Matrix::strideability strideability;
  //: The Matrix type resulting from wrapping a scaled adator around this Matrix
  typedef typename Matrix::scaled_type scaled_type;
  //: Whether the Matrix owns its data, either external_tag or internal_tag
  typedef typename Matrix::storage_loc storage_loc;

  //: A OneD part of a Matrix. This could be a Row, a Column or a Diagonal depending on the type of Matrix.
  typedef typename Matrix::OneD OneD;

  //: The element type of the matrix
  typedef typename Matrix::value_type value_type;
  typedef typename Matrix::reference reference;
  typedef typename Matrix::const_reference const_reference;
  typedef typename Matrix::pointer pointer;

  //: A NonNegativeIntegral type
  typedef typename Matrix::size_type size_type;
  typedef typename Matrix::difference_type difference_type;

};
//: Row Matrix Traits
//!component: type
//!category: containers, tags
template <class Matrix>
struct row_matrix_traits {
  typedef typename Matrix::Row Row;
};

//: Column Matrix Traits
//!component: type
//!category: containers, tags
template <class Matrix>
struct column_matrix_traits {
  typedef typename Matrix::Column Column;
};

//: Diagonal Matrix Traits
//!component: type
//!category: containers, tags
template <class Matrix>
struct diagonal_matrix_traits {
  typedef typename Matrix::Diagonal Diagonal;
};

/*
 * Shape Tags
 * add enum for shape tags. -- Rich
 */
//: Identifies rectangular matrices
//!component: type
//!category: containers, tags
class rectangle_tag { public: enum{ id = MAT_RECT}; }; //mh

//: Identifies banded matrices
//!component: type
//!category: containers, tags
class banded_tag { public: enum{ id = MAT_BAND};}; //mh

//: Identifies triangular matrices
//!component: type
//!category: containers, tags
class triangle_tag : public banded_tag { public: enum{id = MAT_TRI};}; //mh

//: Identifies symmetric matrices
//!component: type
//!category: containers, tags
class symmetric_tag : public banded_tag { public: enum{id=MAT_SYMM};}; //mh

//: Identifies hermitian matrices
//!component: type
//!category: containers, tags
class hermitian_tag : public banded_tag{ public: enum{id=MAT_HERM};}; //mh

//: Identifies diagonal matrices
//!component: type
//!category: containers, tags
class diagonal_tag : public banded_tag { public: enum{id=MAT_DIAG};}; //mh

/*
 * Storage Tags
 */

//: Identifies the Matrix as not owning its data
//!component: type
//!category: containers, tags
class external_tag { };

//: Identifies the Matrix as owning its data
//!component: type
//!category: containers, tags
class internal_tag { };

/*
 * Orientation Tags
 */

//: Identifies a row-major Matrix
//!component: type
//!category: containers, tags
struct row_tag { enum { id = MAT_ROW_MAJOR }; };

//: Identifies a column-major Matrix
//!component: type
//!category: containers, tags
struct column_tag { enum { id = MAT_COL_MAJOR }; };

/*
 * Sparsity Tags
 */

//: Identifies a dense Matrix or Vector
//!component: type
//!category: containers, tags
struct dense_tag { enum { id = MAT_DENSE }; };

//: Identifies a sparse Matrix or Vector
//!component: type
//!category: containers, tags
struct sparse_tag { enum { id = MAT_SPARSE }; };

/*
 * Traits for linear algebra objects (matrices and vectors)
 */

//: Identifies linear algebra objects as 1D (Vector)
//!component: type
//!category: containers, tags
struct oned_tag { };

//: Identifies linear algebra objects as 2D (Matrix)
//!component: type
//!category: containers, tags
struct twod_tag { };


template <class number_type>
struct number_traits {
  typedef number_type magnitude_type;
};

#if MTL_PARTIAL_SPEC
template <class T>
struct number_traits< std::complex<T> > {
  typedef T magnitude_type;
};
#else
template <>
struct number_traits< std::complex<double> > {
  typedef double magnitude_type;
};
template <>
struct number_traits< std::complex<float> > {
  typedef float magnitude_type;
};
#endif
//: Linear Algebra Object (Matrix and Vector) Traits 
//!component: type
//!category: containers, tags
template <class Linalg>
struct linalg_traits {
  /*  enum { dimension = Linalg::dimension }; 1 for vectors, 2 for matrices */
  //: Whether the object is a 1D or 2D container
  typedef typename Linalg::dimension dimension;
  //: The element type within the container
  typedef typename Linalg::value_type value_type;
  //: Either sparse or dense
  typedef typename Linalg::sparsity sparsity;
  //: The return type for abs(value_type)
  typedef typename number_traits<value_type>::magnitude_type magnitude_type;
};

//: Identifies matrices that can be used with the rows and columns functions
//!component: type
//!category: containers, tags
struct strideable { };

//: Identifies matrices that can not be used with the rows and columns functions
//!component: type
//!category: containers, tags
struct not_strideable { };

/* the following are used in constructors to avoid ambiguity and
   compiler errors */

//: blah
//!noindex:
struct do_transpose { };

//: blah
//!noindex:
struct do_strided { };

//: blah
//!noindex:
struct do_scaled { };

//: blah
//!noindex:
struct do_stream { };

} /* namespace mtl */

#endif /* _MTL_MATRIX_TRAITS_ */
