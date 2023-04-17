import random as rd

import numpy as np
from numpy.testing import assert_allclose

from quad import function
import pytest


def test_quad_function():
    """Test of quadfunction defined in src-cpp/quad.cpp with bindings in
    src-cpp/bind/bindings.cpp"""

    # define function with numpy arrays
    A = np.asarray([[1, 2], [3, 4]], dtype=np.float64)
    x = np.asarray([1, 2], dtype=np.float64)
    b = A @ x
    # f(x) = 0.5*(x^T A x) + b^T x
    f = function(A, b)

    # check that the function value is correct
    assert_allclose(f.eval(x), 40.5, atol=1e-6)

    # check that the gradient is correct
    print(f.grad(x));
    assert_allclose(f.grad(x), np.asarray([10, 22]), atol=1e-6)


def test_quad_function_wrong_input():
    A = np.asarray([[1, 2, 3], [4, 5, 6]], dtype=np.float64)
    b = np.asarray([1, 2], dtype=np.float64)

    with pytest.raises(ValueError, match="Input matrix must be a square matrix"):
        function(A, b)

    A = np.asarray([[1, 2], [3, 4]], dtype=np.float64)
    b = np.asarray([1, 2, 3], dtype=np.float64)

    with pytest.raises(ValueError, match="Input vector must be compatible with the matrix"):
        function(A, b)

    A = np.asarray([[1, 2], [3, 4]], dtype=np.float64)
    b = np.asarray([1, 2], dtype=np.float64)
    x = np.asarray([1, 2, 3], dtype=np.float64)

    with pytest.raises(ValueError, match="Input vector must be compatible with the quadratic function"):
        function(A, b).eval(x)

    with pytest.raises(ValueError, match="Input vector must be compatible with the quadratic function"):
        function(A, b).grad(x)



