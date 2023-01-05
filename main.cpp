// SudokuGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <string>
#include <sstream>
using namespace std;

// Values for the sudoku board
struct sudokuNumbers {
    int number; // The number
    bool solid = true; // true = Placed there by the board / false = Placed there by the player
    sudokuNumbers(int num): number(num) {}
};

// Sudoku board main class
class SudokuBoardLogic {
public:
    sudokuNumbers* currentBoard = nullptr;
    sudokuNumbers* pointer;
    bool completed = false;
    SudokuBoardLogic() {};
    bool AssignBoard(int board);
    void PlayerInput(int& number, int& column, int& row);
    bool CheckCompleted();
    void RemoveValues(int& column, int& row);
    void ListOfRemoveables();
    bool NumCheck(int& randNum, int& row, int& column);
    void ShowBoard();
private:
    list<int> availableNumbers;
    sudokuNumbers sudokuBoard1[9][9]
    {
        5, 3, 4, 6, 7, 8, 9, 1, 2,
        6, 7, 2, 1, 9, 5, 3, 4, 8,
        1, 9, 8, 3, 4, 2, 5, 6, 7,
        8, 5, 9, 7, 6, 1, 4, 2, 3,
        4, 2, 6, 8, 5, 3, 7, 9, 1,
        7, 1, 3, 9, 2, 4, 8, 5, 6,
        9, 6, 1, 5, 3, 7, 2, 8, 4,
        2, 8, 7, 4, 1, 9, 6, 3, 5,
        3, 4, 5, 2, 8, 6, 1, 7, 9,
    };
    sudokuNumbers sudokuBoard2[9][9]
    {
        4, 7, 6, 5, 3, 2, 8, 1, 9,
        2, 5, 8, 1, 4, 9, 7, 3, 6,
        1, 9, 3, 7, 6, 8, 4, 2, 5,
        6, 4, 7, 8, 2, 5, 1, 9, 3,
        5, 1, 9, 3, 7, 6, 2, 8, 4,
        3, 8, 2, 9, 1, 4, 5, 6, 7,
        9, 2, 4, 6, 8, 7, 3, 5, 1,
        7, 6, 1, 2, 5, 3, 9, 4, 8,
        8, 3, 5, 4, 9, 1, 6, 7, 2,
    };
    sudokuNumbers sudokuBoard3[9][9]
    {
        7, 3, 5, 6, 1, 4, 8, 9, 2,
        8, 4, 2, 9, 7, 3, 5, 6, 1,
        9, 6, 1, 2, 8, 5, 3, 7, 4,
        2, 8, 6, 3, 4, 9, 1, 5, 7,
        4, 1, 3, 8, 5, 7, 9, 2, 6,
        5, 7, 9, 1, 2, 6, 4, 3, 8,
        1, 5, 7, 4, 9, 2, 6, 8, 3,
        6, 9, 4, 7, 3, 8, 2, 1, 5,
        3, 2, 8, 5, 6, 1, 7, 4, 9,
    };
    bool ColumnNumberReturn(int& randNum, const int& column);
    bool RowNumberReturn(int& randNum, const int& row);
    bool SquareNumberReturn(int& randNum, const int& intervalRow, const int& intervalColumn);
    void AddBlanks();
};

// Checks the row provided to see if any numbers overlap
bool SudokuBoardLogic::RowNumberReturn(int& randNum, const int& row) {
    pointer = &currentBoard[row * 9];
    for (int i = 0; i < 9; i++) {
        if (pointer[i].number == randNum)
        {
            cout << "(Row) Number " << pointer[i].number << " on row " << row << " and column " << i << " equal to randNum " << randNum << "\n";
            return false;
        }
    }
    return true;
}

// Checks the column provided to see if any numbers overlap
bool SudokuBoardLogic::ColumnNumberReturn(int& randNum, const int& column) {
    for (int i = 0; i < 9; i++) {
        pointer = &currentBoard[i * 9];
        if (pointer[column].number == randNum) 
        {
            cout << "(Column) Number " << pointer[i * 9].number << " on row " << i << " and column " << column << " equal to randNum " << randNum << "\n";
            return false;
        }
    }
    return true;
}

