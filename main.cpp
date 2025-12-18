#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;


struct Question {
    int id;
    string questionText;
    string options[4];  // Array of 4 options
    int correctAnswer;
    string explanation;
};

// Stack for undo functionality (previous questions)
stack<Question> questionHistory;

// Queue for question ordering
queue<Question> questionQueue;

// Array to store all questions
Question questionBank[30];
int totalQuestions = 30;

// User answer tracking
struct UserAnswer {
    int questionId;
    int selectedAnswer;
    bool isCorrect;
    int timeSpent;
};

// Array to store user answers
UserAnswer userAnswers[30];
int answerCount = 0;

// Stack for navigation history
stack<int> navigationStack;

// Console color functions for Windows
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor() {
    setColor(7); // Default white
}

// Function to clear screen
void clearScreen() {
    system("cls");
}

// Function to initialize all 30 questions about Philippine Climate Action
void initializeQuestions() {
    // Question 1
    questionBank[0].id = 1;
    questionBank[0].questionText = "What percentage of renewable energy does the Philippines aim to achieve by 2030?";
    questionBank[0].options[0] = "25%";
    questionBank[0].options[1] = "35%";
    questionBank[0].options[2] = "45%";
    questionBank[0].options[3] = "50%";
    questionBank[0].correctAnswer = 1;
    questionBank[0].explanation = "The National Renewable Energy Program (NREP) targets 35% by 2030.";

    // Question 2
    questionBank[1].id = 2;
    questionBank[1].questionText = "Which government body handles climate change policy in the Philippines?";
    questionBank[1].options[0] = "Department of Environment";
    questionBank[1].options[1] = "Climate Change Commission";
    questionBank[1].options[2] = "Energy Regulatory Board";
    questionBank[1].options[3] = "National Disaster Agency";
    questionBank[1].correctAnswer = 1;
    questionBank[1].explanation = "The Climate Change Commission (CCC) is the lead policy-making body.";

    // Question 3
    questionBank[2].id = 3;
    questionBank[2].questionText = "How much has temperature increased in the Philippines (2025 analysis)?";
    questionBank[2].options[0] = "0.5 to 1.0 degrees";
    questionBank[2].options[1] = "1.3 to 2.2 degrees";
    questionBank[2].options[2] = "2.5 to 3.0 degrees";
    questionBank[2].options[3] = "3.0 to 4.0 degrees";
    questionBank[2].correctAnswer = 1;
    questionBank[2].explanation = "Temperature increased by 1.3 to 2.2 degrees Celsius.";

    // Question 4
    questionBank[3].id = 4;
    questionBank[3].questionText = "What innovative carbon credit system is the Philippines testing?";
    questionBank[3].options[0] = "Green Credits";
    questionBank[3].options[1] = "Transition Credits";
    questionBank[3].options[2] = "Blue Credits";
    questionBank[3].options[3] = "Climate Bonds";
    questionBank[3].correctAnswer = 1;
    questionBank[3].explanation = "Philippines is testing 'transition credits' to cut coal use.";

    // Question 5
    questionBank[4].id = 5;
    questionBank[4].questionText = "By what % has climate change increased Category 3-5 typhoon likelihood?";
    questionBank[4].options[0] = "10%";
    questionBank[4].options[1] = "15%";
    questionBank[4].options[2] = "25%";
    questionBank[4].options[3] = "35%";
    questionBank[4].correctAnswer = 2;
    questionBank[4].explanation = "Studies show a 25% increase in severe typhoon likelihood.";

    // Question 6
    questionBank[5].id = 6;
    questionBank[5].questionText = "What is the local name for Super Typhoon Rai?";
    questionBank[5].options[0] = "Yolanda";
    questionBank[5].options[1] = "Odette";
    questionBank[5].options[2] = "Haiyan";
    questionBank[5].options[3] = "Pablo";
    questionBank[5].correctAnswer = 1;
    questionBank[5].explanation = "Super Typhoon Rai is locally known as Odette.";

    // Question 7
    questionBank[6].id = 7;
    questionBank[6].questionText = "Where does the Philippines rank globally for disaster risk?";
    questionBank[6].options[0] = "1st";
    questionBank[6].options[1] = "2nd";
    questionBank[6].options[2] = "5th";
    questionBank[6].options[3] = "10th";
    questionBank[6].correctAnswer = 1;
    questionBank[6].explanation = "Philippines is ranked 2nd highest for disaster risk vulnerability.";

    // Question 8
    questionBank[7].id = 8;
    questionBank[7].questionText = "What is the renewable energy target by 2040?";
    questionBank[7].options[0] = "35%";
    questionBank[7].options[1] = "45%";
    questionBank[7].options[2] = "50%";
    questionBank[7].options[3] = "60%";
    questionBank[7].correctAnswer = 2;
    questionBank[7].explanation = "The NREP targets 50% renewable energy by 2040.";

    // Question 9
    questionBank[8].id = 9;
    questionBank[8].questionText = "Which fossil fuel company are Filipino communities suing?";
    questionBank[8].options[0] = "ExxonMobil";
    questionBank[8].options[1] = "BP";
    questionBank[8].options[2] = "Shell";
    questionBank[8].options[3] = "Chevron";
    questionBank[8].correctAnswer = 2;
    questionBank[8].explanation = "Communities are suing Shell Plc for climate damage.";

    // Question 10
    questionBank[9].id = 10;
    questionBank[9].questionText = "What % of current energy mix is renewable (2025)?";
    questionBank[9].options[0] = "22.7%";
    questionBank[9].options[1] = "27.7%";
    questionBank[9].options[2] = "32.7%";
    questionBank[9].options[3] = "37.7%";
    questionBank[9].correctAnswer = 2;
    questionBank[9].explanation = "Philippines has 32.7% renewable energy currently.";

    // Question 11
    questionBank[10].id = 11;
    questionBank[10].questionText = "Which renewable energy source has the Philippines significant potential in?";
    questionBank[10].options[0] = "Wind";
    questionBank[10].options[1] = "Solar";
    questionBank[10].options[2] = "Geothermal";
    questionBank[10].options[3] = "Tidal";
    questionBank[10].correctAnswer = 2;
    questionBank[10].explanation = "Philippines has abundant geothermal resources due to volcanic activity.";

    // Question 12
    questionBank[11].id = 12;
    questionBank[11].questionText = "What law fosters renewable energy rollout in the Philippines?";
    questionBank[11].options[0] = "Clean Energy Act";
    questionBank[11].options[1] = "Renewable Energy Act";
    questionBank[11].options[2] = "Green Power Law";
    questionBank[11].options[3] = "Climate Action Act";
    questionBank[11].correctAnswer = 1;
    questionBank[11].explanation = "The Renewable Energy Act accelerates renewable energy deployment.";

    // Question 13
    questionBank[12].id = 13;
    questionBank[12].questionText = "How much has typhoon maximum potential intensity increased due to climate change?";
    questionBank[12].options[0] = "1 meter per second";
    questionBank[12].options[1] = "2 meters per second";
    questionBank[12].options[2] = "3 meters per second";
    questionBank[12].options[3] = "5 meters per second";
    questionBank[12].correctAnswer = 1;
    questionBank[12].explanation = "Typhoon intensity increased by about 2 meters per second.";

    // Question 14
    questionBank[13].id = 14;
    questionBank[13].questionText = "What year was the General Appropriations Act with climate provisions enacted?";
    questionBank[13].options[0] = "2023";
    questionBank[13].options[1] = "2024";
    questionBank[13].options[2] = "2025";
    questionBank[13].options[3] = "2026";
    questionBank[13].correctAnswer = 2;
    questionBank[13].explanation = "Republic Act No. 12116 for Fiscal Year 2025 contains climate provisions.";

    // Question 15
    questionBank[14].id = 15;
    questionBank[14].questionText = "Which renewable energy sources are being prioritized in the Philippines?";
    questionBank[14].options[0] = "Only Solar";
    questionBank[14].options[1] = "Solar, Wind, Geothermal, Hydropower";
    questionBank[14].options[2] = "Only Wind";
    questionBank[14].options[3] = "Only Geothermal";
    questionBank[14].correctAnswer = 1;
    questionBank[14].explanation = "Philippines is developing a mix of solar, wind, geothermal, and hydropower.";

    // Question 16
    questionBank[15].id = 16;
    questionBank[15].questionText = "Which typhoon killed at least 114 people in the Philippines in 2025?";
    questionBank[15].options[0] = "Typhoon Haiyan";
    questionBank[15].options[1] = "Typhoon Kalmaegi";
    questionBank[15].options[2] = "Typhoon Rai";
    questionBank[15].options[3] = "Typhoon Goni";
    questionBank[15].correctAnswer = 1;
    questionBank[15].explanation = "Typhoon Kalmaegi was one of the strongest in 2025, causing severe flooding.";

    // Question 17
    questionBank[16].id = 17;
    questionBank[16].questionText = "The Philippines' climate target is consistent with limiting warming to what?";
    questionBank[16].options[0] = "1.5 degrees C";
    questionBank[16].options[1] = "2.0 degrees C";
    questionBank[16].options[2] = "2.5 degrees C";
    questionBank[16].options[3] = "3.0 degrees C";
    questionBank[16].correctAnswer = 0;
    questionBank[16].explanation = "Philippines targets are consistent with limiting warming to 1.5Â°C.";

    // Question 18
    questionBank[17].id = 18;
    questionBank[17].questionText = "What is a major barrier to Philippines' climate resilience?";
    questionBank[17].options[0] = "Lack of technology";
    questionBank[17].options[1] = "Corruption and complacency";
    questionBank[17].options[2] = "Geography";
    questionBank[17].options[3] = "Population";
    questionBank[17].correctAnswer = 1;
    questionBank[17].explanation = "Corruption and complacency turn natural hazards into tragedies.";

    // Question 19
    questionBank[18].id = 19;
    questionBank[18].questionText = "Which President reaffirmed Philippines' climate commitment in December 2025?";
    questionBank[18].options[0] = "Rodrigo Duterte";
    questionBank[18].options[1] = "Ferdinand Marcos Jr.";
    questionBank[18].options[2] = "Benigno Aquino";
    questionBank[18].options[3] = "Gloria Arroyo";
    questionBank[18].correctAnswer = 1;
    questionBank[18].explanation = "President Ferdinand R. Marcos Jr. reaffirmed commitment on Dec 5, 2025.";

    // Question 20
    questionBank[19].id = 20;
    questionBank[19].questionText = "What Article in climate agreements concerns Philippine experts?";
    questionBank[19].options[0] = "Article 4";
    questionBank[19].options[1] = "Article 5";
    questionBank[19].options[2] = "Article 6";
    questionBank[19].options[3] = "Article 7";
    questionBank[19].correctAnswer = 2;
    questionBank[19].explanation = "Experts are concerned about Article 6 implementation and safeguards.";

}

