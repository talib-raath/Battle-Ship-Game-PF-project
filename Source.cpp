#include <iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<fstream>
#include<Windows.h>
using namespace std;
//Prototype of functions
void main_menu(); //  Print main_menu
void mode(); // For difficulty level
void grid_filling(char grid[][15], char p_2_grid[][15], int row, int col); //Fill the grid with aterik(*)
void grid_printing(char grid[][15], int row, int col); //Print the grid of according to dificult level
void ship_placing(char grid[][15], int col, int row, int mode, int turn); //For the placing of ships for both player
int machine_placing(int row); //For the placing of ship of a machine
void attack(char p_1_grid[][15], char p_2_grid[][15], int row, int col, int mode); //For the attack on each others grid
int winnning_cond(char grid[][15], int col, int row, int ship_sink[][5]);
int overlap(char grid[][15], int r, int c, int size, char rotation);
void rules();
void credits();
void location(char grid[][15], int row, int col, int count); //Printing the location of a ship while placing
void player_2_Attack(char p_1_grid[][15], int row, int col, int mode); //For the attack of player-2 on player-1 grid
void player_1_Attack(char p_2_grid[][15], int row, int col);//For the attack of player-1 on player-2 grid
void score_print(); //For the printing of a highest score
void score_store(int score); //Function to store score in a file

//Declaring global variable to store the record of ship places then checking for that they are destroyed or not
int player_1_sink[2][5], player_2_sink[2][5];
int level = 0;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int main()
{   
    main_menu();
}

// Making of a function to show a main menu.
void main_menu()
{
    SetConsoleTextAttribute(hConsole, 5);
    system("cls");
    int choice = 0;
    cout << "\n";

    cout << setw(33) << setfill('*') << ' ' << "Welcome To Batleship Game" << setw(25) << setfill('*') << " " << endl;
    cout << "                             *******************************\n";
    cout << setw(33) << setfill(' ') << ' ' << "1-Play Game\n";
    cout << setw(33) << setfill(' ') << ' ' << "2-Rules\n";
    cout << setw(33) << setfill(' ') << ' ' << "3-High Score\n";
    cout << setw(33) << setfill(' ') << ' ' << "4-Credits\n";
    cout << setw(33) << setfill(' ') << ' ' << "5-Exit\n\n";
    SetConsoleTextAttribute(hConsole, 3);

    cout << setw(33) << setfill(' ') << ' ' << "Select an option: ";
    SetConsoleTextAttribute(hConsole, 5);

    choice = _getche();
    choice = choice - 48;

    if (choice == 1)
    {
        mode();
    }

    else if (choice == 2)
    {
        rules();
        system("cls");
        main_menu();
    }
    else if (choice == 3)
    {
        score_print();
        cout << "\\n";
        system("pause");
        main_menu();

    }
    else if (choice == 4)
    {
        credits();
        system("cls");
        main_menu();
    }

    else if (choice == 5)
    {
        exit(1);
       
    }
}

