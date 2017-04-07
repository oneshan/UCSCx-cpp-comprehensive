/*
 *   HW 2 - proj2code.cpp
 *   @author: Wan-Shan Liao
 *   @compiler: Apple LLVM version 8.0.0 (clang-800.0.42.1)
 *   @os: macOS Sierra
 *   @year: 2017
 */

#include <iostream>
#include <limits>
using namespace std;

#define MAXSIZE 5

class CarNode {
    public:
	    CarNode() : m_pNext(0), m_ticketNum(0) {}
	    ~CarNode() {}
	    CarNode(CarNode &) : m_pNext(0), m_ticketNum(0) {}
	
	    // assign next pointer
	    void SetNext(CarNode* p) {m_pNext=p;}
	
	    // assign ticket number
	    void SetTicketNum(int tN) {m_ticketNum=tN;}
	
	    // get the next pointer
	    CarNode *GetNext(void) {return(m_pNext);}
	
	    // get the ticket number
	    int GetTicketNum(void) {return(m_ticketNum);}

    private:
        int m_ticketNum;    // ticket number of car
        CarNode *m_pNext;   // pointer to next node in stack
};

class CAlley {
    public:
        CAlley() : m_pTop(0), mSize(0), mMaxSize(MAXSIZE) {}
        ~CAlley() {}
        CAlley(CAlley &) : m_pTop(0), mSize(0), mMaxSize(MAXSIZE) {}

        int Park(int);                  // park a car
        void Retrieve(int, CAlley *);   // retrieve a car
        void Terminate();               // quit the program
        void Display();                 // display contents af alley

    private:
        void SetTop(CarNode *p) {m_pTop=p;} // assign top pointer

        // check if stack is empty
        bool Empty() {return ((mSize==0) ? true : false);}
        
        // check if stack is full
        bool Full() {return ((mSize==MAXSIZE) ? true : false);}
        
        // push one node onto top of stack
        int Push(CarNode *);
        
        // pop one node from the top of stack 
        CarNode * Pop();

        CarNode *m_pTop;     // pointer to top of Alley (stack)
        int mSize;           // number of nodes in Allay (stack) 
        int mMaxSize;        // max number of nodes in Alley (stack)
};

// Display all cars in Alley A
void CAlley::Display() 
{
    cout << "Alley A: ";
    CarNode *pCurrent = m_pTop;
    while (pCurrent != NULL) {
        cout << pCurrent->GetTicketNum() << " ";
        pCurrent = pCurrent->GetNext();
    }
    cout << endl;
}


// Delete Linked List nodes
void CAlley::Terminate()
{
    CarNode *pCurrent, *pDelete;
    while (!Empty()){
        pCurrent = Pop();
        pDelete = pCurrent;
        delete pDelete;
        pCurrent = pCurrent->GetNext();
    }
}

////////////////////////////////////////////////////////////////
// Function: CAlley::Push
// Purpose: Add a new node to top of stack
// Parameters:
// CarNode * pNewNode- the node to be added to top of stack
// Local Variables:
//   status - return 1 if pushed sucessfully
//          - return 0 if stack was full
////////////////////////////////////////////////////////////////

int CAlley::Push(CarNode* pNewNode)
{
    if (Full()) {
        return 0;
    }
    if (Empty()) {
        pNewNode->SetNext(NULL);
    } else {
        pNewNode->SetNext(m_pTop);
    }
    m_pTop = pNewNode;
    mSize++;
    return 1;
}

/////////////////////////////////////////////////////////////////
// Function: CAlley::Pop
// Purpose: Remove a node to top of Allay (stack).
// Parameters:
// CarNode * pNewNode- returns the node removed from top of Allay
//                     is zero if stack is empty
// Local Variables:
/////////////////////////////////////////////////////////////////
CarNode * CAlley::Pop()
{
    if (Empty()) {
        return NULL;
    } else {
        CarNode *pNewNode = m_pTop;
        m_pTop = m_pTop->GetNext();
        mSize--;
        return pNewNode;
    }
}

