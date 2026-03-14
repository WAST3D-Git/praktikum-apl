#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_USER = 50;
const int MAX_PROJECT = 100;
const int MAX_KOMENTAR = 50;

struct Project{
    string judul;

    struct Detail{
        string deskripsi, software, deadline, klien, status;
    }detail;

    string komentar[MAX_KOMENTAR];
    int jumlahKomentar = 0;

};

struct User{
    string nama;
    string nim;
    string role;
};

void tampilkanHeader(string judul) {
    system("cls||clear");

    if (judul != "") {
        cout << judul << endl;

    } else {
        cout << "===========================================\n";
        cout << "   SISTEM MANAJEMEN PROYEK DESAIN GRAFIS   \n";
        cout << "===========================================\n";
    }
}

bool cariProyek(Project projects[MAX_PROJECT], int index, int jumlahProject, string kataKunci, int foundIndex[]) {
    if (index >= jumlahProject) {
        return false;
    }
    
    if (projects[index].judul.find(kataKunci) != string::npos) {
        foundIndex[0] = index;
        return true;
    }
    
    return cariProyek(projects, index + 1, jumlahProject, kataKunci, foundIndex);
}

void cariProyek(Project projects[MAX_PROJECT], int jumlahProject) {
    tampilkanHeader("=== CARI PROYEK ===");

    if(jumlahProject == 0){
        cout << "\nBelum ada proyek yang tersedia.\n";
        system("pause");
        return;
    }

    string cari;
    cout << "Masukkan judul proyek: "; getline(cin,cari);

    bool ditemukan = false;
    int foundIndex[1] = {-1}; 
    int i = 0;
    
    while (i < jumlahProject) {

        if (cariProyek(projects, i, jumlahProject, cari, foundIndex)) {
            cout << "\n=== PROYEK DITEMUKAN ===\n";
            cout << "Judul     : " << projects[foundIndex[0]].judul << endl;
            cout << "Deskripsi : " << projects[foundIndex[0]].detail.deskripsi << endl;
            cout << "Software  : " << projects[foundIndex[0]].detail.software << endl;
            cout << "Deadline  : " << projects[foundIndex[0]].detail.deadline << endl;
            cout << "Klien     : " << projects[foundIndex[0]].detail.klien << endl;
            cout << "Status    : " << projects[foundIndex[0]].detail.status << endl;

            cout << "Komentar  : ";
            if(projects[foundIndex[0]].jumlahKomentar == 0){
                cout << "-";
            }else{
                for(int j=0;j<projects[foundIndex[0]].jumlahKomentar;j++){
                    cout << "\n  - " << projects[foundIndex[0]].komentar[j];
                }
            }
            cout << endl;
            ditemukan = true;
            i = foundIndex[0] + 1;
            foundIndex[0] = -1; 
        } else {
            i++;
        }
    }

    if(!ditemukan)
        cout<<"\nProyek tidak ditemukan\n";

    system("pause");
}

void tampilkanProyek(Project projects[MAX_PROJECT], int jumlahProject) {
    system("cls||clear");

    if(jumlahProject == 0){
        cout << "Belum ada proyek\n";
        return;
    }

    cout << left << setw(5) << "No" 
         << setw(20) << "Judul" 
         << setw(25) << "Deskripsi"
         << setw(15) << "Software" 
         << setw(15) << "Deadline" 
         << setw(15) << "Klien" 
         << setw(12) << "Status" 
         << setw(40) << "Komentar" << endl;

    cout << string(147,'=') << endl;

    for(int i=0; i < jumlahProject ;i++){
        string semuaKomentar;
        
        if(projects[i].jumlahKomentar == 0)
            semuaKomentar = "-";
        else {
            for(int k = 0; k < projects[i].jumlahKomentar; k++) {
                if(k > 0) semuaKomentar += "; ";
                semuaKomentar += to_string(k+1) + ". " + projects[i].komentar[k];
            }
        }

        cout << left << setw(5) << i+1 
             << setw(20) << projects[i].judul 
             << setw(25) << projects[i].detail.deskripsi
             << setw(15) << projects[i].detail.software 
             << setw(15) << projects[i].detail.deadline 
             << setw(15) << projects[i].detail.klien 
             << setw(12) << projects[i].detail.status 
             << setw(40) << semuaKomentar << endl;
    }
}

int registrasiUser(User users[MAX_USER], int jumlahUser) {
    tampilkanHeader("=== REGISTRASI ===");

    if(jumlahUser < MAX_USER){
        string nama,nim;

        cout<<"Username : "; getline(cin,nama);
        cout<<"Password : "; getline(cin,nim);

        bool sudahAda=false;

        for(int i = 0;i < jumlahUser;i++){
            if(users[i].nama == nama){
                sudahAda = true;
                break;
            }
        }

        if(nama == "" || nim == ""){
            cout << "\nUsername dan password wajib diisi\n";
            system("pause");
            return jumlahUser;
        }
        else if(sudahAda){
            cout << "\nUsername sudah digunakan\n";
            system("pause");
            return jumlahUser;
        }
        else{
            users[jumlahUser].nama = nama;
            users[jumlahUser].nim = nim;
            users[jumlahUser].role = "user";
            cout << "\nRegistrasi berhasil\n";
            system("pause");
            return jumlahUser + 1;
        }
    } else {
        cout << "\nUser sudah mencapai batas maksimum\n";
        system("pause");
        return jumlahUser;
    }
}

