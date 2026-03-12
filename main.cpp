#include <iostream>
#include <cmath>

class TComplex;

// 1. Алгебраїчна форма
class AComplex {
public:
    double re, im;

    void checkInvariant() const {
        if (std::isnan(re) || std::isnan(im)) std::cerr << "_Error_ Invariant AComplex violated!\n";
    }

    AComplex(double r = 0, double i = 0) : re(r), im(i) {
        std::cout << "_Creation_ AComplex\n";
        checkInvariant();
    }
    
    AComplex(const TComplex& t);

    AComplex& operator+=(const AComplex& o) { re += o.re; im += o.im; return *this; }
    AComplex& operator-=(const AComplex& o) { re -= o.re; im -= o.im; return *this; }
    AComplex& operator*=(const AComplex& o); 
    AComplex& operator/=(const AComplex& o); 
};

// 2. Тригонометрична форма
class TComplex {
public:
    double r, phi;

    void checkInvariant() {
        if (r < 0) { r = -r; phi += 3.1415926535; }
    }

    TComplex(double radius = 0, double angle = 0) : r(radius), phi(angle) {
        checkInvariant();
        std::cout << "_Creation_ TComplex\n";
    }
    
    TComplex(const AComplex& a) {
        r = std::hypot(a.re, a.im);
        phi = std::atan2(a.im, a.re);
        checkInvariant();
        std::cout << "_Conversion_ AComplex --> TComplex\n";
    }

    TComplex& operator*=(const TComplex& o) { r *= o.r; phi += o.phi; return *this; }
    TComplex& operator/=(const TComplex& o) { r /= o.r; phi -= o.phi; return *this; }
    TComplex& operator+=(const TComplex& o); 
    TComplex& operator-=(const TComplex& o); 
};

AComplex::AComplex(const TComplex& t) : re(t.r * std::cos(t.phi)), im(t.r * std::sin(t.phi)) {
    std::cout << "_Conversion_ TComplex --> AComplex\n";
}

AComplex operator+(const AComplex& a, const AComplex& b) { return AComplex(a.re + b.re, a.im + b.im); }
AComplex operator-(const AComplex& a, const AComplex& b) { return AComplex(a.re - b.re, a.im - b.im); }

TComplex operator*(const TComplex& a, const TComplex& b) { return TComplex(a.r * b.r, a.phi + b.phi); }
TComplex operator/(const TComplex& a, const TComplex& b) { return TComplex(a.r / b.r, a.phi - b.phi); }

AComplex& AComplex::operator*=(const AComplex& o) { return *this = AComplex(TComplex(*this) * TComplex(o)); }
AComplex& AComplex::operator/=(const AComplex& o) { return *this = AComplex(TComplex(*this) / TComplex(o)); }
TComplex& TComplex::operator+=(const TComplex& o) { return *this = TComplex(AComplex(*this) + AComplex(o)); }
TComplex& TComplex::operator-=(const TComplex& o) { return *this = TComplex(AComplex(*this) - AComplex(o)); }

int main() {
    AComplex a(2, 3);
    TComplex t(5, 0.5);
    double realNum = 10.0;

    std::cout << "\n___ Test of mixed operations ___\n";
    
    AComplex sum1 = realNum + a; 
    TComplex prod1 = t * realNum;
    
    a += t;
    t /= a;

    return 0;
}