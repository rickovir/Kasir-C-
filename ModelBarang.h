#include <conio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct Barang
{
	string kode;
	string nama;
	int harga;
	Barang *next;
	Barang *prev;
};

class ModelBarang
{
	private:
		Barang *head = NULL, *tail = NULL, *baru, *b1, *b2, *brg;
		
		void garis(int v)
		{
			for(int i=0;i<v;i++)
				cout<<"-";
			cout<<endl;
		}
		
	public:
		void load_data()
		{
			int harga;
			string nama, kode;
			ifstream baca ("barang.dat");
			while(baca >> kode >> nama >> harga)
				insert_barang(harga, nama, kode);
			baca.close();
		}
		
		void backup_data()
		{
			ofstream tulis ("barang.dat");
			brg = head;
			do
			{
				tulis<<brg->kode<<" \t "<<brg->nama<<" \t "<<brg->harga<<endl;
				brg = brg->next;
			}
			while(brg != head);
			tulis.close();
		}
		
		void insert_barang(int harga, string nama, string kode)
		{
			baru = new Barang;
			baru->harga = harga;
			baru->nama = nama;
			baru->kode = kode;
			baru->next = baru;
			baru->prev = baru;
			if(head == NULL)
			{
				head = tail = baru;
			}
			else
			{
				tail->next = baru;
				baru->prev = tail;
				tail = baru;
			}
			tail->next = head;
			head->prev = tail;
		}
		
		void update_barang(int harga, string nama, string kode)
		{
			brg = head;
			do
			{
				if(brg->kode == kode)
				{
					brg->nama = nama;
					brg->harga = harga;
					break;
				}
				else
					brg = brg->next;
			}
			while(brg != head);
		}
		
		void delete_barang(string kode)
		{
			int h = 0;
			brg = head;
			do
			{
				if(brg->kode == kode)
				{
					if(brg->kode == head->kode)
					{
						head = head->next;
						head->prev = tail;
						tail->next = head;
					}
					else if(brg->kode == tail->kode)
					{
						tail = tail->prev;
						tail->next = head;
						head->prev = tail;
					}
					else
					{
						b1 = brg->prev;
						b2 = brg->next;
						b1->next = b2;
						b2->prev = b1;
					}
					h++;
					delete brg;
					break;
				}
				else
					brg = brg->next;
			}
			while(brg != head);
			if(h == 0)
				cout<<"barang tersebut tidak ada"<<endl;
		}
		
		void view_barang()
		{
			int i = 1;
			brg = head;
			garis(53);
			cout<<"No"<<setw(3)<<" | "<<setw(5)<<"Kode"<<setw(3)<<" | "<<setw(20)<<"Nama"<<setw(3)<<" | "<<setw(2)<<"    "<< setw(12)<<"Harga"<<endl;
			garis(53);
			do
			{
				cout<<setw(2)<<i<<setw(3)<<" | "<< setw(5)<<brg->kode<<setw(3)<<" | "<< setw(20)<<brg->nama<<setw(3)<<" | "<<setw(2)<<"Rp. "<< setw(12)<<brg->harga<<endl;
				brg = brg->next;
				i++;
			}
			while(brg != head);	
			garis(53);
		}
		
		int num_barang(string kode)
		{
			int h = 0;
			brg = head;
			do
			{
				if(brg->kode == kode)
				{
					h++;
				}
				brg = brg->next;
			}
			while(brg != head);
			return h;
		}
		
		void search_barang(string kode)
		{
			int h = 0;
			brg = head;
			do
			{
				if(brg->kode == kode)
				{
					h++;
					break;
				}
				else
					brg = brg->next;
			}
			while(brg != head);
			
			if(h>0)
			{
				cout<<"Ditemukan data dengan Kode = '"<<kode<<"'\n"<<endl;
				garis(53);
				cout<<"| "<<setw(5)<<"kode"<<setw(3)<<" | "<<setw(20)<<"nama"<<setw(3)<<" | "<<setw(2)<<"    "<< setw(12)<<"harga"<<setw(3)<<" | "<<endl;
				garis(53);
				cout<<"| "<< setw(5)<<brg->kode<<setw(3)<<" | "<< setw(20)<<brg->nama<<setw(3)<<" | "<<setw(2)<<"Rp. "<< setw(12)<<brg->harga<<setw(3)<<" | "<<endl;
				garis(53);
			}
			else 
			{
				cout<<"Barang dengan Kode = '"<<kode<<"' kosong\n";
			}
		}
		
		void get_barang(string kode, string* nama, int* harga)
		{
			int h=0;
			brg = head;
			do
			{
				if(brg->kode == kode)
				{
					*nama = brg->nama;
					*harga = brg->harga;
					h++;
					break;
				}
				else
					brg = brg->next;
			}
			while(brg != head);
			if(h==0)
			{
				cout<<"Barang Tidak ada\n";
				*nama = "-";
				*harga = 0;
			}
		}
};

