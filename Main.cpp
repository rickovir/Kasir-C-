#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <string>
#include "ModelTransaksi.h"
#include "ModelBarang.h"
#include "ModelDiskon.h"
using namespace std;
//deklarasi object class
ModelBarang m_barang;
ModelDiskon m_diskon;
ModelTransaksi m_trans;

void header(char judul[], int j)
{
	int hl = j+42;
	for(int i=0; i<hl;i++)
		cout<<"=";
		
	cout<<endl<<"||                   ";
	for(int i=0; i<j;i++)
		cout<<judul[i];
		
	cout<<"                   ||"<<endl;
	for(int i=0; i<hl;i++)
		cout<<"=";
		
	cout<<endl;
}

void del_transaksi()
{
	system("cls");
	header("Hapus Transaksi Pertanggal",26);
	char tgl[11];
	cout<<"Tanggal 'dd-mm-yyyy' = ";
	cin>>tgl;
	m_trans.hapus_transaksi(tgl);
}

void rpt_bln_transaksi()
{
	system("cls");
	header("Laporan Transaksi Bulanan",25);
	char bln[2];
	cout<<"Bulan 'mm' = ";
	cin>>bln;
	m_trans.view_report_bln(bln);
}

void rpt_tgl_transaksi()
{
	system("cls");
	header("Laporan Transaksi Pertanggal",28);
	char tgl[11];
	cout<<"Tanggal 'dd-mm-yyyy' = ";
	cin>>tgl;
	m_trans.view_report_tgl(tgl);
}

void rpt_brg_transaksi()
{
	system("cls");
	header("Laporan Transaksi Perbarang",27);
	string kode;
	cout<<"Kode Barang = ";
	cin>>kode;
	m_trans.view_report_brg(kode);
}

void start_transaksi()
{
	int n=0, diskon;
	char lg;
	float total;
	do
	{
		system("cls");
		header("Transaksi Barang Supermarket Plus",33);
		string kode_barang, nama_barang;
		int harga_barang;
		cout<<"Kode Barang   = "; cin>>kode_barang;
		m_barang.get_barang(kode_barang, &nama_barang, &harga_barang);
		if(nama_barang != "-")
		{
			m_trans.add_cart(kode_barang, nama_barang, harga_barang);
			n++;
		}
		cout<<"Ada lagi ? [y/n] "; cin>>lg;
	}
	while(n<100 && lg == 'Y');
	total = m_trans.get_total();
	diskon = m_diskon.get_diskon(total);
	m_trans.view_total(diskon);
	m_trans.submit_cart();
}

void menu_transaksi()
{
	m_trans.load_data();
	m_diskon.sorting_diskon();
	char p;
	do
	{
		system("cls");
		header("Menu Transaksi",14);
		cout<<"1. Transaksi"<<endl;
		cout<<"2. Hapus Transaksi"<<endl;
		cout<<"3. Laporan Transaksi pertanggal"<<endl;
		cout<<"4. Laporan Transaksi perbarang"<<endl;
		cout<<"5. Laporan Bulanan"<<endl;
		cout<<"6. Keluar"<<endl;
		cout<<"Masukan pilihan anda = ";
		cin>>p;
		if(p=='1')
			start_transaksi();
		else if(p=='2')
			del_transaksi();
		else if(p=='3')
			rpt_tgl_transaksi();
		else if(p=='4')
			rpt_brg_transaksi();
		else if(p=='5')
			rpt_bln_transaksi();
		system("pause");
	}
	while(p!='6');
	m_trans.backup_data();
}

void del_diskon()
{
	system("cls");
	string kode;
	
	header("Delete Diskon",13);
	cout<<"Masukan Kode Diskon = "; cin>>kode;
	m_diskon.delete_diskon(kode);
}

void vw_diskon()
{
	system("cls");
	header("View Diskon",11);
	m_diskon.view_diskon();
}

void in_diskon()
{
	system("cls");
	string kode;
	int besar, total;
	
	header("Insert Diskon",13);
	cout<<"Masukan Data dibawah ini :"<<endl;
	cout<<"Kode Diskon  = "; cin>>kode;
	cout<<"Total Harga  = Rp. "; cin>>total;
	cout<<"Diskon       = "; cin>>besar;
	m_diskon.insert_diskon(besar,total,kode);
}

