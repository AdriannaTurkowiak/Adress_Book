#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <sstream>

using namespace std;

struct Osoba {
    int id;
    string imie, nazwisko, nrTel, email, adres;
};

int rejestrujOsobe (vector <Osoba> &adresaci, int iloscOsobWPliku);
vector <Osoba> wczytajOsobyZPliku ();
void wyszukajOsobePoImieniu (vector <Osoba> adresaci);
void wyszukajOsobePoNazwisku (vector <Osoba> adresaci);
void wyswietlWszystkieOsoby (vector <Osoba> adresaci);
void zapiszPlik(vector <Osoba> adresaci);
vector <Osoba> edytujDane (vector <Osoba> adresaci);
vector <Osoba> usunOsobe (vector <Osoba> adresaci);

int main() {
    Osoba wszystkieDaneJednejOsoby;
    int wyborOpcjiWMenu, wyborOpcjiWPodmenu;
    int iloscOsobWPliku = 0, ID = 1;
    vector <Osoba> adresaci;

    adresaci = wczytajOsobyZPliku ();
    iloscOsobWPliku = adresaci.size();

    while(true) {
        system("cls");

        cout << "Witaj w ksiazce adresowej. Wybierz czynnosc wpisujac odpowiedni numer:" << endl;
        cout << endl;
        cout << "1. Dodaj osobe do ksiazki" << endl;
        cout << "2. Wyszukaj w ksiazce osobe o okreslonym imieniu" << endl;
        cout << "3. Wyszukaj w ksiazce osobe o okreslonym nazwisku" << endl;
        cout << "4. Wyswietl wszystkie kontakty znajdujace sie w ksiazce adresowej" << endl;
        cout << "5. Usun wybrana osobe z ksiazki adresowej" << endl;
        cout << "6. Edytuj dane wybranej osoby z ksiazki adresowej" << endl;
        cout << "9. Zakoncz program" << endl;

        cin >> wyborOpcjiWMenu;

        switch (wyborOpcjiWMenu) {

        case 1:
            iloscOsobWPliku = rejestrujOsobe (adresaci, iloscOsobWPliku);
            break;
        case 2:
            wyszukajOsobePoImieniu (adresaci);
            break;
        case 3:
            wyszukajOsobePoNazwisku (adresaci);
            break;
        case 4:
            wyswietlWszystkieOsoby (adresaci);
            break;
        case 5:
            adresaci = usunOsobe (adresaci);
            break;
        case 6:
            adresaci = edytujDane (adresaci);
            break;
        case 9:
            exit (0);
            break;
        }
    }
    return 0;
}

int rejestrujOsobe (vector <Osoba> &adresaci, int iloscOsobWPliku) {

    Osoba nowaOsoba;
    string imie, nazwisko, nrTel, email, adres;
    int id = 0;

    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin >> nrTel;
    cout << "Podaj email: ";
    cin >> email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, adres);

    if (iloscOsobWPliku == 0) {
        nowaOsoba.id = 1;
    } else {
        iloscOsobWPliku = adresaci.size();
        nowaOsoba.id = (adresaci[iloscOsobWPliku-1].id) + 1;
    }

    nowaOsoba.imie = imie;
    nowaOsoba.nazwisko = nazwisko;
    nowaOsoba.nrTel = nrTel;
    nowaOsoba.email = email;
    nowaOsoba.adres = adres;
    adresaci.push_back(nowaOsoba);

    fstream plikDoZapisu;
    plikDoZapisu.open("KsiazkaAdresowa.txt",ios::out | ios::app);

    if (plikDoZapisu.good() == true) {

        plikDoZapisu << nowaOsoba.id << "|" << nowaOsoba.imie << "|" << nowaOsoba.nazwisko << "|" << nowaOsoba.nrTel << "|" << nowaOsoba.email << "|" << nowaOsoba.adres << "|" << endl;
        plikDoZapisu.close();
        cout << endl << "Osoba dodana do ksiazki adresowej" << endl;
        Sleep (1500);
        iloscOsobWPliku ++;
    }

    else {
        cout << "Nie moge otworzyc pliku." << endl;
        system("pause");
    }
    return iloscOsobWPliku;
}

