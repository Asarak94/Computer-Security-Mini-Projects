// g++ rsa.cpp -o rsa -lcryptopp
#include <iostream>

#include "../crypto_package/rsa.h"
#include "../crypto_package/integer.h"
#include "../crypto_package/osrng.h"
#include <Windows.h>

int main() {
	
	AutoSeededRandomPool rnd;
	RSA::PrivateKey rsaPrivate;

	//Assign n value, number of bits
	const int bits = 768;
	rsaPrivate.GenerateRandomWithKeySize(rnd, bits);

	// Assign e value as publicKey
	const int publicKey = 65537;

	//Covert e value in to Hex format
	std::ostringstream ss;
	ss << "0x" << std::hex << publicKey;
	std::string publicKeyHex = ss.str();

	// Assign Keys-> n,e,d
	CryptoPP::Integer n(rsaPrivate.GetModulus()), e(publicKeyHex), d(rsaPrivate.GetPrivateExponent());
	std::cout << "n: " << n << std::endl;

	CryptoPP::RSA::PrivateKey privKey;
	privKey.Initialize(n, e, d);

	CryptoPP::RSA::PublicKey pubKey;
	pubKey.Initialize(n, e);

	//Define timer 
	clock_t startTime1, startTime2, finishTime1, finishTime2;

	// Assign Plain Text
	std::string message = "asara";
	CryptoPP::Integer m((const byte*)message.data(), message.size());
	std::cout << "m: " << m << std::endl;

	// RSA Encryption
	startTime1 = clock();
	CryptoPP::Integer c = pubKey.ApplyFunction(m);
	finishTime1 = clock();
	std::cout << "c: " << std::hex << c << std::endl;

	// Calculate Throughput
	double timeTakenEncryption = double(finishTime1 - startTime1) / (double)CLOCKS_PER_SEC;
	std::cout << "timeTaken for Encryption: " << timeTakenEncryption << std::endl;
	double ThroughputEncryption = ((double)message.size() / 1048576) / timeTakenEncryption;
	std::cout << "Encryption Throughput: " << ThroughputEncryption << std::endl;

	// RSA Decryption
	startTime2 = clock();
	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::Integer r = privKey.CalculateInverse(prng, c);
	finishTime2 = clock();
	std::cout << "r: " << std::hex << r << std::endl;

	// Calculate Throughput
	double timeTakenDecryption = double(finishTime2 - startTime2) / (double)CLOCKS_PER_SEC;
	std::cout << "timeTaken for Decryption: " << timeTakenDecryption << std::endl;
	double ThroughputDecryption = ((double)message.size() / 1048576) / timeTakenDecryption;
	std::cout << "Decryption Throughput: " << ThroughputDecryption << std::endl;

	// Recover PlainText
	std::string recovered;
	recovered.resize(r.MinEncodedSize());

	r.Encode((byte*)recovered.data(), recovered.size());
	std::cout << "recovered plain text: " << recovered << std::endl;

	return 0;
}