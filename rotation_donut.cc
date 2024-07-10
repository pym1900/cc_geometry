#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <unistd.h>

constexpr int screen_width = 80;
constexpr int screen_height = 22;
constexpr int buffer_size = screen_width * screen_height;

int main() {
    float A = 0, B = 0;
    std::vector<float> z(buffer_size, 0);
    std::vector<char> b(buffer_size, ' ');

    std::cout << "\x1b[2J";
    while (true) {
        std::fill(b.begin(), b.end(), ' ');
        std::fill(z.begin(), z.end(), 0);

        for (float j = 0; j < 6.28; j += 0.07) {
            for (float i = 0; i < 6.28; i += 0.02) {
                float c = std::sin(i);
                float d = std::cos(j);
                float e = std::sin(A);
                float f = std::sin(j);
                float g = std::cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = std::cos(i);
                float m = std::cos(B);
                float n = std::sin(B);
                float t = c * h * g - f * e;
                int x = static_cast<int>(screen_width / 2 + 30 * D * (l * h * m - t * n));
                int y = static_cast<int>(screen_height / 2 + 15 * D * (l * h * n + t * m));
                int o = x + screen_width * y;
                int N = static_cast<int>(8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n));

                if (screen_height > y && y > 0 && x > 0 && screen_width > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[std::max(0, N)];
                }
            }
        }

        std::cout << "\x1b[H";
        for (int k = 0; k < buffer_size; k++) {
            std::cout << (k % screen_width ? b[k] : '\n');
        }
        
        A += 0.04;
        B += 0.02;
        usleep(30000);
    }

    return 0;
}
