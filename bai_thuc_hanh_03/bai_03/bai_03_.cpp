#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string chuanhoaten(const string& loai) {
    if (loai == "car") return "Car";
    if (loai == "motorcycle") return "Motorcycle";
    if (loai == "bicycle") return "Bicycle";
    return loai;
}
//chi nhap moi so
int so(const string& so) {
    int x;
    cout << sp;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Gia tri khong hop le, nhap lai: ";
    }
    return x;
}

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, const string& loai, int gio, int tg);

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

phuong_tien::phuong_tien(int ma, const string& loai, int gio, int tg) {
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
    int suc_chua_ht;           
    int so_luong_pt;
    phuong_tien** ds_xe;        // mang con tro dong tren Heap

    static int suc_chua_ban_dau(char kt);
    void mo_rong(int suc_chua_moi);              
    void giai_phong();                           
    void sao_chep_tu(const bai_xe& other);       

public:
    bai_xe();
    bai_xe(int ma, char kt);
    ~bai_xe();                                   
    bai_xe(const bai_xe& other);                 
    bai_xe& operator=(const bai_xe& other);     

    int lay_ma_bai() const;
    int lay_so_luong() const;
    int lay_suc_chua() const;

    bool them(const phuong_tien& v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(const string& loai, int& dem, double& tong) const;
};

int bai_xe::suc_chua_ban_dau(char kt) {
    return (kt == 'S') ? 1 : (kt == 'M') ? 2 : 3;
}

bai_xe::bai_xe() {
    ma_bai = 0;
    kich_thuoc = 'S';
    suc_chua_ht = suc_chua_ban_dau('S');
    so_luong_pt = 0;
    ds_xe = new phuong_tien*[suc_chua_ht];
    for (int i = 0; i < suc_chua_ht; i++) ds_xe[i] = nullptr;
}

bai_xe::bai_xe(int ma, char kt) {
    ma_bai = ma;
    kich_thuoc = kt;
    suc_chua_ht = suc_chua_ban_dau(kt);
    so_luong_pt = 0;
    ds_xe = new phuong_tien*[suc_chua_ht];
    for (int i = 0; i < suc_chua_ht; i++) ds_xe[i] = nullptr;
}
//ham giai phong
void bai_xe::giai_phong() {
    if (ds_xe != nullptr) {
        for (int i = 0; i < so_luong_pt; i++) {
            delete ds_xe[i];
            ds_xe[i] = nullptr;
        }
        delete[] ds_xe;
        ds_xe = nullptr;
    }
    so_luong_pt = 0;
    suc_chua_ht = 0;
}
//ham sao chep
void bai_xe::sao_chep_tu(const bai_xe& other) {
    ma_bai = other.ma_bai;
    kich_thuoc = other.kich_thuoc;
    suc_chua_ht = other.suc_chua_ht;
    so_luong_pt = other.so_luong_pt;
    ds_xe = new phuong_tien*[suc_chua_ht];
    for (int i = 0; i < suc_chua_ht; i++) ds_xe[i] = nullptr;
    for (int i = 0; i < so_luong_pt; i++)
        ds_xe[i] = new phuong_tien(*other.ds_xe[i]);   // sao chep sau
}

bai_xe::~bai_xe() {
    giai_phong();
}

bai_xe::bai_xe(const bai_xe& other) {
    ds_xe = nullptr;
    sao_chep_tu(other);
}

bai_xe& bai_xe::operator=(const bai_xe& other) {
    if (this != &other) {
        giai_phong();
        sao_chep_tu(other);
    }
    return *this;
}
//ham mo rong
void bai_xe::mo_rong(int suc_chua_moi) {
    if (suc_chua_moi <= suc_chua_ht) return;
    phuong_tien** moi = new phuong_tien*[suc_chua_moi];
    for (int i = 0; i < suc_chua_moi; i++) moi[i] = nullptr;
    for (int i = 0; i < so_luong_pt; i++) moi[i] = ds_xe[i];   // chep con tro cu
    delete[] ds_xe;                                            // chi xoa mang con tro
    ds_xe = moi;
    suc_chua_ht = suc_chua_moi;
}

int bai_xe::lay_ma_bai() const {
    return ma_bai;
}

int bai_xe::lay_so_luong() const {
    return so_luong_pt;
}

int bai_xe::lay_suc_chua() const {
    return suc_chua_ht;
}

bool bai_xe::them(const phuong_tien& v) {
    if (so_luong_pt == suc_chua_ht) {
        cout << "Bai " << ma_bai << " da day, tu dong mo rong " << suc_chua_ht
             << " -> " << suc_chua_ht * 2 << "\n";
        mo_rong(suc_chua_ht * 2);
    }
    ds_xe[so_luong_pt] = new phuong_tien(v);
    so_luong_pt++;
    return true;
}

bool bai_xe::xoa(int ma_xe) {
    for (int i = 0; i < so_luong_pt; i++) {
        if (ds_xe[i]->lay_ma_xe() == ma_xe) {
            delete ds_xe[i];                            //thu hoi bo nho xe
            ds_xe[i] = nullptr;
            for (int j = i; j < so_luong_pt - 1; j++)
                ds_xe[j] = ds_xe[j + 1];                //don sang trai
            ds_xe[so_luong_pt - 1] = nullptr;           //o cuoi = nullptr
            so_luong_pt--;                              //giam so luong
            return true;
        }
    }
    return false;
}

bool bai_xe::chua(int ma_xe) const {
    for (int i = 0; i < so_luong_pt; i++) {
        if (ds_xe[i]->lay_ma_xe() == ma_xe)
            return true;
    }
    return false;
}
//ham hien thi
void bai_xe::hien_thi() const {
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_luong_pt << "/" << suc_chua_ht << " xe\n";
    for (int i = 0; i < so_luong_pt; i++) {
        ds_xe[i]->hien_thi();
    }
}

bool bai_xe::co_loai(const string& loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    for (int i = 0; i < so_luong_pt; i++) {
        if (ds_xe[i]->lay_loai_xe() == loai) {
            dem++;
            tong += ds_xe[i]->tinh_phi();
        }
    }
    return dem > 0;
}

class SystemInterface {
private:
    int suc_chua_bai;           
    int bai_do_hien_tai;        
    bai_xe** baixe;             // mang con tro dong chua cac bai

    int tim_bai(int ma) const;
    int tim_xe(int ma) const;
    void resizeSystem(int suc_chua_moi);
    void giai_phong();
    void sao_chep_tu(const SystemInterface& other);

public:
    SystemInterface();
    ~SystemInterface();                                      
    SystemInterface(const SystemInterface& other);           
    SystemInterface& operator=(const SystemInterface& other);
    void runMenu();
};

SystemInterface::SystemInterface() {
    suc_chua_bai = 5;
    bai_do_hien_tai = 0;
    baixe = new bai_xe*[suc_chua_bai];
    for (int i = 0; i < suc_chua_bai; i++) baixe[i] = nullptr;
}

void SystemInterface::giai_phong() {
    if (baixe != nullptr) {
        for (int i = 0; i < bai_do_hien_tai; i++) {
            delete baixe[i];
            baixe[i] = nullptr;
        }
        delete[] baixe;
        baixe = nullptr;
    }
    bai_do_hien_tai = 0;
    suc_chua_bai = 0;
}

void SystemInterface::sao_chep_tu(const SystemInterface& other) {
    suc_chua_bai = other.suc_chua_bai;
    bai_do_hien_tai = other.bai_do_hien_tai;
    baixe = new bai_xe*[suc_chua_bai];
    for (int i = 0; i < suc_chua_bai; i++) baixe[i] = nullptr;
    for (int i = 0; i < bai_do_hien_tai; i++)
        baixe[i] = new bai_xe(*other.baixe[i]);              // sao chep sau
}

SystemInterface::~SystemInterface() {
    giai_phong();
}

SystemInterface::SystemInterface(const SystemInterface& other) {
    baixe = nullptr;
    sao_chep_tu(other);
}

SystemInterface& SystemInterface::operator=(const SystemInterface& other) {
    if (this != &other) {
        giai_phong();
        sao_chep_tu(other);
    }
    return *this;
}

void SystemInterface::resizeSystem(int suc_chua_moi) {
    if (suc_chua_moi <= suc_chua_bai) return;
    bai_xe** moi = new bai_xe*[suc_chua_moi];
    for (int i = 0; i < suc_chua_moi; i++) moi[i] = nullptr;
    for (int i = 0; i < bai_do_hien_tai; i++) moi[i] = baixe[i];
    delete[] baixe;
    baixe = moi;
    suc_chua_bai = suc_chua_moi;
}

int SystemInterface::tim_bai(int ma) const {
    for (int i = 0; i < bai_do_hien_tai; i++)
        if (baixe[i]->lay_ma_bai() == ma) return i;
    return -1;
}

int SystemInterface::tim_xe(int ma) const {
    for (int i = 0; i < bai_do_hien_tai; i++)
        if (baixe[i]->chua(ma)) return i;
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
        int chon = so("Chon: ");

        switch (chon) {
        case 1: 
            {
            char kt;
            int ma = so("Ma bai: ");
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
            if (bai_do_hien_tai == suc_chua_bai) {
                cout << "He thong day, tu dong mo rong " << suc_chua_bai
                     << " -> " << suc_chua_bai * 2 << "\n";
                resizeSystem(suc_chua_bai * 2);
            }
            baixe[bai_do_hien_tai] = new bai_xe(ma, kt);
            bai_do_hien_tai++;
            cout << "Da tao bai " << ma << "\n";
            break;
        }
        case 2: 
            {
            if (bai_do_hien_tai == 0) {
                cout << "Chua co bai do nao, hay tao bai.\n";
                break;
            }
            string loai;
            int ma_bai = so("Ma bai: ");
            int vt = tim_bai(ma_bai);
            if (vt == -1) {
                cout << "Khong tim thay bai " << ma_bai << "\n";
                break;
            }
            int ma = so("Ma xe: ");
            cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
            loai = chuanhoaten(loai);
            if (loai == "") {
                cout << "Loai xe khong hop le!\n";
                break;
            }
            int gio = so("Gio vao (0-23): ");
            int tg = so("Thoi luong (1-23): ");
            if (gio < 0 || gio > 23 || tg < 1 || tg > 23) {
                cout << "Gio vao hoac thoi luong khong hop le!\n";
                break;
            }
            if (tim_xe(ma) != -1) {
                cout << "Ma xe da ton tai.\n";
                break;
            }
            phuong_tien v(ma, loai, gio, tg);
            baixe[vt]->them(v);
            cout << "Da them xe " << ma << " | Phi: $" << fixed << setprecision(2)
                 << v.tinh_phi() << "\n";
            break;
        }
        case 3: 
            {
            int ma = so("Ma bai can xoa: ");
            int vt = tim_bai(ma);
            if (vt == -1) {
                cout << "Khong tim thay bai " << ma << "\n";
                break;
            }
            delete baixe[vt];                       // giai phong bai + toan bo xe ben trong
            baixe[vt] = nullptr;
            for (int j = vt; j < bai_do_hien_tai - 1; j++)
                baixe[j] = baixe[j + 1];            // don mang con tro
            baixe[bai_do_hien_tai - 1] = nullptr;
            bai_do_hien_tai--;
            cout << "Da xoa bai " << ma << "\n";
            break;
        }
        case 4: 
            {
            int ma = so("Ma xe can lay ra: ");
            int vt = tim_xe(ma);
            if (vt != -1) {
                baixe[vt]->xoa(ma);
                cout << "Da lay xe ra\n";
            }
            else cout << "Khong tim thay xe\n";
            break;
        }
        case 5:
            if (bai_do_hien_tai == 0)
                cout << "Chua co bai do nao.\n";
            for (int i = 0; i < bai_do_hien_tai; i++)
                if (baixe[i] != nullptr) baixe[i]->hien_thi();   // bo qua o nullptr
            break;
        case 6: {
            int ma = so("Ma bai: ");
            int vt = tim_bai(ma);
            if (vt != -1) baixe[vt]->hien_thi();
            else cout << "Khong tim thay bai " << ma << "\n";
            break;
        }
        case 7:
            {
            string loai;
            cout << "Loai xe: "; cin >> loai;
            loai = chuanhoaten(loai);

            int dem; double tong;
            bool tim_thay = false;
            for (int i = 0; i < bai_do_hien_tai; i++) {
                if (baixe[i]->co_loai(loai, dem, tong)) {
                    baixe[i]->hien_thi();
                    tim_thay = true;
                }
            }
            if (!tim_thay) cout << "Khong co xe loai " << loai << "\n";
            break;
        }
        case 8: 
            {
            string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
            for (int t = 0; t < 3; ++t) {
                int dem = 0; double tong = 0;
                for (int i = 0; i < bai_do_hien_tai; i++) {
                    int d; double s;
                    baixe[i]->co_loai(loai_arr[t], d, s);
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
            cout << "Goodbye, no see you again!" << endl;
            return;   
        default:
            cout << "Lua chon chua hop le.Chon lai\n";
            break;
        }
    }
}
int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
