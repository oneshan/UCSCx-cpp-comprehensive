/*
 *   HW 3 - proj3code.cpp
 *   @author: Wan-Shan Liao
 *   @compiler: Apple LLVM version 8.0.0 (clang-800.0.42.1)
 *   @os: macOS Sierra
 *   @date: 2017
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

/********************************************************************
 *   CLASS NAME: CEmployee                                           *
 *   PURPOSE:
 *
 *   MEMBER FUNCTIONS:                                               *
 *     void Open (CEmployee *&pHeadPtr, ifstream& inFile);
 *     void AddEmp (CEmployee *&pHeadPtr, CEmployee *&pCurrPtr );
 *     void DeleteEmp (CEmployee *&pHeadPtr);
 *     void SearchEmp (CEmployee *pHeadPtr);
 *     void ListAllEmp (CEmployee *&pHeadPtr);
 *     void SaveToFile (CEmployee *&pHeadPtr);
 *     void ExitProg (CEmployee *pHeadPtr);                          * 
 **********************************************************************/
class CEmployee {
public:
    void Open (CEmployee *&pHeadPtr, ifstream& inFile);
    void AddEmp (CEmployee *&pHeadPtr, CEmployee *&pCurrPtr);
    void DeleteEmp (CEmployee *&pHeadPtr);
    void SearchEmp (CEmployee *pHeadPtr);
    void ListAllEmp (CEmployee *&pHeadPtr);
    void SaveToFile (CEmployee *&pHeadPtr);
    void ExitProg (CEmployee *pHeadPtr);
  
private:
    char m_Name [20];
    unsigned int m_Age;
    unsigned int m_Salary;
    CEmployee *m_pLink;
};

/********************************************************************
 *   FUNCTION: Open                                                 *
 *   PURPOSE: Read data from the file into a link list in a         *
 *            sorted order by employee name                         *
 *   PARAMETERS: pHeadPtr, inFile                                   *
 *   LOCAL VARIABLES: pCurrPtr, Str, count                          *
 ********************************************************************/
void CEmployee::Open (CEmployee *&pHeadPtr, ifstream& inFile)
{
    char Str[80];   // string to be read from the file
    char d[] = ";"; // delimiter
    int count = 0;  // count of employee reocrds
    CEmployee *pCurrPtr;

    pHeadPtr = 0;
    while (inFile.getline(Str, 80)) {
        pCurrPtr = new CEmployee;
        strcpy(pCurrPtr->m_Name, strtok(Str, d));
        pCurrPtr->m_Age = atoi(strtok(NULL, d));
        pCurrPtr->m_Salary = atoi(strtok(NULL, d));
        this->AddEmp(pHeadPtr, pCurrPtr);   // insert to linked list
        ++count;
    } // while

    inFile.close();
    cout << count << " employee records are imported.\n";
}

/***********************************************************************
 *   FUNCTION:  DeleteEmp                                               *
 *   PURPOSE:  Deletes employees from link list.                        *
 *   PARAMETERS:  pHeadPtr                                              *
 *   LOCAL VARIABLES: pCurrPtr, pLastPtr, Del_name                      *
 ***********************************************************************/
void CEmployee::DeleteEmp (CEmployee *&pHeadPtr)
{
    static char Del_name[20];   // Employee name to delete
    CEmployee *pCurrPtr, *pLastPtr;

    // User input
    cout << "\nEnter Employee Name to delete: ";
    cin.getline(Del_name, sizeof(Del_name));
    cin.clear();

    // Find and delete employee from linked list
    // 1) Empty list
    if (pHeadPtr == NULL) {
        cout << "Name: " << Del_name << " not found\n";
        return;
    }
    // 2) Employee to be deleted is head of linked list
    if (strcmp(pHeadPtr->m_Name, Del_name) == 0) {
        pCurrPtr = pHeadPtr;
        pHeadPtr = pHeadPtr->m_pLink;
        delete pCurrPtr;
        cout << "Name: " << Del_name << " has been deleted\n";
        return;
    }

    // 3) General Case
    pLastPtr = pHeadPtr;
    pCurrPtr = pHeadPtr->m_pLink;
    while (pCurrPtr != NULL) {
        if (strcmp(pCurrPtr->m_Name, Del_name) == 0) {
            pLastPtr->m_pLink = pCurrPtr->m_pLink;
            delete pCurrPtr;
            cout << "Name: " << Del_name << " has been deleted\n";
            return;
        }
        else if (strcmp(pCurrPtr->m_Name, Del_name) > 0) {
            break;
        }
        pLastPtr = pCurrPtr;
        pCurrPtr = pCurrPtr->m_pLink;
    }

    cout << "Name: " << Del_name << " not found\n";
}

