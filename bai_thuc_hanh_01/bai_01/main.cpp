#include <iomanip>
#include <string>
#include <iostream>
using namespace std;
class Vehicle {
    private:
    int VehicleID;
    std::string VehicleType;   //car, motobike, bicycle
    int entryTime;            
    int parkingDuration;       //thoi luong
    double parkingFee;
    bool isOccupied; //dangChiemCho

    public:
    //khai bao ham tao
    Vehicle();
    Vehicle(int id, const string& type, int entry, int duration);

    //Getter
    int getVehicleID() const;
    string getVehicleType() const;
    int entryTime() const;
    int getparkingDuration() const;
    double getparkingFee() const;
    bool getisOccupied() const;

    //Setter
    void setVehicleID(int id);
    void setVehicleType(const string& type);
    void setentryTime(int giovao);
    void setparkingDuration(int thoiluong);
    void setparkingFee(double phido);
    void setisOccupied(bool trangthai);

    static string ChuanHoaLoaiXe(const string& type)
    static bool laLoaixeHopLe(const string& type)
    
    void calculateFee();
    void display() const;
};
    
    Vehicle();
        {
        VehicleID = 0;
        VehicleType = "Unknown";
        entryTime = 0;
        parkingDuration = 1;
        parkingFee = 0.0;
        isOccupied = false;
        }
        
        
    Vehicle(int id, std::string type, int entry, double fee, int duration, bool occupied)
    {
        VehicleID = id;
        VehicleType = loaixe;
        entryTime = giovao;
        parkingFee = phido;
        parkingDuration = thoiluong;
        isOccupied = true;
        calculateFee();  
    }

//Getter
int getVehicleID() const { return VehicleID; }
std::string getVehicleType() const { return VehicleType; }
int entryTime() const { return entryTime; }
int getparkingDuration() const { return parkingDuration; }
double getparkingFee() const { return parkingFee; }
bool getisOccupied() const { return isOccupied; }

//Setter
void setVehicleID(int id) { VehicleID = id; }

void setVehicleType(std::string type)
 {
    std::string type = loaixe;
    if(loaixe == "Car" || loaixe == "Motorcycle" || loaixe == "Bicycle")
    {
        VehicleType = loaixe;
    }
    else
    {
        VehicleType = "Unknown";
    }
 }


void setentryTime(int entry)
{
    if(entry >= 0 && entry <= 23)
    {
        entryTime = giovao;
    }
    else
    {
        entryTime = 0;
    }
}


void setparkingDuration(int duration) 
{ 
    if(duration >= 1 && duration <=23)
    {
        parkingDuration = thoiluong;
    }
    else
    {
        parkingDuration = 1;
    }
}


void setparkingFee(double fee) 
{
    if(fee >= 0)
    {
        parkingFee = phido;
    }
    else
    {
        parkingFee = 0.0;
    }
}

void setisOccupied(bool trangthai) 
{
    isOccupied = trangthai;
}

void calculateFee()
{
    double phicoban = 0.0;
    if(VehicleType == "Car") 
    {
        phicoban = 6.00;
    } 
    else if (VehicleType == "Motorcycle") 
    {
        phicoban = 4.00;
    } 
    else if (VehicleType == "Bicycle") 
    {
        phicoban = 2.00;
    }

    bool giocaodiem = (entryTime >= 6 && entryTime <= 9) || (entryTime >= 15 && entryTime <= 18);
    parkingFee = 0.0;
    for(int i = 0; i < parkingDuration; ++i) 
    if( i<=2 )
    {
        if(giocaodiem) 
        {
            parkingFee += phicoban * 1.3;
        } 
        else 
        {
            parkingFee += phicoban * 0,95;
        }
    }
    else
    {
        parkingFee += phicoban * 0,9;
    }
}

void display() const
{
    if(!isOccupied) return;
    std::cout << "Vehicle ID: " << VehicleID << std::endl;
    std::cout << "Vehicle Type: " << VehicleType << std::endl;
    std::cout << "Entry Time: " << entryTime  << std::endl;
    std::cout << "Parking Duration: " << parkingDuration << std::endl;
    std::cout << "Parking Fee: $" << std::fixed << std::setprecision(2) << parkingFee << std::endl;
}


class ParkingLot {

    private:
    int parkID;
    char size;
    Vehicle vehicle1;
    Vehicle vehicle2;
    Vehicle vehicle3;
    bool hasVehicle1;
    bool hasVehicle2;
    bool hasVehicle3;

