/*
 *   HW 4 - proj4code.cpp
 *   @author: Wan-Shan Liao
 *   @compiler: Apple LLVM version 8.0.0 (clang-800.0.42.1)
 *   @os: macOS Sierra
 *   @date: 3/05/2017
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
using namespace std;

// This data structure should be a record in a input file
struct AirFile {
    int Type;
    char Name[20];
    int nPassenger;
    int nWeight;
    int EngineGas;
    int Range;
};

enum AirShipType {AIRPLANE, BALLOON};
enum EngineType {JET, PROPELLER};
enum GasType {HELIUM, HYDROGEN};

// Base Class
class CAirship {
    public:
        CAirship() { }
        virtual void GetData(AirFile &data) = 0;
        virtual void ShowData() = 0;
        AirShipType GetAirshipType() {return m_AirshipType;}
    protected:
        AirShipType m_AirshipType;
};

// Derived Class
class CAirplane : public CAirship {
    public:
        CAirplane() : CAirship() {}
        void GetData(AirFile &data);
        void ShowData();
        const char *SetEngineType(EngineType Engine);
    private:
        int m_Range;
        char m_Name[20];
        EngineType m_Engine;
};


// Function: SetEngineType
const char *CAirplane::SetEngineType(EngineType Engine)
{
    switch (Engine) {
        case JET:
            return "Jet";
            break;
        case PROPELLER:
            return "Propeller";
            break;
        default:
            return "No Engine Type";
            break;
    } //end switch
}

// Function: GetData
void CAirplane::GetData(AirFile &data)
{
    // cast integer to enum
    m_AirshipType = AirShipType(data.Type);
    // cast integer to enum
    m_Engine = EngineType(data.EngineGas);

    strcpy(m_Name, data.Name);
    m_Range = data.Range;
}

// Function: ShowData
void CAirplane::ShowData()
{
    cout << setw(20) << left << m_Name << setw(10);
    cout << SetEngineType(m_Engine) << setw(10) << "\t" << m_Range << endl;
}


// Derived Class
class CBalloon : public CAirship {
    public:
        CBalloon() : CAirship() {}
        void GetData(AirFile &data);
        void ShowData();
        const char *SetGasType(GasType Gas);
    private:
        int m_Range;
        char m_Name[20];
        GasType m_Gas;
};

// Function: SetGasType
const char *CBalloon::SetGasType(GasType Gas)
{
    switch (Gas) {
        case HELIUM:
            return "Helium";
            break;
        case HYDROGEN:
            return "Hydrogen";
            break;
        default:
            return "No Engine Type";
            break;
    } //end switch
}

// Function: GetData
void CBalloon::GetData(AirFile &data)
{
    // cast integer to enum
    m_AirshipType = AirShipType(data.Type);
    // cast integer to enum
    m_Gas = GasType(data.EngineGas);

    strcpy(m_Name, data.Name);
    m_Range = data.Range;
}

// Function: ShowData
void CBalloon::ShowData()
{
    cout << setw(20) << left << m_Name << setw(10);
    cout << SetGasType(m_Gas) << setw(10) << "\t" << m_Range << endl;
}

// Airplane = 0
// Ballon = 1
int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: PR <filename>\n";
        return 1;
    }

    ifstream Infile(argv[1]);
    if (!Infile) {
        cout << "Cannot open file\n";
        return 1;
    }

    char LineBuf[100];
    char d[] = ",";

    CAirship *pAirship[10];
    int i = 0;

    while (!Infile.eof() && Infile.getline(LineBuf, 100)) {
        struct AirFile data;
        data.Type = atoi (strtok(LineBuf, d));

        switch (data.Type) {
            case AIRPLANE:
            // Create Airplane Object
                pAirship[i] = new CAirplane();
                strcpy(data.Name,strtok(NULL, d));
                data.nPassenger = atoi (strtok(NULL, d));
                data.nWeight = atoi (strtok(NULL, d));
                data.EngineGas = atoi (strtok(NULL, d));
                data.Range = atoi (strtok(NULL, d));
                break;
            case BALLOON:
            // Create Balloon Object
                pAirship[i] = new CBalloon();
                strcpy(data.Name ,strtok(NULL, d));
                data.nPassenger = atoi (strtok(NULL, d));
                data.nWeight = atoi (strtok(NULL, d));
                data.EngineGas = atoi (strtok(NULL, d));
                data.Range = atoi (strtok(NULL, d));
                break;
            default:
                break;
        } // end switch

        // call appropriate function
        pAirship[i++]->GetData(data);
        memset(LineBuf,'\0',100);
    }

    cout << "\n\nList of all Airplanes\n";
    cout << setw(20) << left << "Name" << "Engine Type";
    cout << "\t\tMaximum Range" << "\n";
    cout << "------------------------------------------------\n";

    for (int i = 0; i < 10; ++i)
        if (pAirship[i]->GetAirshipType() == AIRPLANE)
            pAirship[i]->ShowData();
    
    cout << "\n\nList of all Balloons\n";
    cout << setw(20) << left << "Name" << "Gas Type";
    cout << "\t\tMaximum Altitude" << "\n";
    cout << "----------------------------------------------------\n";
    for (int i = 0; i < 10; ++i)
        if (pAirship[i]->GetAirshipType() == BALLOON)
            pAirship[i]->ShowData();
    
    // Delete appropriate object
    for (int i = 0; i < 10; i++)
        if (pAirship[i])
            delete pAirship[i];

    return 0;
}
