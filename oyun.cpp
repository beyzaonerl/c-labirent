#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Oyuncu sınıfı
class Oyuncu {
public:
    int saglik;
    int saliriGucu;
    int iksirler;

    Oyuncu() : saglik(100), saliriGucu(20), iksirler(2) {}

    void saldiri() {
        cout << "Saldiriyorsun! Saldiri gucun: " << saliriGucu << endl;
    }

    void iksirKullanimi() {
        if (iksirler > 0) {
            saglik += 30;
            iksirler--;
            cout << "Bir iksir kullandiniz! Saglik: " << saglik << ", Kalan Iksirler: " << iksirler << endl;
        } else {
            cout << "Hiç iksiriniz kalmadi!" << endl;
        }
    }
};

// Düşman sınıfı
class Dusman {
public:
    string tur;
    int saglik;
    int saldiriGucu;

    Dusman(string t, int s, int g) : tur(t), saglik(s), saldiriGucu(g) {}

    void saldiri() {
        cout << tur << " size saldiriyor! Saldiri gücü: " << saldiriGucu << endl;
    }
};

// Oda sınıfı
class Oda {
public:
    string tur;

    Oda(string t) : tur(t) {}

    void odaDurumu() {
        if (tur == "düşman") {
            cout << "Bu odada bir düşman var!" << endl;
        } else if (tur == "hazine") {
            cout << "Bu odada bir hazine buldunuz!" << endl;
        } else {
            cout << "Bu oda bos gorunuyor." << endl;
        }
    }
};

// Oyunun başlangıç kodu
int main() {
    // Rastgelelik için zaman tabanlı seed
    srand(static_cast<unsigned int>(time(0)));

    // Oyuncu oluştur
    Oyuncu oyuncu;

    // Düşman oluştur (örnek)
    Dusman orumcek("Orumcek", 30, 10);

    // Oda oluştur (rastgele bir tür seçelim)
    string odaTur[] = {"düşman", "hazine", "boş"};
    string randomOdaTur = odaTur[rand() % 3];
    Oda oda(randomOdaTur);

    // Hoş geldiniz mesajı
    cout << "Hos geldin macera sever! Zindani kesfetmeye baslayin." << endl;
    cout << "Saglik: " << oyuncu.saglik << ", Saldiri Gucu: " << oyuncu.saliriGucu 
         << ", Iksirler: " << oyuncu.iksirler << endl;

    // Oda açıklaması
    oda.odaDurumu();

    // Eğer odada düşman varsa, dövüş başlat
    if (oda.tur == "dusman") {
        orumcek.saldiri();
        cout << "Ne yapmak istersiniz? (saldir, kac): ";
        string tepki;
        cin >> tepki;

        if (tepki == "saldir") {
            cout << "Orumcege saldiriyorsunuz!" << endl;
            orumcek.saglik -= oyuncu.saliriGucu;
            cout << "Orumcegin kalan sagligi: " << orumcek.saglik << endl;

            if (orumcek.saglik > 0) {
                cout << "Orumcek size saldiriyor!" << endl;
                oyuncu.saglik -= orumcek.saldiriGucu;
                cout << "Kalan sagliginiz: " << oyuncu.saglik << endl;
            } else {
                cout << "Orumcegi yendiniz!" << endl;
            }
        } else if (tepki == "kac") {
            cout << "Kacmayi deniyorsunuz..." << endl;
            if (rand() % 2 == 0) {
                cout << "Basariyla kactiniz!" << endl;
            } else {
                cout << "Kacis başarisiz! Orumcek size saldiriyor!" << endl;
                oyuncu.saglik -= orumcek.saldiriGucu;
                cout << "Kalan sagliginiz: " << oyuncu.saglik << endl;
            }
        }
    } else if (oda.tur == "hazine") {
        cout << "Hazineden bir iksir buldunuz! Iksir sayiniz artiyor." << endl;
        oyuncu.iksirler++;
    }

    // Oyunun son durumu
    cout << "Zindan kesfiniz sona erdi. Saglik: " << oyuncu.saglik << ", Iksirler: " << oyuncu.iksirler << endl;

    return 0;
}
