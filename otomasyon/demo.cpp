#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Hasta sınıfı
class Hasta {
public:
	int hastaID;
    string adSoyad;
    string hastalikTuru;
    int oncelikPuani;
	string ameliyatTuru; // Ameliyat türü
    string ameliyatTarihi; // Ameliyat tarihi
	

    Hasta* next; // İleriye yönelik bağlantı
    Hasta* prev; // Geriye yönelik bağlantı

    Hasta(int hastaID, string adSoyad, string hastalikTuru, int oncelikPuani) : hastaID(hastaID), adSoyad(adSoyad), hastalikTuru(hastalikTuru), oncelikPuani(oncelikPuani), next(nullptr), prev(nullptr) {}
};

// Doktor sınıfı
class Doktor {
public:
    string kullaniciAdi;
    string sifre;

    Doktor* next; // İleriye yönelik bağlantı

    Doktor(string kullaniciAdi, string sifre) : kullaniciAdi(kullaniciAdi), sifre(sifre), next(nullptr) {}
};

// Otomasyon sınıfı
class Otomasyon {
private:
    Doktor* doktorlarBas;
    Hasta* hastalarBas;
    int doktorGirisDenemeSayisi; // Doktor giriş deneme sayısını tutmak için bir değişken ekledik
	Doktor* doktorlar[3]; // Örnek olarak 3 doktor için bir dizi tanımladık


public:
    Otomasyon() : doktorlarBas(nullptr), hastalarBas(nullptr) {} 
	
        // Doktor ekleme fonksiyonu
    void doktorEkle(string kullaniciAdi, string sifre) {
        Doktor* yeniDoktor = new Doktor(kullaniciAdi, sifre);
        if (doktorlarBas == nullptr) {
            doktorlarBas = yeniDoktor;
        } else {
            Doktor* iter = doktorlarBas;
            while (iter->next != nullptr) {
                iter = iter->next;
            }
            iter->next = yeniDoktor;
        }
    }
	
	// Doktor bilgilerini gösterme (yardımcı fonksiyon)
    void doktorBilgileriniGoster() {
        Doktor* iter = doktorlarBas;
        while (iter != nullptr) {
            cout << "Kullanici Adi: " << iter->kullaniciAdi << ", Sifre: " << iter->sifre << endl;
            iter = iter->next;
        }
    }
	
	void doktorMenu();
	void hastaEkle(); 
    void hastaSil();
	void hastaDetaylariniGetir();
	void ameliyatEkle();
	void ameliyatSil();
	void ameliyatDetaylariniGetir();
	void ameliyatUcretiniHesapla();
	void anamenuyeDon();
	void cikis();

	 void doktorlariYazdir();
    void tumHastalariYazdir();
    void ameliyatHastalariniYazdir();
    void hastalarinOncelikPuanlariniYazdir();
    void hastaMenu();

	void hastaneyiDegerlendir();

    // Doktor giriş fonksiyonu
    void doktorGiris() {
        int kalanDenemeHakki = 3; // Kullanıcıya 3 deneme hakkı verelim
        while (kalanDenemeHakki > 0) {
            cout << "Kullanici Adi: ";
            string kullaniciAdi;
            cin >> kullaniciAdi;
            cout << "Sifre: ";
            string sifre;
            cin >> sifre;

            // Doktorları dolaşarak doğrulama yapalım
            Doktor* iter = doktorlarBas;
            while (iter != nullptr) {
                if (iter->kullaniciAdi == kullaniciAdi && iter->sifre == sifre) {
                    cout << "Giris basarili. Hosgeldiniz, " << iter->kullaniciAdi << "!\n";
                    //doğru giriş yapıldığında doktor menüsüne yönlendir
                    doktorMenu(); 
                    return;
                }
                iter = iter->next;
            }

            // Eğer doğru giriş yapılmadıysa deneme sayısını azalt
            kalanDenemeHakki--;

            if (kalanDenemeHakki > 0) {
                cout << "Kullanici adi veya sifre yanlis. Tekrar deneyin. Kalan deneme sayisi: " << kalanDenemeHakki << endl;
            } else {
                cout << "Giris hakkiniz doldu. Lutfen daha sonra tekrar deneyin.\n";
                cikis(); // Deneme hakkı dolan kullanıcıyı çıkışa yönlendir
            }
        }
    }
};


