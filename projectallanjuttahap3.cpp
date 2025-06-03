#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;

// list function
// cariMember
// setWarna
// loadingAnimasi
// asciiHotel
// tampilProfilHotel
// inisialisasiKamar
// daftar
// login
// tampilkanDaftarKamar
// tampilHarga
// cetakNota
// tampilHistory
// pesanKamar
// cariPemesanan
// menu

// deklarasi global
const int MAX_KAMAR = 30;
const int MAX_MEMBER = 100;
struct Member
{
    string username;
    string password;
};

struct Kamar
{
    string tipe;
    int harga;
    bool tersedia;
};
Member daftarMember[MAX_MEMBER];
Kamar daftarKamar[MAX_KAMAR];
int jumlahMember = 0;

Member *cariMember(const string &username)
// eror handle buat edit akun member
{
    for (int i = 0; i < jumlahMember; i++)
    {
        if (daftarMember[i].username == username)
        {
            return &daftarMember[i]; // mengembalikan alamat member
        }
    }
    return nullptr; // tidak ditemukan
}

void setWarna(int warna)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), warna);
}

void loadingAnimasi(string pesan)
{
    cout << pesan;
    for (int i = 0; i < 3; i++)
    {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\n";
}

void asciiHotel()
{
    // ilustrasi logo hotel
    cout << R"(
     _____________________________
    |                             |
    |   HOTEL NYAMAN SEJAHTERA    |
    |_____________________________|
    | []  []  []  []  []  []  []  |
    |                             |
    |   []  []  []  []  []  []    |
    |_____________________________|
    )" << "\n";
}

void tampilProfilHotel()
{
    // salam pembuka
    system("cls");
    setWarna(7); // putih
    asciiHotel();
    cout << "=========================================\n";
    cout << "         HOTEL NYAMAN SEJAHTERA\n";
    cout << "=========================================\n";
    cout << "     ~ Tempat Istirahat Ternyaman ~\n";
    cout << "-----------------------------------------\n";
    cout << " Alamat   : Jl. Bahagia No.123, Yogyakarta\n";
    cout << " Fasilitas: Kolam renang, spa, restoran,\n";
    cout << "            layanan kamar 24 jam.\n";
    cout << "=========================================\n\n";
    cout << "Selamat datang di sistem pemesanan kamar kami!\n";
    cout << "Nikmati kenyamanan dan layanan terbaik.\n\n";
    loadingAnimasi("Memuat sistem");
    system("pause");
    setWarna(7);
}

void inisialisasiKamar()
{
    // mengisi ketersediaan kamar di dimensi array struct kamar {string tipe, int harga, bool tersedia}
    for (int i = 0; i < 10; i++)
    {
        daftarKamar[i] = {"Deluxe", 500000, true};
        daftarKamar[i + 10] = {"Standar", 300000, true};
        daftarKamar[i + 20] = {"Suite", 700000, true};
    }
}

int daftar()
{
    // mengisi struct member (daftarmember) dengan inputan user; daftar akun hotel baru biar dapet diskon di function void pesanKamar()
    string user, pass;
    system("cls");
    cout << "======= PENDAFTARAN MEMBER =======\n";
    cout << "Masukkan username baru: ";
    cin >> user;
    cout << "Masukkan password: ";
    cin >> pass;
    // mengisi struct member daftarMember [jumlahMember(0)++] dengan inputan user
    daftarMember[jumlahMember++] = {user, pass};
    cout << "Pendaftaran berhasil! Silakan login untuk klaim diskon.\n";
    system("pause");
    return jumlahMember - 1; // menggeser isi dari nilai struct jumlahMember++ menjadi padan dengan aturan c++ (array-1)
}
int login()
{
    string user, pass;
    system("cls");
    cout << "=========== LOGIN MEMBER ===========\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    for (int i = 0; i < jumlahMember; i++)
    {
        if (daftarMember[i].username == user && daftarMember[i].password == pass)
        {
            cout << "Login berhasil. Diskon 20% akan diberikan.\n";
            system("pause");
            return i;
        }
    }

    cout << "Login gagal. Pilihan:\n";
    cout << "1. Daftar Member Baru\n";
    cout << "2. Lanjut tanpa login\n";
    int pilihan;
    cout << "Pilihan: ";
    cin >> pilihan;
    if (pilihan == 1)
        return daftar();
    else
        return -1;
}

