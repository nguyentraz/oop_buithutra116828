#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

string chuanhoaten(string loai) {
    string chuanhoa = loai;  
    if (loai == "car") return "Car";
    if (loai == "motorcycle") return "Motorcycle";
    if (loai == "bicycle") return "Bicycle";
    return loai;                            
}

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() {
    ma_xe = 0;
    loai_xe = "";
    gio_vao = 0;
    tg_do = 0;
}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg) {
    ma_xe = ma;
    loai_xe = loai;
    gio_vao = gio;
    tg_do = tg;
}

int phuong_tien::lay_ma_xe() const {
    return ma_xe;
}

string phuong_tien::lay_loai_xe() const {
    return loai_xe;
}

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    double phi = tinh_phi();
    cout << "  Ma phuong tien: " << ma_xe << endl;
    cout << "  Loai phuong tien: " << loai_xe << endl;
    cout << "  Gio vao: " << gio_vao << endl;
    cout << "  Thoi gian do xe: " << tg_do << endl;
    cout << "  Phi do xe: $" << fixed << setprecision(2) << phi << endl;
}


class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int XeToiDa = 3;
    phuong_tien phuongtien[XeToiDa];   
    int so_luong_pt;                   
    int suc_chua() const;              

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma_bai() const;
    int lay_so_luong() const;
    
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};

bai_xe::bai_xe() {
    ma_bai = 0;
    kich_thuoc = 'S';
    so_luong_pt = 0;
}

bai_xe::bai_xe(int ma, char kt) {
    ma_bai = ma;
    kich_thuoc = kt;
    so_luong_pt = 0;
}

