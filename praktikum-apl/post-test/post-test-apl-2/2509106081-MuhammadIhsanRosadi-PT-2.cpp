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

}projects[MAX_PROJECT];

struct User{
    string nama;
    string nim;
    string role;
}users[MAX_USER];

int main(){
    int jumlahUser = 1;
    int jumlahProject = 0;

    users[0] = {"Rosadi","081","admin"};

    int menuAwal;

    do{
        system("cls||clear");

        cout << "===========================================\n";
        cout << "   SISTEM MANAJEMEN PROYEK DESAIN GRAFIS   \n";
        cout << "===========================================\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "Pilih: "; cin >> menuAwal;
        cin.ignore();

        // REGISTER
        if(menuAwal == 2){
            system("cls||clear");
            cout << "=== REGISTRASI ===\n";

            if(jumlahUser < MAX_USER){
                string nama,nim;

                cout<<"Username : "; getline(cin,nama);
                cout<<"Password : "; getline(cin,nim);

                bool sudahAda=false;

                for(int i = 0;i <= jumlahUser;i++){
                    if(users[i].nama == nama){
                        sudahAda = true;
                        break;
                    }
                }

                if(nama == "" || nim == ""){
                    cout << "\nUsername dan password wajib diisi\n";
                }

                else if(sudahAda){
                    cout << "\nUsername sudah digunakan\n";
                }

                else{
                    users[jumlahUser].nama = nama;
                    users[jumlahUser].nim = nim;
                    users[jumlahUser].role = "user";

                    jumlahUser++;

                    cout << "\nRegistrasi berhasil\n";
                }
            } else {
                cout << "\nUser sudah mencapai batas maksimum\n";
            }

            system("pause");
        }

        // LOGIN
        else if(menuAwal == 1){
            int percobaanLogin = 0;
            string username, password;
            int userIndex = -1;

            while(percobaanLogin < 3){
                system("cls||clear");
                cout<<"======= LOGIN =======\n";
                cout<<"Username : "; getline(cin,username);
                cout<<"Password : "; getline(cin,password);

                for(int i=0;i < jumlahUser; i++){
                    if(users[i].nama == username && users[i].nim == password){
                        userIndex = i;
                        break;
                    }
                }

                if (userIndex != -1) {
                    cout << "\nLogin berhasil! Selamat datang, "
                        << username << "!\n";
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

            if(userIndex == -1) return 0;

            // ADMIN
            if(users[userIndex].role == "admin"){
                int pilih;

                do{
                    system("cls||clear");
                    cout << "=========== MENU ADMIN ===========\n";
                    cout << "1. Tambah Proyek\n";
                    cout << "2. Lihat Proyek\n";
                    cout << "3. Update Proyek\n";
                    cout << "4. Hapus Proyek\n";
                    cout << "5. Logout\n";
                    cout << "Pilih: "; cin >> pilih;
                    cin.ignore();

                    // CREATE
                    if(pilih == 1){
                        system("cls||clear");
                        cout << "=== TAMBAH PROYEK ===\n";

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

                                jumlahProject++;

                                cout<<"\nProyek berhasil ditambahkan.\n";
                            } else {
                                cout << "\nJudul dan klien wajib diisi.\n";
                            }

                            system("pause");

                        } else {
                            cout << "\nProyek sudah mencapai batas maksimum.\n";
                            system("pause");
                        }
                    }

                    // READ
                    else if(pilih == 2){
                        system("cls||clear");

                        if(jumlahProject == 0){
                            cout << "Belum ada proyek\n";
                        }

                        else{
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

                        system("pause");
                    }

                    // UPDATE
                    else if(pilih == 3){
                        system("cls||clear");
                        cout << "=== UPDATE PROYEK ===\n";

                        if(jumlahProject == 0){
                            cout<<"\nBelum ada proyek\n";
                            system("pause");
                            continue;
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

                    // DELETE
                    else if(pilih == 4){
                        system("cls||clear");
                        cout << "=== HAPUS PROYEK ===\n";

                        if(jumlahProject == 0){
                            cout << "\nTidak ada proyek untuk dihapus.\n";
                            system("pause");
                            continue;
                        }

                        for(int i = 0; i < jumlahProject; i++){
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
                                jumlahProject--;
                                cout << "Proyek berhasil dihapus\n";
                            } else {
                                cout << "Penghapusan dibatalkan\n";
                            }
                        } else {
                            cout << "\nNomor tidak valid!\n";
                        }

                        system("pause");
                    } 
                    else if(pilih != 5){
                        cout << "\nPilihan tidak valid\n";
                        system("pause");
                    }

                }while (pilih != 5);
            }

            // USER BIASA
            else{
                int pilihUser;

                do{
                    system("cls||clear");

                    cout << "=========== MENU USER ===========\n";
                    cout << "1. Lihat Proyek\n";
                    cout << "2. Cari Proyek\n";
                    cout << "3. Tambah Komentar\n";
                    cout << "4. Logout\n";
                    cout << "Pilih: "; cin >> pilihUser;
                    cin.ignore();

                    // READ
                    if(pilihUser == 1){
                        system("cls||clear");

                        if(jumlahProject == 0){
                            cout<<"Belum ada proyek yang tersedia\n";
                        }

                        else{
                            cout << left << setw(5) << "No" 
                                << setw(20) << "Judul" 
                                << setw(25) << "Deskripsi"
                                << setw(15) << "Software" 
                                << setw(15) << "Deadline" 
                                << setw(15) << "Klien" 
                                << setw(12) << "Status" 
                                << setw(40) << "Komentar" << endl;

                            cout << string(147, '=') << endl;

                            for(int i=0;i<jumlahProject;i++){
                                string semuaKomentar;
                                
                                if(projects[i].jumlahKomentar == 0)
                                    semuaKomentar = "-";
                                else {
                                    for(int k = 0; k < projects[i].jumlahKomentar; k++) {
                                        if(k > 0) semuaKomentar += "; ";
                                        semuaKomentar += to_string(k+1) + ". " + projects[i].komentar[k];
                                    }
                                }

                                cout << left << setw(5) << i + 1 
                                    << setw(20) << projects[i].judul 
                                    << setw(25) << projects[i].detail.deskripsi
                                    << setw(15) << projects[i].detail.software 
                                    << setw(15) << projects[i].detail.deadline 
                                    << setw(15) << projects[i].detail.klien 
                                    << setw(12) << projects[i].detail.status 
                                    << setw(40) << semuaKomentar << endl;
                            }
                        }

                        system("pause");
                    }                       

                    // CARI PROYEK
                    else if(pilihUser == 2){
                        system("cls||clear");
                        cout << "=== CARI PROYEK ===\n";

                        if(jumlahProject == 0){
                            cout << "\nBelum ada proyek yang tersedia.\n";
                            system("pause");
                            continue;
                        }

                        string cari;
                        cout << "Masukkan judul proyek: "; getline(cin,cari);

                        bool ditemukan=false;

                        for(int i = 0;i < jumlahProject;i++){
                            if(projects[i].judul.find(cari)!=string::npos){

                                cout << "\n=== PROYEK DITEMUKAN ===\n";
                                cout << "Judul     : " << projects[i].judul << endl;
                                cout << "Deskripsi : " << projects[i].detail.deskripsi << endl;
                                cout << "Software  : " << projects[i].detail.software << endl;
                                cout << "Deadline  : " << projects[i].detail.deadline << endl;
                                cout << "Klien     : " << projects[i].detail.klien << endl;
                                cout << "Status    : " << projects[i].detail.status << endl;

                                cout << "Komentar  : ";
                                if(projects[i].jumlahKomentar == 0){
                                    cout << "-";
                                }else{
                                    for(int j=0;j<projects[i].jumlahKomentar;j++){
                                        cout << "\n  - " << projects[i].komentar[j];
                                    }
                                }

                                cout << endl;
                                ditemukan=true;
                            }
                        }

                        if(!ditemukan)
                            cout<<"\nProyek tidak ditemukan\n";

                        system("pause");
                    } 

                    // KOMENTAR
                    else if(pilihUser == 3){
                        system("cls||clear");
                        cout << "=== TAMBAH KOMENTAR ===\n";

                        if(jumlahProject == 0){
                            cout << "\nBelum ada proyek yang tersedia.\n";
                            system("pause");
                            continue;
                        }

                        for(int i = 0; i < jumlahProject; i++){
                            cout << i+1 << ". " << projects[i].judul << endl;
                        }

                        int nomor;
                        cout << "\nNomor proyek: "; cin>>nomor;
                        cin.ignore();

                        if(nomor > 0 && nomor <= jumlahProject){
                            int index = nomor - 1;

                            if(projects[index].jumlahKomentar < MAX_KOMENTAR){
                                string komentar;
                                cout << "Komentar: "; getline(cin,komentar);
                                projects[index].komentar[projects[index].jumlahKomentar] = komentar;
                                projects[index].jumlahKomentar++;
                                cout<<"\nKomentar ditambahkan\n";
                            } else {
                                cout << "\nKomentar sudah penuh\n";
                            }
                        } else {
                            cout <<  "\nNomor proyek tidak valid\n";
                        }

                        system("pause");

                    } else if(pilihUser != 4){
                        cout << "\nPilihan tidak valid\n";
                        system("pause");
                    }

                }while (pilihUser != 4);
            }
        } else if(menuAwal != 3){
            cout << "\nPilihan tidak valid\n";
            system("pause");
        } else {
            system("cls||clear");
            cout << "Terima kasih sudah menggunakan program. Sampai jumpa!";
            break;
        }

    }while (menuAwal != 3);

    return 0;
}