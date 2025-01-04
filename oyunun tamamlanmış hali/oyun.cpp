#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Soyutlama: Basket ve Oyuncu için soyut sınıflar
class Basket {
public:
    virtual void showInfo() = 0;  // Soyut metot
    virtual bool atisGerceklestir(int oyuncuPozisyonu, int oyuncuMesafesi) = 0;
};

// Pota şutları ve pozisyonlarıyla ilgili sınıf
class PotayaAtis : public Basket {
private:
    int potaMesafesi;
    int potaPozisyonu; // 0: Sağ, 1: Sol, 2: Orta, 3: Uzun

public:
    PotayaAtis() {
        // Rastgele pota pozisyonu ve mesafesi belirleme
        potaPozisyonu = rand() % 4; // 0, 1, 2, veya 3 (4 farklı nokta)
        potaMesafesi = rand() % 10 + 5; // 5 ile 15 arasında mesafe
    }

    void showInfo() override {
        cout << "Pota pozisyonu: ";
        switch (potaPozisyonu) {
            case 0: cout << "Sağ"; break;
            case 1: cout << "Sol"; break;
            case 2: cout << "Orta"; break;
            case 3: cout << "Uzun"; break;
        }
        cout << endl;
        cout << "Pota mesafesi: " << potaMesafesi << " metre" << endl;
    }

    bool atisGerceklestir(int oyuncuPozisyonu, int oyuncuMesafesi) override {
        // Başarı olasılığını artırmak için daha geniş bir mesafe aralığı kontrol et
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
    int pozisyon; // 0: Sag, 1: Sol, 2: Orta, 3: Uzun
    int mesafe;   // Şut mesafesi (5 ile 15 arasında)
    int puan;     // Şutlardan elde edilen toplam puan

public:
    Oyuncu(string ad) : isim(ad), puan(0) {
        // Oyuncuya rastgele pozisyon ve mesafe atama
        pozisyon = rand() % 4; // 0, 1, 2, 3 (4 farklı nokta)
        mesafe = rand() % 11 + 5; // 5 ile 15 arasında mesafe
    }

    void showInfo() {
        cout << "Oyuncu: " << isim << endl;
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

    // Enkapsülasyon: Getter metodları
    int getPozisyon() {
        return pozisyon;
    }

    int getMesafe() {
        return mesafe;
    }

    int getPuan() {
        return puan;
    }

    // Oyuncunun yeni pozisyon seçmesi
    void pozisyonSec() {
        cout << "Pozisyon Secin (0: Sag, 1: Sol, 2: Orta, 3: Uzun): ";
        cin >> pozisyon;
        if (pozisyon < 0 || pozisyon > 3) {
            cout << "Gecersiz pozisyon! Sag, Sol, Orta veya Uzun arasinda bir deger girin." << endl;
            pozisyonSec();  // Hatalı giriş yaparsa tekrar dene
        }
    }

    // Puan ekleme
    void puanEkle() {
        puan++;
    }
};

class BasketbolOyunu {
private:
    Oyuncu oyuncu1;
    Oyuncu oyuncu2;
    PotayaAtis pota;

public:
    BasketbolOyunu(string isim1, string isim2) : oyuncu1(isim1), oyuncu2(isim2) {}

    void oyuncuSutHaklariniGerceklestir(Oyuncu &oyuncu) {
        for (int i = 0; i < 3; ++i) {
            pota = PotayaAtis(); // Yeni bir pota oluştur
            pota.showInfo();

            oyuncu.showInfo();
            oyuncu.pozisyonSec();
            int oyuncuPozisyonu = oyuncu.getPozisyon();
            int oyuncuMesafesi = oyuncu.getMesafe();

            cout << "Sut atilacak nokta: ";
            switch (oyuncuPozisyonu) {
                case 0: cout << "Sag" << endl; break;
                case 1: cout << "Sol" << endl; break;
                case 2: cout << "Orta" << endl; break;
                case 3: cout << "Uzun" << endl; break;
            }
            cout << "Mesafe: " << oyuncuMesafesi << " metre" << endl;

            // Şutun başarılı olup olmadığını kontrol et
            if (pota.atisGerceklestir(oyuncuPozisyonu, oyuncuMesafesi)) {
                cout << "Sut Basarili! Potaya attiniz." << endl;
                oyuncu.puanEkle();
            } else {
                cout << "Sut Basarisiz! Potaya atamadiniz." << endl;
            }
        }

        cout << "Toplam Puan: " << oyuncu.getPuan() << endl;
    }

    void oyunuBaslat() {
        cout << "Oyunu baslatmak icin hazir olun!" << endl;

        // Oyuncuların şutlarını gerçekleştir
        cout << "\n1. Oyuncu:" << endl;
        oyuncuSutHaklariniGerceklestir(oyuncu1);
        cout << "\n2. Oyuncu:" << endl;
        oyuncuSutHaklariniGerceklestir(oyuncu2);

        // Kazananı belirleme
        if (oyuncu1.getPuan() > oyuncu2.getPuan()) {
            cout << "\nKazanan: " << oyuncu1.getPuan() << " puan ile Oyuncu 1" << endl;
        } else if (oyuncu2.getPuan() > oyuncu1.getPuan()) {
            cout << "\nKazanan: " << oyuncu2.getPuan() << " puan ile Oyuncu 2" << endl;
        } else {
            cout << "\nBeraberlik!" << endl;
        }
    }
};

int main() {
    srand(time(0));  // Rastgele sayı üreticisini başlat

    BasketbolOyunu oyun("Batuhan", "Beyza");
    oyun.oyunuBaslat();

    return 0;
}