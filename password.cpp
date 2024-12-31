#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <time.h>
#include <cmath>
#include <cstring>
#include <conio.h>
#include <map>
#include <direct.h>

using namespace std;

string customAlphabetCaesarEncode(const string &alphabet, int shift, const string &message)
{
    string result = "";
    for (char c : message)
    {
        if (isalpha(c))
        {
            char upperC = toupper(c);
            size_t pos = alphabet.find(upperC);
            if (pos != string::npos)
            {
                char newChar = alphabet[(pos + shift) % alphabet.length()];
                result += islower(c) ? tolower(newChar) : newChar;
            }
            else
            {
                result += c; 
            }
        }
        else
        {
            result += c; 
        }
    }
    return result;
}

string customAlphabetCaesarDecode(const string &alphabet, int shift, const string &message)
{
    string result = "";
    for (char c : message)
    {
        if (isalpha(c))
        {
            char upperC = toupper(c);
            size_t pos = alphabet.find(upperC);
            if (pos != string::npos)
            {
                char newChar = alphabet[(pos - shift + alphabet.length()) % alphabet.length()];
                result += islower(c) ? tolower(newChar) : newChar;
            }
            else
            {
                result += c; 
            }
        }
        else
        {
            result += c; 
        }
    }
    return result;
}

// VERNAM CIPHER
string vernamEncryption(string text, string key)
{
    string cipherText = "";
    int cipher[key.length()];

    for (int i = 0; i < key.length(); i++)
    {
        cipher[i] = text.at(i) - 'A' + key.at(i) - 'A';
    }
    for (int i = 0; i < key.length(); i++)
    {
        if (cipher[i] > 25)
        {
            cipher[i] = cipher[i] - 26;
        }
    }
    for (int i = 0; i < key.length(); i++)
    {
        int x = cipher[i] + 'A';
        cipherText += (char)x;
    }
    return cipherText;
}

static string vernamDecryption(string s, string key)
{
    string plainText = "";
    int plain[key.length()];

    for (int i = 0; i < key.length(); i++)
    {
        plain[i] = s.at(i) - 'A' - (key.at(i) - 'A');
    }
    for (int i = 0; i < key.length(); i++)
    {
        if (plain[i] < 0)
        {
            plain[i] = plain[i] + 26;
        }
    }

    for (int i = 0; i < key.length(); i++)
    {
        int x = plain[i] + 'A';
        plainText += (char)x;
    }

    return plainText;
}

vector<int> generateRandomKey(int length)
{
    vector<int> key1;
    srand(static_cast<unsigned int>(time(nullptr))); 

    for (int i = 0; i < length; ++i)
    {
        key1.push_back(rand() % 26); 
    }
    return key1;
}

string xorEncryption(const string &text, int key)
{
    string cipherText;
    for (size_t i = 0; i < text.length(); ++i)
    {
        cipherText += text[i] ^ key;
    }
    return cipherText;
}

string xorDecryption(const string &cipherText, int key)
{
    string decryptedText;
    for (size_t i = 0; i < cipherText.length(); ++i)
    {
        decryptedText += cipherText[i] ^ key;
    }
    return decryptedText;
}

// VIGENÈRE CIPHER

