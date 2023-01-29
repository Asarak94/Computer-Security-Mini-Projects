#include "./crypto_package/cryptlib.h"
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "./crypto_package/md5.h"
#include "./crypto_package/hex.h"
#include "./crypto_package/files.h"
#include "crypto_package/sha.h"
#include "crypto_package/ripemd.h"
#include <iostream>
using namespace CryptoPP;
using namespace std;

void md5(string plainText) {

    HexEncoder encoder(new FileSink(cout));
    string messageDigest;
    //Define timer 
    clock_t startTime1, finishTime1;


    startTime1 = clock();
    Weak::MD5 hash;
    //Adding Data
    hash.Update((const byte*)&plainText[0], plainText.size());
    messageDigest.resize(hash.DigestSize());

    //Calculate the hash
    hash.Final((byte*)&messageDigest[0]);
    finishTime1 = clock();

    double timeforHashing = double(finishTime1 - startTime1) / (double)CLOCKS_PER_SEC;
   /* cout << "timeTaken for Hashing: " << timeTakenHashing << endl;*/
    double ThroughputMD5 = ((double)plainText.size() / 1048576) / timeforHashing;

    //cout << "Input Message: " << plainText << endl;

    cout << "MD5 Hash Value: ";
    StringSource(messageDigest, true, new Redirector(encoder));
    cout << endl;
    cout << " Throughput of MD5 Hashing in Mbps: " << ThroughputMD5;
    cout << endl;

}

void sha256(string plainText) {

    HexEncoder encoder(new FileSink(cout));
    string messageDigest;
    //Define timer 
    clock_t startTime2, finishTime2;

    startTime2 = clock();
    SHA256 hash;
    hash.Update((const byte*)plainText.data(), plainText.size());
    messageDigest.resize(hash.DigestSize());
    hash.Final((byte*)&messageDigest[0]);
    finishTime2 = clock();

    double timeforHashing = double(finishTime2 - startTime2) / (double)CLOCKS_PER_SEC;
    /* cout << "timeTaken for Hashing: " << timeTakenHashing << endl;*/
    double Throughputsha256 = ((double)plainText.size() / 1048576) / timeforHashing;

    cout << "SHA256 Hash Value: ";
    StringSource(messageDigest, true, new Redirector(encoder));
    cout << endl;
    cout << " Throughput of SHA256 Hashing in Mbps: " << Throughputsha256;
    cout << endl;

}

void ripemd160(string plainText) {

    HexEncoder encoder(new FileSink(cout));
    string messageDigest;
    //Define timer 
    clock_t startTime3,finishTime3;

    startTime3 = clock();
    RIPEMD160 hash;
    hash.Update((const byte*)plainText.data(), plainText.size());
    messageDigest.resize(hash.DigestSize());
    hash.Final((byte*)&messageDigest[0]);
    finishTime3 = clock();

    double timeforHashing = double(finishTime3 - startTime3) / (double)CLOCKS_PER_SEC;
    /* cout << "timeTaken for Hashing: " << timeTakenHashing << endl;*/
    double Throughputripemd160 = ((double)plainText.size() / 1048576) / timeforHashing;

    cout << "RIPEMD160 Hash Value: ";
    StringSource(messageDigest, true, new Redirector(encoder));
    cout << endl;
    cout << " Throughput of RIPEMD160 Hashing in Mbps: " << Throughputripemd160;
    cout << endl;

}

char* getRandomPlain(int length)
{
    char* plain = new char[length];
    for (int i = 0; i < length; i++) {
        plain[i] = rand() % 26;
        plain[i] = 'A' + plain[i];
    }
    return plain;
}

int main(int argc, char* argv[])
{
    // Generate a random 1MB string
    int plainLength = 1024 * 1024 * sizeof(unsigned char);
    char* randomvalue = getRandomPlain(plainLength);
    string plainText = randomvalue;

    md5(plainText);
    sha256(plainText);
    ripemd160(plainText);
    return 0;
}