vector <Osoba> wczytajOsobyZPliku () {

    vector <Osoba> adresaci;
    Osoba nowaOsoba;
    fstream plikDoOdczytu;
    plikDoOdczytu.open ("KsiazkaAdresowa.txt", ios::in);

    string liniaOdczytanaZPliku;
    int numerLiniiWPliku = 1;
    int iloscOsobWPliku = 0;

    while(getline(plikDoOdczytu, liniaOdczytanaZPliku)) {

        if (liniaOdczytanaZPliku.empty())
            break;

        vector <string> daneOsobowe;
        stringstream ss(liniaOdczytanaZPliku);

        while (getline(ss, liniaOdczytanaZPliku, '|')) {
            daneOsobowe.push_back(liniaOdczytanaZPliku);
        }

        for (int i = 0; i <= 6; i++) {
            switch (i) {

            case 0:
                nowaOsoba.id = atoi(daneOsobowe[i].c_str());
                break;
            case 1:
                nowaOsoba.imie = daneOsobowe[i];
                break;
            case 2:
                nowaOsoba.nazwisko = daneOsobowe[i];
                break;
            case 3:
                nowaOsoba.nrTel = daneOsobowe[i];
                break;
            case 4:
                nowaOsoba.email = daneOsobowe[i];
                break;
            case 5:
                nowaOsoba.adres = daneOsobowe[i];
                break;
            }

        }
        if (numerLiniiWPliku > 0) {
            iloscOsobWPliku++;
        }
        numerLiniiWPliku ++;
        adresaci.push_back(nowaOsoba);
    }
    plikDoOdczytu.close();
    cout << adresaci.size();
    return adresaci;
}

void wyszukajOsobePoImieniu (vector <Osoba> adresaci) {

    Osoba nowaOsoba;
    string szukaneImie;

    if (adresaci.size() == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        Sleep (1500);
    } else {
        cout << "Podaj imie, jakie chcesz wyszukac: " << endl;
        cin >> szukaneImie;
        bool czyKontaktIstnieje = false;

        if(adresaci.size() !=0) {
            for(int numerOsoby = 0; numerOsoby < adresaci.size(); numerOsoby++) {
                if (szukaneImie == adresaci[numerOsoby].imie) {

                    cout << endl;
                    cout << "ID osoby: " << adresaci[numerOsoby].id << endl;
                    cout << "Imie: " << adresaci[numerOsoby].imie << endl;
                    cout << "Nazwisko: " << adresaci[numerOsoby].nazwisko << endl;
                    cout << "Numer telefonu: " << adresaci[numerOsoby].nrTel << endl;
                    cout << "Adres e-mail: " << adresaci[numerOsoby].email << endl;
                    cout << "Adres zamieszkania: " << adresaci[numerOsoby].adres << endl;
                    cout << endl;
                    czyKontaktIstnieje = true;
                }
            }
            if(!czyKontaktIstnieje) {
                cout << "Nie ma osoby o takim imieniu w ksiazce adresowej!" << endl;
                Sleep(1500);
            }
            Sleep(3000);
        }
    }
}

void wyszukajOsobePoNazwisku (vector <Osoba> adresaci) {

    Osoba nowaOsoba;
    string szukaneNazwisko;
    if (adresaci.size() == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        Sleep (1500);
    } else {
        cout << "Podaj nazwisko, jakie chcesz wyszukac: " << endl;
        cin >> szukaneNazwisko;
        bool czyKontaktIstnieje = false;

        if(adresaci.size() !=0) {
            for(int numerOsoby = 0; numerOsoby < adresaci.size(); numerOsoby++) {
                if (szukaneNazwisko == adresaci[numerOsoby].nazwisko) {

                    cout << endl;
                    cout << "ID osoby: " << adresaci[numerOsoby].id << endl;
                    cout << "Imie: " << adresaci[numerOsoby].imie << endl;
                    cout << "Nazwisko: " << adresaci[numerOsoby].nazwisko << endl;
                    cout << "Numer telefonu: " << adresaci[numerOsoby].nrTel << endl;
                    cout << "Adres e-mail: " << adresaci[numerOsoby].email << endl;
                    cout << "Adres zamieszkania: " << adresaci[numerOsoby].adres << endl;
                    cout << endl;
                    czyKontaktIstnieje = true;
                }
            }
            if(!czyKontaktIstnieje) {
                cout << "Nie ma osoby o takim nazwisku w ksiazce adresowej!" << endl;
                Sleep(1500);
            }
            Sleep(3000);
        }
    }
}

void wyswietlWszystkieOsoby (vector <Osoba> adresaci) {

    if (adresaci.size() == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        Sleep (1500);
    } else {

        for(int numerOsoby = 0; numerOsoby < adresaci.size(); numerOsoby++) {

            cout << endl;
            cout << "ID osoby: " << adresaci[numerOsoby].id << endl;
            cout << "Imie: " << adresaci[numerOsoby].imie << endl;
            cout << "Nazwisko: " << adresaci[numerOsoby].nazwisko << endl;
            cout << "Numer telefonu: " << adresaci[numerOsoby].nrTel << endl;
            cout << "Adres e-mail: " << adresaci[numerOsoby].email << endl;
            cout << "Adres zamieszkania: " << adresaci[numerOsoby].adres << endl;
            cout << endl;
        }
        Sleep(3000);
    }
}