int login(User users[MAX_USER], int jumlahUser) {
    int percobaanLogin = 0;
    string username, password;

    while(percobaanLogin < 3){
        system("cls||clear");
        tampilkanHeader("======= LOGIN =======");
        cout<<"Username : "; getline(cin,username);
        cout<<"Password : "; getline(cin,password);

        for(int i = 0;i < jumlahUser; i++){
            if(users[i].nama == username && users[i].nim == password){
                cout << "\nLogin berhasil! Selamat datang, " << username << "!\n";
                system("pause");
                return i;
            }
        }

        percobaanLogin++;
        if (percobaanLogin == 3) {
            cout << "\nLogin gagal.\n";
            cout << "Anda telah mencapai batas percobaan login. Program dihentikan.";
            return -2;
        }

        cout << "\nLogin gagal! (Batas percobaan login 3x).\n";
        cout << "Percobaan login ke-" << percobaanLogin << ", Silahkan coba lagi.\n";
        system("pause");
    }
    return -1;
}

int tambahProyek(Project projects[MAX_PROJECT], int jumlahProject) {
    tampilkanHeader("=== TAMBAH PROYEK ===");

    if(jumlahProject < MAX_PROJECT){
        string judul,deskripsi,software,deadline,klien,status;

        cout << "Judul : "; getline(cin,judul);
        cout << "Deskripsi : "; getline(cin,deskripsi);
        cout << "Software : "; getline(cin,software);
        cout << "Deadline : "; getline(cin,deadline);
        cout << "Klien : "; getline(cin,klien);
        cout << "Status : "; getline(cin,status);

        if(judul != "" && klien != ""){
            projects[jumlahProject].judul = judul;
            projects[jumlahProject].detail.deskripsi = deskripsi;
            projects[jumlahProject].detail.software = software;
            projects[jumlahProject].detail.deadline = deadline;
            projects[jumlahProject].detail.klien = klien;
            projects[jumlahProject].detail.status = status;
            cout<<"\nProyek berhasil ditambahkan.\n";
            system("pause");
            return jumlahProject + 1;
        } else {
            cout << "\nJudul dan klien wajib diisi.\n";
            system("pause");
            return jumlahProject;
        }
    } else {
        cout << "\nProyek sudah mencapai batas maksimum.\n";
        system("pause");
        return jumlahProject;
    }
}

void updateProyek(Project projects[MAX_PROJECT], int jumlahProject) {
    tampilkanHeader("=== UPDATE PROYEK ===");

    if(jumlahProject == 0){
        cout<<"\nBelum ada proyek\n";
        system("pause");
        return;
    }

    for(int i=0; i < jumlahProject; i++){
        cout << i+1 << ". " << projects[i].judul << " - " << projects[i].detail.status << endl;
    }

    int nomor;
    cout << "\nNomor proyek yang akan diupdate: "; cin>>nomor;
    cin.ignore();

    if(nomor > 0 && nomor <= jumlahProject){
        int idx = nomor-1;
        
        cout << "\nData lama:\n";
        cout << "Judul: " << projects[idx].judul << endl;
        cout << "Deskripsi: " << projects[idx].detail.deskripsi << endl;
        cout << "Software: " << projects[idx].detail.software << endl;
        cout << "Deadline: " << projects[idx].detail.deadline << endl;
        cout << "Klien: " << projects[idx].detail.klien << endl;
        cout << "Status: " << projects[idx].detail.status << endl;
        
        cout << "\nMasukkan data baru (kosongkan jika tidak ingin mengubah):\n";
        
        string input;
        
        cout << "Judul baru: "; getline(cin, input);
        if(input != "") projects[idx].judul = input;
        
        cout << "Deskripsi baru: "; getline(cin, input);
        if(input != "") projects[idx].detail.deskripsi = input;
        
        cout << "Software baru: "; getline(cin, input);
        if(input != "") projects[idx].detail.software = input;
        
        cout << "Deadline baru: "; getline(cin, input);
        if(input != "") projects[idx].detail.deadline = input;
        
        cout << "Klien baru: "; getline(cin, input);
        if(input != "") projects[idx].detail.klien = input;
        
        cout << "Status baru: "; getline(cin, input);
        if(input != "") projects[idx].detail.status = input;

        cout << "\nUpdate berhasil!\n";
    } else {
        cout << "\nNomor tidak valid!\n";
    }
    system("pause");
}