void up_diskon()
{
	system("cls");
	string kode;
	int besar, total;
	header("Update Diskon",13);
	cout<<"Masukan Kode Diskon = "; cin>>kode;
	if(m_diskon.num_diskon(kode) >0)
	{
		cout<<"Total Harga  = Rp. "; cin>>total;
		cout<<"Diskon       = "; cin>>besar;
		m_diskon.update_diskon(besar,total,kode);
	}
	else
		cout<<"Diskon tersebut tidak ada\n";
}


void menu_diskon()
{
	char p;
	do
	{
		system("cls");
		header("Menu Diskon",11);
		cout<<"1. Insert Diskon"<<endl;
		cout<<"2. Edit Diskon"<<endl;
		cout<<"3. Lihat Diskon"<<endl;
		cout<<"4. Hapus Diskon"<<endl;
		cout<<"5. Keluar"<<endl;
		cout<<"Masukan pilihan anda = ";
		cin>>p;
		if(p=='1')
			in_diskon();
		else if(p=='2')
			up_diskon();
		else if(p=='3')
			vw_diskon();
		else if(p=='4')
			del_diskon();
		system("pause");
	}
	while(p!='5');
}
//end of diskon

// barang
void vw_barang()
{
	system("cls");
	header("View Barang",11);
	m_barang.view_barang();
}

void in_barang()
{
	system("cls");
	int harga;
	string nama, kode;
	header("Insert Barang",13);
	cout<<"Masukan Data dibawah ini :"<<endl;
	cout<<"Kode Barang  = "; 
	cin>>kode;
	cout<<"Nama Barang  = "; 
	cin>>nama;
	cout<<"Harga        = Rp. "; 
	cin>>harga;
	m_barang.insert_barang(harga,nama,kode);
}

void up_barang()
{
	system("cls");
	int harga;
	string nama, kode;
	
	header("Update Barang",13);
	cout<<"Masukan Kode Barang = "; cin>>kode;
	if(m_barang.num_barang(kode) >0)
	{
		cout<<"Nama Barang  = "; cin>>nama;
		cout<<"Harga        = "; cin>>harga;
		m_barang.update_barang(harga,nama,kode);
	}
	else
		cout<<"Barang tersebut tidak ada\n";
}

void del_barang()
{
	system("cls");
	string kode;
	
	header("Delete Barang",13);
	cout<<"Masukan Kode Barang = "; cin>>kode;
	m_barang.delete_barang(kode);
}

void sc_barang()
{
	system("cls");
	string kode;
	
	header("Cari Barang",11);
	cout<<"Masukan Kode Barang = "; cin>>kode;
	m_barang.search_barang(kode);
}

void menu_barang()
{
	char p;
	do
	{
		system("cls");
		header("Menu Barang",11);
		cout<<"1. Insert Barang"<<endl;
		cout<<"2. Edit Barang"<<endl;
		cout<<"3. Lihat Barang"<<endl;
		cout<<"4. Hapus Barang"<<endl;
		cout<<"5. Cari Barang"<<endl;
		cout<<"6. Keluar"<<endl;
		cout<<"Masukan pilihan anda = ";
		cin>>p;
		if(p=='1')
			in_barang();
		else if(p=='2')
			up_barang();
		else if(p=='3')
			vw_barang();
		else if(p=='4')
			del_barang();
		else if(p=='5')
			sc_barang();
		system("pause");
	}
	while(p!='6');
}
//end of barang

void menu()
{
	char p;
	do
	{
		system("cls");
		header("Menu Utama",10);
		cout<<"1. Barang"<<endl;
		cout<<"2. Transaksi"<<endl;
		cout<<"3. Diskon"<<endl;
		cout<<"4. Keluar"<<endl;
		cout<<"Masukan pilihan anda = ";
		cin>>p;
		if(p=='1')
			menu_barang();
		else if(p=='2')
			menu_transaksi();
		else if(p=='3')
			menu_diskon();
	}
	while(p!='4');
}

int main()
{
	system("title Program Kasir");
	system("color F0");
	m_barang.load_data();
	m_diskon.load_data();
	menu();
	m_diskon.backup_data();
	m_barang.backup_data();
}

