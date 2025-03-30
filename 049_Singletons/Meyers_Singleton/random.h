#pragma once

#include <iostream>
#include <random>

namespace Uniform {
    class Random {
        public:
            static Random& getinstance(long double a, long double b);
            Random(const Random&) = delete;
            Random& operator=(const Random&) = delete;
            Random(Random&&) = delete;
            Random& operator=(Random&&) = delete;
            static double Generator(long double a = -1.0, long double b = 1.0);
        private:
            Random(long double a, long double b);
            ~Random();

            double gen_random() noexcept;
        
            std::random_device rd;
            std::mt19937 gen;
            std::uniform_real_distribution<double> dis;
    };
}

namespace Normal {
    class Random {
        public:
            static Random& getinstance(long double a, long double b);
            Random(const Random&) = delete;
            Random& operator=(const Random&) = delete;
            Random(Random&&) = delete;
            Random& operator=(Random&&) = delete;
            static double Generator(long double a = -1.0, long double b = 1.0);
        private:
            Random(long double a, long double b);
            ~Random();

            double gen_random() noexcept;
        
            std::random_device rd;
            std::mt19937 gen;
            std::normal_distribution<double> dis;
    };
}