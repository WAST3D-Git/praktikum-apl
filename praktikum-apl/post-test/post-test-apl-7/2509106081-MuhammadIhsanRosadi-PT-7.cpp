#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <stdexcept>
#include "color_utils.h"

using namespace std;

const int MAX_USER = 50;
const int MAX_PROJECT = 100;
const int MAX_KOMENTAR = 25;

struct Project {
    int id;
    string judul;

    struct Detail {
        string deskripsi, software, deadline, klien, status;
    } detail;

    string komentar[MAX_KOMENTAR];
    int jumlahKomentar = 0;
};

struct User {
    string nama;
    string nim;
    string role;
};

void tampilkanHeader(string judul) {
    system("cls||clear");

    if (judul != "") {
        setColor(YELLOW);
        cout << judul << endl;
        resetColor();
    } else {
        cout << "===========================================\n";
        setColor(CYAN);
        cout << "   SISTEM MANAJEMEN PROYEK DESAIN GRAFIS   \n";
        resetColor();
        cout << "===========================================\n";
    }
}

int partitionJudul(Project* projects, int low, int high) {
    int mid = low + (high - low) / 2;
    string pivot = projects[mid].judul;

    swap(projects[mid], projects[high]);

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (projects[j].judul <= pivot) {
            i++;
            swap(projects[i], projects[j]);
        }
    }
    swap(projects[i + 1], projects[high]);
    return i + 1;
}

void quickSortJudul(Project* projects, int low, int high) {
    if (low < high) {
        int pi = partitionJudul(projects, low, high);
        quickSortJudul(projects, low, pi - 1);
        quickSortJudul(projects, pi + 1, high);
    }
}

int linearSearchByID(Project* projects, int n, int targetID, int* indexDitemukan) {
    for (int i = 0; i < n; i++) {
        if ((projects + i) -> id == targetID) {
            *indexDitemukan = i;
            setColor(GREEN);
            cout << "\nProyek dengan ID " << targetID << " ditemukan!\n";
            resetColor();
            return 1;
        }
    }
    return 0;
}

int binarySearchByJudul(Project* projects, int n, string targetJudul, int* indexDitemukan) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if ((projects + mid) -> judul == targetJudul) {
            *indexDitemukan = mid;
            setColor(GREEN);
            cout << "\nProyek dengan judul \"" << targetJudul << "\" ditemukan!\n";
            resetColor();
            return 1;
        }

        if ((projects + mid) -> judul < targetJudul) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0;
}

void tampilkanDetailProyek(Project* project) {
    cout << "\n=== DETAIL PROYEK ===\n";
    setColor(CYAN);
    cout << "ID        : ";
    resetColor();
    cout << project -> id << endl;
    
    setColor(CYAN);
    cout << "Judul     : ";
    resetColor();
    cout << project -> judul << endl;
    
    setColor(CYAN);
    cout << "Deskripsi : ";
    resetColor();
    cout << project -> detail.deskripsi << endl;
    
    setColor(CYAN);
    cout << "Software  : ";
    resetColor();
    cout << project -> detail.software << endl;
    
    setColor(CYAN);
    cout << "Deadline  : ";
    resetColor();
    cout << project -> detail.deadline << endl;
    
    setColor(CYAN);
    cout << "Klien     : ";
    resetColor();
    cout << project -> detail.klien << endl;
    
    setColor(CYAN);
    cout << "Status    : ";
    resetColor();
    if (project -> detail.status == "Selesai") {
        setColor(GREEN);
        cout << project -> detail.status;
        resetColor();
    } else if (project -> detail.status == "Proses") {
        setColor(YELLOW);
        cout << project -> detail.status;
        resetColor();
    } else if (project -> detail.status == "Ditunda") {
        setColor(RED);
        cout << project -> detail.status;
        resetColor();
    } else {
        cout << project -> detail.status;
    }
    cout << endl;
    
    setColor(CYAN);
    cout << "Komentar  : ";
    resetColor();
    if (project -> jumlahKomentar == 0) {
        cout << "-";
    } else {
        for (int j = 0; j < project -> jumlahKomentar; j++) {
            cout << "\n  ";
            setColor(GREEN);
            cout << "- ";
            resetColor();
            cout << project -> komentar[j];
        }
    }
    cout << endl;
}