// hastaneyi değerlendirme seçeneği
void Otomasyon::hastaneyiDegerlendir() {
    // Mevcut hasta sayısını hesapla
    int hastaSayisi = 0;
    Hasta* iterHasta = hastalarBas;
    while (iterHasta != nullptr) {
        hastaSayisi++;
        iterHasta = iterHasta->next;
    }

    // Ameliyat sayısını ve ameliyat ücretini hesapla
    int ameliyatSayisi = 0;
    int toplamUcret = 0;
    iterHasta = hastalarBas;
    while (iterHasta != nullptr) {
        if (!iterHasta->ameliyatTuru.empty()) {
            ameliyatSayisi++;
            // Ameliyat ücreti: Öncelik puanı * 100
            toplamUcret += iterHasta->oncelikPuani * 100;
        }
        iterHasta = iterHasta->next;
    }

    // Hasta öncelik sayısını hesapla
    // Öncelik sayısı, her hastalık türünün öncelik puanının toplamı olabilir
    // Örnek olarak, aynı hastalık türüne sahip hastaların öncelik puanlarını toplayabiliriz
    // Ancak bu örnek için rastgele öncelik puanları üreteceğiz.
    int toplamOncelik = 0;
    iterHasta = hastalarBas;
    while (iterHasta != nullptr) {
        toplamOncelik += iterHasta->oncelikPuani;
        iterHasta = iterHasta->next;
    }

    // İstatistikleri ekrana yazdır
    cout << "Mevcut Hasta Sayisi: " << hastaSayisi << endl;
    cout << "Ameliyat Sayisi: " << ameliyatSayisi << endl;
    cout << "Toplam Ameliyat Ucreti: " << toplamUcret << " TL" << endl;
    cout << "Hasta Oncelik Sayisi: " << toplamOncelik << endl;
}




// hasta girişi işlevleri
 // Hastane doktorlarını yazdırma işlevi
void Otomasyon::doktorlariYazdir() {
    Doktor* iter = doktorlarBas;
    cout << "Hastane Doktorlari:\n";
    while (iter != nullptr) {
        cout << "Kullanici Adi: " << iter->kullaniciAdi << endl;
        iter = iter->next;
    }
}

// Tüm hastaları yazdırma işlevi
void Otomasyon::tumHastalariYazdir() {
    Hasta* iter = hastalarBas;
    cout << "Tum Hastalar:\n";
    while (iter != nullptr) {
        cout << "Hasta ID: " << iter->hastaID << ", Ad Soyad: " << iter->adSoyad << endl;
        iter = iter->next;
    }
}

// Ameliyat hastalarını yazdırma işlevi
void Otomasyon::ameliyatHastalariniYazdir() {
    Hasta* iter = hastalarBas;
    cout << "Ameliyat Hastalari:\n";
    while (iter != nullptr) {
        if (!iter->ameliyatTuru.empty()) {
            cout << "Hasta ID: " << iter->hastaID << ", Ad Soyad: " << iter->adSoyad << ", Ameliyat Turu: " << iter->ameliyatTuru << endl;
        }
        iter = iter->next;
    }
}

// Tüm hastaların öncelik puanlarını yazdırma işlevi
void Otomasyon::hastalarinOncelikPuanlariniYazdir() {
    Hasta* iter = hastalarBas;
    cout << "Tum Hastalarin Oncelik Puanlari:\n";
    while (iter != nullptr) {
        cout << "Hasta ID: " << iter->hastaID << ", Ad Soyad: " << iter->adSoyad << ", Oncelik Puani: " << iter->oncelikPuani << endl;
        iter = iter->next;
    }
}