//Function to select mode of games
void mode()
{
    int ismachine = 0;
    system("cls");
    int mode = 0;

    int row = 0, col = 0;
    char p_1_grid[15][15], p_2_grid[15][15];
    cout << "\n";
    cout << setw(33) << setfill(' ') << ' ' << "1-Player Vs Player\n";
    cout << setw(33) << setfill(' ') << ' ' << "2-Player Vs Machine\n\n";
    SetConsoleTextAttribute(hConsole, 3);

    cout << setw(33) << setfill(' ') << ' ' << "Select an Option: ";
    mode = _getche();
    mode = mode - 48;
    //Difficulties level Menu
    system("cls");
    SetConsoleTextAttribute(hConsole, 5);
    cout << "\n";
    cout << setw(33) << setfill(' ') << ' ' << "1-Easy\n";
    cout << setw(33) << setfill(' ') << ' ' << "2-Medium\n";
    cout << setw(33) << setfill(' ') << ' ' << "3-Hard\n\n";
    SetConsoleTextAttribute(hConsole, 3);

    cout << setw(33) << setfill(' ') << ' ' << "Select Difficult Level: ";

    level = _getche();
    level = level - 48;
    if (level == 1)
    {
        row = 8, col = 8;
    }
    else if (level == 2)
    {
        row = 12, col = 12;
    }
    else if (level == 3)
    {
        row = 15, col = 15;
    }

    // Calling of Functions to fill a grid with *
    ismachine = 1;

    grid_filling(p_1_grid, p_2_grid, row, col);
    system("cls");
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 4);

    cout << setw(40) << setfill(' ') << ' ' << "Player-1 Grid\n";
    grid_printing(p_1_grid, row, col);
    SetConsoleTextAttribute(hConsole, 4);

    cout << setw(33) << setfill(' ') << ' ' << "PLayer-1 Place your ships\n\n";
    ship_placing(p_1_grid, col, row, mode, ismachine);
    cout << setw(33) << setfill(' ') << ' ';
    system("pause");
    system("cls");

    ismachine = 0;
    //code for machine to place ships
    if (mode == 2)
    {
        ismachine = 2;
        cout << "\n\n\n\n\n\n\n\n\n\n";
        SetConsoleTextAttribute(hConsole, 2);

        cout << setw(33) << setfill(' ') << ' ' << "Please wait for few seconds.....\n";
        cout << setw(33) << setfill(' ') << ' ' << "Machine is Placing Ships in Grid\n";
        cout << setw(33) << setfill(' ') << ' ';
        system("pause");
        /* grid_printing(p_2_grid, row, col);
         cout << setw(33) << setfill(' ') << ' ' << "Machine Placing Ships\n\n";*/
        ship_placing(p_2_grid, col, row, mode, ismachine);

    }
    else {
        ismachine = 1;
        cout << "\n";
        SetConsoleTextAttribute(hConsole, 4);

        cout << setw(40) << setfill(' ') << ' ' << "Player-2 Grid\n";
        grid_printing(p_2_grid, row, col);
        SetConsoleTextAttribute(hConsole, 4);

        cout << setw(33) << setfill(' ') << ' ' << "Player-2 Place your Ships\n\n";
        ship_placing(p_2_grid, col, row, mode, ismachine);
        cout << setw(33) << setfill(' ') << ' ';
        system("pause");
    }
    system("cls");
    attack(p_1_grid, p_2_grid, row, col, mode);


}

//Filling of a grid

void grid_filling(char grid[][15], char p_2_grid[][15], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            grid[i][j] = '*';
            p_2_grid[i][j] = '*';
        }
    }

}

