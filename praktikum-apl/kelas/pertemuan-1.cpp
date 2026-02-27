#include <iostream> 
using namespace std;

int main() {


    cout << "Hello, World!" << endl;

    cout << "Size of int: " << sizeof(int) << " bytes" << endl;

    struct mahasiswa
    {
        string nama;
        int umur;
    };

    mahasiswa mahasiswa;
    cout << "Nama: " << mahasiswa.nama << ", Umur: " << mahasiswa.umur << endl;
    getline(cin, mahasiswa.nama);
    cin >> mahasiswa.umur;
    cout << "Nama: " << mahasiswa.nama << ", Umur: " << mahasiswa.umur << endl;


    switch (mahasiswa.umur)
    {
    case 18:
        cout << "Mahasiswa berusia 18 tahun." << endl;
        break;
    
    default:
        break;
    }

    string array[5] = {"satu", "dua", "tiga", "empat", "lima"};

    for(string i : array) {
        cout << i << endl;
    }

    int i = 0;
    do {
        cout << array[i] << endl;
        i++;
    } while (i < 5);

    
    return 0;
}