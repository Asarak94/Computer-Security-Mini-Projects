#include "./crypto_package/integer.h"
#include "./crypto_package/osrng.h"
#include "./crypto_package/hrtimer.h"
#include "./crypto_package/algparam.h"
#include <iostream>

int main(int argc, char* argv[])
{
    using namespace CryptoPP;

    Integer x;
    ThreadUserTimer timer;
    AutoSeededRandomPool prng;

    AlgorithmParameters params = MakeParameters("BitLength", 768)
        ("RandomNumberType", Integer::PRIME);

    for (int i = 0; i < 10; i++) {
        std::cout << "Prime Number" << i << std::endl;
        std::cout << std::endl;
        timer.StartTimer();
        x.GenerateRandom(prng, params);
        double time = timer.ElapsedTimeAsDouble();

        std::cout << "Time for generating the Prime Number: " << i <<  time << " seconds" << std::endl;
        std::cout << std::endl;
        std::cout << x << std::endl;
        std::cout << std::endl;

    }


    return 0;
}