//Placing of ships in a grid.
void ship_placing(char grid[][15], int col, int row, int mode, int ismachine)
{
    int no_of_ships = 0;
    char rotation = 'h';
    static int turn = 0;
    turn++;
    int size = 0;
    static int  count = 0;
    //Setting the nu,ber of shhips according to the mode
    if (level == 1)
        no_of_ships = 1;
    if (level == 2)
        no_of_ships = 2;
    if (level == 3)
        no_of_ships = 3;

    count = count + 1;
    if (count > 2)
    {
        turn = 1;
        count = 1;
    }

    int r = 0, c = 0;
    //----------------------------------------------------------------------------------------------------------------------
    for (int i = 0; i < no_of_ships; i++)
    {
        SetConsoleTextAttribute(hConsole, 4);

        if (ismachine == 1)
        {
            cout << setw(33) << setfill(' ') << ' ' << "Enter the Rotation of a Carrier Ship(V/H): ";
            cin >> rotation;
            cout << setw(33) << setfill(' ') << ' ' << "Enter the Location of Carrier Ship (" << 8 << "*1)" << endl;//size 8*1 --->8 row and one col.
        }
        if (mode == 2 && ismachine == 2 || mode == 3 && ismachine == 2)
        {
            rotation = 'v';
            r = machine_placing(row);
            //cout << setw(33) << setfill(' ') << ' ' << "Row-" << r;
            c = machine_placing(row);
            // cout << "    " << "Col-" << c << endl;
        }
        else
        {
            cout << setw(33) << setfill(' ') << ' ' << "Row-";
            cin >> r;
            cout << setw(33) << setfill(' ') << ' ' << "Col-";
            cin >> c;
            cout << "\n";
        }
        r--;
        c--;
        if(row==8)
        if (row - r < 8) 
            r = 1; 
        //overlap function is called tocheck the overlapping of position of ships in a gird whikle placing

        if (turn == 1)
        {
            player_1_sink[0][0] = r;
            player_1_sink[1][0] = c;
        }
        else
        {
            player_2_sink[0][0] = r;
            player_2_sink[1][0] = c;
        }

        overlap(grid, r, c, 8, rotation);

        if (rotation == 'v' || rotation == 'V')
        {
            for (int j = 0; j < 8; j++)
            {
                grid[j][c] = '1';
            }
        }
        else
        {
            for (int j = 0; j < 8; j++)
            {
                grid[r][j] = '1';
            }
        }
        system("cls");
        if (ismachine == 1)
            location(grid, row, col, count);
        cout << endl;
    }

    //----------------------------------------------------------------------------------------------------------------------

    for (int i = 0; i < no_of_ships; i++)
    {
        //Using do while because of ovelapping to get input again.
        do {
            SetConsoleTextAttribute(hConsole, 4);

            if (ismachine == 1)
            {
                cout << setw(33) << setfill(' ') << ' ' << "Enter the Rotaion of Battle Ship ship(V/H): ";
                cin >> rotation;
                cout << setw(33) << setfill(' ') << ' ' << "Enter the Location of Battleship Ship(" << 5 << "*1)" << endl;//size 5*1

            }
            if (mode == 2 && ismachine == 2 || mode == 3 && ismachine == 2)
            {
                rotation = 'v';
                r = machine_placing(row);

                c = machine_placing(row);

                cout << "\n";

            }
            else
            {
                cout << setw(33) << setfill(' ') << ' ' << "Row-";
                cin >> r;
                cout << setw(33) << setfill(' ') << ' ' << "Col-";
                cin >> c;
                cout << "\n";
            }
            c--;
            r--;
            //overlap function is called tocheck the overlapping of position of ships in a gird whikle placing

            if (turn == 1)
            {
                player_1_sink[0][1] = r;
                player_1_sink[1][1] = c;
            }
            else
            {
                player_2_sink[0][1] = r;
                player_2_sink[1][1] = c;
            }

        } while (overlap(grid, r, c, 5, rotation) == 1 || (row - r) < 5 || (col - c) < 5);

        //placing of a ship
        if (rotation == 'v' || rotation == 'V')
        {
            for (int j = 0; j < 5; j++)
            {
                grid[r][c] = '2';
                r++;
            }
        }
        else
        {
            for (int j = 0; j < 5; j++)
            {
                grid[r][c] = '2';
                c++;
            }
        }
        system("cls");
        if (ismachine == 1)
            location(grid, row, col, count);
        cout << endl;
    }
    //----------------------------------------------------------------------------------------------------------
    for (int i = 0; i < no_of_ships; i++)
    {
        do
        {
            SetConsoleTextAttribute(hConsole, 4);

            if (ismachine == 1)
            {
                cout << setw(33) << setfill(' ') << ' ' << "Enter the Rotaion Cruiser ship(V/H): ";
                cin >> rotation;
                cout << setw(33) << setfill(' ') << ' ' << "Enter the Location of Cruiser Ship(" << 4 << "*1)" << endl;// size 4*

            }
            if (mode == 2 && ismachine == 2 || mode == 3 && ismachine == 2)
            {
                rotation = 'v';
                r = machine_placing(row);
                //cout << setw(33) << setfill(' ') << ' ' << "Row-" << r;
                c = machine_placing(row);
                //cout << "    " << "Col-" << c;
                cout << "\n";

            }
            else
            {
                cout << setw(33) << setfill(' ') << ' ' << "Row-";
                cin >> r;
                cout << setw(33) << setfill(' ') << ' ' << "Col-";
                cin >> c;
                cout << "\n";
            }
            c--;
            r--;
            //overlap function is called tocheck the overlapping of position of ships in a gird whikle placing

            if (turn == 1)
            {
                player_1_sink[0][2] = r;
                player_1_sink[1][2] = c;
            }
            else
            {
                player_2_sink[0][2] = r;
                player_2_sink[1][2] = c;
            }
        } while (overlap(grid, r, c, 4, rotation) == 1 || (row - r < 4) || (col - c) < 4);
        //placing of a ship
        if (rotation == 'v' || rotation == 'V')
        {
            for (int j = 0; j < 4; j++)
            {
                grid[r][c] = '3';
                r++;
            }
        }
        else
        {
            for (int j = 0; j < 4; j++)
            {
                grid[r][c] = '3';
                c++;
            }
        }
        system("cls");
        //Location function is used to print the location of ships after placing
        if (ismachine == 1)
            location(grid, row, col, count);
        cout << endl;
    }

    int over_lap = 0, temp = 0;

    //------------------------------------------------------------------------------------------------------------------
    for (int i = 0; i < no_of_ships; i++)
    {
        do
        {
            SetConsoleTextAttribute(hConsole, 4);

            over_lap = 0;
            if (ismachine == 1)
            {
                cout << setw(33) << setfill(' ') << ' ' << "Enter the Rotaion Submarine  ship(V/H): ";
                cin >> rotation;
                cout << setw(33) << setfill(' ') << ' ' << "Enter the Location of Submarine Ship(" << 3 << "*2)" << endl;//size 3*2

            }
            if (mode == 2 && ismachine == 2 || mode == 3 && ismachine == 2)
            {
                rotation = 'v';
                r = machine_placing(row);
               
                c = machine_placing(row);
                cout << "\n";
            }
            else
            {
                cout << setw(33) << setfill(' ') << ' ' << "Row-";
                cin >> r;
                cout << setw(33) << setfill(' ') << ' ' << "Col-";
                cin >> c;
                cout << "\n";
            }

            c--;
            r--;

            temp = r;
            //checking for the overlapping of a submarine ship
            if (rotation == 'v' || rotation == 'V')
            {
                for (int k = 0; k < 3; k++)
                {

                    if (grid[r][c] != '*' || grid[r][c + 1] != '*')
                    {
                        over_lap = 1;
                        break;
                    }
                    r++;
                }
                r = temp;
               
            }
          
            else
            {
                temp = c;
                for (int k = 0; k < 3; k++)
                {

                    if (grid[r][c] != '*' || grid[r + 1][c] != '*')
                    {
                        over_lap = 1;
                        break;
                    }
                    c++;
                }
                c = temp;
                cout << "c= " << c << endl;
                system("pause");
            }

           
            if (turn == 1)
            {
                player_1_sink[0][3] = r;
                player_1_sink[1][3] = c;
            }
            else
            {
                player_2_sink[0][3] = r;
                player_2_sink[1][3] = c;
            }

        } while (over_lap == 1 || row - r < 2 || col - c < 1);

        r = temp;
        //Placing of a ship
        if (rotation == 'v' || rotation == 'V')
        {
            for (int j = 0; j < 3; j++)
            {
                grid[r][c] = '4';
                grid[r][c + 1] = '4';
                r++;
            }
        }
        else
        {
            for (int j = 0; j < 3; j++)
            {
                grid[r][c] = '4';
                grid[r + 1][c] = '4';
                c++;
            }
        }
        system("cls");
        if (ismachine == 1)
            location(grid, row, col, count);
        cout << endl;

    }
    //-----------------------------------------------------------------------------------------------------
    for (int i = 0; i < no_of_ships; i++)

    {
        do
        {
            SetConsoleTextAttribute(hConsole, 4);

            if (ismachine == 1)
            {
                cout << setw(33) << setfill(' ') << ' ' << "Enter the Rotaion of Destroyer ship(V/H): ";
                cin >> rotation;
                cout << setw(33) << setfill(' ') << ' ' << "Enter the Location of Destroyer Ship(" << 2 << "*1)" << endl;//size 2*1 ---> 2 row and 1 col

            }
            if (mode == 2 && ismachine == 2 || mode == 3 && ismachine == 2)
            {
                rotation = 'v';
                r = machine_placing(row);
                //cout << setw(33) << setfill(' ') << ' ' << r << endl;
              //  cout << setw(33) << setfill(' ') << ' ' << system("pause");
                c = machine_placing(row);
                //  cout << "    " << "Col-" << c;
                cout << "\n";
                // cout << setw(33) << setfill(' ') << ' ' << system("pause");
            }
            else
            {
                cout << setw(33) << setfill(' ') << ' ' << "Row-";
                cin >> r;
                cout << setw(33) << setfill(' ') << ' ' << "Col-";
                cin >> c;
                cout << "\n";
            }
            c--;
            r--;

            if (turn == 1)
            {
                player_1_sink[0][4] = r;
                player_1_sink[1][4] = c;
            }
            else
            {
                player_2_sink[0][4] = r;
                player_2_sink[1][4] = c;
            }
        } while (overlap(grid, r, c, 2, rotation) == 1 || row - r < 1 || (col - c) < 4);

        //placing of a ship
        if (rotation == 'v' || rotation == 'V')
        {
            for (int j = 0; j < 2; j++)
            {
                grid[r][c] = '5';
                r++;
            }
        }
        else
        {
            for (int j = 0; j < 2; j++)
            {
                grid[r][c] = '5';
                c++;
            }
        }
        system("cls");
        if (ismachine == 1)
            location(grid, row, col, count);
        cout << endl;
    }
    if (ismachine == 2)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n";
        cout << setw(33) << setfill(' ') << ' ' << "Machine has Placed ships\n";
        cout << setw(33) << setfill(' ') << ' ';
        system("pause");

    }
}