string generateKey(string str, string key)
{
    int x = str.size();

    for (int i = 0;; i++)
    {
        if (x == i)
            i = 0;
        if (key.size() == str.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}

string vigenereEncryption(string str, string key)
{
    string cipher_text;

    for (int i = 0; i < str.size(); i++)
    {
        char x = (str[i] + key[i]) % 26;
        x += 'A';
        cipher_text.push_back(x);
        key = generateKey(str, key);
    }
    return cipher_text;
}

string vigenereDecryption(string cipher_text, string key)
{
    string orig_text;

    for (int i = 0; i < cipher_text.size(); i++)
    {
        char x = ((cipher_text[i] - key[i] + 26) % 26 + 26) % 26 + 'A';
        orig_text.push_back(x);
        key = generateKey(cipher_text, key);
    }
    return orig_text;
}


string PasswordGenerator()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    string pass;
    string lower = "abcdefghijklmnopqrstuvwxyz";
    string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string num = "0123456789";
    string special = "`~@#$%^&*()-_=+\\|{};:',<>./?[]";
    string data = lower + upper + num + special;
    for (int i = 1; i <= 12; i++)
    {
        pass += data[rand() % data.size()];
    }
    cout << "Generated Password is: " << pass << endl;
    return pass;
}
bool isSpecialChar(char c)
{
    if (int(c) >= 32 && int(c) <= 47)
    {
        return true;
    }
    if (int(c) >= 58 && int(c) <= 64)
    {
        return true;
    }
    if (int(c) >= 91 && int(c) <= 96)
    {
        return true;
    }
    if (int(c) >= 123 && int(c) <= 126)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PasswordChecker()
{
    string password;
    short nums = 0, capAlphaCnt = 0, specialCharCnt = 0, passLength = 0;
    cout << "Enter your password: ";
    cin >> password;
    if (password.length() >= 8)
    {
        passLength = 1;
    }
    for (int i = 0; i < password.length(); i++)
    {
        if (isupper(password[i]))
        {
            capAlphaCnt++;
        }
        if (isSpecialChar(password[i]))
        {
            specialCharCnt++;
        }
        if (password[i] >= '0' && password[i] <= '9')
        {
            nums++;
        }
    }
    if (capAlphaCnt > 0 && specialCharCnt > 0 && nums > 0 && passLength)
    {
        cout << "STRONG PASSWORD!" << endl;
    }
    else
    {
        cout << "WEAK PASSWORD!" << endl;
    }
}

void estimateCrackTime(string password)
{
    int lowercase = 26;
    int uppercase = 26;
    int digits = 10;
    int specialChars = 32; 

    int passwordLength = password.length();
    int totalCharSetSize = lowercase + uppercase + digits + specialChars;
    
    unsigned long long totalCombinations = pow(totalCharSetSize, passwordLength);

    double guessesPerSecond = 100000000000.0;

    double timeInSeconds = totalCombinations / guessesPerSecond;

    double timeInMinutes = timeInSeconds / 60;
    double timeInHours = timeInMinutes / 60;
    double timeInDays = timeInHours / 24;
    double timeInYears = timeInDays / 365.25;

    cout << "Estimated Time to Crack Your Password: " << endl;
    cout << "Seconds: " << timeInSeconds << " seconds" << endl;
    cout << "Minutes: " << timeInMinutes << " minutes" << endl;
    cout << "Hours: " << timeInHours << " hours" << endl;
    cout << "Days: " << timeInDays << " days" << endl;
    cout << "Years: " << timeInYears << " years" << endl;
}
void getKeyMatrix(string key, vector<vector<int>> &keyMatrix, int n)
{
    int k = 0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}

void encrypt(vector<vector<int>> &cipherMatrix, 
             vector<vector<int>> &keyMatrix, 
             vector<vector<int>> &messageVector, int n)
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < 1; j++)
        {
            cipherMatrix[i][j] = 0;
            for (int x = 0; x < n; x++)
            {
                cipherMatrix[i][j] += keyMatrix[i][x] * messageVector[x][j];
            }
            cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
        }
    }
} 
//Hill Cipher
void HillCipher(string message, string key, int n)
{
    if (key.length() != n * n)
    {
        cout << "Error: Key length must be " << n * n << " characters long for an " << n << "x" << n << " matrix.\n";
        return;
    }

    if (message.length() % n != 0)
    {
        cout << "Error: Message length must be a multiple of " << n << ".\n";
        return;
    }

    vector<vector<int>> keyMatrix(n, vector<int>(n));
    getKeyMatrix(key, keyMatrix, n);

    cout << "\nKey Matrix (" << n << "x" << n << "):\n";
    for (auto row : keyMatrix)
    {
        for (auto val : row)
            cout << val << " ";
        cout << endl;
    }

    string CipherText;
    for (int b = 0; b < message.length(); b += n)
    {
        vector<vector<int>> messageVector(n, vector<int>(1));
        for (int i = 0; i < n; i++)
            messageVector[i][0] = (message[b + i]) % 65;

        vector<vector<int>> cipherMatrix(n, vector<int>(1));
        encrypt(cipherMatrix, keyMatrix, messageVector, n);

        for (int i = 0; i < n; i++)
            CipherText += cipherMatrix[i][0] + 65;
    }

    cout << "\nCiphertext: " << CipherText << endl;
}

void exit()
{
    {
        cout << " _______ Thank you for Your Time ___________\n";
        cout << " ";
        cout << " ";
        cout << "\n";
    }
}
long long gcd(long long a, long long b);
long long modular_exponentiation(long long base, long long exp, long long mod);
void generate_keys(long long &n, long long &e, long long &d);
long long encrypt(long long plaintext, long long e, long long n);
long long decrypt(long long ciphertext, long long d, long long n);

// GCD
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long modular_exponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1; 
        base = (base * base) % mod;
    }
    return result;
}


void generate_keys(long long &n, long long &e, long long &d) {
    long long p, q, phi;
    
    cout << "Enter two large prime numbers (p and q): ";
    cin >> p >> q;

    n = p * q;                 
    phi = (p - 1) * (q - 1);   

    e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) {
            break;
        }
        e++;
    }

    d = 1;
    while ((d * e) % phi != 1) {
        d++;
    }

    cout << "Public Key: (" << e << ", " << n << ")" << endl;
    cout << "Private Key: (" << d << ", " << n << ")" << endl;
}

long long encrypt(long long plaintext, long long e, long long n) {
    return modular_exponentiation(plaintext, e, n);
}

