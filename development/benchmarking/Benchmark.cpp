#include <chrono>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "Benchmark.h"


// Benchmark
void Benchmark::writePairsToCSV(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    //file << "Test,Time (ms)\n";

    for (const auto& pair : this->m_results) {
        //file << pair.first << "," << std::fixed << pair.second << "\n";
        file << std::fixed << pair.second << "\n";
    }

    file.close();
}

void Benchmark::profileTick() {
    m_start = std::chrono::high_resolution_clock::now();
}

void Benchmark::profileTock(const std::string& label) {
    m_stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = m_stop - m_start;
    std::cout << label << ": " << std::fixed << dur.count() << "ms" << '\n';

    m_results.emplace_back(label, dur.count());
}

// VecStruct.h test
void vecStructTest(int multi) {
    std::vector<Vec3> v1;
    std::vector<Vec3> v2;
    float x = 0; // to use the result of operations so the compiler doesn't skip the operations

    auto boiler = [&](unsigned int length) {
        v1 = {};
        v2 = {};
        float x = 0;

        for (int j = 0; j < length; j++) {
            v1.emplace_back(((float)(j - (length / 2))) / 100.0f, ((float)(j - (length / 2.2))) / 100.0f, ((float)(j - (length / 1.8))) / 100.0f);
            v2.emplace_back(((float)(j - (length / 2))) / 100.0f, ((float)(j - (length / 2.2))) / 100.0f, ((float)(j - (length / 1.8))) / 100.0f);
        }
    };

    Benchmark b;

    boiler(1000000 * multi);

    b.profileTick();
    boiler(1000000 * multi);
    b.profileTock("VecStruct.h Initialization");

    // addition
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.Add(j);
            x += i.x;
        }
    }
    b.profileTock("VecStruct.h Addition");
    std::cout << x << '\n';

    // subtraction
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.Subtract(j);
            x += i.x;
        }
    }
    b.profileTock("VecStruct.h Subtraction");
    std::cout << x << '\n';

    // dot product
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.DotProduct(j);
            x += i.x;
        }
    }
    b.profileTock("VecStruct.h Dot Product");
    std::cout << x << '\n';

    // cross product
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.CrossProduct(j);
            x += i.x;
        }
    }
    b.profileTock("VecStruct.h Cross Product");
    std::cout << x << '\n';

    // scalar multiplication
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (float j = 0; j< 1000*multi; j++) {
            i.ScalarMulti(j);
            x += i.x;
        }
    }
    b.profileTock("VecStruct.h Scalar Multiplication");
    std::cout << x << '\n';

    // negatation
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        i.Negate();
        x += i.x;
    }
    b.profileTock("VecStruct.h Negatation");
    std::cout << x << '\n';

    // length
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        x += i.Length();
    }
    b.profileTock("VecStruct.h Length");
    std::cout << x << '\n';

    // normalize
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        i.Normalize();
        x += i.x;
    }
    b.profileTock("VecStruct.h Normalize");
    std::cout << x << '\n';

    b.writePairsToCSV("./resultsVecStruct.csv");
}

// Vec.h test
void vecTest(int multi) {
    std::vector<Vec> v1;
    std::vector<Vec> v2;
    float x = 0; // to use the result of operations so the compiler doesn't skip the operations

    auto boiler = [&](unsigned int length) {
        v1 = {};
        v2 = {};
        float x = 0;

        for (int j = 0; j < length; j++) {
            v1.emplace_back(((float)(j - (length / 2))) / 100.0f, ((float)(j - (length / 2.2))) / 100.0f, ((float)(j - (length / 1.8))) / 100.0f);
            v2.emplace_back(((float)(j - (length / 2))) / 100.0f, ((float)(j - (length / 2.2))) / 100.0f, ((float)(j - (length / 1.8))) / 100.0f);
        }
    };

    Benchmark b;

    boiler(1000000 * multi);

    b.profileTick();
    boiler(1000000 * multi);
    b.profileTock("Vec.h Initalization");

    // addition
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.Add(j);
            x += i.getX();
        }
    }
    b.profileTock("Vec.h Addition");
    std::cout << x << '\n';

    // subtraction
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.Subtract(j);
            x += i.getX();
        }
    }
    b.profileTock("Vec.h Subtraction");
    std::cout << x << '\n';

    // dot product
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.DotProduct(j);
            x += i.getX();
        }
    }
    b.profileTock("Vec.h Dot Product");
    std::cout << x << '\n';

    // cross product
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.CrossProduct(j);
            x += i.getX();
        }
    }
    b.profileTock("Vec.h Cross Product");
    std::cout << x << '\n';

    // scalar multiplication
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (float j = 0; j< 1000*multi; j++) {
            i.ScalarMulti(j);
            x += i.getX();
        }
    }
    b.profileTock("Vec.h Scalar Multiplication");
    std::cout << x << '\n';

    // negatation
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        i.Negate();
        x += i.getX();
    }
    b.profileTock("Vec.h Negatation");
    std::cout << x << '\n';

    // length
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        x += i.Length();
    }
    b.profileTock("Vec.h Length");
    std::cout << x << '\n';

    // normalize
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        i.Normalize();
        x += i.getX();
    }
    b.profileTock("Vec.h Normalize");
    std::cout << x << '\n';

    b.writePairsToCSV("./resultsVec.csv");
}


