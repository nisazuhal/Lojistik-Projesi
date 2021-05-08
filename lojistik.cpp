#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <algorithm>

using namespace std;

class AracTuru
{
public:
	AracTuru(vector<char>& aracTuruIn) :aracTuru{ aracTuruIn }
	{

	}

	friend ostream& operator<<(ostream& os, Arac &arac)
	{
		AracTuru a1{ arac.getAracTuru() };
		for (int i{ 0 }; i < a1.aracTuru.size(); i++)
		{
			os << a1.aracTuru[i];
		}
		return os;
	}
	
	

private:
	vector<char>aracTuru;
};


class Sofor
{
public:
	Sofor(string isimIn, string soyisimIn) :
		isim{ isimIn }, soyisim{ soyisimIn }
	{

	}

	string getIsim()
	{
		return isim;
	}

	string getSoyIsim()
	{
		return soyisim;
	}

private:
	string isim;
	string soyisim;

};

class Plaka
{
public:
	Plaka(string plaka) {
		if(plaka.size() > 8)
			throw out_of_range("overflow");
		else
		{
			if(stoi(plaka.substr(0, 2)) < 1 || stoi(plaka.substr(0, 2)) > 81)
				throw out_of_range("exceed_or_invalid");
			else
			{
				if((plaka[2] < 'A' || plaka[2] > 'Z'))
					throw out_of_range("invalid");
				else
				{
					if ((stoi(plaka.substr(6, 2)) < 0 || stoi(plaka.substr(6, 2)) > 99))
						throw out_of_range("exceed_or_invalid");
					else
						(*this).plaka = plaka;
				}
			}
		}
	}

	string getPlate()
	{
		return plaka;
	}

private:
	string plaka;

};

enum class YukTuru {
	KURU_YUK,
	GIDA,
	KIMYASAL

};

ostream& operator <<(ostream& out,const YukTuru& yukturu)
{
	if (yukturu == YukTuru::KURU_YUK)
		out << "KURU_YUK";
	else if (yukturu == YukTuru::GIDA)
		out << "GIDA";
	else if (yukturu == YukTuru::KIMYASAL)
		out << "KIMYASAL";
	else
		throw invalid_argument("invalid");
	return out;
}

class Yuk
{
public:
	

	Yuk(const string& yukIsimIn, YukTuru yukTipiIn, int yukHacmiIn, int yukAgirligiIn) :
		yukIsim{ yukIsimIn }, yukTipi{ yukTipiIn }
	{
		setYukHacmi(yukHacmiIn);
		setYukAgirligi(yukAgirligiIn);
	}
	void setYukIsim(const string& yukIsimIn) {
		yukIsim = yukIsimIn;
	}
	string getYukIsim()const {
		return yukIsim;
	}

	void setYukHacmi(int yukHacmiIn) {
		if (yukHacmiIn >= 0)
			yukHacmi = yukHacmiIn;
		else
			throw invalid_argument("0 >= olmali!");
	}
	int getYukHacmi()const {
		return yukHacmi;
	}

	void setYukAgirligi(int yukAgirligiIn) {
		if (yukAgirligiIn >= 0)
			yukAgirligi = yukAgirligiIn;
		else
			throw invalid_argument("0 >= olmali!");
	}
	int getYukAgirligi()const {
		return yukAgirligi;
	}

	void setYukTuru(YukTuru yukTipiIn) {
		yukTipi = yukTipiIn;
	}
	YukTuru getYukTuru() const {
		return yukTipi;
	}
	bool operator <(const Yuk& yuk1) const
	{
		return yukAgirligi < yuk1.yukAgirligi;
	}

	bool operator <(const Yuk& yuk1) const
	{
		return yukHacmi < yuk1.yukHacmi;
	}

	bool operator <(const Yuk& yuk1) const
	{
		return yukIsim < yuk1.yukIsim;
	}

private:
	string yukIsim;
	int yukHacmi;
	int yukAgirligi;
	YukTuru yukTipi;
};


class Arac
{
	friend ostream& operator<<(ostream& out, const Arac& c_arac)
	{
		out << "Plaka: " << c_arac.getPlaka().getPlate() << endl
			<< "Sofor" << c_arac.getAracSofor().getIsim() << " " << c_arac.getAracSofor().getSoyIsim() << endl
			<< "Arac Turu:" << c_arac.getAracTuru() << endl;

		for (auto& ite : c_arac.yukListesi)
		{
			out << "Yuk Adi" << ite.getYukIsim() << endl
				<< "Yuk Turu" << ite.getYukTuru() << endl
				<< "Yuk Hacmi" << ite.getYukHacmi() << endl
				<< "Yuk Agirligi" << ite.getYukAgirligi() << endl;
		}
		return out;
	}


public:

