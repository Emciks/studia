#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

enum class RasaKonia { BRAK = 0, ZIMNOKRWISTY, FOLBLUT, MUSTANG };

class IstotaZywa {
protected:
    string miano;
    int kondycja;
    int maxKondycja;
    int silaKopyta;

public:
    IstotaZywa(string imie, int hp, int sila)
        : miano(imie), kondycja(hp), maxKondycja(hp), silaKopyta(sila) {}

    virtual ~IstotaZywa() = default;

    bool CzyZyje() const { return kondycja > 0; }
    string PodajMiano() const { return miano; }
    int PodajKondycje() const { return kondycja; }
    int PodajSile() const { return silaKopyta; }

    void PrzyjmijCios(int rany) {
        kondycja -= rany;
        if (kondycja < 0) kondycja = 0;
    }
};

class Wierzchowiec : public IstotaZywa {
private:
    RasaKonia rasa;
    int zebraneMarchewki;
    int etapSzlaku;

public:
    Wierzchowiec() : IstotaZywa("Bezimienny", 0, 0), rasa(RasaKonia::BRAK), zebraneMarchewki(10), etapSzlaku(1) {}

    void Wyhoduj(RasaKonia r, string nazwa, int startHp, int startSila) {
        rasa = r;
        miano = nazwa;
        kondycja = startHp;
        maxKondycja = startHp;
        silaKopyta = startSila;
    }

    int SprawdzEtap() const { return etapSzlaku; }
    void RuszajDalej() { etapSzlaku++; }

    int LiczMarchewki() const { return zebraneMarchewki; }
    void DodajMarchewki(int sztuki) { zebraneMarchewki += sztuki; }

    RasaKonia SprawdzRase() const { return rasa; }

    void ZjedzPasze(int kalorie) {
        kondycja = min(maxKondycja, kondycja + kalorie);
    }
    void PelnyWypoczynek() { kondycja = maxKondycja; }
    void PodkujKopyta(int bonus) { silaKopyta += bonus; }
    void ZlamNoge() { kondycja = 0; }

    void PokazKarte() const {
        cout << "\n=================== [ KARTA KONIA ] ===================" << endl;
        cout << " IMIE: " << miano << " | ZDROWIE: " << kondycja << "/" << maxKondycja << " Tchnien" << endl;
        cout << " MOC WYKOPU: " << silaKopyta << " | PRZYSMAKI: " << zebraneMarchewki << " Marchewek" << endl;
        cout << " AKTUALNY KAMIEN MILOWY SZLAKU: [" << etapSzlaku << "/10]" << endl;
        cout << "=======================================================\n" << endl;
    }


    bool ZapiszDoStajni(const string& sciezka) {
        ofstream plik(sciezka);
        if (!plik) return false;
        plik << static_cast<int>(rasa) << "\n" << miano << "\n"
             << kondycja << "\n" << maxKondycja << "\n"
             << zebraneMarchewki << "\n" << silaKopyta << "\n" << etapSzlaku;
        return true;
    }

    bool WyjdzZeStajni(const string& sciezka) {
        ifstream plik(sciezka);
        if (!plik) return false;
        int idRasy;
        if (plik >> idRasy >> miano >> kondycja >> maxKondycja >> zebraneMarchewki >> silaKopyta >> etapSzlaku) {
            rasa = static_cast<RasaKonia>(idRasy);
            return true;
        }
        return false;
    }
};

class SymulatorGolegoSiodla {
private:
    Wierzchowiec naszKon;

    const string plikZasobow = "C:\\Users\\emili\\OneDrive\\Pulpit\\gra\\save.txt";

    void KreacjaKonia() {
        cout << "\n*** TARG KONSKI W KANSAS - WYBIERZ SWOJE PRZEZNACZENIE ***\n";
        cout << "1. [ZIMNOKRWISTY] -> Prawdziwy czolg (Duzo zdrowia, Zdolnosc: Taranowanie - x2 obrazenia)\n";
        cout << "2. [FOLBLUT]      -> Kon wyscigowy (Srednie zdrowie, Zdolnosc: Precyzyjny wykop w splot - +5 dmg)\n";
        cout << "3. [MUSTANG]      -> Dziecko prerii (Dobre zdrowie, Zdolnosc: Wierzgniecie deba - ignoruje cios)\n";
        cout << "Wskaz palcem (1-3): ";

        int wybor;
        if (!(cin >> wybor)) {
            cin.clear(); cin.ignore(1000, '\n'); wybor = 1;
        }

        switch(wybor) {
            case 1: naszKon.Wyhoduj(RasaKonia::ZIMNOKRWISTY, "Gniady", 40, 8); break;
            case 2: naszKon.Wyhoduj(RasaKonia::FOLBLUT, "Strzala", 25, 12); break;
            case 3: naszKon.Wyhoduj(RasaKonia::MUSTANG, "Duch_Prerii", 35, 6); break;
            default:
                cout << "[!] Wybrales dziwnego osla. Domyslnie bierzemy konia Zimnokrwistego.\n";
                naszKon.Wyhoduj(RasaKonia::ZIMNOKRWISTY, "Gniady", 40, 8);
                break;
        }
    }

