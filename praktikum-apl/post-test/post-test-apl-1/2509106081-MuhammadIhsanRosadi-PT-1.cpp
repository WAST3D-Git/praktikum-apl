#include <iostream>
using namespace std;

int main() {
    int percobaanLogin = 0;
    string username, password;

    while (percobaanLogin < 3) {

        system("cls||clear");
        cout << "======================\n";
        cout << "        LOGIN         \n";
        cout << "======================\n";
        cout << "Masukkan Username: "; cin >> username;
        cout << "Masukkan Password: "; cin >> password;

        if (username == "Rosadi" && password == "081") {
            cout << "\nLogin berhasil! Selamat datang, " << username << "!\n";
            system("pause");
            break;
        } else {
            percobaanLogin++;

            if (percobaanLogin == 3) {
                cout << "\nLogin gagal.\n";
                cout << "Anda telah mencapai batas percobaan login. Program dihentikan.";
                return 0;
            }

            cout << "\nLogin gagal! (Batas percobaan login 3x).\n";
            system("pause");
        }
    }

    int pilihan;
    double nilai;

    do {

        system("cls||clear");
        cout << "======================================\n";
        cout << "       PROGRAM KONVERSI PANJANG       \n";
        cout << "======================================\n";
        cout << "1. Meter -> Kilometer & Centimeter\n";
        cout << "2. Kilometer -> Meter & Centimeter\n";
        cout << "3. Centimeter -> Meter & Kilometer\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu (1-4): "; cin >> pilihan;

        system("cls||clear");

        switch (pilihan) {
            case 1:
                cout << "Masukkan panjang dalam meter: "; cin >> nilai;
                cout << "\n----- Hasil Konversi -----\n";
                cout << nilai << " meter = " << nilai / 1000 << " kilometer\n";
                cout << nilai << " meter = " << nilai * 100 << " centimeter\n";
                system("pause");
                break;

            case 2:
                cout << "Masukkan panjang dalam kilometer: "; cin >> nilai;
                cout << "\n----- Hasil Konversi -----\n";
                cout << nilai << " kilometer = " << nilai * 1000 << " meter\n";
                cout << nilai << " kilometer = " << nilai * 100000 << " centimeter\n";
                system("pause");
                break;

            case 3:
                cout << "Masukkan panjang dalam centimeter: "; cin >> nilai;
                cout << "\n----- Hasil Konversi -----\n";
                cout << nilai << " centimeter = " << nilai / 100 << " meter\n";
                cout << nilai << " centimeter = " << nilai / 100000 << " kilometer\n";
                system("pause");
                break;

            case 4:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;

            default:
                cout << "Pilihan tidak valid. Silakan pilih menu antara 1-4.\n";
                system("pause");
        }

    } while (pilihan != 4);

    return 0;
}