void tampilDaftarKamar()
{
    // menampilkan daftar kamar tersisa... note : sesuai fungsi inisialisasiKamar ().
    system("cls");
    cout << "=========== DAFTAR KAMAR ===========\n";
    int deluxe = 0, standar = 0, suite = 0;
    // perulangan untuk menghitung banyak jumlah kamar, sesyau dengan fungsi inisialisasiKamar().
    for (int i = 0; i < MAX_KAMAR; i++)
    {
        if (daftarKamar[i].tipe == "Deluxe" && daftarKamar[i].tersedia)
            deluxe++;
        if (daftarKamar[i].tipe == "Standar" && daftarKamar[i].tersedia)
            standar++;
        if (daftarKamar[i].tipe == "Suite" && daftarKamar[i].tersedia)
            suite++;
    }
    cout << "Deluxe  | Harga: Rp 500000 | Tersisa: " << deluxe << endl;
    cout << "Standar | Harga: Rp 300000 | Tersisa: " << standar << endl;
    cout << "Suite   | Harga: Rp 700000 | Tersisa: " << suite << endl;
    cout << "======================================\n";
    system("pause");
}

void tampilHarga(bool isMember)
{
    // shorting menggunakan bubble
    system("cls");
    int pilihan;
    cout << "\nLihat daftar harga berdasarkan:\n";
    cout << "1. Harga Terendah ke Tertinggi\n";
    cout << "2. Harga Tertinggi ke Terendah\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    for (int i = 0; i < MAX_KAMAR - 1; i++)
    {
        for (int j = 0; j < MAX_KAMAR - i - 1; j++)
        {
            bool kondisi = (pilihan == 1) ? (daftarKamar[j].harga > daftarKamar[j + 1].harga)
                                          : (daftarKamar[j].harga < daftarKamar[j + 1].harga);
            if (kondisi)
            {
                swap(daftarKamar[j], daftarKamar[j + 1]);
            }
        }
    }

    cout << "\n========== DAFTAR HARGA KAMAR ==========\n\n";
    cout << left << setw(5) << "No"
         << setw(15) << "Tipe Kamar"
         << setw(20) << "Harga Normal";

    if (isMember)
        cout << setw(22) << "Harga Member (-20%)";

    cout << setw(12) << "Status" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < MAX_KAMAR; i++)
    {
        cout << left << setw(5) << (i + 1)
             << setw(15) << daftarKamar[i].tipe
             << "Rp " << setw(17) << daftarKamar[i].harga;

        if (isMember)
        {
            int hargaDiskon = static_cast<int>(daftarKamar[i].harga * 0.8);
            cout << "Rp " << setw(18) << hargaDiskon;
        }

        cout << setw(12) << (daftarKamar[i].tersedia ? "Tersedia" : "Penuh") << endl;
    }

    cout << "\n========================================\n";
    system("pause");
}

// deklarasi struct (scr global) untuk nota dan history pembelian
struct Pemesanan
{
    string nama;
    string alamat;
    string nik;
    string tipeKamar;
    string metodeBayar;
    string jamCekIn;
    string statusLunas;
};

Pemesanan daftarPesanan[MAX_KAMAR];
int jumlahPesanan = 0;

void cetakNota(const Pemesanan &p, int harga, bool isMember)
{
    system("cls");

    cout << "=========== NOTA PEMESANAN ===========\n";
    cout << left << setw(20) << "Nama" << ": " << p.nama << endl;
    cout << left << setw(20) << "Alamat" << ": " << p.alamat << endl;
    cout << left << setw(20) << "NIK" << ": " << p.nik << endl;
    cout << left << setw(20) << "Tipe Kamar" << ": " << p.tipeKamar << endl;
    cout << left << setw(20) << "Jam Check-in" << ": " << p.jamCekIn << endl;
    cout << left << setw(20) << "Metode Bayar" << ": " << p.metodeBayar << endl;
    cout << left << setw(20) << "Status Bayar" << ": " << p.statusLunas << endl;

    if (isMember)
        cout << left << setw(20) << "Diskon Member" << ": 20%\n";

    cout << left << setw(20) << "Total Harga" << ": Rp " << harga << endl;
    cout << "=======================================\n";

    // === Simpan ke file ===
    // Ubah spasi di nama menjadi underscore agar bisa dipakai di nama file
    string namaFile = p.nama;
    for (char &c : namaFile)
    {
        if (isspace(c))
            c = '_';
    }

    namaFile += "_nota.txt";

    ofstream outFile(namaFile);
    if (outFile.is_open())
    {
        outFile << "=========== NOTA PEMESANAN ===========\n";
        outFile << left << setw(20) << "Nama" << ": " << p.nama << endl;
        outFile << left << setw(20) << "Alamat" << ": " << p.alamat << endl;
        outFile << left << setw(20) << "NIK" << ": " << p.nik << endl;
        outFile << left << setw(20) << "Tipe Kamar" << ": " << p.tipeKamar << endl;
        outFile << left << setw(20) << "Jam Check-in" << ": " << p.jamCekIn << endl;
        outFile << left << setw(20) << "Metode Bayar" << ": " << p.metodeBayar << endl;
        outFile << left << setw(20) << "Status Bayar" << ": " << p.statusLunas << endl;

        if (isMember)
            outFile << left << setw(20) << "Diskon Member" << ": 20%\n";

        outFile << left << setw(20) << "Total Harga" << ": Rp " << harga << endl;
        outFile << "=======================================\n";

        outFile.close();
        cout << "\nNota telah disimpan ke file: " << namaFile << endl;
    }
    else
    {
        cerr << "Gagal menyimpan nota ke file.\n";
    }
}

