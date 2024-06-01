#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

struct produk {
    string nmProduk;
    float hargaProduk;
};

struct kasir {
    string nmPembeli;
    float uangSetor;
    stack<produk> belanjaan;
    kasir *next;
};

kasir *head = NULL, *tail = NULL, *cur = NULL;

void buatAntrian(string namaPembeli, float uangPembeli, stack<produk> &keranjang);
void tambahProduk(stack<produk> &keranjang, string nmProduk, float hargaProduk);
void cetakAntrian();
void printAntrianKe(int posisi, const string &filename);

int main() {
    system("cls");
    int brpAntrian;
    cout << "Selamat datang di (GH) Galau Habis Mart!" << endl;
    cout << "Masukan jumlah antrian: "; cin >> brpAntrian;
    for (int i = 0; i < brpAntrian; i++) {
        system("cls");
        string nmPembeli;
        float uangSetor;
        stack<produk> keranjang;
        cout << "Antrian ke-" << i + 1 << endl;
        cout << "Masukan Nama Pembeli: "; cin.ignore(); getline(cin, nmPembeli);

        string nmProduk;
        float hargaProduk;
        char lanjutBelanja;
        do {
            cout << "Masukan Nama Produk: "; cin.ignore(); getline(cin, nmProduk);
            cout << "Masukan Harga Produk: "; cin >> hargaProduk;
            tambahProduk(keranjang, nmProduk, hargaProduk);

            cout << "Tambahkan Produk Belanjaan! ('Y'/'y'): "; cin >> lanjutBelanja;
        } while (lanjutBelanja == 'y' || lanjutBelanja == 'Y');

        uangSetor = 0;
        buatAntrian(nmPembeli, uangSetor, keranjang);
    }

    cetakAntrian();

    int posisiCari;
    cout << "Masukkan posisi antrian yang ingin diprint (1-" << brpAntrian << "): ";
    cin >> posisiCari;
    string filename;
    cout << "Masukkan nama file untuk menyimpan hasil (contoh: strukBelanja.txt): ";
    cin >> filename;

    printAntrianKe(posisiCari, filename);

    return 0;
}

void buatAntrian(string namaPembeli, float uangPembeli, stack<produk> &keranjang) {
    kasir *antrianBaru = new kasir();
    antrianBaru->nmPembeli = namaPembeli;
    antrianBaru->uangSetor = uangPembeli;
    antrianBaru->belanjaan = keranjang;
    antrianBaru->next = NULL;

    if (head == NULL) {
        head = antrianBaru;
        tail = head;
    } else {
        tail->next = antrianBaru;
        tail = antrianBaru;
    }
}

void tambahProduk(stack<produk> &keranjang, string nmProduk, float hargaProduk) {
    produk belanjaan;
    belanjaan.nmProduk = nmProduk;
    belanjaan.hargaProduk = hargaProduk;
    keranjang.push(belanjaan);
}

void cetakAntrian() {
    system("cls");
    cur = head;
    int i = 1;
    while (cur != NULL) {
        float totalBayar = 0;
        cout << "Antrian Ke-" << i << endl;
        cout << "Nama Pembeli: " << cur->nmPembeli << endl << endl;

        if (!cur->belanjaan.empty()) {
            cout << "Isi Keranjang:" << endl;
            stack<produk> tempKeranjang = cur->belanjaan;
            while (!tempKeranjang.empty()) {
                produk curProduk = tempKeranjang.top();
                cout << curProduk.nmProduk << " Rp." << curProduk.hargaProduk << endl;
                totalBayar += curProduk.hargaProduk;
                tempKeranjang.pop();
            }
        } else {
            cout << "Keranjang Kosong!" << endl;
            cout << "-----------------" << endl << endl;
        }

        cout << "\nTotal Harga Belanja Rp." << totalBayar << endl;
        do {
            cout << "Uang yg di Setor: "; cin >> cur->uangSetor;
            if(cur->uangSetor < totalBayar) {
                cout << "Uang Setor Kurang COK!" << endl;
            }
        } while(cur->uangSetor < totalBayar);

        float kembalian = cur->uangSetor - totalBayar;
        cout << "Uang kembalian Rp." << kembalian << endl << endl;
        cout << "-----------------" << endl << endl;
        cur = cur->next;
        i++;
    }
}

void printAntrianKe(int posisi, const string &filename) {
    cur = head;
    int urutan = 1;
    ofstream printAntrian(filename);

    if (!printAntrian) {
        cerr << "File tidak dapat dibuka!" << endl;
        return;
    }

    while (cur != NULL) {
        if (urutan == posisi) {
            printAntrian << "Antrian Ke-" << urutan << endl;
            printAntrian << "Nama Pembeli: " << cur->nmPembeli << endl << endl;

            float totalBayar = 0;
            if (!cur->belanjaan.empty()) {
                printAntrian << "Isi Keranjang:" << endl;
                stack<produk> tempKeranjang = cur->belanjaan;
                while (!tempKeranjang.empty()) {
                    produk curProduk = tempKeranjang.top();
                    printAntrian << curProduk.nmProduk << " Rp." << curProduk.hargaProduk << endl;
                    totalBayar += curProduk.hargaProduk;
                    tempKeranjang.pop();
                }
            } else {
                printAntrian << "Keranjang Kosong!" << endl;
            }

            printAntrian << "\nTotal Harga Belanja Rp." << totalBayar << endl;
            printAntrian << "Uang yg di Setor Rp." << cur->uangSetor << endl;

            float kembalian = cur->uangSetor - totalBayar;
            printAntrian << "Uang Kembalian Rp." << kembalian << endl << endl;
            printAntrian << "-----------------" << endl << endl;

            break;
        }
        cur = cur->next;
        urutan++;
    }

    if (cur == NULL) {
        printAntrian << "Antrian ke-" << posisi << " tidak ditemukan." << endl;
    }

    printAntrian.close();
}