    void Konfrontacja(IstotaZywa drapieznik) {
        cout << "\n[!] RZENIE GROZY: " << drapieznik.PodajMiano() << " zastepuje ci droge!" << endl;

        while (naszKon.CzyZyje() && drapieznik.CzyZyje()) {
            cout << "\n[Twoje Tchnienia: " << naszKon.PodajKondycje() << "]  vs  [" << drapieznik.PodajMiano() << ": " << drapieznik.PodajKondycje() << "]\n";
            cout << "1. Zwykly wykop z zadu\n2. Uzyj instynktu stada (Specjalna)\nWybierz odruch: ";

            int akcja;
            cin >> akcja;

            int mojeObrazenia = naszKon.PodajSile();
            int wrogieObrazenia = drapieznik.PodajSile();

            if (akcja == 2) {
                switch (naszKon.SprawdzRase()) {
                    case RasaKonia::ZIMNOKRWISTY:
                        cout << "-> SZARZA Z BARKU! Wbijasz sie w napastnika cala masa!" << endl;
                        mojeObrazenia *= 2;
                        break;
                    case RasaKonia::FOLBLUT:
                        cout << "-> KOPNIAK W SZYJE! Trafiasz idealnie w punkt wrazliwy!" << endl;
                        mojeObrazenia += 5;
                        break;
                    case RasaKonia::MUSTANG:
                        cout << "-> UNIK W GORE! Stajesz deba, cios wroga przecina puste powietrze!" << endl;
                        wrogieObrazenia = 0;
                        break;
                    default: break;
                }
            }

            cout << "> Zadajesz " << mojeObrazenia << " uderzen kopytem." << endl;
            drapieznik.PrzyjmijCios(mojeObrazenia);

            if (drapieznik.CzyZyje()) {
                cout << "> " << drapieznik.PodajMiano() << " gryzie cie w pecine za " << wrogieObrazenia << " ran!" << endl;
                naszKon.PrzyjmijCios(wrogieObrazenia);
            }
        }

        if (!naszKon.CzyZyje()) {
            cout << "\n[ Padles z wycienczenia na szlaku... Kruki juz kraza. ]" << endl;
        } else {
            cout << "\n[ ZWYCIESTWO! " << drapieznik.PodajMiano() << " ucieka z podkulonym ogonem. ]" << endl;
        }
    }

public:
    void OdpalSzlak() {
        int wejscie;
        cout << "=== DZIKI SZLAK: OPOWIESC O CZTERECH KOPYTACH ===" << endl;
        cout << "1. Rozpocznij nowa wedrowke" << endl;
        cout << "2. Wroc do ostatniego wodopoju (Wczytaj)" << endl;
        cout << "Wybierz (1-2): ";
        cin >> wejscie;

        if (wejscie == 2) {
            if (naszKon.WyjdzZeStajni(plikZasobow)) {
                cout << "[ Sukces: Kon pamieta te trase. Wznowiono podroz. ]" << endl;
            } else {
                cout << "[ Brak zapisu w stajni. Ruszasz w nieznane od zera. ]" << endl;
                KreacjaKonia();
            }
        } else {
            KreacjaKonia();
        }

        PrzemierzajSzlaki();
    }

