#include <iostream>
#include <fstream>
using namespace std;

const int MAX_STUDENTS = 5;
const int MAX_LABS = 3;

// Function Prototypes
void teacherPortal();
void universityCafe();
void csvfile(string studentNames[MAX_STUDENTS],int rollNumbers[MAX_STUDENTS],float labPerformance[MAX_STUDENTS][MAX_LABS],float labReports[MAX_STUDENTS][MAX_LABS],float midterm[MAX_STUDENTS],float cea[MAX_STUDENTS],float finalTerm[MAX_STUDENTS],float totalMarks[MAX_STUDENTS],char grades[MAX_STUDENTS],int numStudents);

int main() {
    int choice;
    do {
        cout << "University Management System\n";
        cout << "1. Teacher Portal\n";
        cout << "2. University Cafe\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            teacherPortal();
            break;
        case 2:
            universityCafe();
            break;
        case 3:
            cout << "Exiting Program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
    return 0;
}

void teacherPortal() {
    const int MAX_CLASSES = 5;
    const int MAX_STUDENTS = 5;
    const int MAX_LABS = 3;
    std::string classes[MAX_CLASSES];
    int numClasses, selectedClass;
    
    cout << "Enter the number of classes (up to 5): ";
    cin >> numClasses;

    // Input class names
    cin.ignore(); // Clear buffer before starting to read class names
    for (int i = 0; i < numClasses; i++) {
        cout << "Enter class " << i + 1 << " name: ";
        getline(cin, classes[i]); // Use getline to read full line including spaces
    }

    // Display classes
    cout << "\nAvailable Classes:\n";
    for (int i = 0; i < numClasses; i++) {
        cout << "Press " << i + 1 << " for " << classes[i] << "\n";
    }

    cout << "Enter your choice: ";
    cin >> selectedClass;

    if (selectedClass < 1 || selectedClass > numClasses) {
        cout << "Invalid class choice.\n";
        return;
    }
    
    // Marks management
    string studentNames[MAX_STUDENTS];
    int rollNumbers[MAX_STUDENTS];
    float labPerformance[MAX_STUDENTS][MAX_LABS];
    float labReports[MAX_STUDENTS][MAX_LABS];
    float midterm[MAX_STUDENTS], cea[MAX_STUDENTS], finalTerm[MAX_STUDENTS];
    float weights[5], totalMarks[MAX_STUDENTS];
    char grades[MAX_STUDENTS];
    

    // Initialize lab performance and report marks to 0
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        for (int j = 0; j < MAX_LABS; ++j) {
            labPerformance[i][j] = 0;
            labReports[i][j] = 0;
        }
    }

    // Input student data
    for (int i = 0; i < MAX_STUDENTS; i++) {
        cout << "Enter student " << i + 1 << " name: ";
        cin.ignore();
        getline(cin, studentNames[i]);

        cout << "Enter roll number: ";
        cin >> rollNumbers[i];
        int choice2; 

        do {
            cout << "Entering marks in each assessment\n";
            cout << "Press 1 for Lab performance\n";
            cout << "Press 2 for Lab reports\n";
            cout << "Press 3 for Midterm\n";
            cout << "Press 4 for CEA\n";
            cout << "Press 5 for Final Term\n";
            cout << "Press 6 to exit\n";
            cin >> choice2;

            switch (choice2) {
                case 1:
                    int labChoice;
                    	cout << "Enter marks for each Lab Performance from 100 (" << MAX_LABS << " labs):\n";
                         for (int j = 0; j < MAX_LABS; j++) {
                            cout << "Lab " << j + 1 << ": ";
                            cin >> labPerformance[i][j];
                         }
                    break;
                case 2:
                    int reportChoice;
                        cout << "Enter marks for each Lab Reports from 100 (" << MAX_LABS << " labs):\n";
                         for (int j = 0; j < MAX_LABS; j++) {
                            cout << "Lab Report " << j + 1 << ": ";
                            cin >> labReports[i][j];
                         }
                    break;
                case 3:
                    cout << "Enter Midterm marks From 100 : ";
                    cin >> midterm[i];
                    break;
                case 4:
                    cout << "Enter CEA marks from 100: ";
                    cin >> cea[i];
                    break;
                case 5:
                    cout << "Enter Final Term marks from 100: ";
                    cin >> finalTerm[i];
                    break;
                case 6:
                    cout << "Exiting Marks Entry System\n";
                    break;
                default: 
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice2 != 6);
    }

    // Assign weights
    cout << "Enter weights for Lab Performance, Lab Reports, Midterm, CEA, Final Term (in %): ";
    for (int i = 0; i < 5; i++) {
        cin >> weights[i];
        weights[i] /= 100; // Convert to fraction
    }

    // Menu for calculating total marks and generating grades
    int option;
    do {
        cout << "\nOptions:\n";
        cout << "1. Calculate Total Marks\n";
        cout << "2. Generate Grades\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                // Calculate total marks
                for (int i = 0; i < MAX_STUDENTS; i++) {
                    float labPerformanceTotal = 0, labReportsTotal = 0;

                    for (int j = 0; j < MAX_LABS; ++j) {
                        labPerformanceTotal += labPerformance[i][j];
                        labReportsTotal += labReports[i][j];
                    }

                    // Assuming equal weightage for each lab and report
                    labPerformanceTotal /= MAX_LABS;
                    labReportsTotal /= MAX_LABS;

                    totalMarks[i] = labPerformanceTotal * weights[0]+ labReportsTotal * weights[1]+
                                    midterm[i] * weights[2] + cea[i] * weights[3] + finalTerm[i] * weights[4];


                    cout << "Total Marks for " << studentNames[i] << " (Roll No: " << rollNumbers[i] << "): "
                         << totalMarks[i] << "\n";
                }
                break;

            case 2:
                // Generate grades
                for (int i = 0; i < MAX_STUDENTS; i++) {
                    if (totalMarks[i] >= 90) grades[i] = 'A';
                    else if (totalMarks[i] >= 80) grades[i] = 'B';
                    else if (totalMarks[i] >= 70) grades[i] = 'C';
                    else if (totalMarks[i] >= 60) grades[i] = 'D';
                    else grades[i] = 'F';
                }

                // Display student grades
                cout << "\nGrades:\n";
                for (int i = 0; i < MAX_STUDENTS; i++) {
                    cout << "Student: " << studentNames[i] << " | Roll No: " << rollNumbers[i]
                         << " | Total Marks: " << totalMarks[i] << " | Grade: " << grades[i] << "\n";
                }
                break;

            case 3:
                cout << "Exiting...\n";
                csvfile( studentNames,rollNumbers,labPerformance,labReports,midterm,cea,finalTerm,totalMarks,grades, MAX_STUDENTS);
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (option != 3);
}
void csvfile(string studentNames[MAX_STUDENTS], int rollNumbers[MAX_STUDENTS], float labPerformance[MAX_STUDENTS][MAX_LABS],
             float labReports[MAX_STUDENTS][MAX_LABS], float midterm[MAX_STUDENTS], float cea[MAX_STUDENTS],
             float finalTerm[MAX_STUDENTS], float totalMarks[MAX_STUDENTS], char grades[MAX_STUDENTS], int numStudents) {
    ofstream studentsdata("Studentsdata.csv");

    
    studentsdata << "Name,Roll Number,Lab Performance (Lab 1),Lab Performance (Lab 2),Lab Performance (Lab 3),Lab Reports (Lab 1),Lab Reports (Lab 2),Lab Reports (Lab 3), Midterm,CEA,Final Term,Total Marks,Grade\n";

    for (int i = 0; i < numStudents; ++i) {
        studentsdata << studentNames[i] << "," << rollNumbers[i];

        for (int j = 0; j < MAX_LABS; ++j) {
            studentsdata << "," << labPerformance[i][j];
        }

        for (int j = 0; j < MAX_LABS; ++j) {
            studentsdata << "," << labReports[i][j];
        }

        studentsdata << "," << midterm[i] << "," << cea[i] << "," << finalTerm[i] << "," << totalMarks[i] << "," << grades[i] <<endl;
    }

    studentsdata.close();
    cout << "Student data is saved in Studentsdata.csv\n";
}
void universityCafe() {
    const int MENU_SIZE = 10;
    std::string items[MENU_SIZE] = {"Burger", "Pizza", "Sandwich", "Pasta", "Fries",
                                    "Coffee", "Tea", "Juice", "Ice Cream", "Cake"};
    float prices[MENU_SIZE] = {300, 500, 150, 350, 200, 120, 80, 150, 100, 250};
    float totalBill = 0;
    int choice, quantity;

    while (true) {
        // Display the menu
        cout << "\n--- University Cafe Menu ---\n";
        for (int i = 0; i < MENU_SIZE; i++) {
            cout << i + 1 << ". " << items[i] << " - Rs. " << prices[i] << "\n";
        }

        cout << "\nEnter the number of the item you want to buy (1-10): ";
        cin >> choice;

        // Validate user input
        if (choice < 1 || choice > MENU_SIZE) {
            cout << "Invalid choice! Please select a valid item.\n";
            continue;
        }


        cout << "Enter quantity: ";
        cin >> quantity;

        // Calculate the cost of the selected item
        totalBill += prices[choice - 1] * quantity;
        cout << quantity << " x " << items[choice - 1] << " added to your bill.\n";

        // Ask if the user wants to buy more or show the bill
        cout << "\nDo you want to buy more items? (y/n): ";
        char decision;
        cin >> decision;

        if (decision == 'n' || decision == 'N') {
            // Show the total bill and exit the function
            cout << "\n--- Total Bill ---\n";
            cout << "Your total bill is Rs. " << totalBill << ".\n";
            cout << "Thank you for visiting the University Cafe!\n";
            break;
        } else if (decision != 'y' && decision != 'Y') {
            // If the user enters an invalid response
            cout << "Invalid response. Assuming you want to continue buying.\n";
        }
    }
}