// code to get a cordinates for placing ships of machine
int machine_placing(int row)
{
    system("cls");
    int num, temp = 0;
    temp++;
    srand(time(0));
    if (temp == 1)
    {
        srand(time(0));
        num = rand() % row + 1;
    }
    else
    {

        srand(time(0));
        temp = 0;
        num = rand() % row + 2;
    }
    if (num > row)
        num = row - 1;


    return num;
}



//code to check the overlapping of ships
int overlap(char grid[][15], int r, int c, int size, char rotation)
{

    int over_lap = 0;
    if (rotation == 'v' || rotation == 'V')
    {
        for (int j = 0; j < size; j++)
        {
            if (grid[r][c] == '1' || grid[r][c] == '2' || grid[r][c] == '3' || grid[r][c] == '4' || grid[r][c] == '5')
            {
                over_lap = 1;
                break;
            }
            r++;
        }
    }
    //code to check the overlapping for horizontally
    else 
    {
        for (int j = 0; j < size; j++)
        {
            if (grid[r][c] == '1' || grid[r][c] == '2' || grid[r][c] == '3' || grid[r][c] == '4' || grid[r][c] == '5')
            {
                over_lap = 1;
                break;
            }
            c++;
        }

    }

    return over_lap;
}


void grid_printing(char grid[][15], int row, int col)
{
    SetConsoleTextAttribute(hConsole, 6);

    cout << setw(33) << setfill(' ') << ' ';
    for (int i = 0; i < col; i++)
    {
        cout << setw(3) << setfill(' ') << i + 1;
    }
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 6);

    //code to draw boundry line
    cout << setw(35) << setfill(' ') << ' ';
    for (int i = 0; i < row * 3 - 1; i++)
    {
        cout << "-";
    }
    cout << "\n";
    for (int i = 0; i < row; i++)
    {
        SetConsoleTextAttribute(hConsole, 6);
        cout << setw(34) << setfill(' ') << i + 1 << "|";
        for (int j = 0; j < col; j++)
        {
            SetConsoleTextAttribute(hConsole, 3);
            if (grid[i][j] == '1' || grid[i][j] == '2' || grid[i][j] == '3' || grid[i][j] == '4' || grid[i][j] == '5')
            {
                cout << "*";
                if (j < row - 1)
                    cout << "  ";
            }
            else
            {
                //if-else used to draw a boundry in an appropriate way
                if (j == row - 1)
                {
                    if (grid[i][j] == 'D')
                    {
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << grid[i][j];
                    }
                    else if (grid[i][j] == 'M')
                    {
                        SetConsoleTextAttribute(hConsole, 6);
                        cout << grid[i][j];
                    }
                    else
                        cout << grid[i][j];
                }
                else if (j < (row - 1))
                    cout << grid[i][j] << "  ";

            }

        }
        SetConsoleTextAttribute(hConsole, 6);
        cout << "|\n";

    }
    cout << setw(35) << setfill(' ') << ' ';
    for (int i = 0; i < row * 3 - 1; i++)
    {
        cout << "-";
    }
    cout << "\n";
}


