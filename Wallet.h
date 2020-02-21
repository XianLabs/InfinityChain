#ifndef WALLET_H
#define WALLET_H
#include <Windows.h>
#include <string>
#include "sha256.h"

using namespace std;

class Wallet
{
private:
	string CoinName;
	double Balance;


	string PubKey;
	string PrivKey;

	string WalletName;

public:

	Wallet(string CoinName, string WalletName);

	string GetPublicKey() { return this->PubKey; };
	double GetBalance() { return this->Balance; };
	string GeneratePrivateKey(); //add seed or something
	string GenerateWalletAddress();
};


#endif