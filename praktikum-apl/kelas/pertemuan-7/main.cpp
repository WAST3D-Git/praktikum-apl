#include <iostream>
    using namespace std;
    int main() {
    try {
        cout << "Masukkan bilangan positif: ";
        int angka;
        cin >> angka;
        if (cin.fail()) {
            throw invalid_argument("Input harus berupa angka!");
        }
        if (angka < 0) {
            throw runtime_error("Bilangan harus bernilai positif!");
        }
        cout << "Anda memasukkan: " << angka << endl;

        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
     }
    cout << "Program selesai." << endl;
    return 0;
}