#pragma once

//#define _mul_thread
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>

#ifdef _WIN32
#define _Noreturn __declspec(noreturn)
#endif

#define radians(x) (x) * M_PI / 180.0f

_Noreturn void _myexit(const char* msg);

#define myexit(x) _myexit(x)



class vec3 {
private:
	
public:
	double _x, _y, _z;
	vec3();
	vec3(double x, double y, double z);

	vec3 add(const vec3& other) const;
	vec3 add(double scalar) const;
	vec3 sub(const vec3& other) const;
	vec3 sub(double scalar) const;
	vec3 mul(double scalar) const;
	double dotproduct(const vec3& other) const;
	vec3 cross(const vec3& other) const;
	double norm(void) const;
	vec3 unit() const;

	//Operator overloads
	vec3 operator+(const vec3& other) const;
	vec3 operator+(double scalar) const;
	vec3 operator-(const vec3& other) const;
	vec3 operator-(double scalar) const;
	double operator*(const vec3& other) const;
	vec3 operator*(double scalar) const;
	vec3 operator/(double scalar) const;
	vec3& operator+=(const vec3& other);
	vec3& operator+=(double scalar);
	friend std::ostream& operator << (std::ostream& out, const vec3& v);
};

typedef vec3 force_t;
typedef vec3 position_t;


class particle {
private:
	position_t _position;
	double _mass;
	double _radius;
	vec3 _velocity;
	vec3 _accel;
	std::vector<force_t> _forces;
	bool is_fixed = false;

public:
	particle(const position_t& position, double mass, double radius);
	particle(particle&& other) noexcept;
	unsigned int register_force(const force_t& force);
	void update_force(const force_t& force, unsigned int idx);
	vec3 get_accel(void) const;
	double get_cross_section(void) const;
	force_t get_air_drag(void) const;
	force_t get_air_drag(vec3& wind) const;
	force_t get_weight(void) const;
	void update(double dt);
	double get_radius(void) const;
	position_t& get_position(void);
	void fix(void);
	vec3& get_velocity(void);
};

class springdamper {
private:
	double _b, _k;
	particle &_p1, &_p2;
	double _ini_len;
	unsigned int idx1, idx2;
public:
	springdamper(double b, double k, particle& p1, particle& p2, const double len);
	springdamper(const springdamper& other) noexcept;
	force_t get_force(void);
	void update(void);

};


class particleSystem {
private:
	force_t* wind;
	unsigned int wind_idx;
	std::vector<particle> _particles;
	std::vector<springdamper> _spdampers;
	unsigned int n_worker = 4;
	std::vector<std::thread> _workers;
	void wait_all(void);

public:
	particleSystem();
	//particleSystem(particleSystem&& other);
	void add_particles(std::vector<particle>& particles);
	void update(double dt);
};
