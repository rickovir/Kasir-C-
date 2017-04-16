#include <conio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct Diskon
{
	string kode;
	int total;
	int besar;
	Diskon *next;
	Diskon *prev;
};

class ModelDiskon
{
	private:
		Diskon *head = NULL, *tail = NULL, *baru, *b1, *b2, *dis;
		
		void garis(int v)
		{
			for(int i=0;i<v;i++)
				cout<<"-";
			cout<<endl;
		}
		
	public:
		
		void load_data()
		{
			string kode;
			int besar, total;
			ifstream baca ("diskon.dat");
			while(baca >> kode >> total >> besar)
				insert_diskon(besar, total, kode);
		}
		
		void backup_data()
		{
			ofstream tulis ("diskon.dat");
			dis = head;
			do
			{
				tulis<<dis->kode<<" \t "<<dis->total<<" \t "<<dis->besar<<endl;
				dis = dis->next;
			}
			while(dis != head);
		}
		
		void insert_diskon(int besar, float total, string kode)
		{
			baru = new Diskon;
			baru->besar = besar;
			baru->total = total;
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
		
		void update_diskon(int besar, float total, string kode)
		{
			dis = head;
			do
			{
				if(dis->kode == kode)
				{
					dis->total = total;
					dis->besar = besar;
					break;
				}
				else
					dis = dis->next;
			}
			while(dis != head);
		}
		
		void delete_diskon(string kode)
		{
			int h = 0;
			dis = head;
			do
			{
				if(dis->kode == kode)
				{
					if(dis->kode == head->kode)
					{
						head = head->next;
						head->prev = tail;
						tail->next = head;
					}
					else if(dis->kode == tail->kode)
					{
						tail = tail->prev;
						tail->next = head;
						head->prev = tail;
					}
					else
					{
						b1 = dis->prev;
						b2 = dis->next;
						b1->next = b2;
						b2->prev = b1;
					}
					h++;
					delete dis;
					break;
				}
				else
					dis = dis->next;
			}
			while(dis != head);
			if(h == 0)
				cout<<"Diskon tersebut tidak ada"<<endl;
		}
		
		void view_diskon()
		{
			int i = 1;
			dis = head;
			garis(53);
			cout<<setw(2)<<"No"<<setw(3)<<" | "<<setw(5)<<"Kode"<<setw(3)<<" | "<<setw(2)<<"    "<<setw(20)<<"Total"<<setw(3)<<" | "<< setw(10)<<"Diskon"<<setw(2)<<"    "<<endl;
			garis(53);
			do
			{
				cout<<setw(2)<<i<<setw(3)<<" | "<< setw(5)<<dis->kode<<setw(3)<<" | "<<setw(2)<<"Rp. "<<  setw(20)<<dis->total<<setw(3)<<" | "<<setw(10)<<dis->besar<<setw(2)<<" % "<<endl;
				dis = dis->next;
				i++;
			}
			while(dis != head);	
			garis(53);
		}
		
		int num_diskon(string kode)
		{
			int h = 0;
			dis = head;
			do
			{
				if(dis->kode == kode)
				{
					h++;
				}
				dis = dis->next;
			}
			while(dis != head);
			return h;
		}
		
		void sorting_diskon()
		{
			b1 = head;
			b2 = head->next;
			int it; string st;
			do
			{
				do
				{
					if(b2->total < b1->total)
					{
						st = b1->kode;
						b1->kode = b2->kode;
						b2->kode = st;
						
						it = b1->besar;
						b1->besar = b2->besar;
						b2->besar = it;
						
						it = b1->total;
						b1->total = b2->total;
						b2->total = it;
					}
					b2 = b2->next;	
				}
				while(b2 != head);
				b1 = b1->next;
			}
			while(b1 != head);
		}
		
		int get_diskon(float totalharga)
		{
			int diskon = 0;
			dis = head;
			do
			{
				if(dis->total <= totalharga)
				{
					diskon = dis->besar;
					break;
				}
				else 
					dis = dis->next;
			}
			while(dis != head);
			return diskon;
		}
};
