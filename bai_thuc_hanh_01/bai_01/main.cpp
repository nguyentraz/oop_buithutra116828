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
    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma_bai() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};

bai_xe::bai_xe() {
    ma_bai = 0;
    kich_thuoc = 'S';
    co1 = false;
    co2 = false;
    co3 = false;
}

bai_xe::bai_xe(int ma, char kt) {
    ma_bai = ma;
    kich_thuoc = kt;
    co1 = false;
    co2 = false;
    co3 = false;
}

int bai_xe::lay_ma_bai() const {
    return ma_bai;
}

bool bai_xe::them(phuong_tien v) {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    if (cap >= 1 && !co1) { pt1 = v; co1 = true; return true; }
    if (cap >= 2 && !co2) { pt2 = v; co2 = true; return true; }
    if (cap >= 3 && !co3) { pt3 = v; co3 = true; return true; }
    return false;
}

bool bai_xe::xoa(int ma_xe) {
    if (co1 && pt1.lay_ma_xe() == ma_xe) {
        if (co2) {
            pt1 = pt2;
            if (co3) { pt2 = pt3; co3 = false; }
            else co2 = false;
        } else co1 = false;
        return true;
    }
    if (co2 && pt2.lay_ma_xe() == ma_xe) {
        if (co3) { pt2 = pt3; co3 = false; }
        else co2 = false;
        return true;
    }
    if (co3 && pt3.lay_ma_xe() == ma_xe) {
        co3 = false;
        return true;
    }
    return false;
}

bool bai_xe::chua(int ma_xe) const {
    if (co1 && pt1.lay_ma_xe() == ma_xe) return true;
    if (co2 && pt2.lay_ma_xe() == ma_xe) return true;
    if (co3 && pt3.lay_ma_xe() == ma_xe) return true;
    return false;
}

void bai_xe::hien_thi() const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    int so_xe = (int)co1 + (int)co2 + (int)co3;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe << "/" << cap << " xe\n";
    if (co1) pt1.hien_thi();
    if (co2) pt2.hien_thi();
    if (co3) pt3.hien_thi();
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    if (co1 && pt1.lay_loai_xe() == loai) { ++dem; tong += pt1.tinh_phi(); }
    if (co2 && pt2.lay_loai_xe() == loai) { ++dem; tong += pt2.tinh_phi(); }
    if (co3 && pt3.lay_loai_xe() == loai) { ++dem; tong += pt3.tinh_phi(); }
    return dem > 0;
}

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3;

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() {
    co1 = false;
    co2 = false;
    co3 = false;
}

void SystemInterface::runMenu() {
  
    while (true) {
        cout << "    QUAN LY BAI DO XE   \n";
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
            if (co1 && co2 && co3) {
                cout << "Da du 3 bai, khong the tao them.\n";
                break;
            }
            int ma; char kt;
            cout << "Ma bai: "; cin >> ma;
            cout << "Kich thuoc (S/M/L): "; cin >> kt;
            
            kt = (char)toupper((unsigned char)kt);
            if (kt != 'S' && kt != 'M' && kt != 'L') {
                cout << "Kich thuoc khong hop le!\n";
                break;
            }
            
            if ((co1 && bai1.lay_ma_bai() == ma) ||
                (co2 && bai2.lay_ma_bai() == ma) ||
                (co3 && bai3.lay_ma_bai() == ma)) {
                cout << "Ma bai da ton tai.\n";
                break;
            }
            if (!co1)      { bai1 = bai_xe(ma, kt); co1 = true; }
            else if (!co2) { bai2 = bai_xe(ma, kt); co2 = true; }
            else           { bai3 = bai_xe(ma, kt); co3 = true; }
            cout << "Da tao bai " << ma << "\n";
            break;
        }

        case 2: {
            if (!co1 && !co2 && !co3) {
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
            if ((co1 && bai1.chua(ma)) || (co2 && bai2.chua(ma)) || (co3 && bai3.chua(ma))) {
                cout << "Ma xe da ton tai.\n";
                break;
            }
            phuong_tien v(ma, loai, gio, tg);
            bool ok = false;
            if (co1 && !ok) ok = bai1.them(v);
            if (co2 && !ok) ok = bai2.them(v);
            if (co3 && !ok) ok = bai3.them(v);
            if (ok) cout << "Da them xe " << ma << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
            else    cout << "Tat ca bai da day.\n";
            break;
        }

        case 3: {
            int ma;
            cout << "Ma bai can xoa: "; cin >> ma;
            if (co1 && bai1.lay_ma_bai() == ma) {
                if (co2) {
                    bai1 = bai2;
                    if (co3) { bai2 = bai3; co3 = false; }
                    else co2 = false;
                }
                else co1 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co2 && bai2.lay_ma_bai() == ma) {
                if (co3) { bai2 = bai3; co3 = false; }
                else co2 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co3 && bai3.lay_ma_bai() == ma) {
                co3 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            else cout << "Khong tim thay bai " << ma << "\n";
            break;
        }

        case 4: {
            int ma;
            cout << "Ma xe can lay ra: "; cin >> ma;
            bool ok = false;
            if (co1 && !ok) ok = bai1.xoa(ma);
            if (co2 && !ok) ok = bai2.xoa(ma);
            if (co3 && !ok) ok = bai3.xoa(ma);
            cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
            break;
        }

        case 5:
            if (!co1 && !co2 && !co3) cout << "Chua co bai do nao.\n";
            if (co1) bai1.hien_thi();
            if (co2) bai2.hien_thi();
            if (co3) bai3.hien_thi();
            break;

        case 6: {
            int ma;
            cout << "Ma bai: "; cin >> ma;
            if (co1 && bai1.lay_ma_bai() == ma) bai1.hien_thi();
            else if (co2 && bai2.lay_ma_bai() == ma) bai2.hien_thi();
            else if (co3 && bai3.lay_ma_bai() == ma) bai3.hien_thi();
            else cout << "Khong tim thay bai " << ma << "\n";
            break;
        }

        case 7: {
            string loai;
            cout << "Loai xe: "; cin >> loai;
            loai = chuanhoaten(loai);
            if (loai == "") {
                cout << "Loai xe khong hop le!\n";
                break;
            }
            int dem; double tong;
            bool tim_thay = false;
            if (co1 && bai1.co_loai(loai, dem, tong)) { bai1.hien_thi(); tim_thay = true; }
            if (co2 && bai2.co_loai(loai, dem, tong)) { bai2.hien_thi(); tim_thay = true; }
            if (co3 && bai3.co_loai(loai, dem, tong)) { bai3.hien_thi(); tim_thay = true; }
            if (!tim_thay) cout << "Khong co xe loai " << loai << "\n";
            break;
        }

        case 8: {
            string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
            for (int t = 0; t < 3; ++t) {
                int dem = 0; double tong = 0;
                int d; double s;
                if (co1) { bai1.co_loai(loai_arr[t], d, s); dem += d; tong += s; }
                if (co2) { bai2.co_loai(loai_arr[t], d, s); dem += d; tong += s; }
                if (co3) { bai3.co_loai(loai_arr[t], d, s); dem += d; tong += s; }
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