// Hasta menüsü
void Otomasyon::hastaMenu() {
    while (true) {
        cout << "\n--- Hasta Menusu ---\n";
        cout << "1. Hastane doktorlarini yazdir\n";
        cout << "2. Tum hastalari yazdir\n";
        cout << "3. Ameliyat hastalarini yazdir\n";
        cout << "4. Tum hastalarin oncelik puanlarini yazdir\n";
        cout << "5. Ana menuye don\n";
        cout << "6. Cikis\n";
        cout << "Seciminizi yapin: ";

        int secim;
        cin >> secim;

        switch (secim) {
            case 1:
                doktorlariYazdir();
                break;
            case 2:
                tumHastalariYazdir();
                break;
            case 3:
                ameliyatHastalariniYazdir();
                break;
            case 4:
                hastalarinOncelikPuanlariniYazdir();
                break;
            case 5:
                return;
            case 6:
                cikis();
                break;
            default:
                cout << "Gecersiz secim. Lutfen tekrar deneyin.\n";
        }
    }
}








    // Doktor menüsü
    void Otomasyon::doktorMenu() {
        cout << "\n--- Doktor Menusu ---\n";
        cout << "1. Hasta Ekle\n";
        cout << "2. ID bilgisi kullanarak hasta sil\n";
        cout << "3. Hasta detaylarini getir\n";
        cout << "4. Ameliyat Ekle\n";
        cout << "5. Ameliyat sil\n";
        cout << "6. Ameliyat detaylarini getir\n";
        cout << "7. ID ye gore ameliyat ucretini hesapla\n";
		
        cout << "8. Ana menuye don\n";
        cout << "9. Cikis\n";
        cout << "Seciminizi yapin: ";

        int secim;
        cin >> secim;

        switch (secim) {
            case 1:
                this->hastaEkle();
                doktorMenu(); // Doktor menüsüne geri dön
                break;
            case 2:
                this->hastaSil();
                doktorMenu(); // Doktor menüsüne geri dön
                break;
            case 3:
                this->hastaDetaylariniGetir();
                doktorMenu(); // Doktor menüsüne geri dön
                break;
            case 4:
                this->ameliyatEkle();
                doktorMenu(); // Doktor menüsüne geri dön
                break;
            case 5:
                this->ameliyatSil();
                doktorMenu(); // Doktor menüsüne geri dön
                break;
            case 6:
                this->ameliyatDetaylariniGetir();
                doktorMenu(); // Doktor menüsüne geri dön
                break;
            case 7:
                this->ameliyatUcretiniHesapla();
                doktorMenu(); // Doktor menüsüne geri dön
                break;
			case 8:
                this->anamenuyeDon();
                break;
            case 9:
                cikis();
                break;
            default:
                cout << "Gecersiz secim. Lutfen tekrar deneyin.\n";
                //doktorMenu(); // Geçersiz seçim durumunda tekrar doktor menüsünü göster
        }
    }

    
		// hasta ekle
		void Otomasyon::hastaEkle() {
		cout << "Hasta ekleme fonksiyonu\n";
		int hastaID;
		string adSoyad, hastalikTuru;
		int oncelikPuani;
		
		cout << "Hasta ID: ";
        cin >> hastaID;
		cout << "Ad Soyad: ";
		cin.ignore(); // getline kullanmadan önce bir önceki girişin tamamlanmasını sağlamak için
		getline(cin, adSoyad);
		cout << "Hastalik Turu: ";
		getline(cin, hastalikTuru);
		cout << "Oncelik Puani: ";
		cin >> oncelikPuani;

		Hasta* yeniHasta = new Hasta(hastaID, adSoyad, hastalikTuru, oncelikPuani);

		// Eğer liste boşsa yeni hasta başa eklenir
		if (hastalarBas == nullptr) {
			hastalarBas = yeniHasta;
		} 
		else {
			Hasta* iter = hastalarBas;
			// Hasta listesini dolaşarak uygun yer bulunur
			while (iter->next != nullptr) {
				iter = iter->next;
			}
			iter->next = yeniHasta; // Yeni hasta listeye eklenir
			yeniHasta->prev = iter; // Yeni hasta ile önceki hasta arasındaki bağlantı kurulur
		}

		cout << "Hasta basariyla eklendi!\n";
}


		// Hasta silme işlevi
		void Otomasyon::hastaSil() {
		if (hastalarBas == nullptr) {
			cout << "Listede silinecek hasta bulunmamaktadir.\n";
			return;
		}

		int silinecekID;
		cout << "Silinecek hasta ID'sini giriniz: ";
		cin >> silinecekID;

			// Listenin başındaki hasta siliniyorsa
		if (hastalarBas->hastaID == silinecekID) {
			Hasta* silinecekHasta = hastalarBas;
			hastalarBas = hastalarBas->next;
        if (hastalarBas != nullptr)
            hastalarBas->prev = nullptr;
        delete silinecekHasta;
        cout << "Hasta basariyla silindi!\n";
        return;
		}

		Hasta* iter = hastalarBas;
		while (iter->next != nullptr && iter->next->hastaID != silinecekID) {
			iter = iter->next;
		}

		if (iter->next == nullptr) {
			cout << "Bu ID'ye sahip bir hasta bulunamadi.\n";
			return;
		}

		Hasta* silinecekHasta = iter->next;
		iter->next = silinecekHasta->next;
		if (silinecekHasta->next != nullptr)
			silinecekHasta->next->prev = iter;
			delete silinecekHasta;
			cout << "Hasta basariyla silindi!\n";
		}

		// Hasta detaylarını getirme fonksiyonu
		void Otomasyon::hastaDetaylariniGetir() {
		if (hastalarBas == nullptr) {
			cout << "Listede hasta bulunmamaktadir.\n";
			return;
		}	
	
		Hasta* iter = hastalarBas;
		while (iter != nullptr) {
        cout << "Hasta ID: " << iter->hastaID << endl;
        cout << "Ad Soyad: " << iter->adSoyad << endl;
        cout << "Hastalik Turu: " << iter->hastalikTuru << endl;
        cout << "Oncelik Puani: " << iter->oncelikPuani << endl;
        cout << "---------------------\n";
        iter = iter->next;
	}
}

		// Ameliyat Ekle
		void Otomasyon::ameliyatEkle() {
		// Öncelikle hasta ID'sini alalım
		int hastaID;
		cout << "Ameliyat yapilacak hasta ID'sini giriniz: ";
		cin >> hastaID;

    // Hasta ID'sine göre hasta bulunur
    Hasta* iter = hastalarBas;
    while (iter != nullptr) {
        if (iter->hastaID == hastaID) {
            // Hasta bulundu, ameliyat bilgileri alınabilir
            string ameliyatTuru, ameliyatTarihi;
            cout << "Ameliyat Turu: ";
            cin >> ameliyatTuru;
            cout << "Ameliyat Tarihi: ";
            cin >> ameliyatTarihi;

            // Hasta nesnesine ameliyat bilgileri eklenir
            iter->ameliyatTuru = ameliyatTuru;
            iter->ameliyatTarihi = ameliyatTarihi;

            cout << "Ameliyat basariyla eklendi!\n";
            return;
        }
        iter = iter->next;
    }

    // Hasta bulunamadıysa
    cout << "Belirtilen ID'ye sahip hasta bulunamadi.\n";
}