void tampilHistory()
{
    system("cls");
    cout << "=========== HISTORY PEMESANAN ===========\n";
    if (jumlahPesanan == 0)
    {
        cout << "Belum ada pemesanan.\n";
    }
    else
    {
        for (int i = 0; i < jumlahPesanan; i++)
        {
            cout << i + 1 << ". Nama: " << daftarPesanan[i].nama
                 << " | Kamar: " << daftarPesanan[i].tipeKamar
                 << " | Status: " << daftarPesanan[i].statusLunas << endl;
        }
    }
    system("pause");
}

void pesanKamar(int idxMember)
{
    system("cls");
    // fungsi pesan kamar, sesuai dengan kondisi login // guest mode
    if (idxMember == -1)
    {
        int pilihanMember;
        while (true)
        {
            cout << "Apakah Anda member?\n";
            cout << "1. Ya, saya ingin login member untuk diskon\n";
            cout << "2. Tidak, saya ingin pesan tanpa member\n";
            cout << "3. Belum punya member, daftar dulu\n";
            cout << "Pilihan Anda: ";
            cin >> pilihanMember;

            if (cin.fail() || pilihanMember < 1 || pilihanMember > 3)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Input tidak valid. Masukkan angka 1-3.\n\n";
                continue;
            }
            break;
        }

        if (pilihanMember == 1)
        {
            idxMember = login();
            if (idxMember == -1)
            {
                int retryChoice;
                while (true)
                {
                    cout << "\nLogin gagal. Pilih:\n";
                    cout << "1. Daftar Member\n";
                    cout << "2. Lanjut tanpa Member\n";
                    cout << "Pilihan Anda: ";
                    cin >> retryChoice;

                    if (cin.fail() || retryChoice < 1 || retryChoice > 2)
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Input tidak valid. Masukkan 1 atau 2.\n";
                        continue;
                    }

                    if (retryChoice == 1)
                        idxMember = daftar();

                    break;
                }
            }
        }
        else if (pilihanMember == 3)
        {
            idxMember = daftar();
        }
    }

    if (jumlahPesanan >= MAX_KAMAR)
    {
        cout << "Maaf, semua kamar sudah penuh.\n";
        system("pause");
        return;
    }

    Pemesanan p;
    cin.ignore();

    cout << "\n======== FORM PEMESANAN KAMAR ========\n";
    cout << "Nama         : ";
    getline(cin, p.nama);
    cout << "Alamat       : ";
    getline(cin, p.alamat);
    cout << "NIK          : ";
    getline(cin, p.nik);

    // Tampilkan tipe kamar tersedia beserta harga
    string tipeTersedia[30];
    int hargaTipe[30];
    int jumlahTersedia = 0;

    for (int i = 0; i < MAX_KAMAR; i++)
    {
        if (daftarKamar[i].tersedia)
        {
            bool sudahAda = false;
            for (int j = 0; j < jumlahTersedia; j++)
            {
                if (tipeTersedia[j] == daftarKamar[i].tipe)
                {
                    sudahAda = true;
                    break;
                }
            }
            if (!sudahAda)
            {
                tipeTersedia[jumlahTersedia] = daftarKamar[i].tipe;
                hargaTipe[jumlahTersedia] = daftarKamar[i].harga;
                jumlahTersedia++;
            }
        }
    }

    if (jumlahTersedia == 0)
    {
        cout << "Maaf, semua kamar sudah dipesan.\n";
        system("pause");
        return;
    }

    cout << "\nKamar tersedia:\n";
    for (int i = 0; i < jumlahTersedia; i++)
    {
        cout << i + 1 << ". " << tipeTersedia[i]
             << " | Harga: Rp " << hargaTipe[i];
        if (idxMember != -1)
            cout << " (Setelah diskon: Rp " << hargaTipe[i] * 0.8 << ")";
        cout << endl;
    }

    int pilihKamar;
    while (true)
    {
        cout << "Pilih tipe kamar (masukkan nomor): ";
        cin >> pilihKamar;
        if (cin.fail() || pilihKamar < 1 || pilihKamar > jumlahTersedia)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Pilihan tidak valid. Coba lagi.\n";
            continue;
        }
        break;
    }
    p.tipeKamar = tipeTersedia[pilihKamar - 1];

    int harga = 0;
    bool ditemukan = false;
    for (int i = 0; i < MAX_KAMAR; i++)
    {
        if (daftarKamar[i].tipe == p.tipeKamar && daftarKamar[i].tersedia)
        {
            daftarKamar[i].tersedia = false;
            harga = daftarKamar[i].harga;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "Maaf, kamar tidak tersedia lagi.\n";
        system("pause");
        return;
    }

    cin.ignore();
    cout << "Jam Check-in : ";
    getline(cin, p.jamCekIn);
    cout << "Metode pembayaran (Cash/Debit): ";
    getline(cin, p.metodeBayar);
    cout << "Status pembayaran (Lunas/Belum): ";
    getline(cin, p.statusLunas);

    daftarPesanan[jumlahPesanan++] = p;

    if (idxMember != -1)
        harga *= 0.8;

    cetakNota(p, harga, idxMember != -1);

    cout << "\nKembali ke menu utama...\n";
    system("pause");
}

