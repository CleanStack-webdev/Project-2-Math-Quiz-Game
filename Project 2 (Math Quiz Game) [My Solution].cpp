#include <iostream> 
#include <cstdlib>              // for rand() and srand()
#include <ctime>                // for time()

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stGameResults
{
    short QuestionsNumber = 0;
    enQuestionsLevel QuestionsLevel = enQuestionsLevel::EasyLevel;
    string QuestionsLevelName = "";
    enOperationType OperationType = enOperationType::Add;
    string OperationTypeName = "";
    short RightAnswers = 0;
    short WrongAnswers = 0;
};

struct stMathQuestion
{
    enQuestionsLevel RoundQuestionLevel = enQuestionsLevel::EasyLevel;
    enOperationType OperationRoundType = enOperationType::Add;
    string OperationSymbol = "";
    int Operand1 = 0, Operand2 = 0;
    int PlayerAnswer = 0;
    int CorrectAnswer = 0;
};

int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

short ReadHowManyQuestions()
{
    short QuestionsNumber;
    
    cout << "How Many Questions do you want to answer ? ";
    cin >> QuestionsNumber;

    return QuestionsNumber;
}

enQuestionsLevel ReadQuestionsLevel()
{
    int choice;

    do {
        cout << "\nEnter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> choice;
    } while (choice < 1 || choice > 4);

    return (enQuestionsLevel)choice;
}

enOperationType ReadOperationType()
{
    int choice;

    do {
        cout << "\nEnter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> choice;
    } while (choice < 1 || choice > 5);

    return (enOperationType)choice;
}

string GetQuestionsLevelName(enQuestionsLevel QuestionsLevel)
{
    string arrQuestionsLevel[4] = { "Easy" , "Med" , "Hard" , "Mix" };

    return arrQuestionsLevel[QuestionsLevel - 1];
}

string GetOperationSymbol(enOperationType OperationType)
{
    string arrOperationType[5] = { " +" , " -" , " x" , " /" ," Mix" };

    return arrOperationType[OperationType - 1];
}

int CalculateOperationResult(stMathQuestion MathQuestion)
{
    switch (MathQuestion.OperationRoundType)
    {
    case enOperationType::Add:
        return MathQuestion.Operand1 + MathQuestion.Operand2;
    case enOperationType::Sub:
        return MathQuestion.Operand1 - MathQuestion.Operand2;
    case enOperationType::Mul:
        return MathQuestion.Operand1 * MathQuestion.Operand2;
    case enOperationType::Div:
        return MathQuestion.Operand1 / MathQuestion.Operand2;
    }
}

int QuestionsLevelDegree(enQuestionsLevel QuestionsLevel)
{
    switch (QuestionsLevel)
    {
    case enQuestionsLevel::EasyLevel:
        return RandomNumber(1, 10);
    case enQuestionsLevel::MedLevel:
        return RandomNumber(10, 50);
    case enQuestionsLevel::HardLevel:
        return RandomNumber(50, 100);
    }
}

enQuestionsLevel GetRoundQuestionLevel(enQuestionsLevel QuestionsLevel)
{
    if (QuestionsLevel == enQuestionsLevel::Mix)
    {
        short level = RandomNumber(1, 3);
        QuestionsLevel = (enQuestionsLevel)level;
    }

    return QuestionsLevel;
}

int QuizQuestions(stMathQuestion MathQuestion)
{
    cout << MathQuestion.Operand1 << endl;
    cout << MathQuestion.Operand2 << MathQuestion.OperationSymbol << endl;
    cout << "_________________" << endl;
    cin >> MathQuestion.PlayerAnswer;

    return MathQuestion.PlayerAnswer;
}

void CheckPlayerAnswer(int PlayerAnswer, int CorrectAnswer)
{
    if (PlayerAnswer == CorrectAnswer)
    {
        cout << "Right Answer :-)" << endl;
    }
    else
    {
        cout << "\aWrong Answer :-(" << endl;
        cout << "The right answer is: " << CorrectAnswer << endl;
    }
}

enOperationType GetOperationRoundType(enOperationType OperationType)
{
    if (OperationType == enOperationType::MixOp)
    {
        short Op = RandomNumber(1, 4);
        return (enOperationType)Op;
    }
    else
    {
        return OperationType;
    }
}

void SetAnswerScreenColor(int PlayerAnswer, int CorrectAnswer)
{
    if (PlayerAnswer == CorrectAnswer)
        system("color 2F");
    else
        system("color 4F");
}

stGameResults PlayGame()
{
    stGameResults GameResults;
    stMathQuestion MathQuestion;

    GameResults.QuestionsNumber = ReadHowManyQuestions();
    GameResults.QuestionsLevel = ReadQuestionsLevel();
    GameResults.OperationType = ReadOperationType(); 

    GameResults.QuestionsLevelName = GetQuestionsLevelName(GameResults.QuestionsLevel);
    GameResults.OperationTypeName = GetOperationSymbol(GameResults.OperationType);

    for (short RoundNumber = 1; RoundNumber <= GameResults.QuestionsNumber; RoundNumber++)
    {
        cout << endl << "Question [" << RoundNumber << "/" << GameResults.QuestionsNumber << "]\n\n";
  
        MathQuestion.RoundQuestionLevel = GetRoundQuestionLevel(GameResults.QuestionsLevel);

        MathQuestion.Operand1 = QuestionsLevelDegree(MathQuestion.RoundQuestionLevel);
        MathQuestion.Operand2 = QuestionsLevelDegree(MathQuestion.RoundQuestionLevel);

        MathQuestion.OperationRoundType = GetOperationRoundType(GameResults.OperationType);
        MathQuestion.OperationSymbol = GetOperationSymbol(MathQuestion.OperationRoundType);

        MathQuestion.PlayerAnswer = QuizQuestions(MathQuestion);
        MathQuestion.CorrectAnswer = CalculateOperationResult(MathQuestion);

        CheckPlayerAnswer(MathQuestion.PlayerAnswer, MathQuestion.CorrectAnswer);
        SetAnswerScreenColor(MathQuestion.PlayerAnswer, MathQuestion.CorrectAnswer);

        if (MathQuestion.PlayerAnswer == MathQuestion.CorrectAnswer)
            GameResults.RightAnswers++;
        else
            GameResults.WrongAnswers++;
    }

    return GameResults;
}

string ShowFinalResult(short RightAnswers, short WrongAnswers)
{
    if (RightAnswers >= WrongAnswers)
        return "Pass :-)";
    else
        return "Fail :-(";
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << "\n\n\n_________________________________\n\n";
    cout << "  Final Results is " << ShowFinalResult(GameResults.RightAnswers, GameResults.WrongAnswers) << endl;
    cout << "_________________________________\n\n";
    cout << "Number of Questions: " << GameResults.QuestionsNumber << endl;
    cout << "Questions Level    : " << GameResults.QuestionsLevelName << endl;
    cout << "Operation Type     :" << GameResults.OperationTypeName << endl;
    cout << "Number of Right Answers: " << GameResults.RightAnswers << endl;
    cout << "Number of Wrong Answers: " << GameResults.WrongAnswers << endl;
    cout << "_________________________________" << endl;
}

void ResetScreen()
{
    // Optional: clear the screen
    system("cls");

    // Optional: reset color
    system("color 0F"); // Default console color
}

void StartGame()
{
    char PlayAgain = 'Y';

    do {
        ResetScreen();
        stGameResults GameResults = PlayGame();
        ShowFinalGameResults(GameResults);
        
        cout << "\nDo you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main() {
    //Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}