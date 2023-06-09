//
// Created by Luis - Work on 10.04.23.
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "quad_function.hpp"

namespace py = pybind11;

PYBIND11_MODULE(quad, m
){
py::options options;
//options.
//disable_function_signatures ();     // disable *default* function signatures in the docstrings
//options.
//disable_enum_members_docstring (); // disable *default* enum members docstrings
py::class_<quadFunction>(m, "Function")
.
def(py::init<py::EigenDRef < Eigen::MatrixXd>, py::EigenDRef<Eigen::VectorXd>>
(), R"pbdoc("Class for representing a function of the form

	.. math::

		  f(x)=x^{T}Ax+b^{T}x

	:param: matrix: Matrix :math:`A` (dtype: float64)
	:type matrix: NDArray
	:param vector: Vector :math:`b` (dtype: float64)
	:type vector: NDArray

	)pbdoc", py::arg("matrix"), py::arg("vector"))
.def_property("matrix", &quadFunction::get_mat, &quadFunction::set_mat, R"pbdoc(Matrix :math:`A`
	)pbdoc")
.def_property("vector", &quadFunction::get_vec, &quadFunction::set_vec, R"pbdoc(Vector :math:`b`
	)pbdoc")
.def("eval", &quadFunction::eval, R"pbdoc(Evaluates the quadratic function at the given point.

    :param x: Point at which to evaluate the function (dtype: float64)
    :type x: NDArray

    )pbdoc", py::arg("x"), py::return_value_policy::take_ownership)
.def("grad", &quadFunction::grad, R"pbdoc(Evaluates the gradient of the quadratic function at the given point.

    :param x: Point at which to evaluate the gradient of the function (dtype: float64)
    :type x: NDArray

    )pbdoc", py::arg("x"),
py::return_value_policy::take_ownership);
}