// Load questions into queue
void loadQuestionsToQueue() {
    for (int i = 0; i < totalQuestions; i++) {
        questionQueue.push(questionBank[i]);
    }
}

// Display question with colored formatting
void displayQuestion(Question q) {
    clearScreen();
    setColor(11); // Cyan
    cout << "\n========================================\n";
    setColor(14); // Yellow
    cout << "Question " << q.id << " of " << totalQuestions << "\n";
    setColor(11);
    cout << "========================================\n\n";
    
    setColor(15); // White
    cout << q.questionText << "\n\n";
    
    for (int i = 0; i < 4; i++) {
        setColor(10); // Green
        cout << i + 1 << ". ";
        setColor(7); // Default
        cout << q.options[i] << "\n";
    }
    
    setColor(11);
    cout << "========================================\n";
    resetColor();
}

// Process answer using stack for history
void processAnswer(Question currentQ, int userChoice, int timeTaken) {
    // Push to history stack
    questionHistory.push(currentQ);
    
    // Record answer in array
    userAnswers[answerCount].questionId = currentQ.id;
    userAnswers[answerCount].selectedAnswer = userChoice;
    userAnswers[answerCount].isCorrect = (userChoice - 1 == currentQ.correctAnswer);
    userAnswers[answerCount].timeSpent = timeTaken;
    answerCount++;
    
    cout << "\n";
    // Display result
    if (userChoice - 1 == currentQ.correctAnswer) {
        setColor(10); // Green
        cout << "CORRECT! ";
        resetColor();
        cout << currentQ.explanation << "\n";
    }
    else {
        setColor(12); // Red
        cout << "WRONG! ";
        resetColor();
        cout << "Correct answer: " << currentQ.options[currentQ.correctAnswer] << "\n";
        cout << "Explanation: " << currentQ.explanation << "\n";
    }
}

