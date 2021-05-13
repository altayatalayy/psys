#include "psys.hpp"


// Vector
vec3::vec3() {
	_x = 0.0f; _y = 0.0f; _z = 0.0f;
}

vec3::vec3(double x, double y, double z) {
	_x = x; _y = y; _z = z;
}

vec3 vec3::add(const vec3& other) const {
	return  vec3(_x + other._x, _y + other._y, _z + other._z);
}

 vec3 vec3::add(double scalar) const {
	return vec3(_x + scalar, _y + scalar, _z + scalar);
}

 vec3 vec3::sub(const vec3& other) const {
	return add(other * -1);
}

 vec3 vec3::sub(double scalar) const {
	return add(-scalar);
}

 vec3 vec3::mul(double scalar) const {
	return vec3(_x*scalar, _y*scalar, _z*scalar);
}

double vec3::dotproduct(const vec3& other) const {
	double rv = 0;
	rv += _x * other._x;
	rv += _y * other._y;
	rv += _z * other._z;
	return rv;
}

 vec3 vec3::cross(const vec3& other) const {
	double x, y, z;
	x = _y*other._z - _z*other._y;
	y = _z*other._x - _x*other._z;
	z = _x*other._y - _y*other._x;
	return vec3(x, y, z);
}

 double vec3::norm(void) const {
	 return sqrt(_x*_x + _y*_y + _z*_z);
 }

 vec3 vec3::unit() const {
	 if (norm() == 0)
		 return vec3();
	 return *this/norm();
 }


//vec3 operator overloads
 vec3 vec3::operator+(const vec3& other) const {
	return add(other);
}

 vec3 vec3::operator+(double scalar) const {
	return add(scalar);
}

 vec3 vec3::operator-(const vec3& other) const {
	return sub(other);
}

 vec3 vec3::operator-(double scalar) const {
	return sub(scalar);
}

double vec3::operator*(const vec3& other) const {
	return dotproduct(other);
}

vec3 vec3::operator*(double scalar) const {
	return mul(scalar);
}

vec3 vec3::operator/(double scalar) const {
	return mul(1/scalar);
}

vec3& vec3::operator+=(const vec3& other) {
	_x += other._x;
	_y += other._y;
	_z += other._z;
	return *this;
}

vec3& vec3::operator+=(double scalar) {
	_x += scalar;
	_y += scalar;
	_z += scalar;
	return *this;
}


std::ostream& operator << (std::ostream& out, const vec3& v){
	out << "(" << v._x << "i, " << v._y << "j, " << v._z << "k)" << std::endl;
	return out;
}

// Particle
particle::particle(const position_t& position, double mass, double radius) 
	:_position(position), _mass(mass), _radius(radius)
{
	
	_velocity = *new vec3();
	_accel = *new vec3();
}

particle::particle(particle&& other) noexcept{
	_position = other._position;
	_mass = other._mass;
	_radius = other._radius;
	_velocity = other._velocity;
	_accel = other._accel;
	_forces = std::move(other._forces);
	is_fixed = other.is_fixed;
}

particle::particle(const particle& other) noexcept{
	_position = other._position;
	_mass = other._mass;
	_radius = other._radius;
	_velocity = other._velocity;
	_accel = other._accel;
	_forces = other._forces;
	is_fixed = other.is_fixed;

}

unsigned int particle::register_force(const force_t& force) {
	_forces.push_back(force);
	return _forces.size()-1;
}

void particle::update_force(const force_t& force, unsigned int idx) {
	if (idx >= _forces.size()) {
		myexit("particle force idx error");
	}
	_forces[idx] = force;
}

vec3 particle::get_accel(void) const{
	if (is_fixed) return vec3();
	vec3 acc = vec3();
	for (const force_t& f : _forces) {
		acc += f;
	}
	acc += get_weight();
	acc += get_air_drag();
	return acc/_mass;
}


double particle::get_cross_section(void) const {
	return M_PI * _radius/100 * _radius/100;
}

force_t particle::get_air_drag(void) const {
	double cd = 0.9, rho = 1.225;
	double drag_norm = cd * get_cross_section() * rho * _velocity.norm() * _velocity.norm() / 2;
	return (_velocity.unit()*-1) * drag_norm;
}

force_t particle::get_air_drag(vec3& wind) const {
	double cd = 0.9, rho = 1.225;
	vec3 v = _velocity + wind;
	double drag_norm = cd * get_cross_section() * rho * v.norm() * v.norm() / 2;
	return v.unit() * drag_norm;
}

force_t particle::get_weight(void) const {
	const double g = 9.81;
	return vec3(0, -g * _mass, 0);
}

void particle::update(double dt) {
	vec3 acc = get_accel();
	_velocity += acc * dt;
	_position += _velocity * dt;
}

double particle::get_radius() const{
	return _radius;
}

position_t& particle::get_position(void) {
	return std::ref(_position);
}

vec3& particle::get_velocity(void) {
	return std::ref(_velocity);
}

void particle::fix(void) {
	is_fixed = true;
}

//SpringDamper

springdamper::springdamper(double b, double k, particle& p1, particle& p2, const double len)
	:_b(b), _k(k), _p1(p1), _p2(p2), _ini_len(len)
{
	idx1 = _p1.register_force(*new vec3());
	idx2 = _p2.register_force(*new vec3());
}

springdamper::springdamper(const springdamper& other) noexcept
	:_p1(other._p1), _p2(other._p2)
{
	_b = other._b;
	_k = other._k;
	_ini_len = other._ini_len;
	idx1 = other.idx1;
	idx2 = other.idx2;

}

force_t springdamper::get_force(){
	force_t f = force_t();
	vec3 dx = _p1.get_position() - _p2.get_position();
	vec3 dv = _p1.get_velocity() - _p2.get_velocity();
	f += dv * _b;
	vec3 u = dx.unit() * _ini_len;
	f += (dx - u) * _k;
	return f;
}

void springdamper::update(void) {
	force_t f = get_force();
	_p1.update_force(f * -1, idx1);
	_p2.update_force(f, idx2);
}


//Particle system
particleSystem::particleSystem() : sim_time(0.0f), is_running(false), _dt(0.01){
	wind = new force_t(1, 0, 0);
	wind_idx = 1;
	_workers.reserve(n_worker);
	_particles.reserve(12);
}



void particleSystem::add_particles(std::vector<particle>& particles) {
	_particles = std::move(particles);
	for (int i = 0; i < _particles.size(); i++) {
		if (i < _particles.size() - 1) {
			_spdampers.push_back(springdamper(2.2, 4.6*5, _particles[i], _particles[i + 1], 2.5));
		}
	}
}


void particleSystem::update(double dt) {
	sim_time += dt;
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	for (particle& p : _particles) {
		p.update(dt);
	}
	for(springdamper& sd : _spdampers){	
			sd.update();
	}
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	double frame_time =  std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
}

double particleSystem::get_sim_time(void) const{
	return sim_time;	
}

void particleSystem::run(void){
	is_running = true;
	std::thread t([&]{
			while(this->is_running){
				this->update(this->_dt);
			}
		}
	);
	_workers.push_back(std::move(t));

}

void particleSystem::stop(void){
	if(is_running){
		is_running = false;
		_workers[0].join();
	}
}


_Noreturn void _myexit(const char* msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
}