//Code to print the position of SHIPS.
void location(char grid[][15], int row, int col, int count)
{
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 4);
    cout << setw(40) << setfill(' ') << ' ' << "Palayer-" << count << " Grid\n";
    SetConsoleTextAttribute(hConsole, 6);
    cout << setw(33) << setfill(' ') << ' ';
    for (int i = 0; i < col; i++)
    {
        cout << setw(3) << setfill(' ') << i + 1;
    }
    cout << "\n";

    //code to draw boundry 
    cout << setw(35) << setfill(' ') << ' ';
    for (int i = 0; i < row * 3 - 1; i++)
    {
        cout << "-";
    }

    cout << "\n";

    for (int i = 0; i < row; i++)
    {
        SetConsoleTextAttribute(hConsole, 6);
        cout << setw(34) << setfill(' ') << i + 1 << "|";
        SetConsoleTextAttribute(hConsole, 15);
        for (int j = 0; j < col; j++)
        {
            //if-else used to draw a boundry in an appropriate way
           
            if (j == row - 1)
            {
                if (grid[i][j] == '1')
                {
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << 1;
                 
                }
                else if (grid[i][j] == '2') {
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << 2;
                  
                }
                else if (grid[i][j] == '3')
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << 3;
                    
                }
                else if (grid[i][j] == '4') {
                    SetConsoleTextAttribute(hConsole, 13);
                    cout << 4;
                
                }
                else if (grid[i][j] == '5') {
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << 5;
                 
                }
                else if (grid[i][j] == '*') {
                    cout << '*';

                }
               
               
            }
              
            else
            { 
                if (grid[i][j]=='1')
                    SetConsoleTextAttribute(hConsole, 10);
                if (grid[i][j] == '2')
                    SetConsoleTextAttribute(hConsole, 11);
                if (grid[i][j] == '3')
                    SetConsoleTextAttribute(hConsole, 12);
                if (grid[i][j] == '4')
                    SetConsoleTextAttribute(hConsole, 13);
                if (grid[i][j] == '5')
                    SetConsoleTextAttribute(hConsole, 14);
                cout << grid[i][j] << "  ";
            }
            SetConsoleTextAttribute(hConsole, 15);
            
        }
        SetConsoleTextAttribute(hConsole, 6);
        cout << "|\n";
    }
    //code to draw a boundry
    cout << setw(35) << setfill(' ') << ' ';
    for (int i = 0; i < row * 3 - 1; i++)
    {
        cout << "-";
    }

    cout << "\n";
}


