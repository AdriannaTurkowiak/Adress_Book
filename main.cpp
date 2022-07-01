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

int rejestrujOsobe (vector <Osoba> &adresaci);
void sprawdzZnakwMenu (char wyborOpcjiWMenu);
void sprawdzZnakwPodmenu (char wyborOpcjWPodmenu);
void wczytajOsobyZPliku (vector <Osoba> &adresaci);
void wyszukajOsobePoImieniu (vector <Osoba> adresaci);
void wyszukajOsobePoNazwisku (vector <Osoba> adresaci);
void wyswietlWszystkieOsoby (vector <Osoba> adresaci);
void zapiszPlik(vector <Osoba> adresaci);
void edytujDane (vector <Osoba> &adresaci);
void usunOsobe (vector <Osoba> &adresaci);
void pokazMenu();

int main() {
    Osoba wszystkieDaneJednejOsoby;
    char wyborOpcjiWMenu;
    int iloscOsobWPliku = 0;
    vector <Osoba> adresaci;
    wczytajOsobyZPliku (adresaci);
    iloscOsobWPliku = adresaci.size();

    while(true) {
        system("cls");

        pokazMenu();
        cin >> wyborOpcjiWMenu;

        sprawdzZnakwMenu (wyborOpcjiWMenu);

        switch (wyborOpcjiWMenu) {

        case '1':
            rejestrujOsobe (adresaci);
            break;
        case '2':
            wyszukajOsobePoImieniu (adresaci);
            break;
        case '3':
            wyszukajOsobePoNazwisku (adresaci);
            break;
        case '4':
            wyswietlWszystkieOsoby (adresaci);
            break;
        case '5':
            usunOsobe (adresaci);
            break;
        case '6':
            edytujDane (adresaci);
            break;
        case '9':
            exit (0);
            break;
        }
    }
    return 0;
}
void pokazMenu() {
        cout << "Witaj w ksiazce adresowej. Wybierz czynnosc wpisujac odpowiedni numer:" << endl;
        cout << endl;
        cout << "1. Dodaj osobe do ksiazki" << endl;
        cout << "2. Wyszukaj w ksiazce osobe o okreslonym imieniu" << endl;
        cout << "3. Wyszukaj w ksiazce osobe o okreslonym nazwisku" << endl;
        cout << "4. Wyswietl wszystkie kontakty znajdujace sie w ksiazce adresowej" << endl;
        cout << "5. Usun wybrana osobe z ksiazki adresowej" << endl;
        cout << "6. Edytuj dane wybranej osoby z ksiazki adresowej" << endl;
        cout << "9. Zakoncz program" << endl;}
