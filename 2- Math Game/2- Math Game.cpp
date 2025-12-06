
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };

enum enOparationType {Add = 1 , Sub = 2 , Mul = 3 , Div = 4 , Mix = 5};

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOparationType OparationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer;
    int PlayerAnswer;
    bool AnswerResult = false; 
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionsLevel QuestionLevel;
    enOparationType OparationType;
    short NumberOfWrongAnswer = 0;
    short NumberOfRightAnswer = 0;
    bool IsPass = false;
};

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    string ArrQuestionLevelText[4] = { "Easy" , "Med" , "Hard" , "Mix" };
    return ArrQuestionLevelText[QuestionLevel - 1];
}

string GetOpTypeSympol(enOparationType OpType)
{
    switch (OpType)
    {
    case enOparationType::Add:
        return "+";

    case enOparationType::Sub:
        return "-";

    case enOparationType::Mul:
        return "*";

    case enOparationType::Div:
        return "/";

    default:
        return "Mix";
       
    }
}

short ReadHowManyQuestions()
{
    short Questions = 0;

    do
    {
        cout << "Please enter number of questions : ";
        cin >> Questions;
    } while (Questions < 1 || Questions > 10);

    return Questions;
}

enQuestionsLevel ReadQuestinsLevel()
{
    short Level;

    do
    {
        cout << "Please enter Questions Level : [1] Easy , [2] Med , [3] Hard , [4] Mix : ";
        cin >> Level;

    } while (Level < 1 || Level > 4);

    return (enQuestionsLevel)Level;
}

enOparationType ReadOparationType()
{
    short OpType;

    do
    {
        cout << "Please enter Oparation Type : [1] Add , [2] Sub , [3] Mult , [4] Div , [5] Mix : ";
        cin >> OpType;

    } while (OpType < 1 || OpType > 5);

    return (enOparationType)OpType;
}

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

enOparationType GetRandomOparationType()
{
    int Op = RandomNumber(1, 4);
    return (enOparationType)Op;
}

int SimpleCalculator(int Number1, int Number2, enOparationType OpType)
{
    switch (OpType)
    {
    case enOparationType::Add:
        return Number1 + Number2;

    case enOparationType::Sub:
        return Number1 - Number2;

    case enOparationType::Mul:
        return Number1 * Number2;

    case enOparationType::Div:
        return Number1 / Number2;

    default:
        return 0;
    }
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOparationType OparationType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::MixLevel)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    }

    if (OparationType == enOparationType::Mix)
    {
        OparationType = GetRandomOparationType();
    }

    Question.OparationType = OparationType;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::Easy:

        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OparationType);
        Question.QuestionLevel = QuestionLevel;

        return Question;

    case enQuestionsLevel::Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OparationType);
        Question.QuestionLevel = QuestionLevel;

        return Question;

    case enQuestionsLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OparationType);
        Question.QuestionLevel = QuestionLevel;

        return Question;
    }

    return Question;
}

void GenerateQuizzQuestions(stQuizz &Quizz)
{
    for (short Questions = 0; Questions < Quizz.NumberOfQuestions; Questions++)
    {
        Quizz.QuestionList[Questions] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OparationType);

    }
}

int ReadQuenstionAnswer()
{
    int Answer;
    cin >> Answer;
    return Answer;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{

    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;

        system("color 4f");  // Red Color
        cout << "\a"; 

        cout << "Wrong Answer :-( " << endl;
        cout << "The Right Answer is : ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";

    }

    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;

        cout << "Right Answer :-)" << endl;
        system("color 2f"); // Green Color

      

    }

}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n";

    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]  \n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << GetOpTypeSympol(Quizz.QuestionList[QuestionNumber].OparationType) << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2;
    cout << "\n_____________________" << endl;
}

void AskAndCorrectQuestionsListAnswer(stQuizz &Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);

        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuenstionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);


    }

    Quizz.IsPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);

}

string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "Pass :-) ";
    else
        return "Fail :-( ";
}

void PrinQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "______________________________\n\n";
    cout << "Final Result is : " << GetFinalResultsText(Quizz.IsPass);
    cout << "\n_____________________________\n\n";

    cout << "Number of Questions : " << Quizz.NumberOfQuestions << endl;
    cout << "Question Level : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "Oparation Type : " << GetOpTypeSympol(Quizz.OparationType) << endl;
    cout << "Number Of Right Answer : " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number Of Wrong Answer : " << Quizz.NumberOfWrongAnswer << endl;
    cout << "________________________________\n";

}

void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadQuestinsLevel();
    Quizz.OparationType = ReadOparationType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionsListAnswer(Quizz);
    PrinQuizzResults(Quizz);
}

void ResetScreen()
{

    system("cls");
    system("color 0f"); // Black Color

}

void MathGame()
{
    char PlayAgain = 'y';

    do
    {

        ResetScreen();
        PlayMathGame();

        cout << endl  << "Do You Want Play Again ? y/n ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));


    MathGame();

}