// Checks the square the number exists within to see if any numbers overlap
bool SudokuBoardLogic::SquareNumberReturn(int& randNum, const int& row, const int& column) {
    int intervalRow, intervalColumn;

    // Finds out the positions needed to check for the square
    if (row < 3) {
        intervalRow = 3;
    }
    else if (row < 6) {
        intervalRow = 6;
    }
    else {
        intervalRow = 9;
    }

    if (column < 3) {
        intervalColumn = 3;
    }
    else if (column < 6) {
        intervalColumn = 6;
    }
    else {
        intervalColumn = 9;
    }

    // Checks the sqaure using the positions provided
    for (int i = (intervalRow - 3); i < intervalRow; i++) {
        pointer = &currentBoard[i * 9];
        for (int i2 = (intervalColumn - 3); i2 < intervalColumn; i2++) {
            if (pointer[i2].number == randNum)
            {
                cout << "(Square)Number " << pointer[i2].number << " on row " << i << " and column " << i2 << " equal to randNum " << randNum << "\n";
                return false;
            }
        }
    }
    return true;
}

// Performs all the basic checks for a number. Returns false if the number already exists in the row, column or square. Returns true if not.
bool SudokuBoardLogic::NumCheck(int& randNum, int& row, int& column) {
    if (RowNumberReturn(randNum, row) == false)
        return false;
    if (ColumnNumberReturn(randNum, column) == false)
        return false;
    if (SquareNumberReturn(randNum, row, column) == false)
        return false;

    return true;
}

// Assigns the board to one of the presets depending on what the player chooses
bool SudokuBoardLogic::AssignBoard(int board) {

    try
    {
        // ResetBoard();
        switch (board) {

        case 1:
            currentBoard = *sudokuBoard1;
            break;

        case 2:
            currentBoard = *sudokuBoard2;
            break;

        case 3:
            currentBoard = *sudokuBoard3;
            break;
        }
        AddBlanks();

        return true;
    }
    catch (int e)
    {
        return false;
    }

}

// Takes the inputted number, row and column given by the player. Runs checks to see if the number can fit into the board and if so places it there
void SudokuBoardLogic::PlayerInput(int& number, int& column, int& row) {
    if (column < 1 || column > 9) {
        cout << "Please enter a number within 1 - 9 \n\n";
        return;
    }
    if (row < 1 || row > 9) {
        cout << "Please enter a number within 1 - 9 \n\n";
        return;
    }

    column -= 1;
    row -= 1;
    sudokuNumbers* playerPointer = &currentBoard[row * 9];
    if (NumCheck(number, row, column) == false || playerPointer[column].number != 0) { // Check over this, it should probably be OR instead of AND
        cout << "Number can't be placed there \n";
        return;
    }
    else {
        playerPointer[column].number = number;
        playerPointer[column].solid = false;
        ShowBoard();
        return;
    }
}

// Checks if the player has completed the board
bool SudokuBoardLogic::CheckCompleted() {
    for (int i = 0; i < 9; i++) {
        pointer = &currentBoard[i * 9];
        for (int i2 = 0; i2 < 9; i2++) {
            if (pointer[i2].number == 0)
                return false;
        }
    }
    return true;
}

// Takes the inputted row and column given by the player. Runs checks to see if the number there can be removed and if so removes it
void SudokuBoardLogic::RemoveValues(int& column, int& row) {
    if (column < 1 || column > 9) {
        cout << "Please enter a number within 1 - 9 \n\n";
        return;
    }
    if (row < 1 || row > 9) {
        cout << "Please enter a number within 1 - 9 \n\n";
        return;
    }

    column -= 1;
    row -= 1;
    pointer = &currentBoard[row * 9];
    if (pointer[column].solid == true) {
        cout << "Number can't be removed \n";
    }
    else {
        cout << "Removing number " << pointer[column].number << " at column " << (column + 1) << " and row " << (row + 1) << "\n\n";
        pointer[column].number = 0;
        ShowBoard();
    }
}

// Produces a list of removable numbers that the player has placed within the board
void SudokuBoardLogic::ListOfRemoveables() {
    for (int i = 0; i < 9; i++) {
        pointer = &currentBoard[i * 9];
        for (int i2 = 0; i2 < 9; i2++) {
            if (pointer[i2].solid != true && pointer[i2].number != 0)
                cout << "Number: " << pointer[i2].number << " on column " << (i2 + 1) << " and row " << (i + 1) << "\n";
        }
    }
}

// Shows the current board
void SudokuBoardLogic::ShowBoard() {
    for (int i = 0; i < 9; i++) {
        pointer = &currentBoard[i * 9]; // points to the array of numbers on that row.
        for (int i2 = 0; i2 < 9; i2++) {
            cout << pointer[i2].number << ' '; // Goes across the array and prints each number on the row
            if (i2 == 2 || i2 == 5)
                cout << " | ";
            
        }
        cout << '\n';
        if (i == 2 || i == 5)
            cout << "-----------------------\n";
    }
}