void cariProyek(Project* projects, int jumlahProject) {
    tampilkanHeader("=== CARI PROYEK ===");

    try {
        if (jumlahProject == 0) {
            throw runtime_error("Belum ada proyek yang tersedia.");
        }

        int pilihanMetode;
        cout << "\nPILIH METODE PENCARIAN:\n";
        cout << "1. Pencarian berdasarkan ID (Linear Search)\n";
        cout << "2. Pencarian berdasarkan Judul (Binary Search)\n";
        cout << "Pilih (1/2): "; cin >> pilihanMetode;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilihanMetode == 1) {
            int targetID;
            cout << "\nMasukkan ID Proyek: "; cin >> targetID;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            int indexDitemukan;
            if (linearSearchByID(projects, jumlahProject, targetID, &indexDitemukan)) {
                tampilkanDetailProyek(projects + indexDitemukan);
            } else {
                cout << "\nProyek dengan ID " << targetID << " tidak ditemukan!\n";
            }
        } 
        else if (pilihanMetode == 2) {
            Project* tempProjects = new Project[jumlahProject];
            for (int i = 0; i < jumlahProject; i++) {
                tempProjects[i] = projects[i];
            }

            quickSortJudul(tempProjects, 0, jumlahProject - 1);

            string targetJudul;
            cout << "\nMasukkan Judul Proyek: "; getline(cin, targetJudul);

            int indexDitemukan;
            if (binarySearchByJudul(tempProjects, jumlahProject, targetJudul, &indexDitemukan)) {
                tampilkanDetailProyek(&tempProjects[indexDitemukan]);
            } else {
                cout << "\nProyek dengan judul \"" << targetJudul << "\" tidak ditemukan!\n";
            }

            delete[] tempProjects;
        } 
        else {
            cout << "\nPilihan tidak valid!\n";
        }

    } catch (const runtime_error& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
    }

    system("pause");
}

void insertionSortID(Project* projects, int n) {
    for (int i = 1; i < n; i++) {
        Project key = projects[i];
        int j = i - 1;

        while (j >= 0 && projects[j].id < key.id) {
            projects[j + 1] = projects[j];
            j--;
        }
        projects[j + 1] = key;
    }
}

