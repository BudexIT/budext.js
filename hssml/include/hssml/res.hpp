#pragma once

#include <string>

namespace hssml {

class Err {
public:
	Err(int c = 0) {
		m_code = c;
	}
	Err(int c, const std::string& e) {
		m_code = c;
		m_err = e;
	}
	Err(const Err& other) {
		m_code = other.m_code;
		m_err = other.m_err;
	}
	~Err() {
	}

	int code() const {
		return m_code;
	}
	const std::string& string() const {
		return m_err;
	}

private:
	int m_code;
	std::string m_err;
};

struct Nothing {
};

template <typename T>
class Res {
public:
	Res() {
		m_err = Err(0);
	}
	Res(Err e) {
		m_err = e;
	}
	Res(T&& v) {
		m_val = v;
	}
	~Res() {
	}

	const Err& error() const {
		return m_err;
	}
	T&& unwrap() {
		return std::move(m_val);
	}

private:
	Err m_err;
	T m_val;
};

using ResNull = Res<Nothing>;

}