int bai_xe::suc_chua() const {
    return (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
}

int bai_xe::lay_ma_bai() const {
    return ma_bai;
}

int bai_xe::lay_so_luong() const {
    return so_luong_pt;
}

bool bai_xe::them(phuong_tien v) {
    if (so_luong_pt >= suc_chua())
        return false;
    phuongtien[so_luong_pt] = v;
    so_luong_pt++;
    return true;
}

bool bai_xe::xoa(int ma_xe) {
    for (int i = 0; i < so_luong_pt; i++) {
        if (phuongtien[i].lay_ma_xe() == ma_xe) {
            for (int j = i; j < so_luong_pt - 1; j++)
                phuongtien[j] = phuongtien[j + 1];   
            so_luong_pt--;
            return true;
        }
    }
    return false;
}

bool bai_xe::chua(int ma_xe) const {
    for (int i = 0; i < so_luong_pt; i++) {
        if (phuongtien[i].lay_ma_xe() == ma_xe)
            return true;
    }
    return false;
}

void bai_xe::hien_thi() const {
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_luong_pt << "/" << suc_chua() << " xe\n";
    for (int i = 0; i < so_luong_pt; i++) {
        phuongtien[i].hien_thi();
    }
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    for (int i = 0; i < so_luong_pt; i++) {
        if (phuongtien[i].lay_loai_xe() == loai) {
            dem++;
            tong += phuongtien[i].tinh_phi();
        }
    }
    return dem > 0;
}

class SystemInterface {
private:
    static const int BaiToiDa = 10;
    bai_xe baixe[BaiToiDa];       
    int bai_do_hien_tai;         
	  
    int tim_bai(int ma) const;     
    int tim_xe(int ma) const;      

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() {
    bai_do_hien_tai = 0;
}

int SystemInterface::tim_bai(int ma) const {
    for (int i = 0; i < bai_do_hien_tai; i++)
        if (baixe[i].lay_ma_bai() == ma) return i;
    return -1;
}

int SystemInterface::tim_xe(int ma) const {
    for (int i = 0; i < bai_do_hien_tai; i++)
        if (baixe[i].chua(ma)) return i;
    return -1;
}
void SystemInterface::runMenu() {
    while (true) {
        cout << "\n QUAN LY BAI DO XE \n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        int chon;
        scanf("%d",&chon);
		
        switch (chon) {
        case 1: {
            int ma; char kt;
            if (bai_do_hien_tai >= BaiToiDa) {
                cout << "Da du " << BaiToiDa << " bai, khong the tao them.\n";
                break;
            }
            cout << "Ma bai: "; cin >> ma;
            cout << "Kich thuoc (S/M/L): "; cin >> kt;
            kt = (char)toupper((unsigned char)kt);
            if (kt != 'S' && kt != 'M' && kt != 'L') {
                cout << "Kich thuoc khong hop le!\n";
                break;
            }
            if (tim_bai(ma) != -1) {
                cout << "Ma bai da ton tai.\n";
                break;
            }
            baixe[bai_do_hien_tai] = bai_xe(ma, kt);
            bai_do_hien_tai++;
            cout << "Da tao bai " << ma << "\n";
            break;
        }
        case 2:
		{
            if (bai_do_hien_tai == 0)
			{
                cout << "Chua co bai do nao, hay tao bai.\n";
                break;
            }
            int ma, gio, tg; string loai;
            cout << "Ma xe: "; cin >> ma;
            cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
            loai = chuanhoaten(loai);
            if (loai == "") {
                cout << "Loai xe khong hop le!\n";
                break;
            }
            cout << "Gio vao (0-23): "; cin >> gio;
            cout << "Thoi luong (1-23): "; cin >> tg;
            if (gio < 0 || gio > 23 || tg < 1 || tg > 23) {
                cout << "Gio vao hoac thoi luong khong hop le!\n";
                break;
            }
            if (tim_xe(ma) != -1) {
                cout << "Ma xe da ton tai.\n";
                break;
            }
            phuong_tien v(ma, loai, gio, tg);
            bool ok = false;
            for (int i = 0; i < bai_do_hien_tai && !ok; i++)
                ok = baixe[i].them(v);
            if (ok) cout << "Da them xe " << ma << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
            else    cout << "Tat ca bai da day.\n";
            break;
        }
        case 3: {
            int ma;
            cout << "Ma bai can xoa: "; cin >> ma;
            int vt = tim_bai(ma);
            if (vt == -1) {
                cout << "Khong tim thay bai " << ma << "\n";
                break;
            }
            for (int j = vt; j < bai_do_hien_tai - 1; j++)
                baixe[j] = baixe[j + 1];   
            bai_do_hien_tai--;
            cout << "Da xoa bai " << ma << "\n";
            break;
        }
        case 4: {
            int ma;
            cout << "Ma xe can lay ra: "; cin >> ma;
            int vt = tim_xe(ma);
            if (vt != -1) {
                baixe[vt].xoa(ma);
                cout << "Da lay xe ra\n";
            }
            else cout << "Khong tim thay xe\n";
            break;
        }
        case 5:
            if (bai_do_hien_tai == 0)
			cout << "Chua co bai do nao.\n";
            for (int i = 0; i < bai_do_hien_tai; i++)
                baixe[i].hien_thi();
            break;
        case 6: {
            int ma;
            cout << "Ma bai: "; cin >> ma;
            int vt = tim_bai(ma);
            if (vt != -1) baixe[vt].hien_thi();
            else cout << "Khong tim thay bai " << ma << "\n";
            break;
        }
        case 7: {
            string loai;
            cout << "Loai xe: "; cin >> loai;
            loai = chuanhoaten(loai);
            
            int dem; double tong;
            bool tim_thay = false;
            for (int i = 0; i < bai_do_hien_tai; i++) {
                if (baixe[i].co_loai(loai, dem, tong)) {
                    baixe[i].hien_thi();
                    tim_thay = true;
                }
            }
            if (!tim_thay) cout << "Khong co xe loai " << loai << "\n";
            break;
        }
        case 8: {
            string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
            for (int t = 0; t < 3; ++t) {
                int dem = 0; double tong = 0;
                for (int i = 0; i < bai_do_hien_tai; i++) {
                    int d; double s;
                    baixe[i].co_loai(loai_arr[t], d, s);
                    dem += d;
                    tong += s;
                }
                cout << loai_arr[t] << ": ";
                if (dem == 0) cout << "khong co xe\n";
                else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
            }
            break;
        }
        case 9:
            cout << "Dang thoat chuong trinh..." << endl;
            return;
        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }
    }
}
int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
