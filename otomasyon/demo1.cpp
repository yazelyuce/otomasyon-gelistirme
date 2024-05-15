#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Ürün struct'ı
struct Urun {
    int ID;
    string ad;
    double fiyat;
    Urun* next;
};

// Ürün takip sistemi sınıfı
class UrunTakipSistemi {
private:
    Urun* bas;

public:
    UrunTakipSistemi() : bas(nullptr) {}

    // Ürün ekleme
    void urunEkle(int ID, string ad, double fiyat) {
        Urun* yeniUrun = new Urun();
        yeniUrun->ID = ID;
        yeniUrun->ad = ad;
        yeniUrun->fiyat = fiyat;
        yeniUrun->next = nullptr;

        if (bas == nullptr) {
            bas = yeniUrun;
        } else {
            Urun* temp = bas;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = yeniUrun;
        }
        cout << "Urun basariyla eklendi.\n";
    }

    
	// Ürün silme
void urunSil(int ID) {
    if (bas == nullptr) {
        cout << "Liste bos. Silinecek urun bulunamadi.\n";
        return;
    }

    // Eğer silinecek ürün listenin başındaysa
    if (bas->ID == ID) {
        Urun* silinecek = bas;
        bas = bas->next;
        delete silinecek;
        cout << "Urun basariyla silindi.\n";
        return;
    }

    // Eğer silinecek ürün listenin başında değilse
    Urun* onceki = bas;
    Urun* simdiki = bas->next;
    while (simdiki != nullptr) {
        if (simdiki->ID == ID) {
            onceki->next = simdiki->next;
            delete simdiki;
            cout << "Urun basariyla silindi.\n";
            return;
        }
        onceki = simdiki;
        simdiki = simdiki->next;
    }

    // Eğer silinecek ürün bulunamazsa
    cout << "Belirtilen ID ile urun bulunamadi.\n";
}

