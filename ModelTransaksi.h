#include <conio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

struct CurrentCart
{
	int id_transaksi;
	string kode;
	string nama;
	int harga;
	int qty;
	int subtotal;
};

struct Transaksi
{
	int id;
	char tanggal[11];
	char jam[6];
	int grandtotal;
	Transaksi* next;
	Transaksi* prev;
};
//class ModelTransaksi
class ModelTransaksi
{
	private:
		int jml = 0, total = 0, totalqty=0, totalakhir=0, grandtotal;
		Transaksi *head = NULL, *tail = NULL, *baru, *b1, *b2, *trans, *b3;
		CurrentCart cart[1000];
		
		void get_current_date(char* d, char* t)
		{
			time_t rawtime;
			tm* timeinfo;
			time( &rawtime );
			timeinfo = localtime( &rawtime );
			strftime(d, 11,"%d-%m-%Y", timeinfo);
			strftime(t, 6,"%H:%M", timeinfo);
		}
		
		void garis(int v)
		{
			for(int i=0;i<v;i++)
				cout<<"-";
			cout<<endl;
		}
		
		void view_cart()
		{
			identic_cart_check();
			cart_sort_qty();
			garis(75);
			cout<<"| "
				<<setw(3)<<"No."
				<<setw(3)<<" | "
				<<setw(5)<<"Kode"
				<<setw(3)<<" | "
				<<setw(15)<<"Nama Barang"
				<<setw(3)<<" | "
				<<setw(2)<<"    "
				<<setw(12)<<"Harga"
				<<setw(3)<<" | "
				<<setw(5)<<" Qty "
				<<setw(3)<<" | "
				<<setw(12)<<"Sub Total"
				<<setw(3)<<" | "
				<<endl;
				garis(75);
			for(int i = 0; i<jml; i++)
			{
				cout<<"| "
				<<setw(3)<<i+1
				<<setw(3)<<" | "
				<<setw(5)<<cart[i].kode
				<<setw(3)<<" | "
				<<setw(15)<<cart[i].nama
				<<setw(3)<<" | "
				<<setw(2)<<"Rp. "
				<<setw(12)<<cart[i].harga
				<<setw(3)<<" | "
				<<setw(5)<<cart[i].qty
				<<setw(3)<<" | "
				<<setw(12)<<cart[i].subtotal
				<<setw(3)<<" | "
				<<endl;
			}
			garis(75);
			cout<<setw(62)<<"Total = "<<setw(3)<<"Rp."<<setw(8)<<total<<endl;
		}
		
		void reset_cart()
		{
			totalakhir=0;
			total = 0;
			jml=0;
			totalqty=0;
		}
		
