#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class khach_hang{
	private:
		string ho_ten;
		string sdt;
		string dia_chi;
	public:
		khach_hang();
		khach_hang(string hoten, string sdt, string dia_chi)
		string lay_hoten() const;
		string lay_sdt()const;
		string lay_diachi() const;
		void hien_thi() const;
};

khach_hang::khach_hang(){
	string hoten = " ";
	string sdt = " ";
	string dia_chi = " ";
}

khach_hang::khach_hang(string hoten, string sdt, string dia_chi){
	string ho_ten = hoten;
	string sdt = so;
	string dia_chi = diachi;
}

string khach_hang::lay_hoten() const{
	return ho_ten;
}
string khach_hang::lay_sdt() const {
	return sdt;
}
string khach_hang::lay_diachi() const {
	return dia_chi;
}
void khach_hang::hien_thi() const {
	cout << "Ho ten khach hang la: " << ho_ten << endl;
	cout << "DT: " << sdt << endl;
	cout << "Dia chi: " << dia_chi << endl;
}

class hang_hoa{
	private:
		string ten_hang;
		int so_luong;
		string quy_cach;
		double so_luong;
		string don_vi_tinh;
		double don_gia;
		double thanh_tien;
	public:
		hang_hoa::hang_hoa();
		{
			string ten_hang = " ";
			string quy_cach = " ";
			string don_vi_tinh = " ";
			double so_luong = 0.0;
			double don_gia = 0.0;
			double thanh_tien = 0.0;
		}
		hang_hoa::hang_hoa(string ten_hang, string quy_cach, string don_vi_tinh, double so_luong, double don_gia, double thanh_tien)
		{
			string ten_hang = ten;
			string quy_cach = quycach;
			string don_vi_tinh = donvi;
			double don_gia = gia;
			double thanh_tien = tong;
		}
};
    