int hapusProyek(Project projects[MAX_PROJECT], int jumlahProject) {
    tampilkanHeader("=== HAPUS PROYEK ===");

    if(jumlahProject == 0){
        cout << "\nTidak ada proyek untuk dihapus.\n";
        system("pause");
        return jumlahProject;
    }

    for(int i=0; i < jumlahProject; i++){
        cout << i+1 << ". " << projects[i].judul << " - " << projects[i].detail.klien << endl;
    }

    int nomor;
    cout << "\nNomor proyek yang akan dihapus: "; cin >> nomor;

    if(nomor > 0 && nomor <= jumlahProject){
        int idx = nomor-1;
        char yakin;
        cout << "\nYakin ingin menghapus? (y/n): "; cin >> yakin;
        
        if(yakin == 'y' || yakin == 'Y'){
            for(int i = idx; i < jumlahProject - 1; i++){
                projects[i] = projects[i+1];
            }
            cout << "Proyek berhasil dihapus\n";
            system("pause");
            return jumlahProject - 1;
        } else {
            cout << "Penghapusan dibatalkan\n";
            system("pause");
            return jumlahProject;
        }
    } else {
        cout << "\nNomor tidak valid!\n";
        system("pause");
        return jumlahProject;
    }
}

void tambahKomentar(Project projects[MAX_PROJECT], int jumlahProject) {
    tampilkanHeader("=== TAMBAH KOMENTAR ===");

    if(jumlahProject == 0){
        cout << "\nBelum ada proyek yang tersedia.\n";
        system("pause");
        return;
    }

    for(int i = 0; i < jumlahProject; i++){
        cout << i+1 << ". " << projects[i].judul << endl;
    }

    int nomor;
    cout << "\nNomor proyek: ";
    cin >> nomor;
    cin.ignore();

    if(nomor > 0 && nomor <= jumlahProject){
        int index = nomor - 1;

        if(projects[index].jumlahKomentar < MAX_KOMENTAR){
            string komentar;

            do {
                cout << "Komentar: ";
                getline(cin, komentar);

                if(komentar == ""){
                    cout << "Komentar tidak boleh kosong! Silahkan isi.\n\n";
                }

            } while(komentar == "");

            projects[index].komentar[projects[index].jumlahKomentar] = komentar;
            projects[index].jumlahKomentar++;

            cout << "\nKomentar ditambahkan\n";
        } 
        else {
            cout << "\nKomentar sudah penuh\n";
        }
    } 
    else {
        cout << "\nNomor proyek tidak valid\n";
    }

    system("pause");
}

int menuAdmin(Project projects[MAX_PROJECT], int jumlahProject) {
    int pilih;
    do{
        tampilkanHeader("=========== MENU ADMIN ===========");
        cout << "1. Tambah Proyek\n";
        cout << "2. Lihat Proyek\n";
        cout << "3. Update Proyek\n";
        cout << "4. Hapus Proyek\n";
        cout << "5. Logout\n";
        cout << "Pilih: "; cin >> pilih;
        cin.ignore();

        if(pilih == 1){
            jumlahProject = tambahProyek(projects, jumlahProject);
        }
        else if(pilih == 2){
            tampilkanProyek(projects, jumlahProject);
            system("pause");
        }
        else if(pilih == 3){
            updateProyek(projects, jumlahProject);
        }
        else if(pilih == 4){
            jumlahProject = hapusProyek(projects, jumlahProject);
        }
        else if(pilih != 5){
            cout << "\nPilihan tidak valid\n";
            system("pause");
        }
    }while (pilih != 5);
    
    return jumlahProject;
}

void menuUser(Project projects[MAX_PROJECT], int jumlahProject) {
    int pilihUser;
    do{
        tampilkanHeader("=========== MENU USER ===========");
        cout << "1. Lihat Proyek\n";
        cout << "2. Cari Proyek\n";
        cout << "3. Tambah Komentar\n";
        cout << "4. Logout\n";
        cout << "Pilih: "; cin >> pilihUser;
        cin.ignore();

        if(pilihUser == 1){
            tampilkanProyek(projects, jumlahProject);
            system("pause");
        }
        else if(pilihUser == 2){
            cariProyek(projects, jumlahProject);
        }
        else if(pilihUser == 3){
            tambahKomentar(projects, jumlahProject);
        }
        else if(pilihUser != 4){
            cout << "\nPilihan tidak valid\n";
            system("pause");
        }
    }while (pilihUser != 4);
}

int main(){
    User users[MAX_USER];
    Project projects[MAX_PROJECT];
    
    int jumlahUser = 1;
    int jumlahProject = 0;

    users[0] = {"Rosadi","081","admin"};

    int menuAwal;

    do{
        system("cls||clear");
        tampilkanHeader("");
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "Pilih: "; cin >> menuAwal;
        cin.ignore();

        if(menuAwal == 2){
            jumlahUser = registrasiUser(users, jumlahUser);
        }
        else if(menuAwal == 1){
            int userIndex = login(users, jumlahUser);
            
            if(userIndex == -2) return 0;
            if(userIndex == -1) continue;

            if(users[userIndex].role == "admin"){
                jumlahProject = menuAdmin(projects, jumlahProject);
            }
            else{
                menuUser(projects, jumlahProject);
            }
        }
        else if(menuAwal != 3){
            cout << "\nPilihan tidak valid\n";
            system("pause");
        }
        else {
            cout << "Terima kasih sudah menggunakan program. Sampai jumpa!";
            break;
        }

    }while (menuAwal != 3);

    return 0;
}