	// Ürün güncelleme
void urunGuncelle(int ID, string yeniAd, double yeniFiyat) {
    Urun* temp = bas;
    while (temp != nullptr) {
        if (temp->ID == ID) {
            temp->ad = yeniAd;
            temp->fiyat = yeniFiyat;
            cout << "Urun basariyla guncellendi.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Belirtilen ID ile urun bulunamadi.\n";
}

	// Ürün arama
void urunAra(int ID) {
    Urun* temp = bas;
    while (temp != nullptr) {
        if (temp->ID == ID) {
            cout << "Urun ID: " << temp->ID << endl;
            cout << "Urun Adi: " << temp->ad << endl;
            cout << "Urun Fiyati: " << temp->fiyat << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Belirtilen ID ile urun bulunamadi.\n";
}

	// Aranan elemanı tüm özellikleriyle yazdır
void urunDetaylariylaYazdir(int ID) {
    Urun* temp = bas;
    while (temp != nullptr) {
        if (temp->ID == ID) {
            cout << "Urun ID: " << temp->ID << endl;
            cout << "Urun Adi: " << temp->ad << endl;
            cout << "Urun Fiyati: " << temp->fiyat << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Belirtilen ID ile urun bulunamadi.\n";
}

	// Tüm ürünleri yazdır
void tumUrunleriYazdir() {
    if (bas == nullptr) {
        cout << "Liste bos.\n";
        return;
    }

    cout << "----- Tum Urunler -----\n";
    Urun* temp = bas;
    while (temp != nullptr) {
        cout << "Urun ID: " << temp->ID << endl;
        cout << "Urun Adi: " << temp->ad << endl;
        cout << "Urun Fiyati: " << temp->fiyat << endl;
        cout << "------------------------\n";
        temp = temp->next;
    }
}

	// Ürün fiyatlarını küçükten büyüğe sırala
void urunFiyatlariniSirala() {
    if (bas == nullptr) {
        cout << "Liste bos.\n";
        return;
    }

    // Ürün fiyatlarını saklayacak bir dizi oluştur
    int urunSayisi = 0;
    Urun* temp = bas;
    while (temp != nullptr) {
        urunSayisi++;
        temp = temp->next;
    }
    double* fiyatlar = new double[urunSayisi];

    // Diziyi doldur
    temp = bas;
    for (int i = 0; i < urunSayisi; i++) {
        fiyatlar[i] = temp->fiyat;
        temp = temp->next;
    }

    // Fiyatları küçükten büyüğe sırala
    sort(fiyatlar, fiyatlar + urunSayisi);

    // Sıralanmış fiyatları yazdır
    cout << "----- Urun Fiyatlari (Kucukten Buyuge) -----\n";
    for (int i = 0; i < urunSayisi; i++) {
        cout << fiyatlar[i] << endl;
    }

    delete[] fiyatlar; // Belleği serbest bırak
}

	// Tüm ürünlerin toplam maliyetini hesapla
double toplamMaliyetHesapla() {
    double toplamMaliyet = 0.0;
    Urun* temp = bas;
    while (temp != nullptr) {
        toplamMaliyet += temp->fiyat;
        temp = temp->next;
    }
    return toplamMaliyet;
}

	// Tüm ürünlere %10 zam yap
void zamYap() {
    Urun* temp = bas;
    while (temp != nullptr) {
        temp->fiyat *= 1.1; // Her ürünün fiyatını %10 artır
        temp = temp->next;
    }
    cout << "Urunlere %10 zam yapildi.\n";
}

	// Minimum maliyete sahip ürünü getir
Urun* minMaliyetliUrunuGetir() {
    if (bas == nullptr) {
        cout << "Liste bos.\n";
        return nullptr;
    }

    Urun* minUrun = bas;
    Urun* temp = bas->next;
    while (temp != nullptr) {
        if (temp->fiyat < minUrun->fiyat) {
            minUrun = temp;
        }
        temp = temp->next;
    }
    return minUrun;
}

	// Maksimum maliyete sahip ürünü getir
Urun* maksMaliyetliUrunuGetir() {
    if (bas == nullptr) {
        cout << "Liste bos.\n";
        return nullptr;
    }

    Urun* maksUrun = bas;
    Urun* temp = bas->next;
    while (temp != nullptr) {
        if (temp->fiyat > maksUrun->fiyat) {
            maksUrun = temp;
        }
        temp = temp->next;
    }
    return maksUrun;
}

	// Girdi olarak alınan ürüne ilişkin aynı maliyetli diğer ürünlerin toplam sayısını bul
int ayniMaliyetliUrunSayisi(double fiyat) {
    int sayac = 0;
    Urun* temp = bas;
    while (temp != nullptr) {
        if (temp->fiyat == fiyat) {
            sayac++;
        }
        temp = temp->next;
    }
    return sayac;
}


// Tüm ürünleri dosyaya yazdır
void tumUrunleriDosyayaYaz(const string& dosyaAdi) {
    ofstream dosya(dosyaAdi);

    if (!dosya.is_open()) {
        cout << "Dosya acilamadi.\n";
        return;
    }

    Urun* temp = bas;
    while (temp != nullptr) {
        dosya << "Urun ID: " << temp->ID << endl;
        dosya << "Urun Adi: " << temp->ad << endl;
        dosya << "Urun Fiyati: " << temp->fiyat << endl;
        dosya << "------------------------\n";
        temp = temp->next;
    }

    dosya.close();
    cout << "Tum urunler dosyaya yazildi.\n";
}

	#include <fstream> // Dosya işlemleri için gerekli

// Dosyadan ürünleri oku ve ekrana yazdır
void urunleriDosyadanOku(const string& dosyaAdi) {
    ifstream dosya(dosyaAdi);

    if (!dosya.is_open()) {
        cout << "Dosya acilamadi.\n";
        return;
    }

    int ID;
    string ad;
    double fiyat;

    cout << "----- Okunan Urunler -----\n";
    while (dosya >> ID >> ad >> fiyat) {
        cout << "Urun ID: " << ID << endl;
        cout << "Urun Adi: " << ad << endl;
        cout << "Urun Fiyati: " << fiyat << endl;
        cout << "------------------------\n";
    }

    dosya.close();
}


	
};

int main() {
    // Uygulama başlangıcında ürün takip sistemi oluşturulacak
    UrunTakipSistemi urunTakip;

    // Ana menüyü oluştur
    int secim;
    while (true) {
        cout << "----- Urun Takip Sistemi -----\n";
        cout << "1. Urun Ekle\n";
        cout << "2. Urun Sil\n";
        cout << "3. Urun Guncelle\n";
        cout << "4. Listede Urun Ara\n";
        cout << "5. Aranan Urunu Yazdir\n";
        cout << "6. Tum Urunleri Yazdir\n";
        cout << "7. Urun Fiyatlarini Sirala\n";
        cout << "8. Tum Urunlerin Maliyetini Hesapla\n";
        cout << "9. Urunlere Zam Yap\n";
        cout << "10. Minimum Maliyetli Urunu Getir\n";
        cout << "11. Maksimum Maliyetli Urunu Getir\n";
        cout << "12. Ayni Maliyetli Urunlerin Sayisini Bul\n";
        cout << "13. Urunleri Dosyaya Yazdir\n";
        cout << "14. Dosyadan Urunleri Oku\n";
        cout << "15. Cikis\n";
        cout << "Seciminizi yapin: ";
        cin >> secim;

        switch (secim) {
            case 1: {
                // Ürün ekle işlevi
                int ID;
                string ad;
                double fiyat;
                cout << "Urun ID: ";
                cin >> ID;
                cout << "Urun Adi: ";
                cin.ignore();
                getline(cin, ad);
                cout << "Urun Fiyati: ";
                cin >> fiyat;
                urunTakip.urunEkle(ID, ad, fiyat);
                break;
            }
            case 2: {
				// Ürün sil işlevi
				int silinecekID;
				cout << "Silinecek urunun ID'sini girin: ";
				cin >> silinecekID;
				urunTakip.urunSil(silinecekID);
				break;
			}
            case 3: {
				// Ürün güncelle işlevi
				int guncellenecekID;
				string yeniAd;
				double yeniFiyat;
				cout << "Guncellenecek urunun ID'sini girin: ";
				cin >> guncellenecekID;
				cout << "Yeni urun adi: ";
				cin.ignore();
				getline(cin, yeniAd);
				cout << "Yeni urun fiyati: ";
				cin >> yeniFiyat;
				urunTakip.urunGuncelle(guncellenecekID, yeniAd, yeniFiyat);
				break;
			}

            case 4: {
    // Ürün ara işlevi
    int arananID;
    cout << "Aranacak urunun ID'sini girin: ";
    cin >> arananID;
    urunTakip.urunAra(arananID);
    break;
}

            case 5: {
    // Aranan elemanı tüm özellikleriyle yazdır işlevi
    int arananID;
    cout << "Aranan urunun ID'sini girin: ";
    cin >> arananID;
    urunTakip.urunDetaylariylaYazdir(arananID);
    break;
}

           case 6: {
    // Tüm ürünleri yazdır işlevi
    urunTakip.tumUrunleriYazdir();
    break;
}

            case 7: {
    // Ürün fiyatlarını sırala işlevi
    urunTakip.urunFiyatlariniSirala();
    break;
}

            case 8: {
    // Tüm ürünlerin toplam maliyetini hesapla işlevi
    double toplamMaliyet = urunTakip.toplamMaliyetHesapla();
    cout << "Tum urunlerin toplam maliyeti: " << toplamMaliyet << endl;
    break;
}

            case 9: {
    // Tüm ürünlere %10 zam yap işlevi
    urunTakip.zamYap();
    break;
}

            case 10: {
    // Minimum maliyete sahip ürünü getir işlevi
    Urun* minUrun = urunTakip.minMaliyetliUrunuGetir();
    if (minUrun != nullptr) {
        cout << "Minimum maliyetli urun: " << minUrun->ad << " (Fiyat: " << minUrun->fiyat << ")" << endl;
    }
    break;
}

            case 11: {
    // Maksimum maliyete sahip ürünü getir işlevi
    Urun* maksUrun = urunTakip.maksMaliyetliUrunuGetir();
    if (maksUrun != nullptr) {
        cout << "Maksimum maliyetli urun: " << maksUrun->ad << " (Fiyat: " << maksUrun->fiyat << ")" << endl;
    }
    break;
}

            case 12: {
    // Girdi olarak alınan ürüne ilişkin aynı maliyetli diğer ürünlerin toplam sayısını bul işlevi
    double arananFiyat;
    cout << "Ayni maliyetli urunlerin sayisini bulmak istediginiz urunun fiyatini girin: ";
    cin >> arananFiyat;
    int sayac = urunTakip.ayniMaliyetliUrunSayisi(arananFiyat);
    cout << "Girdi olarak alinan fiyata sahip urunlerin sayisi: " << sayac << endl;
    break;
}

            case 13: {
    // Tüm ürünleri dosyaya yazdır işlevi
    string dosyaAdi;
    cout << "Tum urunlerin yazilacagi dosyanin adini girin: ";
    cin >> dosyaAdi;
    urunTakip.tumUrunleriDosyayaYaz(dosyaAdi);
    break;
}

           case 14: {
    // Dosyadan ürünleri oku işlevi
    string dosyaAdi;
    cout << "Okunacak dosyanin adini girin: ";
    cin >> dosyaAdi;
    urunTakip.urunleriDosyadanOku(dosyaAdi);
    break;
}

            case 15:
                // Çıkış işlevi
                return 0;
            default:
                cout << "Gecersiz secim. Lutfen tekrar deneyin.\n";
        }
    }

    return 0;
}
