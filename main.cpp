#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <iomanip>
#include <stack>
#include <vector>
#include <fstream>
#include <fstream>

using namespace std;

struct Uzytkownik{
    int id;
    string login, haslo;
};
struct Osoba {
    int id, idUzytkownika;
    string imie, nazwisko, nrTel, email, adres;
};

void pokazGlowneMenu();
void sprawdzZnakwMenuGlownym (char wyborOpcjiWMenuGlownym);
void wczytajUzytkownikowZPliku (vector <Uzytkownik> &uzytkownicy);
void rejestrujUzytkowika (vector <Uzytkownik> &uzytkownicy);
int zalogujUzytkownika (vector <Uzytkownik> &uzytkownicy);
void rejestrujAdresata (vector <Osoba> &adresaci, int idUzytkownika, int idOstatniegoAdresata);
void sprawdzZnakwMenuLogowania (char wyborOpcjiWMenu);
void sprawdzZnakwPodmenu (char wyborOpcjWPodmenu);
int wczytajZPlikuAdresatowDlaDanegoUzytkownika (vector <Osoba> &adresaci, int idUzytkownika);
void wyszukajOsobePoImieniu (vector <Osoba> adresaci, int idUzytkownika);
void wyszukajOsobePoNazwisku (vector <Osoba> adresaci);
void wyswietlWszystkieOsoby (vector <Osoba> adresaci);
void zapiszPlikZAdresatamiPoEdycji(vector <Osoba> &adresaci, int idAdresata);
void zapiszPlikZAdresatamiPoUsuwaniu(vector <Osoba> &adresaci, int idAdresata);
void edytujDane (vector <Osoba> &adresaci);
void usunOsobe (vector <Osoba> &adresaci);
void zapiszPlikZUzytkownikami(vector <Uzytkownik> uzytkownicy);
void pokazMenuPoZalogowaniu();
void zmienHasloUzytkownika (vector <Uzytkownik> &uzytkownicy, int idUzytkownika);
void podmienPlik();