// Ameliyat sil
void Otomasyon::ameliyatSil() {
    if (hastalarBas == nullptr) {
        cout << "Listede hasta bulunmamaktadir.\n";
        return;
    }

    int hastaID;
    cout << "Ameliyati silinecek hastanin ID'sini giriniz: ";
    cin >> hastaID;

    // Hasta ID'sine göre hasta bulunur
    Hasta* iter = hastalarBas;
    while (iter != nullptr) {
        if (iter->hastaID == hastaID) {
            // Hasta bulundu, ameliyat bilgilerini sıfırlayalım
            iter->ameliyatTuru = "";
            iter->ameliyatTarihi = "";
            cout << "Hastanin ameliyat bilgileri basariyla silindi!\n";
            return;
        }
        iter = iter->next;
    }

    // Hasta bulunamadıysa
    cout << "Belirtilen ID'ye sahip hasta bulunamadi.\n";
}

// Ameliyat detaylarını getir
void Otomasyon::ameliyatDetaylariniGetir() {
     if (hastalarBas == nullptr) {
        cout << "Listede hasta bulunmamaktadir.\n";
        return;
    }

    Hasta* iter = hastalarBas;
    while (iter != nullptr) {
        cout << "Hasta ID: " << iter->hastaID << endl;
        cout << "Ad Soyad: " << iter->adSoyad << endl;
        cout << "Ameliyat Turu: " << iter->ameliyatTuru << endl;
        cout << "Ameliyat Tarihi: " << iter->ameliyatTarihi << endl;
        cout << "---------------------\n";
        iter = iter->next;
    }
}