//Attcking function
void attack(char p_1_grid[][15], char p_2_grid[][15], int row, int col, int  mode)
{
    system("cls");

    int p = 0;
    int r = 0, c = 0;
    for (int i = 0; ; i++)
    {
        //Functions called for player-2 Attack on player 1 grid
        player_2_Attack(p_1_grid, row, col, mode);

        //player_2_sink array is send to get the loaction of a ship
        if (winnning_cond(p_1_grid, row, col, player_1_sink) == 5)
        {
            static int  score_2 = 0;
            score_2 = score_2 + 5;
            score_store(score_2);
            grid_printing(p_1_grid, row, col);
            cout << "\n";
            winnning_cond(p_1_grid, row, col, player_1_sink);
            cout << setw(55) << setfill(' ') << ' ' << "\nPlayer-2 Destroyed all Ships\n";
            cout << setw(55) << setfill(' ') << ' ' << "\nPlayer-2 Won the Match\n";
            cout << setw(55) << setfill(' ') << ' ' << "\nPlayer-1 Lose the Match\n";
            cout << setw(55) << setfill(' ') << ' ' << system("pause");
            main_menu();
        }
        cout << "\n";
        cout << setw(33) << setfill(' ') << ' ' << system("pause");

        //---------------------------------------------------------------------------------------------------------------
        //Functions called for player-1 Attack on player-2 grid

        player_1_Attack(p_2_grid, row, col);
        if (winnning_cond(p_2_grid, row, col, player_2_sink) == 5)
        {
            static int score = 0;
            score = score + 5;
            score_store(score);

            score_store(score);
            grid_printing(p_2_grid, row, col);
            cout << "\n";
            winnning_cond(p_2_grid, row, col, player_2_sink);
            cout << "\n";
            cout << setw(33) << setfill(' ') << " " << "Player-1 Destroyed and sank all Ships\n";
            cout << setw(33) << setfill(' ') << ' ' << system("pause");
            main_menu();


        }
        cout << "\n";

        cout << setw(33) << setfill(' ') << ' ' << system("pause");
    }
}



