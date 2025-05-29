#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_STUDENTS = 5;
const int NUM_ASSESSMENTS = 5;

void inputClasses(string classes[], int& numClasses);
void displayClasses(string classes[], int numClasses);
void inputStudentDetails(string studentsNames[], string studentsRolls[], float studentsMarks[MAX_STUDENTS][NUM_ASSESSMENTS], int numStudents);
void inputMarks(float studentsMarks[MAX_STUDENTS][NUM_ASSESSMENTS], int numStudents, float weights[]);
void assignWeights(float weights[]);
void calculateTotalMarks(float studentsMarks[MAX_STUDENTS][NUM_ASSESSMENTS], float studentsTotalMarks[], int numStudents, float weights[]);
void assignGrades(float studentsTotalMarks[], char studentsGrades[], int numStudents);
void displayResults(string studentsNames[], string studentsRolls[], float studentsTotalMarks[], char studentsGrades[], int numStudents);
void writeToCSV(string studentsNames[], string studentsRolls[], float studentsMarks[MAX_STUDENTS][NUM_ASSESSMENTS], float studentsTotalMarks[], char studentsGrades[], int numStudents);
void Universitycafe();

int main() {
   while(1){
   	cout<<endl;
    int choice;
    cout << "Welcome to the University Management System!\n";
    cout << "Press 1 for Teacher Portal\n";
    cout << "Press 2 for University Cafe\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
       
        string classes[10];
        int numClasses;
        string studentsNames[MAX_STUDENTS];
        string studentsRolls[MAX_STUDENTS];
        float studentsMarks[MAX_STUDENTS][NUM_ASSESSMENTS];
        float studentsTotalMarks[MAX_STUDENTS];
        char studentsGrades[MAX_STUDENTS];
        float weights[NUM_ASSESSMENTS] = {0};
        int selectedClass = 0;

        cout << "Welcome to the Teacher Portal!\n";
        inputClasses(classes, numClasses);
        displayClasses(classes, numClasses);
        cout << "Enter the number of the class you want to manage: ";
        cin >> selectedClass;
        if (selectedClass < 1 || selectedClass > numClasses) {
            cout << "Invalid class selection! Exiting program.\n";
            return 1;
        }
        cout << "Managing class: " << classes[selectedClass - 1] << "\n\n";
        inputStudentDetails(studentsNames, studentsRolls, studentsMarks, MAX_STUDENTS);
        assignWeights(weights);
        inputMarks(studentsMarks, MAX_STUDENTS, weights);
        calculateTotalMarks(studentsMarks, studentsTotalMarks, MAX_STUDENTS, weights);
        assignGrades(studentsTotalMarks, studentsGrades, MAX_STUDENTS);
        displayResults(studentsNames, studentsRolls, studentsTotalMarks, studentsGrades, MAX_STUDENTS);
        writeToCSV(studentsNames, studentsRolls, studentsMarks, studentsTotalMarks, studentsGrades, MAX_STUDENTS);
    } else if (choice == 2) {
        cout << "Welcome to the University Cafe!\n";
        Universitycafe();
    } else {
        cout << "Invalid choice! Exiting program.\n";
        return 1;
    }}

    return 0;
}

// Teacher Portal Function Definitions
void inputClasses(string classes[], int& numClasses) {
    cout << "Enter the number of classes: ";
    cin >> numClasses;
    cin.ignore();
    for (int i = 0; i < numClasses; ++i) {
        cout << "Enter the name of class " << (i + 1) << ": ";
        getline(cin, classes[i]);
    }
}

void displayClasses(string classes[], int numClasses) {
    cout << "\nAvailable classes:\n";
    for (int i = 0; i < numClasses; ++i) {
        cout << "Press " << (i + 1) << " for " << classes[i] << "\n";
    }
}

void inputStudentDetails(string studentsNames[], string studentsRolls[], float studentsMarks[MAX_STUDENTS][NUM_ASSESSMENTS], int numStudents) {
    cout << "\nEnter details for " << numStudents << " students:\n";
    cin.ignore();
    for (int i = 0; i < numStudents; ++i) {
        cout << "\nStudent " << (i + 1) << ":\n";
        cout << "Name: ";
        getline(cin, studentsNames[i]);
        cout << "Roll Number: ";
        getline(cin, studentsRolls[i]);
    }
}

void inputMarks(float studentsMarks[MAX_STUDENTS][NUM_ASSESSMENTS], int numStudents, float weights[]) {
    for (int i = 0; i < numStudents; ++i) {
        cout << "\nEntering marks for Student " << (i + 1) << ":\n";
        for (int j = 0; j < NUM_ASSESSMENTS; ++j) {
            string assessmentName;
            switch (j) {
                case 0: assessmentName = "Lab Performance"; break;
                case 1: assessmentName = "Lab Reports"; break;
                case 2: assessmentName = "Midterm"; break;
                case 3: assessmentName = "CEA"; break;
                case 4: assessmentName = "Final Term"; break;
            }
            cout << assessmentName << " (Weight: " << weights[j] << "%): ";
            cin >> studentsMarks[i][j];
        }
    }
}