void sprawdzZnakwMenu (char wyborOpcjiWMenu) {
    if ((wyborOpcjiWMenu > '0') && (wyborOpcjiWMenu < '7') || (wyborOpcjiWMenu == '9'))
        return;
    else {
        cout << "Wprowadzono bledny znak" << endl;
        cout << endl;
        system("pause");
    }
}
void sprawdzZnakwPodmenu (char wyborOpcjWPodmenu){
    if ((wyborOpcjWPodmenu > '0') && (wyborOpcjWPodmenu < '7'))
    return;
    else
    {cout << "Wprowadzono bledny znak" << endl;
    cout << endl;
    system("pause");
    }
}
int rejestrujOsobe (vector <Osoba> &adresaci) {

    Osoba nowaOsoba;
    string imie, nazwisko, nrTel, email, adres;
    int iloscOsobWPliku = adresaci.size();

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

    if (plikDoZapisu.good()) {

        plikDoZapisu << nowaOsoba.id << "|" << nowaOsoba.imie << "|" << nowaOsoba.nazwisko << "|" << nowaOsoba.nrTel << "|" << nowaOsoba.email << "|" << nowaOsoba.adres << "|" << endl;
        plikDoZapisu.close();
        cout << endl << "Osoba dodana do ksiazki adresowej" << endl;
        system("pause");
        iloscOsobWPliku ++;
    }

    else {
        cout << "Nie moge otworzyc pliku." << endl;
        cout << endl;
        system("pause");
    }
}
void wczytajOsobyZPliku (vector <Osoba> &adresaci){

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
}
void wyszukajOsobePoImieniu (vector <Osoba> adresaci) {

    Osoba nowaOsoba;
    string szukaneImie;

    if (adresaci.size() == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        cout << endl;
        system("pause");

    } else {
        cout << "Podaj imie, jakie chcesz wyszukac: " << endl;
        cin >> szukaneImie;
        bool czyKontaktIstnieje = false;

        if(adresaci.size() !=0) {
            for(int numerOsoby = 0; numerOsoby < (int) adresaci.size(); numerOsoby++) {
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
                    system("pause");
                }
            }
            if(!czyKontaktIstnieje) {
                cout << "Nie ma osoby o takim imieniu w ksiazce adresowej!" << endl;
                cout << endl;
                system("pause");
            }
        }
    }
}
void wyszukajOsobePoNazwisku (vector <Osoba> adresaci) {

    Osoba nowaOsoba;
    string szukaneNazwisko;
    if (adresaci.size() == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        cout << endl;
        system("pause");

    } else {
        cout << "Podaj nazwisko, jakie chcesz wyszukac: " << endl;
        cin >> szukaneNazwisko;
        bool czyKontaktIstnieje = false;

        if(adresaci.size() !=0) {
            for(int numerOsoby = 0; numerOsoby < (int) adresaci.size(); numerOsoby++) {
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
                    system("pause");
                }
            }
            if(!czyKontaktIstnieje) {
                cout << "Nie ma osoby o takim nazwisku w ksiazce adresowej!" << endl;
                cout << endl;
                system("pause");
            }
        }
    }
}
void wyswietlWszystkieOsoby (vector <Osoba> adresaci) {

    if (adresaci.size() == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        cout << endl;
        system("pause");

    } else {

        for(int numerOsoby = 0; numerOsoby < (int) adresaci.size(); numerOsoby++) {

            cout << endl;
            cout << "ID osoby: " << adresaci[numerOsoby].id << endl;
            cout << "Imie: " << adresaci[numerOsoby].imie << endl;
            cout << "Nazwisko: " << adresaci[numerOsoby].nazwisko << endl;
            cout << "Numer telefonu: " << adresaci[numerOsoby].nrTel << endl;
            cout << "Adres e-mail: " << adresaci[numerOsoby].email << endl;
            cout << "Adres zamieszkania: " << adresaci[numerOsoby].adres << endl;
            cout << endl;
        }
        system("pause");
    }
}
void zapiszPlik(vector <Osoba> adresaci) {
    ofstream plik;
    plik.open("KsiazkaAdresowa.txt");
    for(int i = 0; i < (int) adresaci.size(); i++) {

        plik << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].nrTel << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl;
    }
    plik.close();
}
void edytujDane (vector <Osoba> &adresaci) {

    int ID;
    string noweImie, noweNazwisko, nowyNumerTelefonu, nowyEmail, nowyAdres;
    char wyborEdytowanejDanej;

    if (adresaci.size() == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        cout << endl;
        system("pause");

    } else {
        system("cls");
        cout << "Zamierzasz edytowac dane osobowe. Wprowadz ID uzytkownika, ktorego dane chcesz edytowac: " << endl;
        cin >> ID;
        bool czyKontaktIstnieje = false;

        if(adresaci.size() !=0) {
            for(int numerOsoby = 0; numerOsoby < (int) adresaci.size(); numerOsoby++) {
                if (ID == adresaci[numerOsoby].id) {

                    cout << "Wpisz numer danej, jaka chcesz zmienic:" << endl;
                    cout << endl;
                    cout << "1. Edytuj imie" << endl;
                    cout << "2. Edytuj nazwisko" << endl;
                    cout << "3. Edytuj numer telefonu" << endl;
                    cout << "4. Edytuj e-mail" << endl;
                    cout << "5. Edytuj adres" << endl;
                    cout << "6. Powrot do menu" << endl;
                    czyKontaktIstnieje = true;
                    cin >> wyborEdytowanejDanej;

                    sprawdzZnakwPodmenu (wyborEdytowanejDanej);

                    switch (wyborEdytowanejDanej) {

                    case '1': {
                        cout << "Stare imie: " << adresaci[numerOsoby].imie << endl;
                        cout << "Wprowadz nowe imie: ";
                        cin >> noweImie;
                        adresaci[numerOsoby].imie = noweImie;
                        cout << "Imie zostalo zmienione" << endl;
                        cout << endl;
                        system("pause");
                        break;
                    }

                    case '2': {
                        cout << "Stare nazwisko: " << adresaci[numerOsoby].nazwisko << endl;
                        cout << "Wprowadz nowe nazwisko: ";
                        cin >> noweNazwisko;
                        adresaci[numerOsoby].nazwisko = noweNazwisko;
                        cout << "Nazwisko zostalo zmienione" << endl;
                        cout << endl;
                        system("pause");
                        break;
                    }

                    case '3': {
                        cout << "Stary numer telefonu: " << adresaci[numerOsoby].nrTel << endl;
                        cout << "Wprowadz nowy numer telefonu: ";
                        cin >> nowyNumerTelefonu;
                        adresaci[numerOsoby].nrTel = nowyNumerTelefonu;
                        cout << "Numer telefonu zostal zmieniony" << endl;
                        cout << endl;
                        system("pause");
                        break;
                    }

                    case '4': {
                        cout << "Stary e-mail: " << adresaci[numerOsoby].email << endl;
                        cout << "Wprowadz nowy e-mail: ";
                        cin >> nowyEmail;
                        adresaci[numerOsoby].email = nowyEmail;
                        cout << "Adres email zostal zmieniony" << endl;
                        cout << endl;
                        system("pause");
                        break;
                    }

                    case '5': {
                        cout << "Stary e-mail: " << adresaci[numerOsoby].adres << endl;
                        cout << "Wprowadz nowy adres: ";
                        cin.sync();
                        getline(cin, nowyAdres);
                        adresaci[numerOsoby].adres = nowyAdres;
                        cout << "Adres zamieszkania zostal zmieniony" << endl;
                        cout << endl;
                        system("pause");
                        break;
                    }

                    case '6':
                        break;
                    }
                }
            }
        }
        if(!czyKontaktIstnieje) {
            cout << "Nie ma osoby o takim ID w ksiazce adresowej!" << endl;
            cout << endl;
            system("pause");
        }
    }
    zapiszPlik(adresaci);
}
void usunOsobe (vector <Osoba> &adresaci) {
    int ID;
    char wybor;
    string dane;

    if (adresaci.size() == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        cout << endl;
        system("pause");

    } else {

        system("cls");
        cout << "Wprowadz ID uzytkownika, ktorego dane chcesz usunac: " << endl;
        cin >> ID;
        bool czyKontaktIstnieje = false;

        if(adresaci.size() !=0) {
            for(int numerOsoby = 0; numerOsoby < (int) adresaci.size(); numerOsoby++) {
                if (ID == adresaci[numerOsoby].id) {
                    cout << "Czy jestes pewien, ze chcesz usunac dane tej osoby? Wybierz t jesli TAK lub n jesli NIE: " << endl;
                    cin >> wybor;
                    if (wybor == 't') {
                        adresaci.erase(adresaci.begin()+(numerOsoby));
                        cout << "Osoba o ID: " << ID << " zostala usunieta z ksiazki adresowej." << endl;
                        cout << endl;
                        czyKontaktIstnieje = true;
                        system("pause");
                    }
                    else if (wybor == 'n') {
                        cout << "Zrezygnowano z usuwania osoby z ksiazki" << endl;
                        cout << endl;
                        system("pause");
                        return;

                    } else {
                        cout << "Podano niewlasciwy znak!" << endl;
                        cout << endl;
                        system("pause");
                    }
                }
            }
            if(!czyKontaktIstnieje) {
                cout << "Nie ma osoby o takim ID w ksiazce adresowej!" << endl;
                cout << endl;
                system("pause");
            }
        }
    }
    zapiszPlik(adresaci);
}
