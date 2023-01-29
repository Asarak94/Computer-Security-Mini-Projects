#include "crypto_package/cryptlib.h"
#include "crypto_package/rijndael.h"
#include "crypto_package/modes.h"
#include "crypto_package/files.h"
#include "crypto_package/osrng.h"
#include "crypto_package/hex.h"
#include "crypto_package/des.h"
#include "crypto_package/aes.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <time.h> 
using std::cerr;
using std::endl;
using CryptoPP::DES;

// Generate a random string according to the given length
char* getRandomPlain(int length)
{
    char* plain = new char[length];
    for (int i = 0; i < length; i++) {
        plain[i] = rand() % 26;
        plain[i] = 'A' + plain[i];
    }
    return plain;
}

void DES_CBC(std::string plaintext_input) {
    using namespace CryptoPP;
    AutoSeededRandomPool prng;

    SecByteBlock key(DES_EDE2::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());

    byte iv[DES_EDE2::BLOCKSIZE];
    prng.GenerateBlock(iv, sizeof(iv));

    std::string cipher4, recovered4;
    clock_t startTime, finishTime;

    /*

   DES CBC MODE ENCRYPTION

*/

    try
    {
        startTime = clock();
        CBC_Mode< DES_EDE2 >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter adds padding
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        StringSource(plaintext_input, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher4)
            ) // StreamTransformationFilter      
        ); // StringSource

        finishTime = clock();
        
        //calculate the throughput
        double timeTaken = double(finishTime - startTime) / (double)CLOCKS_PER_SEC;
        double Throughput = ((double)plaintext_input.size() / 1048576) / timeTaken;
        std::cout << " DES CBC MODE Encryption Throughput in Mbps: " << Throughput;
        std::cout << std::endl;
    }
    catch (const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

    /*

   DES CBC MODE DECRYPTION

*/

    try
    {
        startTime = clock();
        CBC_Mode< DES_EDE2 >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource s(cipher4, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered4)
            ) // StreamTransformationFilter
        ); // StringSource
        //cout << "recovered text: " << recovered4 << endl;

        finishTime = clock();

        //calculate the throughput
        double timeTaken = double(finishTime - startTime) / (double)CLOCKS_PER_SEC;
        double Throughput = ((double)cipher4.size() / 1048576) / timeTaken;
        std::cout << " DES CBC MODE Decryption Throughput in Mbps: " << Throughput;
        std::cout << std::endl;
    }
    catch (const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

}


void TrippleDesCBC(std::string plaintext_input) {
    using namespace CryptoPP;
    AutoSeededRandomPool prng;

    SecByteBlock key(DES_EDE3::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());

    byte iv[DES_EDE3::BLOCKSIZE];
    prng.GenerateBlock(iv, sizeof(iv));

    std::string cipher3, recovered3;
    clock_t startTime, finishTime;

    /*

   3DES CBC MODE ENCRYPTION

   */

    try
    {
        startTime = clock();
        CBC_Mode< DES_EDE3 >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter adds padding
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        StringSource(plaintext_input, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher3)
            ) // StreamTransformationFilter      
        ); // StringSource

        finishTime = clock();

        //calculate the throughput
        double timeTaken = double(finishTime - startTime) / (double)CLOCKS_PER_SEC;
        double Throughput = ((double)plaintext_input.size() / 1048576) / timeTaken;
        std::cout << " 3DES CBC MODE Encryption Throughput in Mbps: " << Throughput;
        std::cout << std::endl;
    }
    catch (const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

    /*

       3DES CBC MODE DECRYPTION

   */


    try
    {
        startTime = clock();
        CBC_Mode< DES_EDE3 >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource s(cipher3, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered3)
            ) // StreamTransformationFilter
        ); // StringSource

        //std::cout << "recovered text: " << recovered3 << endl;

        finishTime = clock();

        //calculate the throughput
        double timeTaken = double(finishTime - startTime) / (double)CLOCKS_PER_SEC;
        double Throughput = ((double)cipher3.size() / 1048576) / timeTaken;
        std::cout << " 3DES CBC MODE Decryption Throughput in Mbps: " << Throughput;
        std::cout << std::endl;
    }
    catch (const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

}

