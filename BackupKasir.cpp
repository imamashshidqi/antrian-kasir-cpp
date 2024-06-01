#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

struct belanjaan {
    string nmBarang;
    float hargaBarang;
};

struct kasir {
    string nmPembeli;
    float uangSetor;
    stack<belanjaan> keranjang;
    kasir *next;
};

kasir *head = NULL, *tail = NULL, *cur = NULL;

void tambahKeranjang(stack<belanjaan> &keranjang, string nmBarang, float hargaBarang) {
    belanjaan barang;
    barang.nmBarang = nmBarang;
    barang.hargaBarang = hargaBarang;
    keranjang.push(barang);
}

void buatAntrian(string nmPembeli, float uangSetor, stack<belanjaan> keranjang) {
    kasir *newNode = new kasir();
    newNode->nmPembeli = nmPembeli;
    newNode->uangSetor = uangSetor;
    newNode->keranjang = keranjang;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = head;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void cetakAntrian() {
    system("cls");

    ofstream cetakStruck;
    cetakStruck.open("backupAntrian.txt");
    cur = head;
    int i = 1;
    while (cur != NULL) {
        cout << "Antrian ke-" << i << endl;
        cetakStruck << "Antrian ke-" << i << endl;
        cout << "Nama pembeli: " << cur->nmPembeli << endl;
        cetakStruck << "Nama pembeli: " << cur->nmPembeli << endl;
        cout << "Uang di setor: " << cur->uangSetor << endl << endl;
        cetakStruck << "Uang di setor: " << cur->uangSetor << endl << endl;

        float totalHarga = 0;
        if (!cur->keranjang.empty()) {
            cout << "Isi keranjang: " << endl;
            stack<belanjaan> tempKeranjang = cur->keranjang;
            while (!tempKeranjang.empty()) {
                belanjaan currentBarang = tempKeranjang.top();
                cout << currentBarang.nmBarang << " Rp." << currentBarang.hargaBarang << endl;
                cetakStruck << currentBarang.nmBarang << " Rp." << currentBarang.hargaBarang << endl;
                totalHarga += currentBarang.hargaBarang;
                tempKeranjang.pop();
            }
        } else {
            cout << "Keranjang Kosong!" << endl;
        }

        float kembali = cur->uangSetor - totalHarga;

        cout << "\nTotal harga belanja Rp." << totalHarga << endl;
        cetakStruck << "Total harga belanja Rp." << totalHarga << endl;
        cout << "Uang kembalian Rp." << kembali << endl;
        cetakStruck << "Uang kembalian Rp." << kembali << endl;
        cout << "--------------------------------------" << endl << endl;
        cetakStruck << "--------------------------------------" << endl << endl;

        cur = cur->next;
        i++;
    }
}

int main() {
    int brpAntrian;

    cout << "Berapa antrian yang dibutuhkan?: "; cin >> brpAntrian;
    for (int i = 0; i < brpAntrian; i++) {
        system("cls");
        string nmPembeli, nmBarang;
        float setor, hargaBarang;
        stack<belanjaan> keranjang;
        cout << "Antrian ke-" << i + 1 << endl;
        cout << "Nama pembeli: "; cin.ignore(); getline(cin, nmPembeli);
        cout << "Uang di Setor: "; cin >> setor;

        char lanjut;
        do {
            cout << "Nama barang belanja: "; cin.ignore(); getline(cin, nmBarang);
            cout << "Harga barang belanja: "; cin >> hargaBarang;
            tambahKeranjang(keranjang, nmBarang, hargaBarang);

            cout << "\nBarang berhasil ditambahkan ke Keranjang" << endl;
            cout << "Apakah Anda ingin menambahkan barang lagi? (Y/y): ";
            cin >> lanjut;
        } while (lanjut == 'y' || lanjut == 'Y');

        buatAntrian(nmPembeli, setor, keranjang);
    }

    cetakAntrian();

    return 0;
}