long long decrypt(long long ciphertext, long long d, long long n) {
    return modular_exponentiation(ciphertext, d, n);
}
int main()
{
    string plainText, ciphertext, decryptedText, keyword,pass;
    int key, n;

    string correctPassword = "PASSWORD123";
    int maxAttempts = 3;
    int attempts = 0;
    string enteredPassword = "";
    char ch;

    do
    {
        cout << "Enter the password: ";
        ch = getch();
        while (ch != 13)
        {
            if (ch == 8)
            {
                if (enteredPassword.length() > 0)
                {
                    cout << "\b \b";
                    enteredPassword.pop_back();
                }
            }
            else
            {
                enteredPassword += ch;
                cout << '*';
            }
            ch = getch();
        }

        cout << endl;

        if (enteredPassword == correctPassword)
        {
            cout << "Password correct. Access granted!" << endl;

            int n = 0;
            do
            {
                cout << "Enter Your Choice" << endl;
                cout << "1. Modified Caesar Cipher" << endl;
                cout << "2. XOR Cipher" << endl;
                cout << "3. Vigenere Cipher" << endl;
                cout << "4. Password Generator" << endl;
                cout << "5. Password Checker" << endl;
                cout << "6. Crack Time Estimator" << endl;
                cout << "7. Hill Cipher" << endl;
                cout << "8. RSA Algorithm" << endl;
                cout << "9. Exit" << endl;
                cout << "Enter Your Choice: ";
                cin >> n;

                switch (n)
                {
                case 1:
                    {
                        string alphabet = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
                        int key;
                        cout << "Enter integer key: ";
                        cin >> key;
                        pass = PasswordGenerator();
                        string encodedMessage = customAlphabetCaesarEncode(alphabet, key, pass);
                        cout << "Encoded message: " << encodedMessage << endl;
                        string decodedMessage = customAlphabetCaesarDecode(alphabet, key, encodedMessage);
                        cout << "Decoded message: " << decodedMessage << endl;
                        break;
                    }

                case 2:
                    {
                        int keyLength;

                        cout << "Enter the key length: ";
                        cin >> keyLength;
                        pass = PasswordGenerator();
                        ciphertext = xorEncryption(pass, keyLength);
                        cout << "Encrypted Text: " << ciphertext << endl;
                        decryptedText = xorDecryption(ciphertext, keyLength);
                        cout << "Decrypted Text: " << decryptedText << endl;
                        break;
                    }

                case 3:
                    {
                        cout << "Enter the string key: ";
                        cin >> keyword;
                        pass = PasswordGenerator();
                        ciphertext = vigenereEncryption(pass, keyword);
                        cout << "Encrypted Text is: " << ciphertext << endl;
                        decryptedText = vigenereDecryption(ciphertext, keyword);
                        cout << "The Message is: " << decryptedText << endl;
                        break;
                    }

                case 4:
                    PasswordGenerator();
                    cout << endl;
                    break;

                case 5:
                    PasswordChecker();
                    cout << "Tip : Add the combination of Special Character, Uppercase, and Numbers" << endl;
                    cout << endl;
                    break;

                case 6:
                    {
                        string password;
                        cout << "Enter the password to estimate cracking time: ";
                        cin >> password;
                        estimateCrackTime(password);
                        break;
                    }
                case 7:{
                	
                	int n;
                    string message, key;
    
                    cout << "Enter the size of the key matrix (n): ";
                    cin >> n;
                    cout << "Enter the message to be encrypted (must be a multiple of " << n << "): ";
                    cin.ignore(); 
                    getline(cin, message);

    
                for (auto &ch : message)
                    ch = toupper(ch);
                while (message.length() % n != 0)
                    message += 'X'; 

    
                cout << "Enter the key (must be " << n * n << " characters): ";
                cin >> key;
 
    
                for (auto &ch : key)
                   ch = toupper(ch);

    
                HillCipher(message, key, n);
                       cout<<endl;
					   break;
				}
                case 8:{
                	long long n, e, d;
    
                generate_keys(n, e, d);

    
                long long plaintext;
                cout << "Enter plaintext (as a number): ";
                cin >> plaintext;

    
                long long ciphertext = encrypt(plaintext, e, n);
                cout << "Encrypted Ciphertext: " << ciphertext << endl;

    
                long long decrypted = decrypt(ciphertext, d, n);
                cout << "Decrypted Plaintext: " << decrypted << endl;
					    break;
				}
                case 9:
                    exit();
                    break;

                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    break;
                }

                } while (n != 9);

                   break;
                }
                else
                {
                cout << "Incorrect password. Try again." << endl;
                attempts++;

            if (attempts >= maxAttempts)
            {
                cout << "Maximum attempts reached. Computer is going to sleep." << endl;
                system("C:\\Windows\\System32\\shutdown /r /t 0");
                break; 
            }
        }
    } while (true);
    return 0;
}