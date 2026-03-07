#include <iostream>
using namespace std;

int main() {

    string buah[5] = {"Apel", "Jeruk", "Mangga", "Pisang", "Rambutan"};

    for (string x : buah) {
        cout << x << endl;
    }   

    int panjang = sizeof(buah) / sizeof(buah[0]);
    cout << "Panjang array buah: " << panjang << endl;


    int nilai[2][2][2] = {
    { {80, 85}, {75, 90} }, 
    { {88, 92}, {70, 78} }
    };
        cout << " = DATA NILAI MAHASISWA =\n\n";
    for (int k = 0; k < 2; k++) {
        cout << "Kelas " << char('A' + k) << endl;
    for (int m = 0; m < 2; m++) {
        cout << " Mahasiswa " << m + 1 << endl;
        cout << " UTS : " << nilai[k][m][0] << endl;
        cout << " UAS : " << nilai[k][m][1] << endl;
    }
        cout << endl;
    }

    typedef struct {
        string nama;
        int umur;
    } Mahasiswa;

    Mahasiswa mhs1;
    mhs1.nama = "Budi";
    mhs1.umur = 20;
    cout << "Nama Mahasiswa: " << mhs1.nama << endl;
    cout << "Umur Mahasiswa: " << mhs1.umur << " tahun" << endl;

    return 0;
}