    void PrzemierzajSzlaki() {
        int decyzja;

        while (naszKon.CzyZyje() && naszKon.SprawdzEtap() <= 10) {

            naszKon.ZapiszDoStajni(plikZasobow);

            naszKon.PokazKarte();
            cout << ">>> DOCIERASZ DO ETAPU SZLAKU NR " << naszKon.SprawdzEtap() << " <<<" << endl;

            switch (naszKon.SprawdzEtap()) {
                case 1:
                    cout << "Na skraju lasu siedzi stary Bobr: 'Hej, koniu! Dam ci kostke cukru za 5 marchewek.'" << endl;
                    cout << "1. Oddaj marchewki (+10 Zdrowia)\n2. Parsknij i idz dalej\nDecyzja: ";
                    cin >> decyzja;
                    if (decyzja == 1 && naszKon.LiczMarchewki() >= 5) {
                        naszKon.DodajMarchewki(-5);
                        naszKon.ZjedzPasze(10);
                        cout << "> Chrupiesz cukier. Odzyskujesz wigor." << endl;
                    } else {
                        cout << "> Maszerujesz dalej." << endl;
                    }
                    naszKon.RuszajDalej();
                    break;

                case 2:
                    cout << "Na polanie widzisz malego, trzesacego sie kucyka o imieniu Plotka!" << endl;
                    cout << "Plotka rzy rozpaczliwie: 'Goni mnie wataha! Ich przywodca zaraz tu bedzie, zaslon mnie!'" << endl;
                    cout << "1. Stan deba w obronie kucyka (Pomoz)\n2. Udawaj, ze skubiesz trawe (Odmow)\nWybierz: ";
                    cin >> decyzja;
                    if (decyzja == 2) {
                        cout << "Tchorzysz. Chwile pozniej dopada Cie klusownik z dwururka, biorac Cie za losia. Padasz martwy!" << endl;
                        naszKon.ZlamNoge();
                    } else {
                        cout << "Stajesz w rozkroku. Z zarosli wychodzi nienaturalnie wielki wilk!" << endl;
                        naszKon.RuszajDalej();
                    }
                    break;

                case 3:
                    Konfrontacja(IstotaZywa("Basior Srebrnogrzbiety", 30, 8));
                    if(naszKon.CzyZyje()) naszKon.RuszajDalej();
                    break;

                case 4:
                    cout << "Trafiasz na rozbity woz osadnikow. Nikogo nie ma, a z workow wysypal sie zlocisty owies." << endl;
                    cout << "Zgarniasz rownowartosc 20 marchewek!" << endl;
                    naszKon.DodajMarchewki(20);
                    naszKon.RuszajDalej();
                    break;

                case 5:
                    cout << "Z nory pod debem wypada wsciekly Borsuk i rzuca ci sie do pecin!" << endl;
                    Konfrontacja(IstotaZywa("Wsciekly Borsuk", 15, 3));
                    if(naszKon.CzyZyje()) naszKon.RuszajDalej();
                    break;

                case 6:
                    cout << "Odnajdujesz krystalicznie czyste, lesne zrodlo. Pijesz wode i skubiesz koniczyne." << endl;
                    cout << "Magia dzikiej natury leczy wszystkie rany. Masz 100% sil!" << endl;
                    naszKon.PelnyWypoczynek();
                    naszKon.RuszajDalej();
                    break;

                case 7:
                    cout << "Stawiasz kopyto w wysokiej trawie... TRZASK! Wdeptujesz w zardzewiale wnyki." << endl;
                    cout << "Tracisz 5 punktow kondycji." << endl;
                    naszKon.PrzyjmijCios(5);
                    if(naszKon.CzyZyje()) naszKon.RuszajDalej();
                    break;

                case 8:
                    cout << "Spotykasz wedrownego Kowala-Samotnika: 'Znam sie na kopytach. Za 20 marchewek podkuje cie tytanem.'" << endl;
                    cout << "1. Zaplac za podkowy (+5 do sily kopniaka)\n2. Zignoruj czlowieka\nWybierz: ";
                    cin >> decyzja;
                    if (decyzja == 1 && naszKon.LiczMarchewki() >= 20) {
                        naszKon.DodajMarchewki(-20);
                        naszKon.PodkujKopyta(5);
                        cout << "> Twoje kopyta dzwonia teraz zlowrogo o kamienie!" << endl;
                    } else {
                        cout << "> Mijasz go klusem." << endl;
                    }
                    naszKon.RuszajDalej();
                    break;

                case 9:
                    cout << "Waski wawoz blokuje ogromny, stary Niedzwiedz Gawedziarz!" << endl;
                    Konfrontacja(IstotaZywa("Niedzwiedz Grizzly", 45, 6));
                    if(naszKon.CzyZyje()) naszKon.RuszajDalej();
                    break;

                case 10:
                    cout << "Wkraczasz do legendarnej Zielonej Doliny. Na srodku stoi on: okrutny Lapacz Koni z lassem w dloni!" << endl;
                    Konfrontacja(IstotaZywa("Kowboj 'Czarny Bill'", 60, 10));
                    if(naszKon.CzyZyje()) {
                        cout << "\n====================================================================" << endl;
                        cout << " WOLNOSC! Pokonales oprawce! Galopujesz ku zachodzacemu sloncu!" << endl;
                        cout << "====================================================================" << endl;
                        naszKon.RuszajDalej();
                    }
                    break;
            }
        }

        if (!naszKon.CzyZyje()) {
            cout << "\n[ Twoja podroz dobiegla konca. Sprobuj jeszcze raz. ]" << endl;
        }
    }
};

int main() {
    SymulatorGolegoSiodla gra;
    gra.OdpalSzlak();
    return 0;
}