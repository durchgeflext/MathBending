#include <iostream>
#include <MathBending/linear_algebra.hpp>


int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
    MathBending::Matrix<float, 4, 5> mat{1.f, 2.f};
    MathBending::Matrix<int, 3, 3> mat2{{1, 3}, {2, 4}};
    MathBending::Vec<float, 7> vec{1.f, 2.f, 3.f};
    MathBending::Vec2<double> vec2;
    MathBending::Vec3<int> vec3;
    MathBending::Vec4<char> vec4;

    vec2.x = 1.;
    vec2.y = 2.;

    std::cout << "Testing UB in this compiler " << vec2.u << ", " << vec2.data[0] << ", " << vec2.v << std::endl;
}