/***********************************************************************
 *   FUNCTION: SaveToFile                                               *
 *   PURPOSE: Saves data in link list to data file empinfo.data         *
 *   PARAMETERS: pHeadPtr                                               *
 *   LOCAL VARIABLES: pCurrPtr                                          *
 ***********************************************************************/
void CEmployee::SaveToFile (CEmployee *&pHeadPtr)
{
    CEmployee *pCurrPtr = pHeadPtr;
    char fname[] = "empinfo.dat";   // Filename to save
    ofstream Outfile(fname);

    while (pCurrPtr != NULL){
        Outfile << pCurrPtr->m_Name << "; " << pCurrPtr->m_Age << "; " << pCurrPtr->m_Salary << "\n";
        pCurrPtr = pCurrPtr->m_pLink;
    }

    Outfile.close();
    cout << "Employee List has been saved to file empinfo.dat\n";
    return;
}

/***********************************************************************
 *   FUNCTION: AddEmp                                                   *
 *   PURPOSE:  Adds emmployees to link list.                            *
 *   PARAMETERS:  pHeadPtr, pCurrPtr                                    *
 *   LOCAL VARIABLES:  pTempPtr, temp_name                              *
 ***********************************************************************/
void CEmployee::AddEmp(CEmployee *&pHeadPtr, CEmployee *&pCurrPtr)
{
    static char temp_name[20];

    // User input
    if (pCurrPtr == NULL) {
        cin.clear();
        pCurrPtr = new CEmployee;
        cout << "Enter Employee Name to add: ";
        cin.getline(pCurrPtr->m_Name, sizeof(pCurrPtr->m_Name));
        cin.clear();
        cout << "Enter Employee's Age: ";
        cin >> pCurrPtr->m_Age;
        cout << "Enter Employee's Salary: ";
        cin >> pCurrPtr->m_Salary;
    }
    cout << "Name: " << pCurrPtr->m_Name << " has been added.\n";

    // Insert employee into the sorted linked list
    // 1) list is empty
    if (pHeadPtr == NULL) {
        pHeadPtr = pCurrPtr;
        return;
    }
    // 2) employee name is smaller than head's
    if (strcmp(pHeadPtr->m_Name, pCurrPtr->m_Name) > 0) {
        pCurrPtr->m_pLink = pHeadPtr;
        pHeadPtr = pCurrPtr;
        return;
    }
    // 3) General case
    CEmployee *pTemp = pHeadPtr;
    while (pTemp->m_pLink != NULL) {
         if (strcmp(pTemp->m_pLink->m_Name, pCurrPtr->m_Name) > 0) {
            pCurrPtr->m_pLink = pTemp->m_pLink;
            pTemp->m_pLink = pCurrPtr;
            return;
        }
        pTemp = pTemp->m_pLink;
    }
    // 4) employee name is larger than all employees' name in the list
    pTemp->m_pLink = pCurrPtr;
}

/********************************************************************
 *  FUNCTION: ExitProg
 *  PURPOSE: Exits program and deletes memory spaces that were being
 *        used.
 *  PARAMETERS: pHeadNode
 *  LOCAL VARIABLES:  pCurr, pDeleteThisNode
 ***********************************************************************/
void CEmployee::ExitProg (CEmployee *pHeadNode)
{
    CEmployee *pCurr, *pDeleteThisNode;

    pCurr = pHeadNode;
    while (pCurr != 0)
    {
        pDeleteThisNode = pCurr;
        pCurr = pCurr->m_pLink;
        delete pDeleteThisNode;
    }
}


/*********************************************************************
 *   FUNCTION:  ListAllEmp                                            *
 *   PURPOSE:  Lists all employees in link list to the screen.        *
 *   PARAMETER:  pHeadPtr                                             *
 *   LOCAL VARIABLES: pCurrPtr, count                                 *
 **********************************************************************/