// Display results using array traversal
void displayResults() {
    clearScreen();
    int correctCount = 0;
    int totalTime = 0;

    setColor(14); // Yellow
    cout << "\n\n=============== QUIZ RESULTS ===============\n";
    resetColor();

    // Traverse answer array
    for (int i = 0; i < answerCount; i++) {
        if (userAnswers[i].isCorrect) {
            correctCount++;
        }
        totalTime += userAnswers[i].timeSpent;
    }

    float percentage = (float)correctCount / answerCount * 100;

    cout << "Total Questions: " << answerCount << "\n";
    setColor(10);
    cout << "Correct Answers: " << correctCount << "\n";
    setColor(12);
    cout << "Wrong Answers: " << (answerCount - correctCount) << "\n";
    resetColor();
    cout << "Accuracy: " << percentage << "%\n";
    cout << "Total Time: " << totalTime << " seconds\n\n";

    if (percentage >= 90) {
        setColor(10);
        cout << "Outstanding! You're a climate action expert!\n";
    }
    else if (percentage >= 70) {
        setColor(11);
        cout << "Great job! You know your climate facts!\n";
    }
    else if (percentage >= 50) {
        setColor(14);
        cout << "Good effort! Keep learning!\n";
    }
    else {
        setColor(12);
        cout << "Keep studying! Climate action needs awareness!\n";
    }

    resetColor();
    setColor(14);
    cout << "===========================================\n";
    resetColor();
}