//Function for attack of player_2
void player_2_Attack(char p_1_grid[][15], int row, int col, int mode)
{
    system("cls");
    int p = 0;
    int r = 0, c = 0;
    cout << "\n";
    cout << setw(40) << setfill(' ') << ' ' << "Player-1 Grid\n";
    grid_printing(p_1_grid, row, col);
    cout << setw(33) << setfill(' ') << ' ' << "Player-2 Turn\n";
    if (mode == 2)
    {
        r = machine_placing(row);
        c = machine_placing(row);
    }
    else
    {
        cout << setw(33) << setfill(' ') << ' ' << "Row-:" << ' ';
        cin >> r;
        cout << setw(33) << setfill(' ') << ' ' << "Col-: ";
        cin >> c;
    }

    // code to marked that ship is damage ship for player-2
    if (p_1_grid[r - 1][c - 1] != '*')
    {
        p_1_grid[r - 1][c - 1] = 'D';
        system("cls");
        cout << "\n";
        cout << setw(40) << setfill(' ') << ' ' << "Player-1 Grid\n";
        grid_printing(p_1_grid, row, col);

        cout << "Player-2 give a damage to Ship\n";
    }
    else
        // code to mark that fire is missed for player-2
    {
        p_1_grid[r - 1][c - 1] = 'M';
        system("cls");
        cout << "\n";
        cout << setw(40) << setfill(' ') << ' ' << "Player-1 Grid\n";
        grid_printing(p_1_grid, row, col);
        cout << "Player-2 missed a Fire\n";
    }

}

//code for player_1 attack

void player_1_Attack(char p_2_grid[][15], int row, int col)
{
    system("cls");
    int p = 0;
    int r = 0, c = 0;
    cout << "\n";
    cout << setw(40) << setfill(' ') << ' ' << "Player-2 Grid\n";

    grid_printing(p_2_grid, row, col);

    cout << setw(33) << setfill(' ') << ' ' << "Player-1 Turn\n";
    cout << setw(33) << setfill(' ') << ' ' << "Row-: ";
    cin >> r;
    cout << setw(33) << setfill(' ') << ' ' << "Col-: ";
    cin >> c;
    // code to marked that ship is damage  for player-1
    if (p_2_grid[r - 1][c - 1] != '*')
    {
        p_2_grid[r - 1][c - 1] = 'D';
        system("cls");
        cout << "\n";
        cout << setw(40) << setfill(' ') << ' ' << "Player-2 Grid\n";
        grid_printing(p_2_grid, row, col);
        cout << "Player-1 give a damage to Ship\n";

    }
    // code to mark that fire is missed for player-2
    else
    {

        p_2_grid[r - 1][c - 1] = 'M';
        system("cls");
        cout << "\n";
        cout << setw(40) << setfill(' ') << ' ' << "Player-2 Grid\n";
        grid_printing(p_2_grid, row, col);
        cout << "Player-1 missed a Fire\n";
    }


}


