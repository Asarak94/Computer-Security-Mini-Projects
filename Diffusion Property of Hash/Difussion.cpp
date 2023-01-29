#include "../crypto_package/cryptlib.h"
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "../crypto_package/md5.h"
#include "../crypto_package/hex.h"
#include "../crypto_package/files.h"
#include "../crypto_package/sha.h"
#include "../crypto_package/ripemd.h"
#include <iostream>
using namespace CryptoPP;
using namespace std;
#include <cstddef>
#include <cstring>
#include <algorithm>
#include <map>

string md5(string plainText) {

    string hashValue;
    HexEncoder encoder(new StringSink(hashValue));
    string messageDigest;

    Weak::MD5 hash;
    //Adding Data
    hash.Update((const byte*)&plainText[0], plainText.size());
    messageDigest.resize(hash.DigestSize());

    //Calculate the hash
    hash.Final((byte*)&messageDigest[0]);

    StringSource ss (messageDigest, true, new Redirector(encoder));
    cout << "MD5 Hash Value: " << hashValue << endl;
    return hashValue;

}

string sha256(string plainText) {
    
    string hashValue;
    HexEncoder encoder(new StringSink(hashValue));
    string messageDigest;

    SHA256 hash;
    hash.Update((const byte*)plainText.data(), plainText.size());
    messageDigest.resize(hash.DigestSize());
    hash.Final((byte*)&messageDigest[0]);

    StringSource ss(messageDigest, true, new Redirector(encoder));
    cout << "SHA256 Hash Value: " << hashValue << endl;
    return hashValue;
}

string ripemd160(string plainText) {

    string hashValue;
    HexEncoder encoder(new StringSink(hashValue));
    string messageDigest;
    //Define timer 

    RIPEMD160 hash;
    hash.Update((const byte*)plainText.data(), plainText.size());
    messageDigest.resize(hash.DigestSize());
    hash.Final((byte*)&messageDigest[0]);

    StringSource ss(messageDigest, true, new Redirector(encoder));
    cout << "RIPEMD160 Hash Value: " << hashValue << endl;
    return hashValue;
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

void compareHash(string hash1,string hash2) {

    int length = hash1.length();

    // Declare map to store the location and it's value
    map<int, char> m;

    string* location = new string[length];

    for (int i = 0; i < length;i++) {
        if (hash1.at(i) != hash2.at(i)) {
            m.insert(pair<int, char>(i, hash2.at(i)));
        }
    }

    // Print the elements stored
    // in the map
    for (auto itr = m.begin();
        itr != m.end(); ++itr) {
        cout <<"changed location :-"<< itr->first << '\t'
            <<"changed value :-"<< itr->second << '\n';
    }

}

int main(int argc, char* argv[])
{

    //Generate a random 1KB string
    int plainLength = 1024* sizeof(unsigned char);
    char* randomvalue = getRandomPlain(plainLength);
    string plainText = randomvalue;

    //Generate Hash values for MD5
    cout << "Generating Hash Values MD5: ";
    cout << endl;
    string hash1=md5(plainText);
    cout << endl;
    cout << "After changing 1st bit: ";
    cout << endl;
    //change first bit by value 'X'
    plainText[0] = 'X';
    string hash2 = md5(plainText);
    compareHash(hash1, hash2); 
    cout << endl;
    cout << endl;

    cout << "After changing last bit: ";
    cout << endl;
    plainText[plainText.length()-1] = 'X';
    string hash3 = md5(plainText);
    compareHash(hash1, hash3);
    cout << endl;
    cout << endl;

    cout << "After changing random bit: ";
    cout << endl;
    plainText[3] = 'X';
    string hash4 = md5(plainText);
    compareHash(hash1, hash4);
    cout << endl;
    cout << endl;

    //Generate Hash values for SHA256
    cout << "Generating Hash Values SHA256: ";
    cout << endl;
    string hash5 = sha256(plainText);

    cout << "After changing 1st bit: ";
    cout << endl;
    //change first bit by value 'X'
    plainText[0] = 'X';
    string hash6 = sha256(plainText);
    compareHash(hash5, hash6);
    cout << endl;
    cout << endl;

    cout << "After changing last bit: ";
    cout << endl;
    plainText[plainText.length() - 1] = 'X';
    string hash7 = sha256(plainText);
    compareHash(hash5, hash7);
    cout << endl;
    cout << endl;

    cout << "After changing random bit: ";
    cout << endl;
    plainText[3] = 'X';
    string hash8 = sha256(plainText);
    compareHash(hash5, hash8);
    cout << endl;
    cout << endl;

    //Generate Hash values for RIPEMD160
    cout << "Generating Hash Values RIPEMD160 : ";
    cout << endl;
    string hash9 = ripemd160(plainText);

    cout << "After changing 1st bit: ";
    cout << endl;
    //change first bit by value 'X'
    plainText[0] = 'X';
    string hash10 = ripemd160(plainText);
    compareHash(hash9, hash10);
    cout << endl;
    cout << endl;

    cout << "After changing last bit: ";
    cout << endl;
    plainText[plainText.length() - 1] = 'X';
    string hash11 = ripemd160(plainText);
    compareHash(hash9, hash11);
    cout << endl;
    cout << endl;

    cout << "After changing random bit: ";
    cout << endl;
    plainText[3] = 'X';
    string hash12 = ripemd160(plainText);
    compareHash(hash9, hash12);
    cout << endl;
    cout << endl;

    return 0;
}