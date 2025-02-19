#include <iostream>

struct Vector {
    float x, y;
    Vector(float x, float y): x(x), y(y) {};
    Vector add(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }
    Vector multiply(const Vector& other) const {
        return Vector(x * other.x, y * other.y);
    }

    Vector operator+(const Vector& other) const {
        return add(other);
    }
    Vector operator*(const Vector& other) const {
        return multiply(other);
    }
    bool operator==(const Vector& other) const {
        return (x == other.x && y == other.y);
    }
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }
};

std::ostream& operator<<(std::ostream& stream, const Vector& other){
    return stream<<other.x<<", "<<other.y<<std::endl;
}

int main() {
    Vector a(1, 2);
    Vector b(2, 3);
    Vector c(0.5f, 1.5f);
    std::cout<<"Vector a : "<<"x : "<<a.x<<", y: "<<a.y<<std::endl;
    std::cout<<"Vector b : "<<"x : "<<b.x<<", y: "<<b.y<<std::endl;
    Vector result = a.add(b.multiply(c));
    Vector result_op = a + b * c;
    std::cout<<"Resultant x + y : "<<"x : "<<result.x<<", y: "<<result.y<<std::endl;
    std::cout<<"Resultant operator x + y : "<<"x : "<<result_op.x<<", y: "<<result_op.y<<std::endl;
    bool iseq = result == result_op;
    bool isne = result != result_op;
    std::cout<<"a == b : "<<iseq<<std::endl;
    std::cout<<"a != b : "<<isne<<std::endl;
}