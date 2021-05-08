//Altay Atalay
//64568

#include "psys.hpp"

const int n = 13;
const double dt = 0.01;

particleSystem ps;

void init_particle_system(particleSystem& ps, const unsigned int n) {
	std::vector<particle> particles;
	for (int i = 0; i < n; i++) {
		particle p = particle(vec3(0, i * -2.5f, 0), 1.5, 0.5);
		if (i == 0) p.fix();
		particles.push_back(std::move(p));
	}

	ps.add_particles(particles);
}

int main(int, char** argv){
	
	init_particle_system(ps, n);

    return 0;
}

