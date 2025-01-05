#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// ANSI Renk Kodları
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"

// Basket sınıfı
class Basket {
public:
    virtual void showInfo() = 0; // Soyut metot
    virtual bool atisGerceklestir(int oyuncuPozisyonu, int oyuncuMesafesi) = 0;
};

// Pota şutları ve pozisyonlarıyla ilgili sınıf
class PotayaAtis : public Basket {
private:
    int potaMesafesi;
    int potaPozisyonu; // 0: Sağ, 1: Sol, 2: Orta, 3: Uzun

public:
    PotayaAtis() {
        potaPozisyonu = rand() % 4;           // 0, 1, 2 veya 3
        potaMesafesi = rand() % 10 + 5;       // 5 ile 15 arasında
    }

    void showInfo() override {
        cout << YELLOW << "==== POTAYA ATIS ====" << RESET << endl;
        cout << "Pota pozisyonu: ";
        switch (potaPozisyonu) {
            case 0: cout << "Sag"; break;
            case 1: cout << "Sol"; break;
            case 2: cout << "Orta"; break;
            case 3: cout << "Uzun"; break;
        }
        cout << endl;
        cout << "Pota mesafesi: " << potaMesafesi << " metre" << endl;
    }

    bool atisGerceklestir(int oyuncuPozisyonu, int oyuncuMesafesi) override {
        if (oyuncuPozisyonu == potaPozisyonu && abs(oyuncuMesafesi - potaMesafesi) <= 2) {
            return true; // Şut başarılı
        }
        return false; // Şut başarısız
    }
};

// Oyuncu sınıfı
class Oyuncu {
private:
    string isim;
    int pozisyon; // 0: Sağ, 1: Sol, 2: Orta, 3: Uzun
    int mesafe;   // Şut mesafesi
    int puan;     // Toplam puan

public:
    Oyuncu(string ad) : isim(ad), puan(0) {
        pozisyon = rand() % 4;
        mesafe = rand() % 11 + 5;
    }

    void showInfo() {
        cout << BLUE << "Oyuncu: " << isim << RESET << endl;
        cout << "Pozisyon: ";
        switch (pozisyon) {
            case 0: cout << "Sag"; break;
            case 1: cout << "Sol"; break;
            case 2: cout << "Orta"; break;
            case 3: cout << "Uzun"; break;
        }
        cout << endl;
        cout << "Mesafe: " << mesafe << " metre" << endl;
    }

    int getPozisyon() { return pozisyon; }
    int getMesafe() { return mesafe; }
    int getPuan() { return puan; }

    void pozisyonSec() {
        cout << "Pozisyon seçin (0: Sag, 1: Sol, 2: Orta, 3: Uzun): ";
        cin >> pozisyon;
        if (pozisyon < 0 || pozisyon > 3) {
            cout << RED << "Gecersiz pozisyon!" << RESET << endl;
            pozisyonSec();
        }
    }

    void puanEkle() { puan++; }
};

// Basketbol Oyunu
class BasketbolOyunu {
private:
    Oyuncu oyuncu1;
    Oyuncu oyuncu2;
    PotayaAtis pota;

public:
    BasketbolOyunu(string isim1, string isim2) : oyuncu1(isim1), oyuncu2(isim2) {}

    void oyuncuSutHaklariniGerceklestir(Oyuncu& oyuncu) {
        for (int i = 0; i < 3; ++i) {
            pota = PotayaAtis();
            pota.showInfo();

            oyuncu.showInfo();
            oyuncu.pozisyonSec();
            int oyuncuPozisyonu = oyuncu.getPozisyon();
            int oyuncuMesafesi = oyuncu.getMesafe();

            cout << "\nAtiş Detaylari: " << endl;
            cout << "Sut Atilan Nokta: ";
            switch (oyuncuPozisyonu) {
                case 0: cout << "Sag"; break;
                case 1: cout << "Sol"; break;
                case 2: cout << "Orta"; break;
                case 3: cout << "Uzun"; break;
            }
            cout << endl;
            cout << "Mesafe: " << oyuncuMesafesi << " metre" << endl;

            if (pota.atisGerceklestir(oyuncuPozisyonu, oyuncuMesafesi)) {
                cout << GREEN << "Sut Basarili! Puan Kazandiniz." << RESET << endl;
                oyuncu.puanEkle();
            } else {
                cout << RED << "Sut Basarisiz! Potayi Kacirdiniz." << RESET << endl;
            }
            cout << "-------------------------------" << endl;
        }
        cout << "Toplam Puan: " << oyuncu.getPuan() << endl;
    }

    void oyunuBaslat() {
        cout << YELLOW << "== Basketbol Oyunu Basliyor! ==" << RESET << endl;

        cout << "\n1. Oyuncu:" << endl;
        oyuncuSutHaklariniGerceklestir(oyuncu1);
        cout << "\n2. Oyuncu:" << endl;
        oyuncuSutHaklariniGerceklestir(oyuncu2);

        if (oyuncu1.getPuan() > oyuncu2.getPuan()) {
            cout << GREEN << "\nKazanan: " << oyuncu1.getPuan() << " puan ile Oyuncu 1!" << RESET << endl;
        } else if (oyuncu2.getPuan() > oyuncu1.getPuan()) {
            cout << GREEN << "\nKazanan: " << oyuncu2.getPuan() << " puan ile Oyuncu 2!" << RESET << endl;
        } else {
            cout << YELLOW << "\nBeraberlik!" << RESET << endl;
        }
    }
};

int main() {
    srand(time(0));

    BasketbolOyunu oyun("Batuhan", "Beyza");
    oyun.oyunuBaslat();

    return 0;
}
