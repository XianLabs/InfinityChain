#include "Blockchain.h"
#include "NodeConnector.h"
#include "NodeServer.h"

bool NodeConnect(string hostAddr, unsigned short nPort)
{
	NodeConnector* n = new NodeConnector(hostAddr.c_str(), 7777);
	if (n == NULL)
	{
		printf("Failed to construct Node Connector: %d.\n", GetLastError());
		return false;
	}

	return true;
}

bool StartServer(unsigned short nPort)
{
	NodeServer* NS = new NodeServer(7777);
	NS->Listen();


	return true;
}

void MainMenu()
{
	cout << "========================================\n";
	cout << "=                                      =\n";
	cout << "=           INFINITY CHAIN             =\n";
	cout << "=                                      =\n";
	cout << "========================================\n";

	cout << "Select one of the following:\n";
	cout << "1. Begin mining new blocks\n";
	cout << "2. Join mining network and mine blocks\n";
	cout << "3. Join network\n";
	cout << "4. Check wallet balance\n";
	cout << "5. Send IXF to wallet\n";

	int option;

	cin >> option;
	Blockchain bChain = Blockchain();

	switch (option)
	{
		case 1:

			for (int i = 1; i <= 1; i++)
			{
				cout << "Mining block " << i << endl;
				bChain.AddBlock(Block(i, "SENSITIVE INFO!"));
			}

			break;

		case 2:
			NodeConnect("127.0.0.1", 7777);

			break;

		case 3:

			StartServer(7777);

			break;

		case 4:

			break;
		case 5:

			break;

		default:
			cout << "Invalid selection.\n";
			break;
	}
}

int main()
{
	MainMenu();
	system("pause");
	return 0;
}
