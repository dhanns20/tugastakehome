
#include <iostream>
#include <string>
using namespace std;

// Variabel global
string nama[5] = {
    "Kopi Susu", "Americano", "Matcha Latte",
    "Cokelat", "Roti Bakar"
};

int harga[5] = {18000, 15000, 20000, 17000, 12000};
int jumlah[5] = {0, 0, 0, 0, 0};

int diskon = 0;
int totalBayar = 0;
bool voucher = false;

// Prototype fungsi
void tampilkanProduk();
void pemesanan();
int hitungSubtotal();
void detailPesanan();
void hitungPembayaran();
void cetakStruk(int uang);
int inputAngka(string pesan, int batas);

// Fungsi input angka
int inputAngka(string pesan, int batas) {
    int angka;

    while (true) {
        cout << pesan;
        cin >> angka;

        if (cin.fail()) {
            cout << "Input harus berupa angka!\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (angka < 1 || angka > batas) {
            cout << "Pilihan tidak valid!\n";
        }
        else {
            return angka;
        }
    }
}

// Menampilkan daftar produk
void tampilkanProduk() {
    cout << "\n======= DAFTAR PRODUK =======\n";

    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << nama[i]
             << " - Rp" << harga[i] << endl;
    }
}

// Fungsi pemesanan
void pemesanan() {
    int pilihan, banyak;
    char tambah;

    do {
        tampilkanProduk();

        pilihan = inputAngka("Pilih produk (1-5): ", 5);
        banyak = inputAngka("Jumlah pesanan: ", 1000);

        jumlah[pilihan - 1] = jumlah[pilihan - 1] + banyak;

        cout << "Produk berhasil ditambahkan!\n";

        cout << "Tambah pesanan lagi? (y/t): ";
        cin >> tambah;

        while (tambah != 'y' && tambah != 'Y' &&
                tambah != 't' && tambah != 'T') {
            cout << "Masukkan y atau t: ";
            cin >> tambah;
        }

    } while (tambah == 'y' || tambah == 'Y');
}

// Menghitung subtotal
int hitungSubtotal() {
    int subtotal = 0;

    for (int i = 0; i < 5; i++) {
        subtotal = subtotal + (harga[i] * jumlah[i]);
    }

    return subtotal;
}

// Menampilkan detail pesanan
void detailPesanan() {
    int subtotal = hitungSubtotal();

    cout << "\n======= DETAIL PESANAN =======\n";

    if (subtotal == 0) {
        cout << "Daftar pesanan masih kosong.\n";
    }
    else {
        for (int i = 0; i < 5; i++) {
            if (jumlah[i] > 0) {
                cout << nama[i]
                     << " | Rp" << harga[i]
                     << " | Jumlah: " << jumlah[i]
                     << " | Subtotal: Rp"
                     << harga[i] * jumlah[i] << endl;
            }
        }

        cout << "-----------------------------\n";
        cout << "Total belanja: Rp" << subtotal << endl;
    }
}

// Menghitung pembayaran
void hitungPembayaran() {
    int subtotal = hitungSubtotal();
    string kode;

    cout << "\n======= PEMBAYARAN =======\n";

    if (subtotal == 0) {
        cout << "Belum ada pesanan!\n";
        return;
    }

    cout << "Subtotal belanja: Rp" << subtotal << endl;

    if (voucher == false) {
        do {
            cout << "Masukkan kode voucher (- jika tidak ada): ";
            cin >> kode;

            if (kode == "MHSUPN") {
                voucher = true;
                cout << "Voucher berhasil digunakan!\n";
                break;
            }
            else if (kode == "-") {
                cout << "Tidak menggunakan voucher.\n";
                break;
            }
            else {
                cout << "Kode voucher salah!\n";
            }

        } while (true);
    }
    else {
        cout << "Voucher sudah digunakan.\n";
    }

    if (voucher == true) {
        diskon = subtotal * 10 / 100;
    }
    else {
        diskon = 0;
    }

    totalBayar = subtotal - diskon;

    cout << "\nSubtotal       : Rp" << subtotal << endl;
    cout << "Nominal diskon : Rp" << diskon << endl;
    cout << "Total bayar    : Rp" << totalBayar << endl;
}

// Mencetak struk
void cetakStruk(int uang) {
    int subtotal = hitungSubtotal();
    int kembalian = uang - totalBayar;

    cout << "\n========== STRUK KAFE ==========\n";

    for (int i = 0; i < 5; i++) {
        if (jumlah[i] > 0) {
            cout << nama[i]
                 << " | Rp" << harga[i]
                 << " | " << jumlah[i]
                 << " | Rp" << harga[i] * jumlah[i]
                 << endl;
        }
    }

    cout << "--------------------------------\n";
    cout << "Total belanja  : Rp" << subtotal << endl;

    if (voucher == true) {
        cout << "Kode voucher   : MHSUPN\n";
    }
    else {
        cout << "Kode voucher   : -\n";
    }

    cout << "Diskon         : Rp" << diskon << endl;
    cout << "Total bayar    : Rp" << totalBayar << endl;
    cout << "Uang bayar     : Rp" << uang << endl;
    cout << "Kembalian      : Rp" << kembalian << endl;

    cout << "================================\n";
    cout << "Terima kasih telah berbelanja!\n";

    // Mengosongkan pesanan
    for (int i = 0; i < 5; i++) {
        jumlah[i] = 0;
    }

    voucher = false;
    diskon = 0;
    totalBayar = 0;
}

// Program utama
int main() {
    int pilihan;
    int uang;
    bool sudahDihitung = false;

    do {
        cout << "\n================================\n";
        cout << "            KASIR KAFE\n";
        cout << "================================\n";
        cout << "1. Pemesanan Produk\n";
        cout << "2. Detail Pesanan\n";
        cout << "3. Perhitungan Pembayaran\n";
        cout << "4. Pembayaran dan Cetak Struk\n";
        cout << "5. Keluar Program\n";
        cout << "================================\n";

        pilihan = inputAngka("Pilih menu: ", 5);

        switch (pilihan) {

            case 1:
                pemesanan();
                sudahDihitung = false;
                break;

            case 2:
                detailPesanan();
                break;

            case 3:
                if (hitungSubtotal() == 0) {
                    cout << "Belum ada pesanan!\n";
                }
                else {
                    hitungPembayaran();
                    sudahDihitung = true;
                }
                break;

            case 4:
                if (hitungSubtotal() == 0) {
                    cout << "Belum ada pesanan!\n";
                }
                else if (sudahDihitung == false) {
                    cout << "Hitung pembayaran terlebih dahulu!\n";
                }
                else {
                    cout << "\nTotal yang harus dibayar: Rp"
                         << totalBayar << endl;

                    do {
                        uang = inputAngka(
                            "Masukkan uang pembayaran: ", 1000000000
                        );

                        if (uang < totalBayar) {
                            cout << "Uang tidak mencukupi!\n";
                        }

                    } while (uang < totalBayar);

                    cetakStruk(uang);
                    sudahDihitung = false;
                }
                break;

            case 5:
                cout << "\nTerima kasih. Semoga hari Anda menyenangkan!\n";
                break;
        }

    } while (pilihan != 5);

    return 0;
}
