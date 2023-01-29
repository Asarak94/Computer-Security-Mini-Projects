using namespace std;

string generateKey(string str, string key)
{
	int x = str.size();

	for (int i = 0; ; i++)
	{
		if (x == i)
			i = 0;
		if (key.size() == str.size())
			break;
		key.push_back(key[i]);
	}
	cout << "key : " << key << "\n";
	return key;
}

string encrypt(string str, string key)
{
	string cipher_text;

	for (int i = 0; i < str.size(); i++)
	{
		int string_index= str[i]-'A';
		int key_index= key[i]-'A';
		int finalValue= string_index+key_index;

		if (finalValue == 26){
		char special_char ='_';
		cipher_text.push_back(special_char);
		}
		else
		{
		char x = finalValue %27;
		// convert into alphabets(ASCII)
		x += 'A';
		cipher_text.push_back(x);
		}
	}
	return cipher_text;
}

// Decryt the the cipher text and return the original message
string decrypt(string cipher_text, string key)
{
	string plaintext;

	for (int i = 0 ; i < cipher_text.size(); i++)
	{
		if(cipher_text[i] == '_'){
			    //define alphabet size from 0
				int alphabet_size= 26;
				int Key_index= key[i]-'A';
				int character_index= alphabet_size-Key_index;

		char x = character_index;
		// convert into alphabets(ASCII)
		x += 'A';
		plaintext.push_back(x);				
		}else{
		// converting in range 0-25
		char x = (cipher_text[i] - key[i] + 27) %27;

		// convert into alphabets(ASCII)
		x += 'A';
		plaintext.push_back(x);
	}
		}
	return plaintext;
}

// Main method 
int main()
{
	string plaintext = "Asara";
	string keyword = "NVCTFGS";

	// Create key according to the length of the plain text 
	string key = generateKey(plaintext, keyword);

	string cipher_text = encrypt(plaintext, key);
	string decrypted_text = decrypt(cipher_text, key);

	cout << "Ciphertext : "
		<< cipher_text << "\n";

	cout << "Original/Plain Text : "
		<< decrypted_text << "\n";
	return 0;
}
