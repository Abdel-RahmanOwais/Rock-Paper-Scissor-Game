#include <iostream>
#include <cstdlib>
#include <Windows.h>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
    short RoundCount = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResultInfo {
    short GameRound = 0;
    short Player1WonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enWinner FinalWinner;
    string WinnerName = "";
};

int ReadHowManyRounds() {
    int HowManyRounds;

    do {
        cout << "How Many Rounds Do You Want To Play From 1 to 20 : ";
        cin >> HowManyRounds;
    } while (HowManyRounds < 1 || HowManyRounds > 20);

    return HowManyRounds;
}

int RandomNumber(int From, int To) {

    int RandNum = rand() % (To - From + 1) + From;

    return RandNum;
}

enWinner WhoIsWonRound(stRoundInfo RoundInfo) {
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice) {
        return enWinner::Draw;
    }

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:

        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }

        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }

        break;

    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }

        break;

    }

    //If he return back here the player 1 surely he gonna win.
    return enWinner::Player1;
}

string ChoiceName(enGameChoice ChoiceName) {
    string arrChoiceName[3] = { "Stone" , "Paper" , "Scissors" };
    return arrChoiceName[ChoiceName - 1];
}

string WinnerName(enWinner Winner) {
    string arrWinnerName[3] = { "Player1" , "Computer" , "Draw (No Winner)" };

    return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayer1Choice() {
    short PlayerChoice = 1;

    do {
        cin >> PlayerChoice;
    } while (PlayerChoice < 1 || PlayerChoice > 3);

    return enGameChoice(PlayerChoice);
}

enGameChoice GetComputerChoice() {
    return (enGameChoice)RandomNumber(1, 3);
}

void PrintRoundResult(stRoundInfo RoundInfo) {

    cout << "\n______________________Round [" << RoundInfo.RoundCount << "]______________________\n\n";
    cout << "Player 1 Choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner    : [" << RoundInfo.WinnerName << "] " << endl;
    cout << "_____________________________________________________\n";
}

enWinner WhoWonTheGame(short Player1WonTimes, short ComputerWonTimes) {

    if (Player1WonTimes > ComputerWonTimes) {
        return enWinner::Player1;
    }
    else if (Player1WonTimes < ComputerWonTimes) {
        return enWinner::Computer;
    }
    else {
        return enWinner::Draw;
    }

}

stGameResultInfo FillFinalGameResult(short Round, short Player1WonTimes, short ComputerWonTimes, short DrawTimes) {
    stGameResultInfo GameResult;

    GameResult.GameRound = Round;
    GameResult.Player1WonTimes = Player1WonTimes;
    GameResult.ComputerWonTimes = ComputerWonTimes;
    GameResult.DrawTimes = DrawTimes;
    GameResult.FinalWinner = WhoWonTheGame(Player1WonTimes, ComputerWonTimes);
    GameResult.WinnerName = WinnerName(GameResult.FinalWinner);

    return GameResult;
}

void WinnerScreenBackgroundColor(enWinner Winner)
{

    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F"); //Screen Is Gonna Be Green.
        Beep(1397, 200);
        break;
    case enWinner::Computer:
        system("color 4F"); //Screen Is Gonna Be Red.
        Beep(440, 665);
        break;
    case enWinner::Draw:
        system("color 6F"); //Screen Is Gonna Be Yellow.
        cout << "\a";
        break;
    }

}

stGameResultInfo PlayGame(short HowManyRounds) {
    stRoundInfo RoundInfo;

    short Player1Count = 0, ComputerCount = 0, DrawCount = 0;

    for (short Round = 1; Round <= HowManyRounds; Round++) {

        cout << "\n\nRound [" << Round << "] Begins : \n";
        cout << "\nYour choice : [1]:Stone, [2]:Paper, [3]:Scissors  "; //I modified it instead of adding it in ReadPlayer1Choice()

        RoundInfo.RoundCount = Round;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoIsWonRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1) {
            Player1Count++;
        }
        else if (RoundInfo.Winner == enWinner::Computer) {
            ComputerCount++;
        }
        else {
            DrawCount++;
        }

        PrintRoundResult(RoundInfo);

        WinnerScreenBackgroundColor(WhoIsWonRound(RoundInfo));
    }

    return FillFinalGameResult(HowManyRounds, Player1Count, ComputerCount, DrawCount);

}

string Tabs(short NumberOfTabs) {
    string t = " ";

    for (short i = 1; i < NumberOfTabs; i++) {
        t += "\t";
        cout << t;
    }

    return t;
}


void PrintGameOver() {
    cout << "\n" << endl;
    cout << Tabs(2) << "_______________________________________________________________________\n";
    cout << Tabs(2) << "                       +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "_______________________________________________________________________\n";

}

void PrintFinalGameResult(stGameResultInfo GameResult) {
    cout << Tabs(2) << "__________________________[ Game Results ]_____________________________\n\n";
    cout << Tabs(2) << "Game Round         : " << GameResult.GameRound << endl;
    cout << Tabs(2) << "Player 1 Won Times : " << GameResult.Player1WonTimes << endl;
    cout << Tabs(2) << "Computer Won Times : " << GameResult.ComputerWonTimes << endl;
    cout << Tabs(2) << "Draw Times         : " << GameResult.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResult.WinnerName << endl;
    cout << Tabs(2) << "_______________________________________________________________________\n";

}

void RestScreen() {
    system("cls"); //Remove Anything in the Screen 

    system("color 0F");  //Reset Screen Black

}

void StartGame() {
    char PlayAgain = ' ';
    stGameResultInfo GameResult;

    do {
        RestScreen();

        GameResult = PlayGame(ReadHowManyRounds());

        PrintGameOver();

        PrintFinalGameResult(GameResult);


        cout << endl << Tabs(3) << "Do You Want Play Again ?  Y/N ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');

    system("color 0F");
    cout << endl << Tabs(3) << "Thank you for playing our game! " << endl << endl;
    cout << Tabs(2) << "Best regards," << endl;
    cout << Tabs(2) << "Abdel-Rahman Owais" << endl;
}


int main()
{
    srand((unsigned)time(NULL));

    StartGame();
}