// Review answers using stack
void reviewAnswersStack() {
    clearScreen();
    setColor(11);
    cout << "\n\n========== ANSWER REVIEW ==========\n";
    resetColor();

    for (int i = 0; i < answerCount; i++) {
        Question q = questionBank[userAnswers[i].questionId - 1];

        cout << "\nQ" << q.id << ": " << q.questionText << "\n";
        cout << "Your answer: " << q.options[userAnswers[i].selectedAnswer - 1] << "\n";
        cout << "Correct answer: " << q.options[q.correctAnswer] << "\n";

        if (userAnswers[i].isCorrect) {
            setColor(10);
            cout << "Status: CORRECT\n";
        }
        else {
            setColor(12);
            cout << "Status: WRONG\n";
        }
        resetColor();
        cout << "---\n";
    }
}

// Save results to file
void saveResultsToFile() {
    ofstream outFile("quiz_results.txt");

    if (outFile.is_open()) {
        outFile << "Climate Action Quiz Results\n";
        outFile << "===========================\n\n";

        int correct = 0;
        for (int i = 0; i < answerCount; i++) {
            outFile << "Q" << userAnswers[i].questionId << ": ";
            outFile << (userAnswers[i].isCorrect ? "Correct" : "Wrong");
            outFile << " (Time: " << userAnswers[i].timeSpent << "s)\n";

            if (userAnswers[i].isCorrect) correct++;
        }

        outFile << "\nTotal Score: " << correct << "/" << answerCount << "\n";
        outFile << "Percentage: " << ((float)correct / answerCount * 100) << "%\n";

        outFile.close();
        cout << "\nResults saved to quiz_results.txt\n";
    }
}

// Main quiz flow
int main() {
    clearScreen();
    setColor(14); // Yellow
    cout << "===========================================\n";
    cout << "   CLIMATE ACTION QUIZ - PHILIPPINES   \n";
    cout << "===========================================\n";
    resetColor();
    cout << "Topic: Philippine Climate Action 2025\n";
    cout << "Questions: 30 | Time Limit: None (Self-paced)\n";
    setColor(14);
    cout << "===========================================\n\n";
    resetColor();

    // Initialize
    initializeQuestions();
    loadQuestionsToQueue();

    cout << "Press Enter to start the quiz...";
    cin.ignore();
    cin.get();

    // Quiz loop using queue
    int questionNum = 1;
    time_t startTime, endTime;

    while (!questionQueue.empty() && questionNum <= 30) {
        Question currentQ = questionQueue.front();
        questionQueue.pop();

        displayQuestion(currentQ);

        cout << "\nEnter your answer (1-4): ";
        int answer;

        startTime = time(0);
        cin >> answer;
        endTime = time(0);

        int timeTaken = difftime(endTime, startTime);

        if (answer < 1 || answer > 4) {
            setColor(12);
            cout << "Invalid input! Skipping question.\n";
            resetColor();
            continue;
        }

        processAnswer(currentQ, answer, timeTaken);
        navigationStack.push(questionNum);

        questionNum++;

        if (questionNum <= 30) {
            cout << "\nPress Enter for next question...";
            cin.ignore();
            cin.get();
        }
    }

    // Display final results
    displayResults();

    // Save to file
    saveResultsToFile();

    // Option to review
    cout << "\nWould you like to review answers? (y/n): ";
    char review;
    cin >> review;

    if (review == 'y' || review == 'Y') {
        reviewAnswersStack();
    }

    setColor(10);
    cout << "\nThank you for taking the Climate Action Quiz!\n";
    cout << "Together we can make a difference!\n";
    resetColor();

    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}
