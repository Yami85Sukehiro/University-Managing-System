#include "Course_Class.cpp"

using namespace std;

int main(){
    system("cls"); // Clear terminal on Linux: system("clear");
    // Read course information from a file
    /*
    ifstream inputFile("courses.txt");
    if (!inputFile) {
        cout << "Error opening the file." << endl;
    } else {
        string line;
        while (getline(inputFile, line)) {
            string courseType = line;
            string courseId;
            string courseName;
            set<DayOfWeek> courseDays;
            int startHour;
            int startMinute;
            int durationHour;
            int durationMinute;
            bool hasProjector;
            vector<int> students;
            string teacher;
            int capacity;
            int sessionCount;
            int location;

            getline(inputFile, line); // Course ID
            courseId = line.substr(10);

            getline(inputFile, line); // Course Name
            courseName = line.substr(13);

            getline(inputFile, line); // Day
            istringstream iss(line.substr(5));
            string dayString;
            while (iss >> dayString) {
                // Code to insert course days into the set
                // Remove the extra condition for single-letter abbreviations
                if (dayString == "Saturday" || dayString == "Sat") {
                    courseDays.insert(DayOfWeek::Saturday);
                } else if (dayString == "Sunday" || dayString == "Sun") {
                    courseDays.insert(DayOfWeek::Sunday);
                } else if (dayString == "Monday" || dayString == "Mon") {
                    courseDays.insert(DayOfWeek::Monday);
                } else if (dayString == "Tuesday" || dayString == "Tue") {
                    courseDays.insert(DayOfWeek::Tuesday);
                } else if (dayString == "Wednesday" || dayString == "Wed") {
                    courseDays.insert(DayOfWeek::Wednesday);
                } else if (dayString == "Thursday" || dayString == "Thu") {
                    courseDays.insert(DayOfWeek::Thursday);
                } else if (dayString == "Friday" || dayString == "Fri") {
                    courseDays.insert(DayOfWeek::Friday);
                } else {
                    // Check if the input is a single letter, add it to the valid days
                    if (dayString.length() == 1) {
                        char dayChar = toupper(dayString[0]);
                        if (dayChar >= 'A' && dayChar <= 'Z') {
                            DayOfWeek day = static_cast<DayOfWeek>(dayChar);
                            courseDays.insert(day);
                        } else {
                            cout << "Invalid day: " << dayString << endl;
                        }
                    } else {
                        cout << "Invalid day: " << dayString << endl;
                    }
                }
            }

            getline(inputFile, line); // Start Time
            sscanf(line.substr(12).c_str(), "%d:%d", &startHour, &startMinute);

            getline(inputFile, line); // Duration
            sscanf(line.substr(10).c_str(), "%d hours, %d minutes", &durationHour, &durationMinute);

            getline(inputFile, line); // Requires Projector
            hasProjector = (line.substr(18) == "Yes");

            getline(inputFile, line); // Students
            // Code to extract student IDs
            istringstream issStudents(line);
            int studentId;
            while (issStudents >> studentId) {
                students.push_back(studentId);
            }

            getline(inputFile, line); // Teacher
            teacher = line.substr(10);

            if (courseType == "Course Type: University Course") {
                getline(inputFile, line); // Capacity
                capacity = stoi(line.substr(10));

                getline(inputFile, line); // Location
                location = stoi(line.substr(9));

                Course* course = new UniversityCourse(courseId, courseName, courseDays, startHour, startMinute,
                                                    durationHour, durationMinute, hasProjector, capacity,
                                                    students, teacher, location);
            } else if (courseType == "Course Type: Scientific Course") {
                getline(inputFile, line); // Session Count
                sessionCount = stoi(line.substr(14));

                getline(inputFile, line); // Location
                location = stoi(line.substr(9));

                Course* course = new ScientificCourse(courseId, courseName, courseDays, startHour, startMinute,
                                                    durationHour, durationMinute, hasProjector, capacity,
                                                    students, teacher, location, sessionCount);
            }

            getline(inputFile, line); // Empty line
        }

        inputFile.close();
    }
*/

    
    while (true) {
        cout << "---------------------------------------------------------" << endl;
        cout << "1. Add a new course" << endl;
        cout << "2. Edit course information" << endl;
        cout << "3. Display course details" << endl;
        cout << "4. Check course completion time" << endl;
        cout << "5. Check if two classes overlap" << endl;
        cout << "6. Generate full report" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the course type (0 for University Course, 1 for Scientific Course): ";
            int courseType;
            cin >> courseType;

            if (courseType == 0) {
                Course course = UniversityCourse();
                cout << "Course added successfully." << endl;
            } else if (courseType == 1) {
                Course course = ScientificCourse();
                cout << "Course added successfully." << endl;
            } else {
                cout << "Invalid course type." << endl;
            }
        } else if (choice == 2) {
            cout << "Enter the course ID to edit: ";
            string courseId;
            cin >> courseId;

            editCourse(Course::courses, courseId);
        } else if (choice == 3) {
            cout << "Enter the course ID to display details: ";
            string courseId;
            cin >> courseId;

            int index = binarySearch(Course::courses, courseId);
            if (index != -1) {
                Course::courses[index]->displayDetails();
            } else {
                cout << "Course not found." << endl;
            }
        } else if (choice == 4) {
            cout << "Enter the course ID to check completion time: ";
            string courseId;
            cin >> courseId;

            int index = binarySearch(Course::courses, courseId);
            if (index != -1) {
                int completionTime = Course::courses[index]->getCompletionTime();
                if (completionTime == -1) {
                    cout << "Course has not started yet or is already completed." << endl;
                } else {
                    int hours = completionTime / 60;
                    int minutes = completionTime % 60;
                    cout << "Course completion time: " << hours << " hours, " << minutes << " minutes" << endl;
                }
            } else {
                cout << "Course not found." << endl;
            }
        } else if (choice == 5) {
            cout << "Enter the first course ID: ";
            string courseId1;
            cin >> courseId1;

            cout << "Enter the second course ID: ";
            string courseId2;
            cin >> courseId2;
            int index1 = binarySearch(Course::courses, courseId1);
            int index2 = binarySearch(Course::courses, courseId2);

            if (index1 != -1 && index2 != -1) {
                bool overlap = Course::courses[index1]->checkOverlap(Course::courses[index2]);
                if (overlap) {
                    cout << "The two classes overlap." << endl;
                } else {
                    cout << "The two classes do not overlap." << endl;
                }
            } else {
                cout << "One or both courses not found." << endl;
            }
        } else if (choice == 6) {
            generateFullReport(Course::courses);
        } else if (choice == 0) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    // Clean up
    for (const auto& course : Course::courses) {
        delete course;
    }

    return 0;
}
