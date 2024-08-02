#include <algorithm>
#include <cmath>
#include <iostream>
#include <array>
#include <vector>
#include <thread>
#include <chrono>
#include <Eigen/Dense>

float A = 0.0f, B = 0.0f, C = 0.0f;

constexpr int width = 144;
constexpr int height = 60;
constexpr char bgASCII = ' ';
constexpr float K1 = 40.0f;
constexpr float incrementSpeed = 0.6f;

float cube_width = 20.0f;
float horizontal_offset = -2 * cube_width;

std::array<float, width * height> z_buffer{};
std::array<char, width * height> buffer{};

Eigen::Matrix3f getRotationMatrix() {
    Eigen::Matrix3f Rx;
    Rx << 1, 0, 0,
          0, cos(A), -sin(A),
          0, sin(A), cos(A);

    Eigen::Matrix3f Ry;
    Ry << cos(B), 0, sin(B),
          0, 1, 0,
          -sin(B), 0, cos(B);

    Eigen::Matrix3f Rz;
    Rz << cos(C), -sin(C), 0,
          sin(C), cos(C), 0,
          0, 0, 1;

    return Rz * Ry * Rx;
}

void calculatePlane(const float& cube_x, const float& cube_y, const float& cube_z, const char& ch) {
    Eigen::Vector3f point(cube_x, cube_y, cube_z);
    Eigen::Matrix3f R = getRotationMatrix();
    Eigen::Vector3f rotated = R * point;

    float x = rotated.x();
    float y = rotated.y();
    float z = rotated.z() + 100.0f; // distanceFromCam

    float ooz = 1.0f / z;

    int xp = static_cast<int>(width / 2 + horizontal_offset + K1 * ooz * x * 2);
    int yp = static_cast<int>(height / 2 + K1 * ooz * y);

    int idx = xp + yp * width;
    if (idx >= 0 && idx < width * height) {
        if (ooz > z_buffer[idx]) {
            z_buffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

int main() {
    std::cout << "\x1b[2J";

    while (true) {
        std::fill(buffer.begin(), buffer.end(), bgASCII);
        std::fill(z_buffer.begin(), z_buffer.end(), 0);

        for (float cube_x = -cube_width; cube_x < cube_width; cube_x += incrementSpeed) {
            for (float cube_y = -cube_width; cube_y < cube_width; cube_y += incrementSpeed) {
                calculatePlane(cube_x, cube_y, -cube_width, '@');
                calculatePlane(cube_width, cube_y, cube_x, '$');
                calculatePlane(-cube_width, cube_y, -cube_x, '~');
                calculatePlane(-cube_x, cube_y, cube_width, '#');
                calculatePlane(cube_x, -cube_width, -cube_y, ';');
                calculatePlane(cube_x, cube_width, cube_y, '+');
            }
        }

        std::cout << "\x1b[H";
        for (int k = 0; k < width * height; ++k) {
            std::cout.put(k % width ? buffer[k] : '\n');
        }

        A += 0.05f;
        B += 0.05f;
        C += 0.01f;

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
    return 0;
}
