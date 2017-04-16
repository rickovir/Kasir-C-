#include <conio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class ModelData
{
	public:
		void garis(int v)
		{
			for(int i=0;i<v;i++)
				cout<<"-";
			cout<<endl;
		}
		void view_barang()
		{
			int harga, stok, prm=0;
			string nama, kode;
			ifstream baca ("barang.dat");
			cout<<endl;
			garis(48);
			cout<<setw(5)<<"kode"<<setw(3)<<" | "<<setw(15)<<"nama"<<setw(3)<<" | "<<setw(2)<<"    "<< setw(10)<<"harga"<<setw(3)<<" | "<<setw(5)<<"stok"<<endl;
			garis(48);
			while(baca >> kode >> nama >> harga >> stok)
			{
				cout<< setw(5)<<kode<<setw(3)<<" | "<< setw(15)<<nama<<setw(3)<<" | "<<setw(2)<<"Rp. "<< setw(10)<<harga<<setw(3)<<" | "<<setw(5)<<stok<<endl;
			}
			garis(48);
			baca.close();
		}
		
		void delete_barang(string kode)
		{
			int lmharga, lmstok, prm=0;
			string lmnama, lmkode;
			ifstream baca ("barang.dat");
			ofstream tulis ("tmp.dat", ios::app);
			while(baca >> lmkode >> lmnama >> lmharga >> lmstok)
			{
				if(lmkode!= kode )
					tulis<<lmkode<<" \t "<<lmnama<<" \t "<<lmharga<<" \t "<<lmstok<<endl;
			}
			baca.close();
			tulis.close();
			remove("barang.dat");
			rename("tmp.dat","barang.dat");
		}
		
		void update_barang(int harga, int stok, string nama, string kode)
		{
			int lmharga, lmstok;
			string lmnama, lmkode;
			ifstream baca ("barang.dat");
			ofstream tulis ("tmp.dat", ios::app);
			while(baca >> lmkode >> lmnama >> lmharga >> lmstok)
			{
				if(lmkode!= kode )
					tulis<<lmkode<<" \t "<<lmnama<<" \t "<<lmharga<<" \t "<<lmstok<<endl;
				else
					tulis<<lmkode<<" \t "<<nama<<" \t "<<harga<<" \t "<<stok<<endl;
			}
			baca.close();
			tulis.close();
			remove("barang.dat");
			rename("tmp.dat","barang.dat");
		}
		
		void insert_barang(int harga, int stok, string nama, string kode)
		{
			ofstream tulis;
			tulis.open("barang.dat", ios::app);
			tulis<<kode<<" \t "<<nama<<" \t "<<harga<<" \t "<<stok<<endl;
			tulis.close();
		}
		
		void search_barang(string kode)
		{
			int lmharga, lmstok, prm=0;
			string lmnama, lmkode;
			ifstream baca ("barang.dat");
			while(baca >> lmkode >> lmnama >> lmharga >> lmstok)
			{
				if(lmkode == kode )
				{
					prm++;
					break;
				}
			}
			if(prm>0)
			{
				cout<<"Ditemukan data dengan Kode = '"<<kode<<"'\n"<<endl;
				cout<<setw(5)<<"kode"<<setw(20)<<"nama"<<setw(15)<<"harga"<<setw(5)<<"stok"<<endl;
				cout<< setw(5)<<kode<< setw(20)<<lmnama<< setw(15)<<lmharga<<setw(5)<<lmstok<<endl;
			}
			else 
			{
				cout<<"Barang dengan Kode = '"<<kode<<"' kosong\n";
			}
		}
};
