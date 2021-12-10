#pragma once
#include <iostream>
#include <cmath>
using namespace std;

bool prime(long long pr){
    for (int i = 2; i <= sqrt(pr); i++){
        if (pr % i == 0)
            return false;
    }
    return true;
}

long long gcd(long long a, long long b){ // Euclid's algorithm
    return b!=0 ? gcd(b, a%b) : a;
}

long long privateKeyGeneration(long long &m, long long &e){
    double k=1;
    while (true){
        double d=(k*m+1)/e;
        if (d == int(d)){
            return d;
        }
        k++;
    }
}

long long publicKeyGeneration(long long &n, long long &m){
    for(int e=3; e<n; ++e){
        if (gcd(e, m)==1){
            return e;
        }
    }
    exit('1');
}

void encrypt(long long &e, long long &n, string &message){
    string encrypted;
    for (int i=0; i<message.size(); ++i) {
        unsigned char temp1 = message[i];
        long long symbol = temp1, multipl = temp1;
        for (int i=0; i<e-1; ++i){
            symbol *= multipl;
            symbol %= n;
        }
        temp1 = symbol;
        encrypted.push_back(temp1);
    }
    cout << "\nThe encrypted message is:\n";
    cout << encrypted;
    message=encrypted;
}

void decrypt(long long &d, long long &n, string &encryptedMessage){
    string decrypted;
    for (int i=0; i<encryptedMessage.size(); ++i){
        unsigned char temp1 = encryptedMessage[i];
        long long symbol = temp1, multipl = temp1;
        for (int j = 0; j < d-1; ++j) {
            symbol *= multipl;
            symbol %= n;
        }
        temp1 = symbol;
        decrypted.push_back(temp1);
    }
    cout << "\nThe decrypted message is:\n";
    cout << decrypted;
}

void rsa(){
    cout << "\nEnter prime number\n";
    long long p, q;
    cin >> p;
    bool flag = prime(p);
    if (!flag){
        cout << "\nWrong input\n";
        exit(1);
    }
    cout << "\nEnter another prime number\n";
    cin >> q;
    flag = prime(q);
    if (!flag || p == q)
    {
        cout << "\nWrong input\n";
        exit(1);
    }
    cout << "\nEnter message\n";
    string message;
    cin >> message;
    long long n = p * q;
    long long m = (p - 1) * (q - 1); // Euler function
    long long e = publicKeyGeneration(n, m);
    long long d = privateKeyGeneration(m, e);
    cout << "Private key(d): " << d << " Public key(e):" << e << " n:" <<  n;
    encrypt(e, n, message);
    decrypt(d, n, message);
}