// Ameliyat ücretini hesaplama fonksiyonu
void Otomasyon::ameliyatUcretiniHesapla() {
// Öncelikle hasta ID'sini alalım
    int hastaID;
    cout << "Ameliyat yapilacak hasta ID'sini giriniz: ";
    cin >> hastaID;

    // Hasta ID'sine göre hasta bulunur
    Hasta* iter = hastalarBas;
    while (iter != nullptr) {
        if (iter->hastaID == hastaID) {
            // Hasta bulundu, ameliyat bilgilerini alabiliriz
            // Öncelik puanı * 100 şeklinde ameliyat ücretini hesaplayalım
            int ameliyatUcreti = iter->oncelikPuani * 100;

            // Hesaplanan ücreti ekrana yazdıralım
            cout << "Ameliyat Ucreti: " << ameliyatUcreti << " TL\n";
            return;
        }
        iter = iter->next;
    }

    // Hasta bulunamadıysa
    cout << "Belirtilen ID'ye sahip hasta bulunamadi.\n";
}



void Otomasyon::anamenuyeDon() {
	 cout << "\n--- Otomasyon ---\n";
        cout << "1. Doktor Girisi\n";
        cout << "2. Hasta Girisi\n";
        cout << "3. Hastane Degerlendir\n";
        cout << "4. Cikis\n";
        cout << "Seciminizi yapin: ";

   
        int secim;
        cin >> secim;
        switch (secim) {
            case 1:
				 // Doktorlar önceden tanımlanıyor (örnek olarak)
				this->doktorEkle("doktor1", "sifre1");
				this->doktorEkle("doktor2", "sifre2");
				this->doktorEkle("doktor3", "sifre3");

				// Doktor bilgilerini gösterme (test amaçlı)
				this->doktorBilgileriniGoster();

				// Doktor girişi
				this->doktorGiris();
				
                break;
            case 2:
				this->hastaMenu();
                // Hasta girişi
                break;
            case 3:
                this->hastaneyiDegerlendir();
                break;
            case 4:
                this->cikis();
                break;
            default:
                cout << "Gecersiz secim. Lutfen tekrar deneyin.\n";
				anamenuyeDon(); // Geçersiz seçim durumunda tekrar ana menüye yönlendir
        }
    }

void Otomasyon::cikis() {
    cout << "Otomasyondan cikis yapildi.\n";
    exit(0);
}



int main() {
    Otomasyon otomasyon;

 while (true) {
        cout << "\n--- Otomasyon ---\n";
        cout << "1. Doktor Girisi\n";
        cout << "2. Hasta Girisi\n";
        cout << "3. Hastane Degerlendir\n";
        cout << "4. Cikis\n";
        cout << "Seciminizi yapin: ";

   
        int secim;
        cin >> secim;
        switch (secim) {
            case 1:
                // Doktorlar önceden tanımlanıyor (örnek olarak)
				otomasyon.doktorEkle("doktor1", "sifre1");
				otomasyon.doktorEkle("doktor2", "sifre2");
				otomasyon.doktorEkle("doktor3", "sifre3");

				// Doktor bilgilerini gösterme (test amaçlı)
				otomasyon.doktorBilgileriniGoster();

				// Doktor girişi
				otomasyon.doktorGiris();		
                break;
            case 2:
				otomasyon.hastaMenu();
                // Hasta girişi
                break;
            case 3:
                otomasyon.hastaneyiDegerlendir();
                break;
            case 4:
                otomasyon.cikis();
                break;
            default:
                cout << "Gecersiz secim. Lutfen tekrar deneyin.\n";
        }
    }
	otomasyon.cikis();
    return 0;
}