void cariPemesanan()
{
    // cari pemesanan berdasarkan nama pemesan
    system("cls");
    if (jumlahPesanan == 0)
    {
        cout << "Belum ada pemesanan yang tercatat.\n";
        system("pause");
        return;
    }

    cin.ignore();
    string cariNama;
    cout << "Masukkan nama pemesan yang ingin dicari: ";
    getline(cin, cariNama);

    bool ditemukan = false;
    cout << "Hasil pencarian:\n";
    for (int i = 0; i < jumlahPesanan; i++)
    {
        if (daftarPesanan[i].nama == cariNama)
        {
            ditemukan = true;
            cout << "------------------------------------\n";
            cout << "Nama        : " << daftarPesanan[i].nama << endl;
            cout << "Tipe Kamar  : " << daftarPesanan[i].tipeKamar << endl;
            cout << "Jam Check-in: " << daftarPesanan[i].jamCekIn << endl;
        }
    }

    if (!ditemukan)
    {
        cout << "Tidak ditemukan pemesanan atas nama '" << cariNama << "'.\n";
    }

    system("pause");
}

void menu(int idxLogin)
{
    bool isMember = (idxLogin != -1);
    int pilihan;
    do
    {
        system("cls");
        cout << "=========== MENU UTAMA ===========\n";
        cout << "1. Lihat Daftar Kamar\n";
        cout << "2. Lihat Daftar Harga\n";
        cout << "3. Pesan Kamar\n";
        cout << "4. Lihat History Pemesanan\n";
        cout << "5. Cari Pemesanan\n";
        cout << "6. Edit Akun Member\n"; // fitur baru
        cout << "7. Logout Akun\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tampilDaftarKamar();
            break;
        case 2:
            tampilHarga(isMember);
            break;
        case 3:
            pesanKamar(idxLogin);
            break;
        case 4:
            tampilHistory();
            break;
        case 5:
            cariPemesanan();
            break;
        case 6:
            if (isMember)
            {
                Member *user = cariMember(daftarMember[idxLogin].username);
                if (user != nullptr)
                {
                    string newPass;
                    cout << "Masukkan password baru: ";
                    cin >> newPass;
                    user->password = newPass;
                    cout << "Password berhasil diubah!\n";
                }
                else
                {
                    cout << "Data member tidak ditemukan.\n";
                }
            }
            else
            {
                cout << "Fitur ini hanya untuk member.\n";
            }
            system("pause");
            break;
        case 7:
            cout << "Logout berhasil. Kembali ke menu awal...\n";
            system("pause");
            return;
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            system("pause");
        }

    } while (pilihan != 7);
}

int main()
{
    inisialisasiKamar();
    tampilProfilHotel();

    bool jalan = true;
    while (jalan)
    {
        int idxLogin = -1;

        system("cls"); // Bersihkan layar sebelum menu login/daftar
        cout << "=========================================\n";
        cout << "                MENU AWAL\n";
        cout << "=========================================\n";
        cout << "1. Login sebagai Member\n";
        cout << "2. Lanjut tanpa login\n";
        cout << "3. Keluar Aplikasi\n";
        cout << "Pilih: ";
        int awalPilihan;
        cin >> awalPilihan;

        switch (awalPilihan)
        {
        case 1:
            idxLogin = login();
            if (idxLogin == -1)
            {
                cout << "Login gagal, lanjut tanpa login.\n";
                system("pause");
            }
            menu(idxLogin); // masuk menu utama
            break;

        case 2:
            menu(-1); // masuk menu utama sebagai non-member
            break;

        case 3:
            cout << "Terima kasih telah menggunakan aplikasi.\n";
            jalan = false;
            break;

        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
            system("pause");
        }
    }

    return 0;
}
