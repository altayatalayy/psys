#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "psys.hpp"

namespace py = pybind11;


PYBIND11_MODULE(psyspy, m) {
	    m.doc() = "particle system plugin"; // optional module docstring
		py::class_<particleSystem>(m, "particleSystem")
			.def(py::init<>())
			.def("add_particles", &particleSystem::add_particles)
			.def("update", &particleSystem::update)
			.def("run", &particleSystem::run)
			.def("stop", &particleSystem::stop)
			.def_property_readonly("sim_time", &particleSystem::get_sim_time);

		py::class_<vec3>(m, "vec3")
			.def(py::init<>())
			.def(py::init<double, double, double>());

		py::class_<particle>(m, "particle")
			.def(py::init<position_t, double, double>());


}
