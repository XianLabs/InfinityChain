#include "Wallet.h"

Wallet::Wallet(string CoinName, string WalletName)
{
	if (CoinName.empty())
	{
		printf("Wallet creation needs currency name.\n");
		return;
	}

	if (WalletName.empty())
	{
		printf("Wallet creation needs a wallet name.\n");
		return;
	}

	this->CoinName = CoinName;
	this->WalletName = WalletName;
}

string Wallet::GeneratePrivateKey()
{


}

string Wallet::GenerateWalletAddress()
{
	return sha256(this->WalletName);

}