void zapiszPlik(vector <Osoba> adresaci) {
    ofstream plik;
    plik.open("KsiazkaAdresowa.txt");
    for(int i = 0; i < adresaci.size(); i++) {

        plik << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].nrTel << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl;
    }
    plik.close();
}

vector <Osoba> edytujDane (vector <Osoba> adresaci) {

    int ID;
    string noweImie, noweNazwisko, nowyNumerTelefonu, nowyEmail, nowyAdres;
    int wyborEdytowanejDanej;

    if (adresaci.size() == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        Sleep (1500);
    } else {

        system("cls");
        cout << "Zamierzasz edytowac dane osobowe. Wprowadz ID uzytkownika, ktorego dane chcesz edytowac: " << endl;
        cin >> ID;

        cout << "Wpisz numer danej, jaka chcesz zmienic:" << endl;
        cout << endl;
        cout << "1. Edytuj imie" << endl;
        cout << "2. Edytuj nazwisko" << endl;
        cout << "3. Edytuj numer telefonu" << endl;
        cout << "4. Edytuj e-mail" << endl;
        cout << "5. Edytuj adres" << endl;
        cout << "6. Powrot do menu" << endl;
        cin >> wyborEdytowanejDanej;

        for(int numerOsoby = 0; numerOsoby < adresaci.size(); numerOsoby++) {

            if (ID == adresaci[numerOsoby].id) {
                switch (wyborEdytowanejDanej) {

                case 1: {
                    cout << "Stare imie: " << adresaci[numerOsoby].imie << endl;
                    cout << "Wprowadz nowe imie: ";
                    cin >> noweImie;
                    adresaci[numerOsoby].imie = noweImie;
                    cout << "Imie zostalo zmienione";
                    Sleep (1500);
                    break;
                }

                case 2: {
                    cout << "Stare nazwisko: " << adresaci[numerOsoby].nazwisko << endl;
                    cout << "Wprowadz nowe nazwisko: ";
                    cin >> noweNazwisko;
                    adresaci[numerOsoby].nazwisko = noweNazwisko;
                    cout << "Nazwisko zostalo zmienione";
                    Sleep (1500);
                    break;
                }

                case 3: {
                    cout << "Stary numer telefonu: " << adresaci[numerOsoby].nrTel << endl;
                    cout << "Wprowadz nowy numer telefonu: ";
                    cin >> nowyNumerTelefonu;
                    adresaci[numerOsoby].nrTel = nowyNumerTelefonu;
                    cout << "Numer telefonu zostal zmieniony";
                    Sleep (1500);
                    break;
                }

                case 4: {
                    cout << "Stary e-mail: " << adresaci[numerOsoby].email << endl;
                    cout << "Wprowadz nowy e-mail: ";
                    cin >> nowyEmail;
                    adresaci[numerOsoby].email = nowyEmail;
                    cout << "Adres email zostal zmieniony";
                    Sleep (1500);
                    break;
                }

                case 5: {
                    cout << "Stary e-mail: " << adresaci[numerOsoby].adres << endl;
                    cout << "Wprowadz nowy adres: ";
                    cin.sync();
                    getline(cin, nowyAdres);
                    adresaci[numerOsoby].adres = nowyAdres;
                    cout << "Adres zamieszkania zostal zmieniony";
                    Sleep (1500);
                    break;
                }

                case 6:
                    continue;
                }
            }
        }
    }
    zapiszPlik(adresaci);
    return adresaci;
}

vector <Osoba> usunOsobe (vector <Osoba> adresaci) {
    int ID;
    char wybor;
    string dane;

    if (adresaci.size() == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        Sleep (1500);
    } else {

        system("cls");
        cout << "Wprowadz ID uzytkownika, ktorego dane chcesz usunac: " << endl;
        cin >> ID;

        cout << "Czy jestes pewien, ze chcesz usunac dane tej osoby? Wybierz t jesli TAK lub n jesli NIE: " << endl;
        cin >> wybor;

        if (wybor == 't') {
            for(int numerOsoby = 0; numerOsoby < adresaci.size(); numerOsoby++) {
                if (ID == adresaci[numerOsoby].id) {
                    adresaci.erase(adresaci.begin()+(numerOsoby));
                    cout << "Osoba o ID: " << ID << " zostala usunieta z ksiazki adresowej." << endl;
                    Sleep (1500);
                }
            }
        } else if (wybor == 'n') {
            return adresaci;
        } else
            cout << "Podano niewlasciwy znak!" << endl;
        Sleep(1000);
    }
    zapiszPlik(adresaci);
    return adresaci;
}