// VecClass.h test
void vecClassTest(int multi) {
    std::vector<VecClass> v1;
    std::vector<VecClass> v2;
    float x = 0; // to use the result of operations so the compiler doesn't skip the operations

    auto boiler = [&](unsigned int length) {
        v1 = {};
        v2 = {};
        float x = 0;

        for (int j = 0; j < length; j++) {
            v1.emplace_back(((float)(j - (length / 2))) / 100.0f, ((float)(j - (length / 2.2))) / 100.0f, ((float)(j - (length / 1.8))) / 100.0f);
            v2.emplace_back(((float)(j - (length / 2))) / 100.0f, ((float)(j - (length / 2.2))) / 100.0f, ((float)(j - (length / 1.8))) / 100.0f);
        }
    };

    Benchmark b;
    
    boiler(1000000 * multi);

    b.profileTick();
    boiler(1000000 * multi);
    b.profileTock("VecClass.h Initialization");

    // addition
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.Add(j);
            x += i.getX();
        }
    }
    b.profileTock("VecClass.h Addition");
    std::cout << x << '\n';

    // subtraction
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.Subtract(j);
            x += i.getX();
        }
    }
    b.profileTock("VecClass.h Subtraction");
    std::cout << x << '\n';

    // dot product
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.DotProduct(j);
            x += i.getX();
        }
    }
    b.profileTock("VecClass.h Dot Product");
    std::cout << x << '\n';

    // cross product
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.CrossProduct(j);
            x += i.getX();
        }
    }
    b.profileTock("VecClass.h Cross Product");
    std::cout << x << '\n';

    // scalar multiplication
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (float j = 0; j< 1000*multi; j++) {
            i.ScalarMulti(j);
            x += i.getX();
        }
    }
    b.profileTock("VecClass.h Scalar Multiplication");
    std::cout << x << '\n';

    // negatation
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        i.Negate();
        x += i.getX();
    }
    b.profileTock("VecClass.h Negatation");
    std::cout << x << '\n';

    // length
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        x += i.Length();
    }
    b.profileTock("VecClass.h Length");
    std::cout << x << '\n';

    // normalize
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        i.Normalize();
        x += i.getX();
    }
    b.profileTock("VecClass.h Normalize");
    std::cout << x << '\n';

    b.writePairsToCSV("./resultsVecClass.csv");
}


// VecClassPointers.h test
void vecClassPointersTest(int multi) {
    std::vector<VecClassPointers> v1;
    std::vector<VecClassPointers> v2;
    float x = 0; // to use the result of operations so the compiler doesn't skip the operations

    auto boiler = [&](unsigned int length) {
        v1 = {};
        v2 = {};
        float x = 0;

        for (int j = 0; j < length; j++) {
            v1.emplace_back(((float)(j - (length / 2))) / 100.0f, ((float)(j - (length / 2.2))) / 100.0f, ((float)(j - (length / 1.8))) / 100.0f);
            v2.emplace_back(((float)(j - (length / 2))) / 100.0f, ((float)(j - (length / 2.2))) / 100.0f, ((float)(j - (length / 1.8))) / 100.0f);
        }
    };

    Benchmark b;

    boiler(1000000 * multi);

    b.profileTick();
    boiler(1000000 * multi);
    b.profileTock("VecClassPointers.h Initialization");

    // addition
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.Add(&j);
            x += i.getX();
        }
    }
    b.profileTock("VecClassPointers.h Addition");
    std::cout << x << '\n';

    // subtraction
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.Subtract(&j);
            x += i.getX();
        }
    }
    b.profileTock("VecClassPointers.h Subtraction");
    std::cout << x << '\n';

    // dot product
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.DotProduct(&j);
            x += i.getX();
        }
    }
    b.profileTock("VecClassPointers.h Dot Product");
    std::cout << x << '\n';

    // cross product
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (auto j : v2) {
            i.CrossProduct(&j);
            x += i.getX();
        }
    }
    b.profileTock("VecClassPointers.h Cross Product");
    std::cout << x << '\n';

    // scalar multiplication
    boiler(1000*multi);
    b.profileTick();
    for (auto i : v1) {
        for (float j = 0; j< 1000*multi; j++) {
            i.ScalarMulti(j);
            x += i.getX();
        }
    }
    b.profileTock("VecClassPointers.h Scalar Multiplication");
    std::cout << x << '\n';

    // negatation
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        i.Negate();
        x += i.getX();
    }
    b.profileTock("VecClassPointers.h Negatation");
    std::cout << x << '\n';

    // length
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        x += i.Length();
    }
    b.profileTock("VecClassPointers.h Length");
    std::cout << x << '\n';

    // normalize
    boiler((1000*multi)*(1000*multi));
    b.profileTick();
    for (auto i : v1) {
        i.Normalize();
        x += i.getX();
    }
    b.profileTock("VecClassPointers.h Normalize");
    std::cout << x << '\n';

    b.writePairsToCSV("./resultsVecClassPointer.csv");
}

int main() {
    vecStructTest(10);

    //vecTest(1);
    
    vecClassTest(10);

    vecClassPointersTest(10);

    int wait;
    std::cin >> wait;

    return 0;
}