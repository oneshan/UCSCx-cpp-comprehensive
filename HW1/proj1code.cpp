/*
 *   HW 1 - proj1code.cpp
 *   @author: Wan-Shan Liao
 *   @compiler: Apple LLVM version 8.0.0 (clang-800.0.42.1)
 *   @os: macOS Sierra
 *   @year: 2017
 */

/* MAGIC SQUARE - An NxN matrix containing values from 1 to N*N that are  */
/* ordered so that the sum of the rows, columns, and the major diagonals  */
/* are all equal.  There is a particular algorithm for odd integers, and  */
/* this program constructs that matrix, up to 13 rows and columns.  This   */
/* program also adds the sums of the row, columns, and major diagonals.   */

#include <iostream>
#include <limits>
#include <cctype>
#include <iomanip>      // use setw() for setting field width
using namespace std;

class CMatrix {
    private:
        int nInput, nOtherDiag;
        int **pnMatrix;

    public:
        void Init();
        bool CheckAndSetInput(int input);
        void RunMagic();
        void Display();
        void DeleteMatrix();
};

int main(int argc, char *argv[])
{
    CMatrix *ptrMatrixData = new CMatrix;
    int input = 0;  // User defined integer

    // Print introduction of what this program is all about.
    cout << "\nMagic Squares: This program produces an NxN matrix where\n";
    cout << "N is some positive odd integer.  The matrix contains the \n";
    cout << "values 1 to N*N.  The sum of each row, each column, and \n";
    cout << "the two main diagonals are all equal.  Not only does this \n";
    cout << "program produces the matrix, it also computes the totals for\n";
    cout << "each row, column, and two main diagonals.\n";
    cout << "\nBecause of display constraints, this program can work with\n";
    cout << "values up to 13 only.\n\n";
    cout << "Enter a positive, odd integer (-1 to exit program):\n";

    // Get input from user, if input is valid then compute and display the magic matrix
    while (cin >> input || !cin.eof())
    {
        if (cin.good()) {
            if (input == -1)
                break;

            if (ptrMatrixData->CheckAndSetInput(input)) {
                ptrMatrixData->Init();
                ptrMatrixData->RunMagic();
                ptrMatrixData->Display();
                ptrMatrixData->DeleteMatrix();
            }
        } else if (!isdigit(input)) {
            cout << "Not a number\n";
        }

        // reset the stream state back to a good state
        cin.clear();
        // remove all remaining junk from the stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter a positive, odd integer (-1 to exit program):\n";
    } // End of while input > -1 loop

    delete ptrMatrixData;
    cout << "\nBye bye!\n";
}

bool CMatrix::CheckAndSetInput(int input)
{
    nInput = input;
    // Validity check for input: Must be a positive odd integer < 13.
    if (nInput <= 0) {
        cout << "Sorry, but the integer has to be positive.\n";
        return false;
    }
    if (nInput > 13) {
        cout << "Sorry, but the integer has to be less than 15.\n";
        return false;
    }
    if (nInput % 2 == 0) {
        cout << "Sorry, but the integer has to be odd.\n";
        return false;
    }
    return true;
}
void CMatrix::Init()
{
    // Initialize pnMatrix and nOtherDiag
    nOtherDiag = 0;
    pnMatrix = new int* [nInput + 1];
  
    for (int row = 0; row <= nInput; ++row) {
        pnMatrix[row] = new int [nInput + 1];
    }

    for (int row = 0; row <= nInput; ++row) {
        for (int col = 0; col <= nInput; ++col) {
            pnMatrix[row][col] = 0;
        }
    }
}

void CMatrix::RunMagic()
{
    // First value gets to sit on 1st row, middle of matrix.
    int row = 1;
    int col = nInput / 2 + 1;

    // Loop for every value up to input*input, and position value in matrix
    for (int value = 1; value <= nInput * nInput; ++value) {
        if (pnMatrix[row][col] > 0) {
            row += 2;
            if (row > nInput)
                row -= nInput;

            col--;
            if (col < 1)
                col = nInput;
        }

        // Assign value to location.
        pnMatrix[row][col] = value;

        // Add to totals
        pnMatrix[0][col] += value;      // Add to its column total.
        pnMatrix[row][0] += value;      // Add to its row total.
        if (row == col)
            pnMatrix[0][0] += value;    // Add to diagonal total if it falls on diagonal
        if (row + col == nInput + 1)
            nOtherDiag += value;        // Add to other diagonal if it falls on line

        // Determine where new row and col are
        row--;
        if (row < 1)
            row = nInput;               // if row exceeds side then go to other side
        col++;
        if (col > nInput)
            col = 1;                    // if col exceeds side then go to other side
    }
}

void CMatrix::Display()
{
    // Print out the matrix with its totals
    
    cout << "\nThe number you selected was " << nInput;
    cout << ", and the matrix is:\n\n";

    for (int row = 1; row <= nInput; ++row) {  // Loop: print a row at a time
        cout << "     ";
        for (int col = 1; col <= nInput; ++col) {
            cout << setw(5) << pnMatrix[row][col];
        }
        cout << " = " << setw(5) << pnMatrix[row][0] << endl;
    }

    // Print out the totals for each column, starting with diagonal total.
    
    for (int col = 0; col <= nInput; ++col) {
        cout << "-----";
    }
    cout << endl << setw(5) << nOtherDiag;      // Print out the diagonal total

    for (int col = 1; col <= nInput; ++col) {
        cout << setw(5) << pnMatrix[0][col];    // Print out the column totals
    }
    cout << "   " << setw(5) << pnMatrix[0][0]; // Print out the other diagonal total.
    cout << endl;
}

void CMatrix::DeleteMatrix()
{
    for (int row = 0; row <= nInput; ++row)
        delete [] pnMatrix[row];
    delete [] pnMatrix;
}
