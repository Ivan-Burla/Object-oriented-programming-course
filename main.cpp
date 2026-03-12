#include <iostream>

// Point

class Point {
    double x, y;
public:
    static int count;

    Point(double x = 0.0, double y = 0.0) : x(x), y(y) { count++; }
    
    Point(const Point& other) : x(other.x), y(other.y) { count++; }

    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double nx) { x = nx; }
    void setY(double ny) { y = ny; }

    Point getMidpoint(const Point& other) const {
        return Point((x + other.x) / 2.0, (y + other.y) / 2.0);
    }
    
    void print() const { std::cout << "(" << x << ", " << y << ")"; }
};
int Point::count = 0;

// Triangle

class Triangle {
    Point v1, v2, v3;
    
    Point *m1 = nullptr, *m2 = nullptr, *m3 = nullptr;

public:
    static int count;

    class Segment {
        const Point& p1;
        const Point& p2;
    public:
        static int count;

        Segment(const Point& p1, const Point& p2) : p1(p1), p2(p2) { count++; }

        void print() const {
            std::cout << "segment: "; p1.print();
            std::cout << " --> "; p2.print(); std::cout << "\n";
        }
    };

    Triangle(const Point& p1, const Point& p2, const Point& p3) : v1(p1), v2(p2), v3(p3) { 
        count++; 
    }

    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;

    ~Triangle() { clearMedians(); }

    const Point& getV1() const { return v1; }
    const Point& getV2() const { return v2; }
    const Point& getV3() const { return v3; }

    void setV1(const Point& p) { v1 = p; clearMedians(); }
    void setV2(const Point& p) { v2 = p; clearMedians(); }
    void setV3(const Point& p) { v3 = p; clearMedians(); }

    void clearMedians() {
        delete m1; m1 = nullptr;
        delete m2; m2 = nullptr;
        delete m3; m3 = nullptr;
    }

    Segment getSide1() const { return Segment(v1, v2); }
    Segment getSide2() const { return Segment(v2, v3); }
    Segment getSide3() const { return Segment(v3, v1); }

    void calcMedians() {
        if (!m1) { 
            m1 = new Point(v2.getMidpoint(v3));
            m2 = new Point(v1.getMidpoint(v3));
            m3 = new Point(v1.getMidpoint(v2));
        }
    }

    Segment getMedian1() { calcMedians(); return Segment(v1, *m1); }
    Segment getMedian2() { calcMedians(); return Segment(v2, *m2); }
    Segment getMedian3() { calcMedians(); return Segment(v3, *m3); }
};

int Triangle::count = 0;
int Triangle::Segment::count = 0;

int main() {
    Point p1(0, 0), p2(6, 0), p3(9, 4);
    Triangle t(p1, p2, p3);

    std::cout << "___Sides___\n";
    t.getSide1().print();
    t.getSide2().print();
    t.getSide3().print();

    std::cout << "\n___Medians___\n";
    t.getMedian1().print();
    t.getMedian2().print();
    t.getMedian3().print();

    std::cout << "\n___Objects Count___\n";
    std::cout << "Points: " << Point::count << "\n";
    std::cout << "Triangles: " << Triangle::count << "\n";
    std::cout << "Segments: " << Triangle::Segment::count << "\n";

    return 0;
}