		void insert_transaksi(char tanggal[], char jam[], float grandtotal, int id=0)
		{
			baru = new Transaksi;
			baru->id   = id;
			strcpy(baru->tanggal, tanggal);
			strcpy(baru->jam, jam);
			baru->grandtotal = grandtotal;
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
		
		void insert_detail_transaksi()
		{
			ofstream tulis;
			tulis.open("detail_transaksi.dat", ios::app);
			for(int i = 0; i<jml; i++)
			{
				tulis<<cart[i].id_transaksi
					<<" \t "
					<<cart[i].kode
					<<" \t "
					<<cart[i].nama
					<<" \t "
					<<cart[i].harga
					<<" \t "
					<<cart[i].qty
					<<" \t "
					<<cart[i].subtotal
					<<endl;
			}
			tulis.close();
		}
		
		void identic_cart_check()
		{
			for(int i = 0; i<jml; i++)
			{
				for(int j = i+1; j<jml; j++)
				{
					if(cart[i].kode == cart[j].kode)
					{
						cart[i].subtotal = cart[i].subtotal + cart[j].subtotal;
						cart[i].qty = cart[i].qty + cart[j].qty;
						for(int k = j; k < jml-1; k++)
						{
							cart[k] = cart[k+1];
						}
						j--;
						jml--;
					}
				}
			}
		}
		
		void swap_int(int* x, int* y)
		{
			int t;
			t = *x;
			*x = *y;
			*y = t;
		}
		
		void swap_str(string* x, string* y)
		{
			string t;
			t = *x;
			*x = *y;
			*y = t;
		}
		
		void cart_sort_qty()
		{
			for(int i = 0; i<jml; i++)
			{
				for(int j=i+1; j<jml; j++)
				{
					if(cart[i].qty < cart[j].qty)
					{
						swap_int(&cart[i].id_transaksi, &cart[j].id_transaksi);
						swap_int(&cart[i].qty, &cart[j].qty);
						swap_int(&cart[i].subtotal, &cart[j].subtotal);
						swap_int(&cart[i].harga, &cart[j].harga);
						swap_str(&cart[i].kode, &cart[j].kode);
						swap_str(&cart[i].nama, &cart[j].nama);
					}
				}
			}
		}
		
		void hapus_detail_transaksi(int del_id_transaksi)
		{
			int id_transaksi, harga, qty, subtotal;
			string nama, kode;
			
			ifstream baca ("detail_transaksi.dat");
			ofstream tulis ("tmp.dat", ios::app);
			while(baca >> id_transaksi >> kode >> nama >> harga >> qty >> subtotal)
			{
				if(id_transaksi != del_id_transaksi )
				{
					tulis<<id_transaksi
					<<" \t "
					<<kode
					<<" \t "
					<<nama
					<<" \t "
					<<harga
					<<" \t "
					<<qty
					<<" \t "
					<<subtotal
					<<endl;
				}
			}
			baca.close();
			tulis.close();
			remove("detail_transaksi.dat");
			rename("tmp.dat","detail_transaksi.dat");
		}
		
	public:
		void load_data()
		{
			int id, grandtotal;
			char tanggal[11], jam[6];
			ifstream baca ("transaksi.dat");
			while(baca >> id >> tanggal >> jam >> grandtotal)
				insert_transaksi(tanggal, jam, grandtotal, id);
				
			baca.close();
		}
		
		void backup_data()
		{
			ofstream tulis ("transaksi.dat");
			trans = head;
			do
			{
				tulis<<trans->id<<" \t "<<trans->tanggal<<" \t "<<trans->jam<<" \t "<<trans->grandtotal<<endl;
				trans = trans->next;
			}
			while(trans != head);
			tulis.close();
		}
		
		void add_cart(string kode, string nama, int harga)
		{
			trans = tail;
			cart[jml].id_transaksi = trans->id + 1;
			cart[jml].kode = kode;
			cart[jml].nama = nama,
			cart[jml].qty = 1;
			cart[jml].subtotal = harga;
			cart[jml].harga = harga;
			jml++;
			total = total + harga;
		}
		
		void view_total(int diskon)
		{
			view_cart();
			cout<<setw(62)<<"Diskon Sebesar = "<<setw(8)<<diskon<<" % "<<endl;
			grandtotal = (float)total * (100-diskon)/100;
			cout<<setw(62)<<"Grand Total = "<<setw(3)<<"Rp."<<setw(8)<<grandtotal<<endl;
		}
		
		int get_total()
		{
			return total;
		}
		
		void submit_cart()
		{
			trans = tail;
			int id = trans->id+1;
			char tanggal[11];
			char jam[6];
			get_current_date(tanggal, jam);
			insert_transaksi(tanggal, jam, grandtotal, id);
			insert_detail_transaksi();
			reset_cart();
		}
		
		void view_report_tgl(char rtgl[])
		{
			int id_transaksi, harga, qty, subtotal , n=0;
			string nama, kode;
			ifstream baca("detail_transaksi.dat");
			
			trans = head;
			do
			{
				if(strcmp(rtgl, trans->tanggal) == 0 )
				{
					while(baca >> id_transaksi >> kode >> nama >> harga >> qty >> subtotal)
					{
						if(id_transaksi == trans->id)
						{
							cart[jml].id_transaksi = id_transaksi;
							cart[jml].kode = kode;
							cart[jml].nama = nama;
							cart[jml].harga = harga;
							cart[jml].qty = qty;
							cart[jml].subtotal =subtotal;
							jml++;
							total = total + subtotal;
							totalqty = totalqty + qty;
						}
					}
					baca.clear();
					baca.seekg(0, ios::beg);
					n++;
					
					totalakhir = (int)totalakhir + trans->grandtotal;
				}
				trans = trans->next;
			}
			while(trans != head);
			baca.close();
			if(n==0)
				cout<<"Tidak ada transaksi pada tanggal tersebut"<<endl;
			else
			{
				view_cart();
				cout<<setw(62)<<"Total setelah kena diskon = "<<setw(3)<<"Rp."<<setw(8)<<totalakhir<<endl;
				cout<<setw(62)<<"Jumlah Barang Terjual = "<<setw(8)<<totalqty<<endl;
				cout<<setw(62)<<"Barang paling banyak dibeli = "<<setw(10)<<cart[0].nama<<endl;
				cout<<setw(62)<<"Barang paling sedikit dibeli = "<<setw(10)<<cart[jml-1].nama<<endl;
			}
			reset_cart();
		}

		void view_report_bln(char rbln[])
		{
			int id_transaksi, harga, qty, subtotal , n=0;
			string nama, kode;
			ifstream baca("detail_transaksi.dat");
			
			trans = head;
			do
			{
				if(rbln[0] == trans->tanggal[3] && rbln[1] == trans->tanggal[4])
				{
					while(baca >> id_transaksi >> kode >> nama >> harga >> qty >> subtotal)
					{
						if(id_transaksi == trans->id)
						{
							cart[jml].id_transaksi = id_transaksi;
							cart[jml].kode = kode;
							cart[jml].nama = nama;
							cart[jml].harga = harga;
							cart[jml].qty = qty;
							cart[jml].subtotal =subtotal;
							jml++;
							total = total + subtotal;
							totalqty = totalqty + qty;
						}
					}
					baca.clear();
					baca.seekg(0, ios::beg);
					n++;
					
					totalakhir = (int)totalakhir + trans->grandtotal;
				}
				trans = trans->next;
			}
			while(trans != head);
			baca.close();
			if(n==0)
				cout<<"Tidak ada transaksi pada bulan tersebut"<<endl;
			else
			{
				view_cart();
				cout<<setw(62)<<"Total setelah kena diskon = "<<setw(3)<<"Rp."<<setw(8)<<totalakhir<<endl;
				cout<<setw(62)<<"Jumlah Barang Terjual = "<<setw(8)<<totalqty<<endl;
				cout<<setw(62)<<"Barang paling banyak dibeli = "<<setw(10)<<cart[0].nama<<endl;
				cout<<setw(62)<<"Barang paling sedikit dibeli = "<<setw(10)<<cart[jml-1].nama<<endl;
			}
			reset_cart();
		}
		
		void view_report_brg(string r_kode_brg)
		{
			int id_transaksi, harga, qty, subtotal , n=1, max=0, min=0;
			char max_tgl[11], max_jam[6], min_tgl[11], min_jam[6];
			string nama, kode;
			ifstream baca("detail_transaksi.dat");
			
			garis(73);
			cout<<"| "
				<<setw(3)<<"No."
				<<setw(3)<<" | "
				<<setw(10)<<"Tanggal"
				<<setw(3)<<" | "
				<<setw(8)<<"Jam"
				<<setw(3)<<" | "
				<<setw(5)<<" Qty "
				<<setw(3)<<" | "
				<<setw(2)<<"    "
				<<setw(12)<<"Harga"
				<<setw(3)<<" | "
				<<setw(12)<<"Sub Total"
				<<setw(3)<<" | "
				<<endl;
			garis(73);
			
			while(baca >> id_transaksi >> kode >> nama >> harga >> qty >> subtotal)
			{
				if(kode == r_kode_brg)
				{
					trans = head;
					do
					{
						if(trans->id == id_transaksi)
						{
							if(max < qty)
							{
								max=qty;
								strcpy(max_tgl, trans->tanggal);
								strcpy(max_jam, trans->jam);
							}
							
							if(n == 1)
							{
								min = qty;
								strcpy(min_tgl, trans->tanggal);
								strcpy(min_jam,trans->jam);
							}
							else if(min > qty)
							{
								min = qty;
								strcpy(min_tgl, trans->tanggal);
								strcpy(min_jam,trans->jam);
							}
							
							cout<<"| "
								<<setw(3)<<n
								<<setw(3)<<" | "
								<<setw(10)<<trans->tanggal
								<<setw(3)<<" | "
								<<setw(8)<<trans->jam
								<<setw(3)<<" | "
								<<setw(5)<<qty
								<<setw(3)<<" | "
								<<setw(2)<<"    "
								<<setw(12)<<harga
								<<setw(3)<<" | "
								<<setw(12)<<subtotal
								<<setw(3)<<" | "
								<<endl;
							n++;
							total = total +subtotal;
							break;
						}
						trans = trans->next;
					}
					while(trans != head);
				}
			}
			garis(73);
			
			cout<<setw(60)<<"Total = "<<setw(3)<<"Rp."<<setw(8)<<total<<endl;
			cout<<setw(60)<<"Pembelian paling banyak pada : "<<endl;
			cout<<setw(60)<<"Tanggal = "<<max_tgl<<endl;			
			cout<<setw(60)<<"Jam = "<<max_jam<<endl;			
			
			cout<<setw(60)<<"Pembelian paling sedikit pada : "<<endl;
			cout<<setw(60)<<"Tanggal = "<<min_tgl<<endl;			
			cout<<setw(60)<<"Jam = "<<min_jam<<endl;
			
			baca.close();
		}
		
		void hapus_transaksi(char htgl[])
		{
			int h = 0;
			trans = head;
			do
			{
				if(strcmp(htgl, trans->tanggal) == 0 )
				{
					if(trans->id == head->id)
					{
						head = head->next;
						head->prev = tail;
						tail->next = head;
						b3 = trans;
						trans = head;
					}
					else if(trans->id == tail->id)
					{
						tail = tail->prev;
						tail->next = head;
						head->prev = tail;
						b3 = trans;
						trans = tail;
					}
					else
					{
						b1 = trans->prev;
						b2 = trans->next;
						b1->next = b2;
						b2->prev = b1;
						b3 = trans;
						trans = b1;
					}
					h++;
					hapus_detail_transaksi(b3->id);
					delete b3;
				}
				else
					trans = trans->next;
			}
			while(trans != head);
			if(h == 0)
				cout<<"Transaksi tersebut tidak ada"<<endl;
		}
};
