#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
	
	// lop khach hang
	class khach_hang{
		private:
			string hoten;
			string diachi;
			string sdt;
		public:
			khach_hang();
			khach_hang(string hoten, string diachi, string sdt);
			string lay_hoten() const;
			string lay_diachi() const;
			string lay_sdt() const;
			void hien_thi() const;
			void nhap();
	};
	
	khach_hang::khach_hang()
	{
		hoten = " ";
		sdt = " ";
		diachi = " ";
	}
	khach_hang::khach_hang(string ten, string dia_chi, string so)
	{
		hoten = ten;
		sdt = so;
		diachi = dia_chi;
	}
	string khach_hang::lay_hoten() const {
		return hoten;
	}
	string khach_hang::lay_diachi() const {
		return diachi;
	}
	string khach_hang::lay_sdt() const {
		return sdt;
	}
	void khach_hang::hien_thi() const 
	{
		cout << "Ho ten khach hang la: " << hoten << endl;
		cout << "SDT la: " << sdt << endl;
		cout << "Dia chi: " << diachi << endl;
	}
	// lop hang hoa
	class hang_hoa{
		private:
			string ten_hang;
			string quy_cach;
			double so_luong;
			string don_vi_tinh;
			double don_gia;
			double thanh_tien;
		public:
			hang_hoa();
			hang_hoa (string ten_hang, string quy_cach, double so_luong, string don_vi_tinh, double don_gia, double thanh_tien);
			string lay_ten_hang() const;
			string lay_quy_cach() const;
			double lay_so_luong() const;
			string lay_don_vi_tinh() const;
			double lay_don_gia() const;
			double lay_thanh_tien() const;
			void hien_thi() const;
			void nhap();
		};
		hang_hoa::hang_hoa()
			{
			ten_hang = " ";
			quy_cach = " ";
			so_luong = 0.0;
			don_vi_tinh = " ";
			don_gia = 0.0;
		    thanh_tien = 0.0;
			}
		hang_hoa::hang_hoa(string ten, string quycach, double soluong, string donvi, double gia, double tong)
			{
			ten_hang = ten;
			quy_cach = quycach;
			so_luong = soluong;
			don_vi_tinh = donvi;
			don_gia = gia;
			thanh_tien = tong;
			}
		double hang_hoa::lay_don_gia() const{
			return don_gia;
		}
		string hang_hoa::lay_ten_hang() const{
			return ten_hang;
		}
		string hang_hoa::lay_quy_cach() const{
			return quy_cach;
		}
		string hang_hoa::lay_don_vi_tinh() const {
			return don_vi_tinh;
		}
		double hang_hoa::lay_so_luong()	const {
			return so_luong;
		}	
		double hang_hoa::lay_thanh_tien() const {
			return thanh_tien;
		}
		void hang_hoa::hien_thi() const 
	{
		cout << "Ten hang la: " << ten_hang << endl;
		cout << "Quy cach cua hang la: " << quy_cach << endl;
		cout << "So luong la: " << so_luong << endl;
		cout << "Don vi tinh cua hang la: " << don_vi_tinh << endl;
		cout << "Don gia: " << don_gia << endl;
		cout << "Thanh tien: " << thanh_tien << endl;
	}
	//lop hoa don
	class hoa_don{
		private:
			string sohd;
			string ngay_lap;
			khach_hang kh;
			hang_hoa ds_hang[10];
			int so_hang;
			double thue_gtgt;
			string hinh_thuc_thanh_toan;
		public:
		hoa_don();
		hoa_don(string sohd, string ngay_lap, khach_hang kh, int so_hang, double thue_gtgt, string hinh_thuc_thanh_toan);
		
		void them_hang(hang_hoa hh);
		void nhap() ;
		double cong_tien_hang() const;
		double tong_thanh_toan() const;
		double tien_thue() const;
		void hien_thi() const;
		void xoa_hang(hang_hoa hh);
		
	};
	hoa_don::hoa_don()
	{
	sohd = " ";
	ngay_lap = " ";
	so_hang = 0;
	thue_gtgt = 0.0;
	hinh_thuc_thanh_toan = " ";
	}
	hoa_don::hoa_don(string shd, string ngay, khach_hang k, int sl, double thue, string httt)
	{
	sohd = shd;
	ngay_lap = ngay;
	khach_hang kh = k;
	so_hang = sl;
	thue_gtgt = thue;
	hinh_thuc_thanh_toan = httt;
	}
	//chuc nang them mat hang
	void hoa_don::them_hang(hang_hoa hh){ 
		if(so_hang < 100)
		{
			ds_hang[so_hang] = hh;
			so_hang ++;
			cout << "Da them mat hang thanh cong"<< endl;
		}
		else
		{
			cout << "Danh sach hang hoa da day" << endl;
		}
	}
	//chuc nang nhap du lieu cua hoa don
	void hoa_don::nhap() 
	{
		cout << "Nhap so hoa don: "; 
		getline(cin,sohd);
		cout << "Ngay lap hoa don: "; getline(cin, ngay_lap);
		kh.nhap();
		cout << "Nhap so luong mat hang:";
		cin >> so_hang;
		cin.ignore();
		
		for(int i=0;i<so_hang;i++)
		{
			cout << "Nhap mat hang thu " << i+1 << endl;
			ds_hang[i].nhap();
		}
		cout << "Nhap thue gtgt: ";
		cin >> thue_gtgt;
		cin.ignore();
		cout << "Hinh thuc thanh toan: "; getline ( cin, hinh_thuc_thanh_toan);
	}
	
	double hoa_don::cong_tien_hang() const
	{
		double tong = 0.0;
		for(int i=0;i<so_hang;i++)
		{
			tong += ds_hang[i].lay_thanh_tien();
		}
		return tong;
	}
	double hoa_don::tien_thue() const
	{
		return cong_tien_hang() * (thue_gtgt /100.0);
	}
	double hoa_don::tong_thanh_toan() const
	{
		return cong_tien_hang() + tien_thue();
	}
	
	//chuc nang hien thi
	void hoa_don::hien_thi() const
	{
		cout << "HOA DON BAN HANG" << endl;
		cout << "So HD: " << sohd << " | Ngay lap: " << ngay_lap << endl;
		kh.hien_thi();
		
		cout << "DANH SACH HANG HOA" << endl;
		if ( so_hang == 0)
		{
			cout << "Chua co mat hang nao trong hoa don" << endl;
		}
		else
		{
		for(int i=0;i<so_hang;i++)
		{
			cout << "Mat hang " << i+1<<":" << endl;
			ds_hang[i].hien_thi();
		}
		cout << "Cong tien hang: " << cong_tien_hang() <<endl;
		cout << "Thue GTGT ( " << thue_gtgt << "%): " << tien_thue() << endl;
		cout << "Tong thanh toan: " << tong_thanh_toan() << endl;
		cout << "Hinh thuc thanh toan: " << hinh_thuc_thanh_toan << endl;
	}
		}
	
	//chuc nang xoa mot mat hang
	void xoa_hang(string ten_can_xoa)
	{
		int vitri = -1;
		for( int i =0; i< so_hang ; i++)
		{
			if(ds_hang[i].lay_ten_hang() == ten_can_xoa)
			{
				vitri =i;
				break;
			}
		}
		if(vitri == -1)
		{
		cout << "Khong tim thay mat hang can xoa" << endl;
		return;
		}
		for(int i=vitri;i<so_hang - 1 ; i++)
		{
			ds_hang[i] = ds_hang[i+1];
		}
		so_hang --;
		cout << "Da xoa mat hang thanh cong: " << ten_can_xoa << endl;
	}
	
	int main(){
		int chon;
		do{
			cout << "QUAN LY HOA DON" << endl;
			cout << "N1.Them mat hang" << endl;
			cout << "N2.Xoa mat hang" << endl;
			cout << "N3.Hien thi hoa don" << endl;
			cout << "N4.Thoat" << endl;
			cout << "Nhap lua chon: ";
			cin >> chon;
			cin.ignore();	
	    switch ( chon )
		{
			case 1: 
			{
				hang_hoa hang_moi;
				cout << "Nhap thong tin mat hang: " << endl;
				hang_moi.nhap();
				hd.them_hang(hang_moi);
				break;
			}
			case 2:
				{
					string ten_can_xoa;
					cout << "Nhap ten mat hang can xoa: ";
					getline(cin, ten_can_xoa);
					hd.xoa_hang(ten_can_xoa);
					break;
				}
			case 3:
				{
					hd.hien_thi();
					break;
				}
			case 4:
				cout << "Googbye. No see you again" << endl;
				break;
				default:
					cout << "Lua chon khong hop le. Chon lai" << endl;
		}
		}
		while ( chon != 0);
		return 0;
	}