int main() {
    vector <Uzytkownik> uzytkownicy;
    vector <Osoba> adresaci;
    char wyborOpcjiMenuGlowne, wyborOpcjiMenuLogowania;
    int idUzytkownika, idOstatniegoAdresata = 0;

    wczytajUzytkownikowZPliku (uzytkownicy);

    while(true) {
        system("cls");

        pokazGlowneMenu();
        cin >> wyborOpcjiMenuGlowne;
        sprawdzZnakwMenuGlownym (wyborOpcjiMenuGlowne);

        if (wyborOpcjiMenuGlowne == '1') {
            rejestrujUzytkowika (uzytkownicy);
        }

        else if (wyborOpcjiMenuGlowne == '2') {
            idUzytkownika = zalogujUzytkownika (uzytkownicy);
            idOstatniegoAdresata = wczytajZPlikuAdresatowDlaDanegoUzytkownika (adresaci, idUzytkownika);

            while (idUzytkownika > 0) {
                system("cls");
                pokazMenuPoZalogowaniu();
                cin >> wyborOpcjiMenuLogowania;
                sprawdzZnakwMenuLogowania (wyborOpcjiMenuLogowania);

                if (wyborOpcjiMenuLogowania == '8') {
                    idUzytkownika = 0;
                    adresaci.clear();
                    cout << "Wylogowano pomyslnie" << endl;
                    system("pause");
                    break;
                }

                switch (wyborOpcjiMenuLogowania) {

                case '1':
                    idOstatniegoAdresata = wczytajZPlikuAdresatowDlaDanegoUzytkownika (adresaci, idUzytkownika);
                    rejestrujAdresata (adresaci, idUzytkownika, idOstatniegoAdresata);
                    break;

                case '2':
                    wyszukajOsobePoImieniu (adresaci, idUzytkownika);
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

                case '7':
                    zmienHasloUzytkownika (uzytkownicy, idUzytkownika);
                    break;
                }
            }
        } else if (wyborOpcjiMenuGlowne == '9') {
            exit (0);
        }
    }
    return 0;
}
void wczytajUzytkownikowZPliku (vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik nowyUzytkownik;
    fstream plikDoOdczytu;
    plikDoOdczytu.open ("Uzytkownicy.txt", ios::in);

    string liniaOdczytanaZPliku;
    int numerLiniiWPliku = 1;
    int iloscOsobWPliku = 0;

    while(getline(plikDoOdczytu, liniaOdczytanaZPliku)) {

        if (liniaOdczytanaZPliku.empty())
            break;

        vector <string> daneUzytkownika;
        stringstream ss(liniaOdczytanaZPliku);

        while (getline(ss, liniaOdczytanaZPliku, '|')) {
            daneUzytkownika.push_back(liniaOdczytanaZPliku);
        }

        for (int i = 0; i < 3; i++) {
            switch (i) {

            case 0:
                nowyUzytkownik.id = atoi(daneUzytkownika[i].c_str());
                break;
            case 1:
                nowyUzytkownik.login = daneUzytkownika[i];
                break;
            case 2:
                nowyUzytkownik.haslo = daneUzytkownika[i];
                break;
            }

        }
        if (numerLiniiWPliku > 0) {
            iloscOsobWPliku++;
        }
        numerLiniiWPliku ++;
        uzytkownicy.push_back(nowyUzytkownik);
    }
    plikDoOdczytu.close();
}
void pokazGlowneMenu(){
    cout << ">>> MENU GLOWNE <<<" << endl;
    cout << "-------------------" << endl;
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "9. Koniec programu" << endl;
    cout << "-------------------" << endl;
    cout << "Twoj wybor: " << endl;
}
void sprawdzZnakwMenuGlownym (char wyborOpcjiWMenuGlownym) {
        if ((wyborOpcjiWMenuGlownym == '1') || (wyborOpcjiWMenuGlownym == '2') || (wyborOpcjiWMenuGlownym == '9'))
        return;
    else {
        cout << "Wprowadzono bledny znak" << endl;
        cout << endl;
        system("pause");
    }
}
void rejestrujUzytkowika (vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik nowyUzytkownik;
    int iloscOsobWPliku = uzytkownicy.size();
    string Login, Haslo;

    fstream plikDoZapisu;
    plikDoZapisu.open("Uzytkownicy.txt",ios::out | ios::app);

    cout << "Podaj nazwe uzytkownika: " << endl;
    cin >> Login;

    if (iloscOsobWPliku == 0) {
        cout << "Podaj haslo: " << endl;
        cin >> Haslo;
        nowyUzytkownik.id = 1;
        nowyUzytkownik.login = Login;
        nowyUzytkownik.haslo = Haslo;
        uzytkownicy.push_back(nowyUzytkownik);

        if (plikDoZapisu.good()) {
            plikDoZapisu << nowyUzytkownik.id << "|" << nowyUzytkownik.login << "|" << nowyUzytkownik.haslo << endl;
            plikDoZapisu.close();
            cout << endl << "Osoba dodana do ksiazki adresowej" << endl;
            system("pause");
            iloscOsobWPliku ++;}

        else {
            cout << "Nie moge otworzyc pliku." << endl;
            cout << endl;
            system("pause");}
            }


    else if(iloscOsobWPliku > 0) {
        int numerOsoby = 0;
        while(numerOsoby < iloscOsobWPliku) {
            if (Login == uzytkownicy[numerOsoby].login) {
                cout << "Uzytkownik o takim loginie jest juz zarejestrowany!" << endl;
                numerOsoby ++;
                system("pause");
                return;
            }

            else {
                numerOsoby ++;
            }
        }

        cout << "Podaj haslo: " << endl;
        cin >> Haslo;
        nowyUzytkownik.id = (uzytkownicy[iloscOsobWPliku-1].id) + 1;
        nowyUzytkownik.login = Login;
        nowyUzytkownik.haslo = Haslo;
        uzytkownicy.push_back(nowyUzytkownik);

        if (plikDoZapisu.good()) {

            plikDoZapisu << nowyUzytkownik.id << "|" << nowyUzytkownik.login << "|" << nowyUzytkownik.haslo << endl;
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
}
int zalogujUzytkownika (vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik nowyUzytkownik;
    int iloscOsobWPliku = uzytkownicy.size();
    string Login, Haslo;

    if (iloscOsobWPliku == 0) {
        cout << "Ksiazka adresowa jest pusta! " << endl;
        system("pause");
        return 0;
    }
    else {
        int numerOsoby = 0;

        cout << "Podaj login: " << endl;
        cin >> Login;

        while(numerOsoby < iloscOsobWPliku) {
            if (Login == uzytkownicy[numerOsoby].login) {
                for (int iloscProb = 0; iloscProb < 3; iloscProb++) {

                    cout << "Podaj haslo. Pozostalo prob: " << 3 - iloscProb << endl;
                    cin >> Haslo;

                    if (Haslo == uzytkownicy[numerOsoby].haslo) {
                        cout << "Zalogowales sie" << endl;
                        system("pause");
                        return uzytkownicy[numerOsoby].id;
                    }
                }
                cout << "Podales 3 razy niepoprawne haslo!" << endl;
                system("pause");
                return 0;
            }
            numerOsoby ++;
        }
        cout << "Nie ma takiej osoby!" << endl;
        system("pause");
    }
    return 0;
}
void pokazMenuPoZalogowaniu() {
        cout << ">>> MENU UZYTKOWNIKA <<<" << endl;
        cout << "------------------------" << endl;
        cout << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj dane adresata" << endl;
        cout << "------------------------" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "8. Wyloguj sie" << endl;
        cout << "------------------------" << endl;
        cout << "Twoj wybor:" << endl;
        }
void sprawdzZnakwMenuLogowania (char wyborOpcjiMenuLogowania) {
    if ((wyborOpcjiMenuLogowania > '0') && (wyborOpcjiMenuLogowania <= '8'))
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
void rejestrujAdresata (vector <Osoba> &adresaci, int idUzytkownika, int idOstatniegoAdresata) {

    Osoba nowaOsoba;
    string imie, nazwisko, nrTel, email, adres;
    string liniaOdczytanaZPliku;
    int numerLiniiWPliku = 1;

    fstream plikDoZapisu;
    plikDoZapisu.open("Adresaci.txt",ios::out | ios::app);

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

    if (idOstatniegoAdresata == 0) {
        nowaOsoba.id = 1;
    } else {
        nowaOsoba.id = idOstatniegoAdresata + 1;
    }
    nowaOsoba.idUzytkownika = idUzytkownika;
    nowaOsoba.imie = imie;
    nowaOsoba.nazwisko = nazwisko;
    nowaOsoba.nrTel = nrTel;
    nowaOsoba.email = email;
    nowaOsoba.adres = adres;
    adresaci.push_back(nowaOsoba);

    if (plikDoZapisu.good()) {

        plikDoZapisu << nowaOsoba.id << "|" << nowaOsoba.idUzytkownika << "|" << nowaOsoba.imie << "|" << nowaOsoba.nazwisko << "|" << nowaOsoba.nrTel << "|" << nowaOsoba.email << "|" << nowaOsoba.adres << "|" << endl;
        plikDoZapisu.close();
        cout << endl << "Osoba dodana do ksiazki adresowej" << endl;
        system("pause");
    }

    else {
        cout << "Nie moge otworzyc pliku." << endl;
        cout << endl;
        system("pause");
    }
    return;
}
int wczytajZPlikuAdresatowDlaDanegoUzytkownika (vector <Osoba> &adresaci, int idUzytkownika){

    Osoba nowaOsoba;
    fstream plikZawierajacyAdresatow;
    plikZawierajacyAdresatow.open ("Adresaci.txt", ios::in);

    string liniaOdczytanaZPliku;
    int numerLiniiWPliku = 1;
    int iloscOsobWPliku = 0;
    int idOstatniegoAdresata = 0;

    while(getline(plikZawierajacyAdresatow, liniaOdczytanaZPliku)) {

        if (liniaOdczytanaZPliku.empty())
            break;

        vector <string> daneOsobowe;
        stringstream ss(liniaOdczytanaZPliku);

        while (getline(ss, liniaOdczytanaZPliku, '|')) {
            daneOsobowe.push_back(liniaOdczytanaZPliku);
        }

        for (int i = 0; i <= 7; i++) {
            switch (i) {

            case 0:
                nowaOsoba.id = atoi(daneOsobowe[i].c_str());
                idOstatniegoAdresata = nowaOsoba.id;
                break;
            case 1:
                nowaOsoba.idUzytkownika = atoi(daneOsobowe[i].c_str());
                if (nowaOsoba.idUzytkownika == idUzytkownika)
                break;
                if (nowaOsoba.idUzytkownika != idUzytkownika)
                {i = 8;
                break;}
           case 2:
                nowaOsoba.imie = daneOsobowe[i];
                break;
            case 3:
                nowaOsoba.nazwisko = daneOsobowe[i];
                break;
            case 4:
                nowaOsoba.nrTel = daneOsobowe[i];
                break;
            case 5:
                nowaOsoba.email = daneOsobowe[i];
                break;
            case 6:
                nowaOsoba.adres = daneOsobowe[i];
                break;
            }
        }
        if (numerLiniiWPliku > 0) {
            iloscOsobWPliku++;
        }
        numerLiniiWPliku ++;

        if (iloscOsobWPliku == 0)
        idOstatniegoAdresata = 0;

         if (nowaOsoba.idUzytkownika == idUzytkownika)
        {adresaci.push_back(nowaOsoba);}}

    plikZawierajacyAdresatow.close();
    return idOstatniegoAdresata;
}
void wyszukajOsobePoImieniu (vector <Osoba> adresaci, int idUzytkownika) {

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
void zapiszPlikZAdresatamiPoEdycji (vector <Osoba> &adresaci, int idAdresata){

    Osoba nowaOsoba;
    fstream plikDoOdczytu;
    ofstream plikDoZapisu;
    plikDoOdczytu.open ("Adresaci.txt", ios::in);
    plikDoZapisu.open("Adresaci_tymczasowy.txt", ios::out);

    string liniaOdczytanaZPliku;
    int numerLiniiWPliku = 1;
    int iloscOsobWPliku = 0;
    int k = 0;
    int l = adresaci.size();

    while(getline(plikDoOdczytu, liniaOdczytanaZPliku)) {

        if (liniaOdczytanaZPliku.empty())
            break;

        vector <string> daneOsobowe;
        stringstream ss(liniaOdczytanaZPliku);

        while (getline(ss, liniaOdczytanaZPliku, '|')) {
            daneOsobowe.push_back(liniaOdczytanaZPliku);
        }

        for (int i = 0; i <= 7; i++) {
            switch (i) {

            case 0:
                nowaOsoba.id = atoi(daneOsobowe[i].c_str());
                if (nowaOsoba.id != idAdresata)
                break;
                if (nowaOsoba.id == idAdresata)
                {i = 8;
                break;}
            case 1:
                nowaOsoba.idUzytkownika = atoi(daneOsobowe[i].c_str());
                break;
            case 2:
                nowaOsoba.imie = daneOsobowe[i];
                break;
            case 3:
                nowaOsoba.nazwisko = daneOsobowe[i];
                break;
            case 4:
                nowaOsoba.nrTel = daneOsobowe[i];
                break;
            case 5:
                nowaOsoba.email = daneOsobowe[i];
                break;
            case 6:
                nowaOsoba.adres = daneOsobowe[i];
                break;
            }
        }
        if (numerLiniiWPliku > 0) {
            iloscOsobWPliku++;
        }
        numerLiniiWPliku ++;
         if (nowaOsoba.id != idAdresata)
           plikDoZapisu << nowaOsoba.id << "|" << nowaOsoba.idUzytkownika << "|" << nowaOsoba.imie << "|" << nowaOsoba.nazwisko << "|" << nowaOsoba.nrTel << "|" << nowaOsoba.email << "|" << nowaOsoba.adres << "|" << endl;
         else {
            for (k = 0; k < l; k ++){
            if (adresaci[k].id == idAdresata)
            plikDoZapisu << adresaci[k].id << "|" << adresaci[k].idUzytkownika << "|" << adresaci[k].imie << "|" << adresaci[k].nazwisko << "|" << adresaci[k].nrTel << "|" << adresaci[k].email << "|" << adresaci[k].adres << "|" << endl;}
        }}

    plikDoOdczytu.close();
    plikDoZapisu.close();

    podmienPlik();
}
void zapiszPlikZAdresatamiPoUsuwaniu (vector <Osoba> &adresaci, int idAdresata){

    Osoba nowaOsoba;
    fstream plikDoOdczytu;
    ofstream plikDoZapisu;
    plikDoOdczytu.open ("Adresaci.txt", ios::in);
    plikDoZapisu.open("Adresaci_tymczasowy.txt", ios::out);

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

        for (int i = 0; i <= 7; i++) {
            switch (i) {

            case 0:
                nowaOsoba.id = atoi(daneOsobowe[i].c_str());
                if (nowaOsoba.id != idAdresata)
                break;
                if (nowaOsoba.id == idAdresata)
                {i = 8;
                break;}
            case 1:
                nowaOsoba.idUzytkownika = atoi(daneOsobowe[i].c_str());
                break;
            case 2:
                nowaOsoba.imie = daneOsobowe[i];
                break;
            case 3:
                nowaOsoba.nazwisko = daneOsobowe[i];
                break;
            case 4:
                nowaOsoba.nrTel = daneOsobowe[i];
                break;
            case 5:
                nowaOsoba.email = daneOsobowe[i];
                break;
            case 6:
                nowaOsoba.adres = daneOsobowe[i];
                break;
            }
        }
        if (numerLiniiWPliku > 0) {
            iloscOsobWPliku++;
        }
        numerLiniiWPliku ++;
         if (nowaOsoba.id != idAdresata)
           plikDoZapisu << nowaOsoba.id << "|" << nowaOsoba.idUzytkownika << "|" << nowaOsoba.imie << "|" << nowaOsoba.nazwisko << "|" << nowaOsoba.nrTel << "|" << nowaOsoba.email << "|" << nowaOsoba.adres << "|" << endl;
         else
            plikDoZapisu <<"";
        }
    plikDoOdczytu.close();
    plikDoZapisu.close();
    podmienPlik();
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
    zapiszPlikZAdresatamiPoEdycji(adresaci, ID);
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
    zapiszPlikZAdresatamiPoUsuwaniu(adresaci, ID);
}
void zapiszPlikZUzytkownikami(vector <Uzytkownik> uzytkownicy) {
    ofstream plik;
    plik.open("Uzytkownicy.txt");
    for(int i = 0; i < (int) uzytkownicy.size(); i++) {

        plik << uzytkownicy[i].id << "|" << uzytkownicy[i].login << "|" << uzytkownicy[i].haslo << endl;
    }
    plik.close();
}
void zmienHasloUzytkownika (vector <Uzytkownik> &uzytkownicy, int idUzytkownika){
    Uzytkownik nowyUzytkownik;
    string stareHaslo, noweHaslo;

    for (int i = 0; i < (int) uzytkownicy.size(); i++)
    {
        if (idUzytkownika == uzytkownicy[i].id){
                stareHaslo = uzytkownicy[i].haslo;
                cout << "Podaj nowe haslo: " << endl;
                cin >> noweHaslo;
                uzytkownicy[i].haslo = noweHaslo;
                cout << "Haslo zostalo zmienione" << endl;
                system("pause");}
}
zapiszPlikZUzytkownikami (uzytkownicy);
}
void podmienPlik(){
    rename("Adresaci_tymczasowy.txt","Adresaci1.txt");
    remove ("Adresaci.txt");
    rename("Adresaci1.txt","Adresaci.txt");
    return;
}
