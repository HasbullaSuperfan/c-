#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <ctime>

using namespace std;

int genereeri_juhuarv(int juhuarv){
	juhuarv = rand()%juhuarv;
	return juhuarv;
}

string suurtaht(string sone){
	string suurtahtedena;
	for(int i = 0; i <= 4; i++){
		suurtahtedena += toupper(sone[i]);
	}
	return suurtahtedena;
}

string vali_sona(string* sone_massiiv, int sonade_arv){
	int juhuarv = genereeri_juhuarv(sonade_arv);
	string valitud_sone = sone_massiiv[juhuarv];
	valitud_sone = suurtaht(valitud_sone);
	return valitud_sone;
}

int salvesta_massiivi(string*& sone_massiiv, string failinimi){
	ifstream sisend(failinimi.c_str());
	int sonade_arv;
	string sone, taht;
	if(sisend.is_open()){
		sisend >> sonade_arv;
		sone_massiiv = new string[sonade_arv+1];
		for(int i = 0; i <= sonade_arv; ++i){
			getline(sisend, sone);
			sone_massiiv[i] = sone;
		}
	}
	else{
		cout << "VIGA" << endl;
	}
	return sonade_arv;
}

bool on_tahed(string sone){
	return sone.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
}

bool sone_kontroll(string sone, string* pakkumised, int sonade_arv1){
	bool kontroll = true;
	if(sone.length() != 5){
		kontroll = false;
	}
	else if(on_tahed(sone)==false){
		kontroll = false;
	}
	//ei kuulu lubatud pakkumiste hulka
	else{
		for(int i = 0; i <= sonade_arv1; ++i){
			if(pakkumised[i] != sone){
				kontroll = false;
				cout << "ise oled neegeer" << endl;
			}
		}
	}
	return kontroll;
}

string loe_pakkumine(){
	cout << "Sisesta sona!" << endl;
	string sone;
	getline(cin, sone);
	return sone;
}

int main(){
	srand(time(0));
	string* lahendused = nullptr;
	string* pakkumised = nullptr;

	string sone = loe_pakkumine();

	string arvatav_sone = {'_','_','_','_','_'};
	int sonade_arv = salvesta_massiivi(lahendused, "lahendused.txt");
	string valitud_sone = vali_sona(lahendused, sonade_arv);
	int sonade_arv1 = salvesta_massiivi(pakkumised, "pakkumised.txt");

	bool kontroll = sone_kontroll(sone, pakkumised, sonade_arv1);

	delete[] lahendused;
	delete[] pakkumised;
	return 0;
}