void mergeStatus(Project* projects, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Project* L = new Project[n1];
    Project* R = new Project[n2];

    for (int i = 0; i < n1; i++)
        L[i] = projects[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = projects[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].detail.status <= R[j].detail.status) {
            projects[k] = L[i];
            i++;
        } else {
            projects[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        projects[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        projects[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSortStatus(Project* projects, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortStatus(projects, left, mid);
        mergeSortStatus(projects, mid + 1, right);
        mergeStatus(projects, left, mid, right);
    }
}

void tampilkanProyek(Project* projects, int jumlahProject) {
    system("cls||clear");

    try {
        if (jumlahProject == 0) {
            throw runtime_error("Belum ada proyek");
        }

        cout << left << setw(5) << "ID"
             << setw(20) << "Judul"
             << setw(25) << "Deskripsi"
             << setw(15) << "Software"
             << setw(15) << "Deadline"
             << setw(15) << "Klien"
             << setw(12) << "Status"
             << setw(40) << "Komentar" << endl;

        cout << string(152, '=') << endl;

        for (int i = 0; i < jumlahProject; i++) {
            string semuaKomentar;

            if ((projects + i)->jumlahKomentar == 0)
                semuaKomentar = "-";
            else {
                for (int k = 0; k < (projects + i)->jumlahKomentar; k++) {
                    if (k > 0) semuaKomentar += "; ";
                    semuaKomentar += to_string(k + 1) + ". " + (projects + i)->komentar[k];
                }
            }

            cout << left << setw(5) << (projects + i)->id
                 << setw(20) << (projects + i)->judul
                 << setw(25) << (projects + i)->detail.deskripsi
                 << setw(15) << (projects + i)->detail.software
                 << setw(15) << (projects + i)->detail.deadline
                 << setw(15) << (projects + i)->detail.klien
                 << setw(12) << (projects + i)->detail.status
                 << setw(40) << semuaKomentar << endl;
        }

    } catch (const runtime_error& e) {
        setColor(RED);
        cout << "Error: " << e.what() << endl;
        resetColor();
    }
}

void tampilkanProyekDenganSorting(Project* projects, int jumlahProject) {
    try {
        if (jumlahProject == 0) {
            throw runtime_error("Belum ada proyek");
        }

        Project tempProjects[MAX_PROJECT];
        for (int i = 0; i < jumlahProject; i++) {
            tempProjects[i] = projects[i];
        }

        int pilihanSorting;
        do {
            tampilkanProyek(tempProjects, jumlahProject);

            cout << endl;
            cout << "PILIH METODE SORTING:\n";
            cout << "1. Sorting Judul (Ascending)\n";
            cout << "2. Sorting ID (Descending)\n";
            cout << "3. Sorting Status (Ascending)\n";
            cout << "4. Kembali\n";
            cout << "Pilih: "; cin >> pilihanSorting;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (pilihanSorting) {
                case 1:
                    quickSortJudul(tempProjects, 0, jumlahProject - 1);
                    cout << "\nData telah diurutkan berdasarkan Judul menggunakan Quick Sort!\n";
                    system("pause");
                    break;
                case 2:
                    insertionSortID(tempProjects, jumlahProject);
                    cout << "\nData telah diurutkan berdasarkan ID menggunakan Insertion Sort!\n";
                    system("pause");
                    break;
                case 3:
                    mergeSortStatus(tempProjects, 0, jumlahProject - 1);
                    cout << "\nData telah diurutkan berdasarkan Status menggunakan Merge Sort!\n";
                    system("pause");
                    break;
                case 4:
                    cout << "Kembali ke menu utama...\n";
                    break;
                default:
                    system("cls||clear");
                    cout << "Pilihan tidak valid!\n";
                    system("pause");
            }
        } while (pilihanSorting != 4);

    } catch (const runtime_error& e) {
        system("cls||clear");
        setColor(RED);
        cout << "Error: " << e.what() << endl;
        resetColor();
        system("pause");
    }
}

int registrasiUser(User* users, int jumlahUser) {
    tampilkanHeader("=== REGISTRASI ===");

    try {
        if (jumlahUser >= MAX_USER) {
            throw runtime_error("User sudah mencapai batas maksimum!");
        }

        string nama, nim;

        cout << "Username : "; getline(cin, nama);
        cout << "Password : "; getline(cin, nim);

        if (nama.empty() || nim.empty()) {
            throw invalid_argument("Username dan password wajib diisi!");
        }

        for (int i = 0; i < jumlahUser; i++) {
            if ((users + i) -> nama == nama) {
                throw runtime_error("Username sudah digunakan!");
            }
        }

        (users + jumlahUser) -> nama = nama;
        (users + jumlahUser) -> nim = nim;
        (users + jumlahUser) -> role = "user";
        setColor(GREEN);
        cout << "\nRegistrasi berhasil\n";
        resetColor();
        system("pause");
        return jumlahUser + 1;

    } catch (const invalid_argument& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
        system("pause");
        return jumlahUser;
    } catch (const runtime_error& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
        system("pause");
        return jumlahUser;
    }
}

int login(User* users, int jumlahUser) {
    int percobaanLogin = 0;
    string username, password;

    while (percobaanLogin < 3) {
        system("cls||clear");
        tampilkanHeader("======= LOGIN =======");
        cout << "Username : "; getline(cin, username);
        cout << "Password : "; getline(cin, password);

        for (int i = 0; i < jumlahUser; i++) {
            if ((users + i) -> nama == username && (users + i) -> nim == password) {
                setColor(GREEN);
                cout << "\nLogin berhasil! Selamat datang, " << username << "!\n";
                resetColor();
                system("pause");
                return i;
            }
        }

        percobaanLogin++;
        if (percobaanLogin == 3) {
            setColor(RED);
            cout << "\nLogin gagal.\n";
            cout << "Anda telah mencapai batas percobaan login. Program dihentikan.";
            resetColor();
            return -2;
        }

        setColor(RED);
        cout << "\nLogin gagal! (Batas percobaan login 3x).\n";
        resetColor();
        setColor(YELLOW);
        cout << "Percobaan login ke-" << percobaanLogin << ", Silahkan coba lagi.\n";
        resetColor();
        system("pause");
    }
    return -1;
}

int tambahProyek(Project* projects, int jumlahProject) {
    tampilkanHeader("=== TAMBAH PROYEK ===");

    try {
        if (jumlahProject >= MAX_PROJECT) {
            throw runtime_error("Proyek sudah mencapai batas maksimum!");
        }

        int id;
        string judul, deskripsi, software, deadline, klien, status;

        cout << "ID Proyek : "; cin >> id;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (id <= 0) {
            throw invalid_argument("ID harus positif!");
        }

        cout << "Judul : "; getline(cin, judul);
        cout << "Deskripsi : "; getline(cin, deskripsi);
        cout << "Software : "; getline(cin, software);
        cout << "Deadline : "; getline(cin, deadline);
        cout << "Klien : "; getline(cin, klien);
        cout << "Status : "; getline(cin, status);

        if (judul.empty() || klien.empty()) {
            throw invalid_argument("Judul dan klien wajib diisi!");
        }

        Project* newProject = projects + jumlahProject;

        newProject -> id = id;
        newProject -> judul = judul;
        newProject -> detail.deskripsi = deskripsi;
        newProject -> detail.software = software;
        newProject -> detail.deadline = deadline;
        newProject -> detail.klien = klien;
        newProject -> detail.status = status;

        setColor(GREEN);
        cout << "\nProyek berhasil ditambahkan.\n";
        resetColor();
        system("pause");
        return jumlahProject + 1;

    } catch (const invalid_argument& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
        system("pause");
        return jumlahProject;
    } catch (const runtime_error& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
        system("pause");
        return jumlahProject;
    }
}

void updateProyek(Project* projects, int jumlahProject) {
    tampilkanHeader("=== UPDATE PROYEK ===");

    try {
        if (jumlahProject == 0) {
            throw runtime_error("Belum ada proyek!");
        }

        for (int i = 0; i < jumlahProject; i++) {
            cout << i + 1 << ". " << (projects + i) -> judul << " - "
                 << (projects + i) -> detail.status << endl;
        }

        int nomor;
        cout << "\nNomor proyek yang akan diupdate: ";
        cin >> nomor;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (nomor <= 0 || nomor > jumlahProject) {
            throw out_of_range("Nomor proyek tidak valid!");
        }

        Project* ptrProyek = projects + (nomor - 1);

        cout << "\nData lama:\n";
        cout << "ID: " << ptrProyek -> id << endl;
        cout << "Judul: " << ptrProyek -> judul << endl;
        cout << "Deskripsi: " << ptrProyek -> detail.deskripsi << endl;
        cout << "Software: " << ptrProyek -> detail.software << endl;
        cout << "Deadline: " << ptrProyek -> detail.deadline << endl;
        cout << "Klien: " << ptrProyek -> detail.klien << endl;
        cout << "Status: " << ptrProyek -> detail.status << endl;

        cout << "\nMasukkan data baru (kosongkan jika tidak ingin mengubah):\n";

        string input;
        int idInput;

        cout << "ID baru: "; cin >> idInput;
        if (idInput > 0)
            ptrProyek -> id = idInput;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Judul baru: "; getline(cin, input);
        if (!input.empty())
            ptrProyek -> judul = input;

        cout << "Deskripsi baru: "; getline(cin, input);
        if (!input.empty())
            ptrProyek -> detail.deskripsi = input;

        cout << "Software baru: "; getline(cin, input);
        if (!input.empty())
            ptrProyek -> detail.software = input;

        cout << "Deadline baru: "; getline(cin, input);
        if (!input.empty())
            ptrProyek -> detail.deadline = input;

        cout << "Klien baru: "; getline(cin, input);
        if (!input.empty())
            ptrProyek -> detail.klien = input;

        cout << "Status baru: "; getline(cin, input);
        if (!input.empty())
            ptrProyek -> detail.status = input;

        setColor(GREEN);
        cout << "\nUpdate berhasil!\n";
        resetColor();

    } catch (const out_of_range& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
    } catch (const runtime_error& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
    }
    system("pause");
}

int hapusProyek(Project* projects, int jumlahProject) {
    tampilkanHeader("=== HAPUS PROYEK ===");

    try {
        if (jumlahProject == 0) {
            throw runtime_error("Tidak ada proyek untuk dihapus!");
        }

        for (int i = 0; i < jumlahProject; i++) {
            cout << i + 1 << ". " << (projects + i) -> judul << " - "
                << (projects + i) -> detail.klien << endl;
        }

        int nomor;
        cout << "\nNomor proyek yang akan dihapus: ";
        cin >> nomor;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (nomor <= 0 || nomor > jumlahProject) {
            throw out_of_range("Nomor proyek tidak valid!");
        }

        int idx = nomor - 1;
        char konfirmasi;
        cout << "\nYakin ingin menghapus? (y/n): "; cin >> konfirmasi;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            for (int i = idx; i < jumlahProject - 1; i++) {
                *(projects + i) = *(projects + i + 1);
            }
            setColor(GREEN);
            cout << "Proyek berhasil dihapus\n";
            resetColor();
            system("pause");
            return jumlahProject - 1;
        } else {
            setColor(RED);
            cout << "Penghapusan dibatalkan\n";
            resetColor();
            system("pause");
            return jumlahProject;
        }

    } catch (const out_of_range& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
        system("pause");
        return jumlahProject;
    } catch (const runtime_error& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
        system("pause");
        return jumlahProject;
    }
}

void tambahKomentar(Project* projects, int jumlahProject) {
    tampilkanHeader("=== TAMBAH KOMENTAR ===");

    try {
        if (jumlahProject == 0) {
            throw runtime_error("Belum ada proyek yang tersedia!");
        }

        for (int i = 0; i < jumlahProject; i++) {
            cout << i + 1 << ". " << (projects + i) -> judul << endl;
        }

        int nomor;
        cout << "\nNomor proyek: ";
        cin >> nomor;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (nomor <= 0 || nomor > jumlahProject) {
            throw out_of_range("Nomor proyek tidak valid!");
        }

        Project* selectedProject = projects + (nomor - 1);

        if (selectedProject -> jumlahKomentar >= MAX_KOMENTAR) {
            throw length_error("Komentar sudah penuh!");
        }

        string komentar;

        do {
            cout << "Komentar: "; getline(cin, komentar);

            if (komentar.empty()) {
                setColor(RED);
                cout << "Komentar tidak boleh kosong! Silahkan isi.\n\n";
                resetColor();
            }

        } while (komentar.empty());

        selectedProject  ->  komentar[selectedProject  ->  jumlahKomentar] = komentar;
        selectedProject  ->  jumlahKomentar++;

        setColor(GREEN);
        cout << "\nKomentar ditambahkan\n";
        resetColor();

    } catch (const out_of_range& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
    } catch (const runtime_error& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
    } catch (const length_error& e) {
        setColor(RED);
        cout << "\nError: " << e.what() << endl;
        resetColor();
    }

    system("pause");
}

int menuAdmin(Project* projects, int jumlahProject) {
    int pilih;
    do {
        tampilkanHeader("=========== MENU ADMIN ===========");
        cout << "1. Tambah Proyek\n";
        cout << "2. Lihat Proyek\n";
        cout << "3. Update Proyek\n";
        cout << "4. Hapus Proyek\n";
        cout << "5. Logout\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilih == 1) {
            jumlahProject = tambahProyek(projects, jumlahProject);
        } else if (pilih == 2) {
            tampilkanProyekDenganSorting(projects, jumlahProject);
        } else if (pilih == 3) {
            updateProyek(projects, jumlahProject);
        } else if (pilih == 4) {
            jumlahProject = hapusProyek(projects, jumlahProject);
        } else if (pilih != 5) {
            setColor(RED);
            cout << "\nPilihan tidak valid\n";
            resetColor();
            system("pause");
        }
    } while (pilih != 5);

    return jumlahProject;
}

void menuUser(Project* projects, int jumlahProject) {
    int pilihUser;
    do {
        tampilkanHeader("=========== MENU USER ===========");
        cout << "1. Lihat Proyek\n";
        cout << "2. Cari Proyek\n";
        cout << "3. Tambah Komentar\n";
        cout << "4. Logout\n";
        cout << "Pilih: "; cin >> pilihUser;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilihUser == 1) {
            tampilkanProyekDenganSorting(projects, jumlahProject);
        } else if (pilihUser == 2) {
            cariProyek(projects, jumlahProject);
        } else if (pilihUser == 3) {
            tambahKomentar(projects, jumlahProject);
        } else if (pilihUser != 4) {
            setColor(RED);
            cout << "\nPilihan tidak valid\n";
            resetColor();
            system("pause");
        }
    } while (pilihUser != 4);
}

int main() {
    User users[MAX_USER];
    Project projects[MAX_PROJECT];

    int jumlahUser = 1;
    int jumlahProject = 0;

    users[0] = { "Rosadi", "081", "admin" };

    int menuAwal;

    do {
        system("cls||clear");
        tampilkanHeader("");
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "Pilih: "; cin >> menuAwal;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (menuAwal == 2) {
            jumlahUser = registrasiUser(users, jumlahUser);
        } else if (menuAwal == 1) {
            int userIndex = login(users, jumlahUser);

            if (userIndex == -2)
                return 0;
            if (userIndex == -1)
                continue;

            if (users[userIndex].role == "admin") {
                jumlahProject = menuAdmin(projects, jumlahProject);
            } else {
                menuUser(projects, jumlahProject);
            }
        } else if (menuAwal != 3) {
            setColor(RED);
            cout << "\nPilihan tidak valid\n";
            resetColor();
            system("pause");
        } else {
            system("cls||clear");
            setColor(GREEN);
            cout << "Terima kasih sudah menggunakan program. Sampai jumpa!";
            resetColor();
            break;
        }

    } while (menuAwal != 3);

    return 0;
}