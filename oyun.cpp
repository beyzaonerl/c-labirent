#include <iostream>
using namespace std;

// Bir sınıf tanımlıyoruz
class Greeter {
public:
    // Merhaba yazan bir üye fonksiyon
    void sayHello() {
        cout << "Merhaba!" << endl;
    }
};

int main() {
    // Greeter sınıfından bir nesne oluştur
    Greeter greeter;

    // Nesne üzerinden fonksiyonu çağır
    greeter.sayHello();

    return 0;
}