	Arac(Plaka aracPlakaIn, Sofor aracSoforIn, list<Yuk> yukListesiIn, AracTuru aracTuruIn) :
		aracPlaka{ aracPlakaIn },
		aracSofor{ aracSoforIn },
		aracTuru{ aracTuruIn }
	{
		setYukListesi(yukListesiIn);
	}

	virtual ~Arac();

	virtual void setPlaka(Plaka aracPlakaIn) {
		aracPlaka = aracPlakaIn;
	}
	virtual Plaka getPlaka() const {
		return aracPlaka;
	}

	virtual void setAracSofor(Sofor aracSoforIn) {
		aracSofor = aracSoforIn;
	}
	virtual Sofor getAracSofor() const {
		return aracSofor;
	}

	virtual void setYukListesi(list<Yuk> yukListesiIn) {
		yukListesi = yukListesiIn;
	}
	virtual list<Yuk> getYukListesi() const {
		return yukListesi;
	}

	virtual void setAracTuru(AracTuru aracTuruIn) {
		aracTuru = aracTuruIn;
	}
	virtual AracTuru getAracTuru() const {
		return aracTuru;
	}

	virtual void yukEkle(Yuk yukIn) {
		yukListesi.push_back(yukIn);
	}
	virtual void yukBosalt(Yuk yukIn) {
		yukListesi.remove(yukIn);
	}

	virtual void yukTemizle() {
		yukListesi.clear();
	}

	/*virtual void printYuk() {
		for (auto it = m_yukListesi.cbegin(); it != m_yukListesi.cend(); ++it)
			cout << it << ' ' ;
	}*/
	virtual bool bosMu() {
		return yukListesi.empty();
	}
	virtual double toplamHacim()
	{
		double _toplamHacim;
		for (auto& ite : yukListesi)
		{
			_toplamHacim += ite.getYukHacmi();
		}
		return _toplamHacim;
	}

	virtual double toplamAgirlik()
	{
		double _toplamAgirlik;
		for (auto& ite : yukListesi)
		{
			_toplamAgirlik += ite.getYukAgirligi();
		}
		return _toplamAgirlik;
	}

	Arac& operator+=(Arac& aracIn)
	{
		for (auto& ite : aracIn.yukListesi)
		{
			this->yukListesi.push_back(ite);
		}
		return *this;
	}

	Arac& operator-=(Arac& aracIn)
	{
		for (auto& ite : aracIn.yukListesi)
		{
			this->yukListesi.remove(ite);
		}
	}


	void agirlikSiralama(list<Yuk> input)
	{

		input.sort([](const Yuk& yuk1, const Yuk& yuk2)
		{
			if (yuk1.getYukAgirligi() == yuk2.getYukAgirligi())
				return yuk1 < yuk2;
			return yuk1.getYukAgirligi() < yuk2.getYukAgirligi();
		});
	}

	void hacimSiralama(list<Yuk> input)
	{

		input.sort([](const Yuk& yuk1, const Yuk& yuk2)
		{
			if (yuk1.getYukHacmi() == yuk2.getYukHacmi())
				return yuk1 < yuk2;
			return yuk1.getYukHacmi() < yuk2.getYukHacmi();
		});
	}

	void isimSiralama(list<Yuk> input)
	{

		input.sort([](const Yuk& yuk1, const Yuk& yuk2)
		{
			if (yuk1.getYukIsim() == yuk2.getYukIsim())
				return yuk1 < yuk2;
			return yuk1.getYukIsim() < yuk2.getYukIsim();
		});
	}

private:
	Plaka aracPlaka;
	Sofor aracSofor;
	list<Yuk> yukListesi;
	AracTuru aracTuru;
};



class Kamyon :public Arac {
public:

	Kamyon(Plaka plakaIn, Sofor soforIn, list<Yuk> yukListesiIn, AracTuru aracTuruIn, double max) :
		Arac(plakaIn, soforIn, yukListesiIn, aracTuruIn)
	{
		setMaxAgirlik();
	}