void AES_CBC(std::string plaintext_input) {

    using namespace CryptoPP;

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    SecByteBlock iv(AES::BLOCKSIZE);

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    std::string cipher1, recovered1;
    clock_t startTime, finishTime;

 /*

    AES CBC MODE ENCRYPTION

*/

    try
    {
        startTime = clock();
        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource s(plaintext_input, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher1)
            ) // StreamTransformationFilter
        ); // StringSource

        finishTime = clock();

        //calculate the throughput
        double timeTaken = double(finishTime - startTime) / (double)CLOCKS_PER_SEC;
        double Throughput = ((double)plaintext_input.size() / 1048576) / timeTaken;
        std::cout << " AES CBC MODE Encryption Throughput in Mbps: " << Throughput;
        std::cout << std::endl;
    }
    catch (const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    /*

        AES CBC MODE DECRYPTION

    */

    try
    {
        startTime = clock();
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource s(cipher1, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered1)
            ) // StreamTransformationFilter
        ); // StringSource

        //std::cout << "recovered text: " << recovered1 << std::endl;
        finishTime = clock();

        //calculate the throughput
        double timeTaken = double(finishTime - startTime) / (double)CLOCKS_PER_SEC;
        double Throughput = ((double)cipher1.size() / 1048576) / timeTaken;
        std::cout << " AES CBC MODE Decryption Throughput in Mbps: " << Throughput;
        std::cout << std::endl;
    }

    catch (const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

}

void AES_ECB(std::string plaintext_input) {
    using namespace CryptoPP;

    AutoSeededRandomPool prng;

    byte key[AES::DEFAULT_KEYLENGTH];
    prng.GenerateBlock(key, sizeof(key));

    std::string cipher2, recovered2;
    clock_t startTime, finishTime;

    /*

        AES ECB MODE ENCRYPTION

   */

    try
    {
        startTime = clock();
        ECB_Mode< AES >::Encryption e;
        e.SetKey(key, sizeof(key));

        // The StreamTransformationFilter adds padding
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        StringSource(plaintext_input, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher2)
            ) // StreamTransformationFilter      
        ); // StringSource

        finishTime = clock();

        //calculate the throughput
        double timeTaken = double(finishTime - startTime) / (double)CLOCKS_PER_SEC;
        double Throughput = ((double)plaintext_input.size() / 1048576) / timeTaken;
        std::cout << " AES ECB MODE Encryption Throughput in Mbps: " << Throughput;
        std::cout << std::endl;
    }
    catch (const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

    /*

    AES ECB MODE DECRYPTION

    */

    try
    {
        startTime = clock();
        ECB_Mode< AES >::Decryption d;
        d.SetKey(key, sizeof(key));

        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource s(cipher2, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered2)
            ) // StreamTransformationFilter
        ); // StringSource

        //std::cout << "recovered text: " << recovered2 << endl;

        finishTime = clock();

        //calculate the throughput
        double timeTaken = double(finishTime - startTime) / (double)CLOCKS_PER_SEC;
        double Throughput = ((double)cipher2.size() / 1048576) / timeTaken;
        std::cout << " AES ECB MODE Decryption Throughput in Mbps: " << Throughput;
        std::cout << std::endl;


    }
    catch (const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

}


int main(int argc, char* argv[])
{
    // Generate a random 1MB string
    int plainLength = 1024 * 1024 * sizeof(unsigned char);
    std::cout << "plainLength: " << plainLength;
    std::cout << std::endl;
    char* randomvalue = getRandomPlain(plainLength);
    std::string plaintext_input = randomvalue;

    // call the encryption modes by passing the random string
    DES_CBC(plaintext_input);
    TrippleDesCBC(plaintext_input);
    AES_CBC(plaintext_input);
    AES_ECB(plaintext_input);
    return 0;

}