// Adds the blanks to the board and makes them available for the player to edit
void SudokuBoardLogic::AddBlanks() {
    int blanks = 0;
    sudokuNumbers* pointer;
    while (blanks <= 50) {
        for (int i = 0; i < 9; i++) {
            pointer = &currentBoard[i * 9];
            for (int i2 = 0; i2 < 9; i2++) {
                if (blanks > 50) {
                    return;
                }
                else {
                    int randNum = rand() % 100 + 1;
                    if (randNum > 40) { // 60% chance to leave it blank
                        pointer[i2].number = 0;
                        blanks++;
                    }
                }
            }
        }
    }
}


// https://java2blog.com/check-if-string-is-number-cpp/
// Splits the string down into the amount of characters in the string
// checks each one to see if it's a digit, if any come up false, returns false
bool isNumber(const string& s)
{
    for (char const& ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

int main()
{
    // Todo: Add a new command that provides a list of numbers which can be removed and what row they are on

    // AssignValues

    // Take answer (number [collum] [row])

    // Check answer

    // Give response

    // Check if game has been beaten

    // Repeat

    SudokuBoardLogic sudokuBoard;
    string stringInput;
    int intInput = 0;
    int number, row, column;

    cout << "\n";


    cout <<
        "1) Help - Brings up the commands \n"
        "2) Play - Begins the game \n"
        "3) Add - Adds a number to the board \n"
        "4) Remove - Removes a number from the board \n"
        "5) List (Removes) - Proivdes a list of numbers that can be removed and what row and column \n"
        "6) Show - Shows the current board \n"
        "7) Quit - Quits the application \n\n";

    while (sudokuBoard.completed == false) {
        cout << "Enter a command number\n";
        getline(cin >> ws, stringInput);

        if (isNumber(stringInput) == false) {
            cout << "Please enter a valid command number \n\n";
        }
        else {
            try {
                intInput = stoi(stringInput);
            }
            catch (int e) {
                cout << "Please enter a valid command number \n\n";
            }

            switch (intInput)
            {
            case 1:
                cout <<
                    "1) Help - Brings up the commands \n"
                    "2) Play - Begins the game \n"
                    "3) Add - Adds a number to the board \n"
                    "4) Remove - Removes a number from the board \n"
                    "5) List (Removes) - Provides a list of numbers that can be removed and what row and column \n"
                    "6) Show - Shows the current board \n"
                    "7) Quit - Quits the application \n\n";
                break;

            case 2:
                if (sudokuBoard.currentBoard != nullptr) {
                    cout << "To change board, please reset the program \n";
                    break;
                }

                cout << "What board would you like to play (1 - 3) \n";
                getline(cin >> ws, stringInput);
                if (isNumber(stringInput) == false) {
                    cout << "Please enter a valid sudoku board \n\n";
                    break;
                }
                try {
                    intInput = stoi(stringInput);
                }
                catch (int e) {
                    cout << "Please enter a valid sudoku board \n\n";
                    break;
                }
                if (intInput < 1 || intInput > 3) {
                    cout << "Please enter a valid sudoku board \n\n";
                    break;
                }


                sudokuBoard.AssignBoard(intInput);
                sudokuBoard.ShowBoard();
                cout << "\n";
                break;

            case 3:
                if (sudokuBoard.currentBoard == nullptr) {
                    cout << "Please create a board first by using command number 2 \n\n";
                    break;
                }
                    
                cout << "Enter what number you would like to enter (1 - 9) \n";
                cin >> number;
                cout << "Enter the column (1 - 9)\n";
                cin >> column;
                cout << "Enter the row (1 - 9)\n";
                cin >> row;
                cout << "Placing number " << number << " at column " << column << " and row " << row << "\n\n";
                sudokuBoard.PlayerInput(number, column, row);
                if (sudokuBoard.CheckCompleted() == true)
                    sudokuBoard.completed = true;
                cout << "\n";
                break;

            case 4:
                if (sudokuBoard.currentBoard == nullptr) {
                    cout << "Please create a board first by using command number 2 \n\n";
                    break;
                }

                cout << "Enter the column (0 - 8)\n";
                cin >> column;
                cout << "Enter the row (0 - 8)\n";
                cin >> row;
                sudokuBoard.RemoveValues(column, row);
                cout << "\n";
                break;

            case 5:
                if (sudokuBoard.currentBoard == nullptr) {
                    cout << "Please create a board first by using command number 2 \n\n";
                    break;
                }

                sudokuBoard.ListOfRemoveables();
                cout << "\n";
                break;

            case 6:
                if (sudokuBoard.currentBoard == nullptr) {
                    cout << "Please create a board first by using command number 2 \n\n";
                    break;
                }

                sudokuBoard.ShowBoard();
                cout << "\n";
                break;

            case 7:
                exit;
                break;

            default:
                cout << "Command not understood \n";
                break;
            }
        }
    }
    cout << "Congratulations you completed the game!";
}