	void setMaxAgirlik()
	{
		double maxAgirlikIn = toplamAgirlik();
		if (maxAgirlikIn >= 2000 && maxAgirlikIn <= 10000)
			maxAgirlik = maxAgirlikIn;
		else
			throw out_of_range("Asiri Yukleme");
	}

	double getMaxAgirlik()
	{
		return maxAgirlik;
	}

	

private:
	double maxAgirlik;
};


class Kamyonet :public Arac
{
public:
	Kamyonet(Plaka plakaIn, Sofor soforIn, list<Yuk> yukListesiIn, AracTuru aracTuruIn) :
		Arac(plakaIn, soforIn, yukListesiIn, aracTuruIn)
	{

	}

	void setMaxAgirlik()
	{
		double maxAgirlikIn = toplamAgirlik();
		if (maxAgirlikIn >= 1500 && maxAgirlikIn <= 3000)
			maxAgirlik = maxAgirlikIn;
		else
			throw out_of_range("Asiri Yukleme");
	}

	int getMaxAgirlik()const {
		return maxAgirlik;
	}

private:
	int maxAgirlik;
};
class AcikKasaKamyonet :public Kamyonet
{
public:
	AcikKasaKamyonet(Plaka plakaIn, Sofor soforIn, list<Yuk> yukListesiIn, AracTuru aracTuruIn, int max) :
		Kamyonet(plakaIn, soforIn, yukListesiIn, aracTuruIn)
	{

	}
	/*void setMaxAgirlik(list<Yuk> yukListesiIn) {
		for (auto iterator)	// doldurulacak

	}*/
	
private:

};
class KapaliKasaKamyonet :public Kamyonet
{
public:
	KapaliKasaKamyonet(Plaka plakaIn, Sofor soforIn, list<Yuk> yukListesiIn, AracTuru aracTuruIn, int maxAgirlik, int maxHacim) :
		Kamyonet(plakaIn, soforIn, yukListesiIn, aracTuruIn)
	{

	}

	void setMaxHacim()
	{
		double maxHacimIn = toplamHacim();
		if (maxHacimIn >= 10 && maxHacimIn <= 30)
			maxHacim = maxHacimIn;
		else
			throw out_of_range("Asiri Yukleme");
	}

private:
	int maxHacim;
};
class SogutmaliKasaKamyonet :public KapaliKasaKamyonet
{
public:
	SogutmaliKasaKamyonet(Plaka plakaIn, Sofor soforIn, list<Yuk> yukListesiIn, AracTuru aracTuruIn, int maxAgirlik, int maxHacim, int sicaklik) :
		KapaliKasaKamyonet(plakaIn, soforIn, yukListesiIn, aracTuruIn, maxAgirlik, maxHacim)
	{
		if (sicaklik > -10 || sicaklik < -40)
			throw out_of_range("sicaklik_degerleri_disinda");
		else
			maxSicaklik = sicaklik;
	}

private:
	int maxSicaklik;
};
class TIR: public Arac
{
public:
	TIR(Plaka c_plaka, Sofor c_sofor, list<Yuk> c_yukListesi, AracTuru c_aracTuru,char*dorse,int maxHacim) :
		Arac(c_plaka, c_sofor, c_yukListesi, c_aracTuru), dorse {dorse}
	{

	}

	void setMaxHacim()
	{
		double maxHacimIn = toplamHacim();
		if (maxHacimIn >= 30 && maxHacimIn <= 40)
			maxHacim = maxHacimIn;
		else
			throw out_of_range("Asiri Yukleme");
	}

	void setDorseKod(char) {

	}

	char getDorseKod() {
		return *dorse;
	}

private:
	char* dorse{ NULL };
	int maxHacim;
};


int main() {

	list <Yuk> yukList;

	char* dorse = new char[20];
	YukTuru yukturu = YukTuru::KURU_YUK;
	Plaka p1("25AB789");
	Sofor s1("Leo", "Messi");
	Yuk y1("kavurma", yukturu, 28, 0);
	Yuk y2("nohut", YukTuru::GIDA, 27, 0);
	yukList.push_back(y1);
	yukList.push_back(y2);
	
	vector <char> aracIsim1{'T', 'I', 'R'};
	AracTuru arac1(aracIsim1);

	cout << yukturu;
	cout << arac1;

	

	TIR a(p1, s1, yukList, arac1, dorse, 32);


	delete[] dorse;

	return 0;
}