void CEmployee::ListAllEmp (CEmployee *&pHeadPtr)
{
    int count = 0;
    CEmployee *pCurrPtr;

    // Print header
    cout << left << setfill(' ') << "#" << '\t';
    cout << setw(22)  << "Employee Name" << setw(20) << "Age" << setw(7) << "Salary" <<  endl;
    cout << string(60, '=') << endl;

    // Print Employee List
    pCurrPtr = pHeadPtr;
    while (pCurrPtr != NULL)
    {
        cout << ++count << "."  << '\t';
        cout << setw(22) << pCurrPtr->m_Name;
        cout << setw(20) << pCurrPtr->m_Age;
        cout.imbue(std::locale(""));    // add comma in salary field
        cout << setw(7) << pCurrPtr->m_Salary << endl;
        pCurrPtr = pCurrPtr->m_pLink;
    }
}

/*********************************************************************
 *   FUNCTION:  SearchEmp                                             *
 *   PURPOSE:  Searches link list for specified employee.             *
 *   PARAMTERS:  pHeadPtr                                             *
 *   LOCAL VARIABLES: CurrPtr, Search_name, flag                      *
 **********************************************************************/
void CEmployee::SearchEmp (CEmployee *pHeadPtr)
{
    static char Search_name[20];    // Employee name to search
    bool flag = false;              // True if employee name is found in the linked list
    CEmployee *pCurrPtr;

    // User Input
    cout << "\nEnter Employee Name to search: ";
    cin.getline(Search_name, sizeof(Search_name));
    cin.clear();

    // Search linked list
    pCurrPtr = pHeadPtr;
    while (pCurrPtr != NULL) {
        if (strcmp(pCurrPtr->m_Name, Search_name) == 0) {
            flag = true;
            break;
        }
        else if (strcmp(pCurrPtr->m_Name, Search_name) > 0) {
            break;
        }
        pCurrPtr = pCurrPtr->m_pLink;
    }

    // Print Result
    if (flag) {
        cout << "Employee Info: " << pCurrPtr->m_Name;
        cout << ", Age: " << pCurrPtr->m_Age;
        cout.imbue(std::locale(""));    // add comma in salary field
        cout << ", Salary: " << pCurrPtr->m_Salary << endl;
    } else {
        cout << "Name: " << Search_name << " not found" << endl;
    }
}


int main(int argc, char *argv[]) {

    CEmployee *pHeadPtr, *pCurrPtr;
    CEmployee *empList = new CEmployee;
    
    int input = -1;
    enum userInput {Add = 1, Delete, Search, List, Save, Exit};

    if (argc != 2) {
        cout << "Usage: WRITE <filename>\n";
        return 1;
    }

    // Open input file
    ifstream inFile;
    inFile.open(argv[1]);

    // Check if input file exists
    if (inFile) {
        empList->CEmployee::Open(pHeadPtr, inFile);
    }
    else {
        cout << "\nFile does not exist. Use Add and Save options to create file\n";
    }

    while (true) {
        cin.clear();

        cout << "\nMenu Options:" << endl;
        cout << "\t" << "1. Add Employee" << endl;
        cout << "\t" << "2. Delete Employee" << endl;
        cout << "\t" << "3. Search Employee" << endl;
        cout << "\t" << "4. List All Employee" << endl;
        cout << "\t" << "5. Save Employee Database" << endl;
        cout << "\t" << "6. Exit Employee Database" << endl;
        cout << "Enter Your Choice: ";
        cin >> input;

        if (cin.good()){
            if (input < 0) break;
        } //end if
        else if (!isdigit(input)) {
            cout << "Invalid input: must be integer 1~6 \n";
            continue;
        }

        cin.clear();
        cin.ignore(1,'\n');

        switch (input) {
            case Add:
                pCurrPtr = 0;
                empList->AddEmp(pHeadPtr, pCurrPtr);
                break;
            case Delete:
                empList->DeleteEmp(pHeadPtr);
                break;
            case Search:
                empList->SearchEmp(pHeadPtr);
                break;
            case List:
                empList->ListAllEmp(pHeadPtr);
                break;
            case Save:
                empList->SaveToFile(pHeadPtr);
                break;
            case Exit:
                empList->ExitProg(pHeadPtr);
                cout << "Bye Bye!\n";
                return 0;
            default:
                cout << "Invalid input: must be integer 1~6 \n";
                break;
        }
        cout << endl;
    }

    return 0;

}