    public:
    ParkingLot();
    ParkingLot(int id, char size);
    bool addVehicle(const Vehicle& vehicle);
    bool removeVehicle(int vehicleID);
    void displayLotInfo() const;
    };


    ParkingLot();
    {
        parkID = 0;
        size = 'S';
        hasVehicle1 = false;
        hasVehicle2 = false;
        hasVehicle3 = false;
    }

    ParkingLot(int id, char size)
    {
        parkID = id;
        if(size == 'S')
        {
            size = 'S';
        }
        else if(size == 'M')
        {
            size = 'M';
        }
        else if(size == 'L')
        {
            size = 'L';
        }
        else size = 'S';
        hasVehicle1 = false;
        hasVehicle2 = false;
        hasVehicle3 = false;
    }

    bool addVehicle(const Vehicle& vehicle)
    {
        if(size == 'S')   //S chứa 1 xe
        if(!hasVehicle1)
        {
            vehicle1 = vehicle;
            hasVehicle1 = true;
            return true;
        }
        else
        {
            return false;
        }

        if(size == 'M')   //M chứa 2 xe
        if(!hasVehicle1)
        {
            vehicle1 = vehicle;
            hasVehicle1 = true;
            return true;
        }
        else if(!hasVehicle2)
        {
            vehicle2 = vehicle;
            hasVehicle2 = true;
            return true;
        }
        else
        {
            return false;
        }

        if(size == 'L')   //L chứa 3 xe
        {
            if(!hasVehicle1)
            {
                vehicle1 = vehicle;
                hasVehicle1 = true;
                return true;
            }
            else if(!hasVehicle2)
            {
                vehicle2 = vehicle;
                hasVehicle2 = true;
                return true;
            }
            else if(!hasVehicle3)
            {
                vehicle3 = vehicle;
                hasVehicle3 = true;
                return true;
            }
            else
            {
                return false;
            }
        }

        bool removeVehicle(int vehicleID)
        {
            if(hasVehicle1 && vehicle1.getVehicleID() == vehicleID)
            {
                hasVehicle1 = false;
                return true;
            }
            else if(hasVehicle2 && vehicle2.getVehicleID() == vehicleID)
            {
                hasVehicle2 = false;
                return true;
            }
            else if(hasVehicle3 && vehicle3.getVehicleID() == vehicleID)
            {
                hasVehicle3 = false;
                return true;
            }
            else
            {
                return false;
            }
        }

        void displayLotInfo() const
        {
            std::cout << "Parking Lot ID: " << parkID << std::endl;
            std::cout << "Size: " << size << std::endl;
            if(hasVehicle1)
            {
                std::cout << "Vehicle 1 Info:" << std::endl;
                vehicle1.display();
            }
            if(hasVehicle2)
            {
                std::cout << "Vehicle 2 Info:" << std::endl;
                vehicle2.display();
            }
            if(hasVehicle3)
            {
                std::cout << "Vehicle 3 Info:" << std::endl;
                vehicle3.display();
            }

        }
        class SystemInterface {

            private:
            ParkingLot parkingLot1;
            ParkingLot parkingLot2;
            ParkingLot parkingLot3;
            bool hasLot1;
            bool hasLot2;
            bool hasLot3;

            public:
            SystemInterface();
            void runMenu();
        };

            SystemInterface()
            {
                hasLot1 = false;
                hasLot2 = false;
                hasLot3 = false;
            }
            void runMenu()
            {
                int chucnang = 0;
                while(chucnang != 9)
                {
                    std::cout << "Menu:" << std::endl;
                    std::cout << "1. Tạo bãi đỗ xe mới" << std::endl;
                    std::cout << "2. Thêm xe vào bãi đỗ" << std::endl;
                    std::cout << "3. Xoá một bãi đỗ xe" << std::endl;
                    std::cout << "4. Lấy xe ra khỏi bãi đỗ" << std::endl;
                    std::cout << "5. Hiển thị danh sách tất cả bãi đỗ xe" << std::endl;
                    std::cout << "6. Hiển thị danh sách xe theo bãi cụ thể" << std::endl;
                    std::cout << "7. Liệt kê xe theo loại phương tiện" << std::endl;
                    std::cout << "8. Xem báo cáo tóm tắt phí đỗ xe trung bình" << std::endl;
                    std::cout << "9. Thoát chương trình" << std::endl;
                    std::cout << "Chọn chức năng bạn cần: ";
                    std::cin >> chucnang;

                    switch(chucnang)
                    {
                        case 1:
                            int id = 0;
                            char size = 'S';
                            std::cout << "Nhập parking lot ID: ";
                            std::cin >> id;
                            std::cout << "Nhập kích thước: ";
                            std::cin >> size;

                            if(!hasLot1)
                            {
                                parkingLot1 = ParkingLot(id, size);
                                hasLot1 = true;
                            }
                            else if(!hasLot2)
                            {
                                parkingLot2 = ParkingLot(id, size);
                                hasLot2 = true;
                            }
                            else if(!hasLot3)
                            {
                                parkingLot3 = ParkingLot(id, size);
                                hasLot3 = true;
                            }
                            else
                            {
                                std::cout << "Không thể tạo thêm bãi đỗ xe." << std::endl;
                            }
                            break;

                        case 2:
                            int vehicleID = 0; entryTime = 0; parkingDuration = 0;
                            std::cout << "Nhập vehicle ID: ";
                            std::cin >> vehicleID;
                            std::cout << "Nhập loại xe: "; 
                            std::cin >> vehicleType;  
                            std::cout << "Nhập giờ xe vào: ";
                            std::cin >> entryTime;
                            std::cout << "Nhập thời lượng đỗ xe: ";
                            std::cin >> parkingDuration;
                            Vehicle( vehicldeID, VehicleType, entryTime, parkingDuration);
                            bool added = false;
                            if(hasLot1)
                            {
                                added = parkingLot1.addVehicle(vehicle);
                            }
                            if(!added && hasLot2)
                            {
                                added = parkingLot2.addVehicle(vehicle);
                            }
                            if(!added && hasLot3)
                            {
                                added = parkingLot3.addVehicle(vehicle);
                            }
                            if(!added)
                            {
                                std::cout << "Không thể thêm xe vào bất kỳ bãi đỗ nào." << std::endl;
                            }

                            break;


                        case 3:
                            int id = 0;
                            std::cout << "Nhập parking lot ID muốn xoá: ";
                            std::cin >> id;
                            if(hasLot1 && parkingLot1.getParkID() == id)
                            {
                                hasLot1 = false;
                                std::cout << "Đã xoá bãi đỗ xe 1." << std::endl;
                            }
                            else if(hasLot2 && parkingLot2.getParkID() == id)
                            {
                                hasLot2 = false;
                                std::cout << "Đã xoá bãi đỗ xe 2." << std::endl;
                            }
                            else if(hasLot3 && parkingLot3.getParkID() == id)
                            {
                                hasLot3 = false;
                                std::cout << "Đã xoá bãi đỗ xe 3." << std::endl;
                            }
                            else
                            {
                                std::cout << "Không tìm thấy bãi đỗ xe với ID đã nhập." << std::endl;
                            }
                            break;

                    
                        case 4:
                            int vehicleID = 0;
                            std::cout << "Nhập vehicle ID muốn lấy ra: ";
                            std::cin >> vehicleID;
                            bool removed = false;
                            if(hasLot1)
                            {
                                removed = parkingLot1.removeVehicle(vehicleID);
                            }  
                            if(!removed && hasLot2)
                            {
                                removed = parkingLot2.removeVehicle(vehicleID);
                            }
                            if(!removed && hasLot3)
                            {
                                removed = parkingLot3.removeVehicle(vehicleID);
                            }
                            if(removed)
                            {
                                std::cout << "Đã lấy xe ra khỏi bãi đỗ." << std::endl;
                            }
                            else
                            {
                                std::cout << "Không tìm thấy xe với ID đã nhập." << std::endl;
                            }
                            break;

                        case 5:
                            if(hasLot1)
                            {
                                parkingLot1.displayLotInfo();
                            }
                            if(hasLot2)
                            {
                                parkingLot2.displayLotInfo();
                            }
                            if(hasLot3)
                            {
                                parkingLot3.displayLotInfo();
                            }
                            break;


                        case 6:
                            int id = 0;
                            std::cout << "Nhập parking lot ID muốn hiển thị: ";
                            std::cin >> id;
                            if(hasLot1 && parkingLot1.getParkID() == id)
                            {
                                parkingLot1.displayLotInfo();
                            }
                            else if(hasLot2 && parkingLot2.getParkID() == id)
                            {
                                parkingLot2.displayLotInfo();
                            }
                            else if(hasLot3 && parkingLot3.getParkID() == id)
                            {
                                parkingLot3.displayLotInfo();
                            }
                            else
                            {
                                std::cout << "Không tìm thấy bãi đỗ xe với ID đã nhập." << std::endl;
                            }
                            break;
                        
                        case 7:
                            std::string type;
                            std::cout << "Nhập loại phương tiện muốn liệt kê: ";
                            std::cin >> type;
                            if(hasLot1)
                            {
                                parkingLot1.displayVehiclesByType(type);
                            }
                            if(hasLot2)
                            {
                                parkingLot2.displayVehiclesByType(type);
                            }
                            if(hasLot3)
                            {
                                parkingLot3.displayVehiclesByType(type);
                            }
                            break;

                        case 8:
                            double tongtien = 0.0;
                            int totalVehicles = 0;
                            if(hasLot1)
                            {
                                tongtien += parkingLot1.calculateTotalFee();
                                totalVehicles += parkingLot1.countVehicles();
                            }
                            if(hasLot2)
                            {
                                tongtien += parkingLot2.calculateTotalFee();
                                totalVehicles += parkingLot2.countVehicles();
                            }
                            if(hasLot3)
                            {
                                tongtien += parkingLot3.calculateTotalFee();
                                totalVehicles += parkingLot3.countVehicles();
                            }
                            std::cout << "Tổng doanh thu: " << tongtien << std::endl;
                            if(totalVehicles > 0)
                            {
                                std::cout << "Phí đỗ xe trung bình: " << (tongtien / totalVehicles) << std::endl;
                            }
                            else
                            {
                                std::cout << "Không có xe nào trong bãi đỗ." << std::endl;
                            }
                            break;
                        
                        case 9:
                            std::cout << "Đóng hệ thống quản lý bãi đỗ xe" << std::endl;
                            break;
                        default:
                            std::cout << "Vui lòng chọn chức năng bạn muốn sử dụng." << std::endl;
                    }
                }
            }
}