void assignWeights(float weights[]) {
    cout << "\nAssign weights to the following assessments:\n";
    cout << "Provide 5 options:\n";
    cout << "Press 1 for Lab Performance\n";
    cout << "Press 2 for Lab Reports\n";
    cout << "Press 3 for Midterm\n";
    cout << "Press 4 for CEA\n";
    cout << "Press 5 for Final Term\n";
    float totalWeight = 0; 
    for (int i = 0; i < NUM_ASSESSMENTS; ++i) {
        int option;
        float weight;
        cout << "\nEnter your choice (1-5) for weightage assignment: ";
        cin >> option;
        string assessmentName;
        switch (option) {
            case 1:
             assessmentName = "Lab Performance";
              break;
            case 2: 
            assessmentName = "Lab Reports";
             break;
            case 3:
             assessmentName = "Midterm";
              break;
            case 4:
             assessmentName = "CEA";
              break;
            case 5:
             assessmentName = "Final Term";
              break;
            default:
                cout << "Invalid choice! Please enter a valid option (1-5).\n";
                --i; 
                continue;
        }
        cout << "Enter weight for " << assessmentName << " (in percentage): ";
        cin >> weight;
        if (weight < 0 || weight > 100) {
            cout << "Invalid weight! It must be between 0 and 100.\n";
            --i; 
            continue;
        }
        if (totalWeight + weight > 100) {
            cout << "Total weight exceeds 100%! Current total is " << totalWeight << "%.\n";
            cout << "Please enter a smaller weight.\n";
            --i; 
            continue;
        }
        weights[option - 1] = weight;
        totalWeight += weight;
        cout << "Assigned weight: " << weight << "%. Total weight so far: " << totalWeight << "%.\n";
    }
    if (totalWeight < 100) {
        cout << "\nWarning: Total weight is less than 100%. Current total: " << totalWeight << "%.\n";
    } else {
        cout << "\nWeights assigned successfully! Total weight is 100%.\n";
    }
}

void calculateTotalMarks(float studentsMarks[MAX_STUDENTS][NUM_ASSESSMENTS], float studentsTotalMarks[], int numStudents, float weights[]) {
    for (int i = 0; i < numStudents; ++i) {
        studentsTotalMarks[i] = 0;
        for (int j = 0; j < NUM_ASSESSMENTS; ++j) {
            studentsTotalMarks[i] += studentsMarks[i][j] * (weights[j] / 100);
        }
    }
}

void assignGrades(float studentsTotalMarks[], char studentsGrades[], int numStudents) {
    for (int i = 0; i < numStudents; ++i) {
        if (studentsTotalMarks[i] >= 90) {
            studentsGrades[i] = 'A';
        } else if (studentsTotalMarks[i] >= 80 && studentsTotalMarks[i]<90) {
            studentsGrades[i] = 'B';
        } else if (studentsTotalMarks[i] >= 70 && studentsTotalMarks[i]<80) {
            studentsGrades[i] = 'C';
        } else if (studentsTotalMarks[i] >= 60 && studentsTotalMarks[i]<70) {
            studentsGrades[i] = 'D';
        } else if(studentsTotalMarks[i]<60) {
            studentsGrades[i] = 'F';
        }
        else
        cout<<"Invalid Input.";
    }
}

void displayResults(string studentsNames[], string studentsRolls[], float studentsTotalMarks[], char studentsGrades[], int numStudents) {
    cout << "\nResults:\n";
    cout << "-----------------------------------------\n";
    cout << "| Name | Roll Number | Total Marks | Grade |\n";
    cout << "-----------------------------------------\n";
    for (int i = 0; i < numStudents; ++i) {
        cout << "| " << studentsNames[i] << " | " << studentsRolls[i] << " | " << studentsTotalMarks[i] << " | " << studentsGrades[i] << " |\n";
    }
}

void writeToCSV(string studentsNames[], string studentsRolls[], float studentsMarks[MAX_STUDENTS][NUM_ASSESSMENTS], float studentsTotalMarks[], char studentsGrades[], int numStudents) {
    ofstream outFile("studentsdetail.csv");

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    outFile << "Name,Roll Number,Lab Performance,Lab Reports,Midterm,CEA,Final Term,Total Marks,Grade\n";

    for (int i = 0; i < numStudents; ++i) {
        outFile << studentsNames[i] << "," << studentsRolls[i];
        for (int j = 0; j < NUM_ASSESSMENTS; ++j) {
            outFile << "," << studentsMarks[i][j];
        }
        outFile << "," << studentsTotalMarks[i] << "," << studentsGrades[i] << "\n";
    }

    outFile.close();
    cout << "\nStudent details have been written to studentsdetail.csv\n";
}