//Function to check the winning condition 
int winnning_cond(char grid[][15], int row, int col, int ship_sink[][5])
{
    int cond = 0;
    //Making an array for winning condition to check that there is a ship sink or not for each type of ship.
    int win[5] = { 0,0,0,0,0 };
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] == '1')
            {
                cond++;
            }
        }
    }
    if (cond == 0)
    {
        if (win[0] != 1)
            win[0] = 1;
        cout << "Carrier Ship has been sank\n";

        //code to mark that shhip is sank

        for (int i = 0; i < 8; i++)
        {
            grid[i][ship_sink[0][0]] = '--';
        }
    }


    cond = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] == '2')
            {
                cond++;

            }
        }

    }
    if (cond == 0)
    {
        if (win[1] != 1)
            win[1] = 1;
        cout << "Battleship Ship has been sank\n";

        int r = ship_sink[0][1];

        int c = ship_sink[1][1];

        //code to mark that shhip is sank
        for (int i = 0; i < 5; i++)
        {
            grid[r][c] = '-';
            r++;
        }
    }
    cond = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] == '3')
            {
                cond++;

            }
        }
    }
    if (cond == 0)
    {
        if (win[2] != 1)
            win[2] = 1;
        cout << "Cruiser Ship has been sank\n";

        int r = ship_sink[0][2];

        int c = ship_sink[1][2];

        //code to mark that shhip is sank
        for (int i = 0; i < 4; i++)
        {
            grid[r][c] = '-';
            r++;
        }

    }
    cond = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] == '4')
            {
                cond++;

            }
        }
    }
    if (cond == 0)
    {
        if (win[3] != 1)
            win[3] = 1;
        cout << "Submarine has been sank\n";

        int r = ship_sink[0][3];

        int c = ship_sink[1][3];

        //code to mark that shhip is sank
        for (int i = 0; i < 3; i++)
        {
            grid[r][c] = '-';
            grid[r][c + 1] = '-';
            r++;
        }
    }
    cond = 0;
    for (int i = 0; i < row; i++)
    {
        if (win[4] != 1)
            win[4] = 1;
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] == '5')
            {
                cond++;

            }
        }
    }
    if (cond == 0)
    {
        if (win[4] != 1)
            win[4] = 1;
        cout << "Destroyer Ship has been sank\n";
        int r = ship_sink[0][4];

        int c = ship_sink[1][4];

        //code to mark that shhip is sank
        for (int i = 0; i < row - 6; i++)
        {
            grid[r][c] = '-';
            r++;
        }
    }
    int total_sink = 0;
    for (int i = 0; i < 5; i++)
    {
        if (win[i] == 1)
            total_sink++;
    }



    return total_sink;
}


//Function for the storing of a score

void score_store(int score)
{
    ofstream scr;
    scr.open("score.txt", ios::app);
    scr << score << endl;
    scr.close();
}
//Function for showing of a score
void score_print()
{
    system("cls");
    ifstream scr;
    int data, highest = 0;
    scr.open("score.txt");
    if (!scr)
    {
        cout << "file can't be load";
    }

    scr >> highest;
    while (!scr.eof())
    {
        scr >> data;
        if (highest < data)
        {
            highest = data;
        }

    }
    cout << "\n";
    cout << setw(33) << setfill(' ') << ' ' << "Highest Score: " << highest << "\n\n";
    scr.close();
    system("pause");
    main_menu();
}

//function to defined the rules of a game
void rules()
{
    system("cls");
    cout << "Rule-1: The object of Battleship is to try and sink all of the other player's before they sink all of your ships.\n\n";
    cout << "Rule-2: You try and hit them by calling out the coordinates of one of the squares on the board.\n\n";
    cout << "Rule-3: Each player places the 5 ships somewhere on their board.\n\n";
    cout << "Rule-4: The Number of ships vary eith difficulty Level\n\n";

    cout << "Rule-5: The 5 ships are:  Carrier (occupies 8 squares), Battleship (5), Cruiser (4), Submarine (3), and Destroyer (2).\n\n";
    cout << "Rule-6: Player's take turns guessing by calling out the coordinates.\n\n";
    cout << "Rule-7: If you called a fire to some coordinate if there is ship is not place then, I marked there miss.\n";
    system("pause");

}


//FUnction to print the credits

void credits()
{
    system("cls");
    cout << "\n";
    cout << setw(33) << " " << "Created By" << setw(25) << setfill('.') << "Talib Raath\n";
    cout << setw(33) << " " << "Created By" << setw(25) << setfill('.') << "Usman Saleem\n";
    system("pause");
}