///////////////////////////////////////////////////////////////
// Function: CAlley::Park ( )
// Purpose: Park a car, if lot is not full. First allocate a
//          node, then add it to the top of the stack
// Parameters:
//   userTicketNum  - the ticket number for the node to be added
// Local Variables:
//   CarNode *pNewNode - local pointer to newly allocated node
//   int status        - 1 if parked sucessfully (lot not full)
//                       0 if not parked (lot was full)
///////////////////////////////////////////////////////////////

int CAlley::Park(int userTicketNum)
{
    CarNode *pNewNode = new CarNode;
    pNewNode->SetTicketNum(userTicketNum);

    if (!Push(pNewNode)) {
        cout << "My LOT is FULL\n";
        delete pNewNode;
        return 0;
    }

    cout << "Ticket No.: " << pNewNode->GetTicketNum() << endl;
    return 1;
}

///////////////////////////////////////////////////////////////
// Function: CAlley:: Retrieve ( int userTicketNum, CAlley *pB)
// Purpose: Retrieve a car from alley A. Search for the car/node
// based on ticket num. by driving a car (popping off top) out of
// A and driving (pushing onto top) into B.
// If the car is found, it is not pushed onto B, but rather,
// it is deleted. Then the cars in B are moved back into A.
//
// Parameters:
//   userTicketNum      - the ticket number for the node to be
//                        added pointer to CAlley B
//
// Local Variables:
//   CarNode *pCurr     - local pointer used as index
//   int found          - 1 if car is found, 0 if not found
///////////////////////////////////////////////////////////////

void CAlley::Retrieve(int userTicketNum, CAlley *AlleyB)
{
    if (this->Empty()) {
        cout << "Lot is Empty, No car to Retireve\n";
        return;
    }

    // Move cars from AlleyA to AlleyB
    // until userTicketNum is found or Alley is empty
    int found = 0;
    while (!this->Empty()) {
        CarNode *topA = this->Pop();
        if (topA->GetTicketNum() == userTicketNum) {
            found = 1;
            break;
        }
        AlleyB->Push(topA);
    }
    if (!found)
        cout << "CAR NOT PARKED IN MY LOT" << '\n';

    // Move all cars from AlleyB back to AlleyA
    while (!AlleyB->Empty()) {
       CarNode *topB = AlleyB->Pop();
       this->Push(topB);
    }

    return;
}

int main()
{
    CAlley *AlleyA = new CAlley();
    CAlley *AlleyB = new CAlley();

    enum userInput {DISPLAY='d', PARK='p', RETRIEVE='r', QUIT='q'};
    int ticketNumber = 1;
    char userCh;

    while (true) {
        cout << "D)isplay\tP)ark\tR)etrieve\tQ)uit: ";
        cin >> userCh; 
        switch (tolower(userCh)) {
            case DISPLAY:
                AlleyA->Display();
                break;
            case PARK:
                if (AlleyA->Park(ticketNumber)) {
                    ticketNumber++;
                }
                break;
            case RETRIEVE:
                int userNum;
                cout << "Ticket no: ";
                cin >> userNum;
                if (cin.good()){
                    if (userNum < 0) {
                        cout << "Invalid input: Ticket Number must be positive integer\n";
                        break;
                    }
                    AlleyA->Retrieve(userNum, AlleyB);
                } else {
                    cout << "Invalid input: Ticket Number must be positive integer\n";
                }
                // reset the stream state back to a good state
                cin.clear();
                // remove all remaining junk from the stream
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case QUIT:
                cout << "\nBye bye!\n";
                AlleyA->Terminate();
                return 0;
            default:
                cout << "Invalid input: Must be Dd/Pp/Rr/Qq \n";
                break;
        }
        cout << endl;
    }
    return 0;
}
