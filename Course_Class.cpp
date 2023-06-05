#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>


using namespace std;

enum class DayOfWeek {
    Saturday,
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday
};

// Forward declarations
class Course;
class UniversityCourse;
class ScientificCourse;
bool hasCommonElements(const set<DayOfWeek>& set1, const set<DayOfWeek>& set2);


// Base class for all courses
class Course {
protected:
    string id;
    string name;
    set<DayOfWeek> days; // Object variable to store the days of the week
    int startHour;
    int startMinute;
    int durationHour;
    int durationMinute;
    bool hasProjector;
    int capacity;
    vector<int> students;
    string teacher;
    int location;

public:
    // Courses list
    static vector<Course*> courses;

    Course() {
        // Initialize member variables using setters
        setId();
        setName();
        setDay();
        setStartHourMinute();
        setDuration();
        setHasProjector();
        setCapacity();
        setStudents();
        setTeacher();
        setLocation();

        courses.push_back(this); // Add the current object to the courses vector
        mergeSort(Course::courses); // Sort the vector after adding a new object
    }

    Course(const string& courseId, const string& courseName, const set<DayOfWeek>& courseDays,
           int courseStartHour, int courseStartMinute, int courseDurationHour, int courseDurationMinute,
           bool courseHasProjector, int courseCapacity, const vector<int>& courseStudents,
           const string& courseTeacher, int courseLocation) 
        : id(courseId), name(courseName), days(courseDays), startHour(courseStartHour),
          startMinute(courseStartMinute), durationHour(courseDurationHour),
          durationMinute(courseDurationMinute), hasProjector(courseHasProjector),
          capacity(courseCapacity), students(courseStudents), teacher(courseTeacher),
          location(courseLocation) {
        courses.push_back(this); // Add the current object to the courses vector
        mergeSort(Course::courses); // Sort the vector after adding a new object
    }

    virtual ~Course() {}
            // Destructor

// Setters:
    // Setter for id
    void setId() {
        cout << "Enter the new id: ";
        cin >> id;
        bool identical = true;
        while (identical) {
            identical = false;
            if (!Course::courses.empty()) {
                for (size_t i = 0; i < (Course::courses.size()) - 1; i++) {
                    Course* course = Course::courses[i];
                    if (course->id == id) {
                        identical = true;
                        cout << "This ID is assigned before." << endl;
                        cout << "Enter the new id: ";
                        cin >> id;
                        break;
                    }
                }
            }
        }
        mergeSort(Course::courses);
    }
    // Setter for name
    void setName() {
        cout << "Enter the new name: ";
        cin.ignore(); // Ignore any remaining newline characters
        getline(cin, name);
    }
    // Setter for day
    void setDay() {
        cout << "Enter the days of the week for the course (separated by spaces): ";
        cin.ignore(); // Clear any remaining newline characters in the input buffer
        string input;
        getline(cin, input);

        istringstream iss(input);
        string dayString;

        while (iss >> dayString) {
            // Remove the extra condition for single-letter abbreviations
            if (dayString == "Saturday" || dayString == "Sat") {
                days.insert(DayOfWeek::Saturday);
            } else if (dayString == "Sunday" || dayString == "Sun") {
                days.insert(DayOfWeek::Sunday);
            } else if (dayString == "Monday" || dayString == "Mon") {
                days.insert(DayOfWeek::Monday);
            } else if (dayString == "Tuesday" || dayString == "Tue") {
                days.insert(DayOfWeek::Tuesday);
            } else if (dayString == "Wednesday" || dayString == "Wed") {
                days.insert(DayOfWeek::Wednesday);
            } else if (dayString == "Thursday" || dayString == "Thu") {
                days.insert(DayOfWeek::Thursday);
            } else if (dayString == "Friday" || dayString == "Fri") {
                days.insert(DayOfWeek::Friday);
            } else {
                // Check if the input is a single letter, add it to the valid days
                if (dayString.length() == 1) {
                    char dayChar = toupper(dayString[0]);
                    if (dayChar >= 'A' && dayChar <= 'Z') {
                        DayOfWeek day = static_cast<DayOfWeek>(dayChar);
                        days.insert(day);
                    } else {
                        cout << "Invalid day: " << dayString << endl;
                    }
                } else {
                    cout << "Invalid day: " << dayString << endl;
                }
            }
        }
    }

    // Setter for startHour and startMinute
    void setStartHourMinute() {
        cout << "Enter the start time (hour minute): ";
        cin >> startHour >> startMinute;
        while (startHour > 23 || startHour < 0){
            cout << "Invalid time!" << endl;
            cout << "Enter the new start hour: ";
            cin >> startHour;
        }
        while (startMinute > 59 || startMinute < 0){
            cout << "Invalid time!" << endl;
            cout << "Enter the new start minute: ";
            cin >> startMinute;
        }
    }
    // Setter for Duration
    void setDuration() {
        cout << "Enter the duration time (hour minute): ";
        cin >> durationHour >> durationMinute;
        while (durationHour > 23 || durationHour < 0){
            cout << "Invalid time!" << endl;
            cout << "Enter the new duration hour: ";
            cin >> durationHour;
        }
        while (durationMinute > 59 || durationMinute < 0){
            cout << "Invalid time!" << endl;
            cout << "Enter the new duration minute: ";
            cin >> durationMinute;
        }
    }
    // Setter for hasProjector
    void setHasProjector() {
        cout << "Does the course have a projector? (1 for yes, 0 for no): ";
        cin >> hasProjector;
    }
    // Setter for Capacity
    void setCapacity() {
        cout << "Enter the new capacity: ";
        cin >> capacity;
        while (capacity > 40){
            cout << "Max copacity is 40!" << endl << "Enter the new capacity: ";
            cin >> capacity;
        }
    }
    // Setter for students
void setStudents() {
    int numStudents;
    cout << "Enter the number of students: ";
    cin >> numStudents;

    while (numStudents > capacity) {
        cout << "Please enter a number smaller/equal to capacity" << endl;
        cout << "Enter the number of students: ";
        cin >> numStudents;
    }

    students.clear(); // Clear the existing students vector

    cout << "Enter the student ids: " << endl;
    cin.ignore(); // Ignore any remaining newline characters

    for (int i = 0; i < numStudents; ++i) {
        int studentId;
        cout << "Enter student ID #" << (i + 1) << ": ";
        cin >> studentId;
        students.push_back(studentId);
    }
}

    // Setter for teacher
    void setTeacher() {
        cout << "Enter the new teacher: ";
        cin.ignore(); // Ignore any remaining newline characters
        getline(cin, teacher);
    }
    // Setter for location
    void setLocation() {
        cout << "How to set location?" << endl;
        cout << "1. Automatically" << endl;
        cout << "2. Manually" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            // Find the maximum location
            int maxLocation = 0;
            for (const auto& course : Course::courses) {
                if (course->location > maxLocation) {
                    maxLocation = course->location;
                }
            }
            location = maxLocation + 1;
        }
        else if (choice == 2) {
            cout << "Enter the new location: ";
            cin >> location;
            while (!isAvailabe(location)){
                cout << "Location already taken at this courses time." << endl;
                cout << "Enter the new location: ";
                cin >> location;
            }
            
        }
    }


// Getters:
    // Getter for ID
    const string& getID() const {
        return id;
    }
    // Getter for name
    const string& getName() const {
        return name;
    }
    // Getter for days
    const set<DayOfWeek>& getDays() const {
        return days;
    }
    // Getter for Start Hour
    int getStartHour() const {
        return startHour;
    }
    // Getter for Start Minute
    int getStartMinute() const {
        return startMinute;
    }
    // Getter for Duration Hour
    int getDurationHour() const {
        return durationHour;
    }
    // Getter for Duration Minute
    int getDurationMinute() const {
        return durationMinute;
    }
    // Getter for Prjector Status
    bool requiresProjector() const {
        return hasProjector;
    }
    // Getter for Students
    const vector<int>& getStudents() const {
        return students;
    }
    // Getter for Teacher
    const string& getTeacher() const {
        return teacher;
    }
    // Getter for Location
    int getLocation() const {
        return location;
    }
    // Getter for Capacity
    int getCapacity() const {
        return capacity;
    }

// Functions:
    // Merge function
    vector<Course*> merge(const vector<Course*>& left, const vector<Course*>& right) {
        vector<Course*> result;
        size_t leftIdx = 0;
        size_t rightIdx = 0;

        while (leftIdx < left.size() && rightIdx < right.size()) {
            // Compare the Course IDs
            if (left[leftIdx]->getID() < right[rightIdx]->getID()) {
                result.push_back(left[leftIdx]);
                leftIdx++;
            } else {
                result.push_back(right[rightIdx]);
                rightIdx++;
            }
        }

        // Append the remaining elements
        while (leftIdx < left.size()) {
            result.push_back(left[leftIdx]);
            leftIdx++;
        }
        while (rightIdx < right.size()) {
            result.push_back(right[rightIdx]);
            rightIdx++;
        }

        return result;
    }

    // Merge sort for Course pointers based on id
    vector<Course*> mergeSort(const vector<Course*>& courses) {
        // Base case: if the vector has 0 or 1 element, it is already sorted
        if (courses.size() <= 1) {
            return courses;
        }

        // Divide the vector into two halves
        size_t middle = courses.size() / 2;
        vector<Course*> left(courses.begin(), courses.begin() + middle);
        vector<Course*> right(courses.begin() + middle, courses.end());

        // Recursively sort the two halves
        left = mergeSort(left);
        right = mergeSort(right);

        // Merge the sorted halves
        return merge(left, right);
    }

    bool checkOverlap(const Course* other) const {
        if (days != other->getDays()) {
            return false;
        }
        return true;
    }


    virtual void displayDetails() const {
        cout << "Course ID: " << getID() << endl;
        cout << "Course Name: " << getName() << endl;
        cout << "Day: ";
        // Loop through the set and print each element
        for (const auto& day : getDays()) {
            switch (day) {
                case DayOfWeek::Saturday:
                    cout << "Saturday ";
                    break;
                case DayOfWeek::Sunday:
                    cout << "Sunday ";
                    break;
                case DayOfWeek::Monday:
                    cout << "Monday ";
                    break;
                case DayOfWeek::Tuesday:
                    cout << "Tuesday ";
                    break;
                case DayOfWeek::Wednesday:
                    cout << "Wednesday ";
                    break;
                case DayOfWeek::Thursday:
                    cout << "Thursday ";
                    break;
                case DayOfWeek::Friday:
                    cout << "Friday ";
                    break;
            }
        }
        cout << endl;
        cout << "Start Time: " << getStartHour() << ":" << getStartMinute() << endl;
        cout << "Duration: " << getDurationHour() << " hours, " << getDurationMinute() << " minutes" << endl;
        cout << "Requires Projector: " << (requiresProjector() ? "Yes" : "No") << endl;
        cout << "Students: ";
        for (int student : getStudents()) {
            cout << student << " ";
        }
        cout << endl;
        cout << "Teacher: " << getTeacher() << endl;
        cout << "Location: " << getLocation() << endl;
    }

    virtual int getCompletionTime() const {
        time_t now = time(0);
        tm* currentTime = localtime(&now);

        int currentHour = currentTime->tm_hour;
        int currentMinute = currentTime->tm_min;

        int courseStart = startHour * 60 + startMinute;
        int current = currentHour * 60 + currentMinute;

        if (current >= courseStart) {
            return current + durationHour * 60 + durationMinute - courseStart;
        } else {
            return -1; // Course hasn't started yet
        }
    }

    bool overlapsWith(const Course& other) const {
        if (days != other.days) {
            return false; // Different days, no overlap
        }

        int startA = startHour * 60 + startMinute;
        int endA = startA + durationHour * 60 + durationMinute;
        int startB = other.startHour * 60 + other.startMinute;
        int endB = startB + other.durationHour * 60 + other.durationMinute;

        if ((startA >= startB && startA <= endB) || (endA >= startB && endA <= endB) ||
            (startB >= startA && startB <= endA) || (endB >= startA && endB <= endA)) {
            return true; // Overlapping time slots
        }

        return false;
    }

    // Function to call for checking location availability
    bool isAvailabe(int location) const {
        for (const auto& course : Course::courses) {
            if (location == course->location && hasCommonElements(days, course->days)) {
                int time1Start = startHour * 60 + startMinute;
                int time1End = time1Start + durationHour * 60 + durationMinute;

                int time2Start = course->startHour * 60 + course->startMinute;
                int time2End = time2Start + course->durationHour * 60 + course->durationMinute;

                // Check for interference
                if ((time1Start >= time2Start && time1Start < time2End) ||
                    (time2Start >= time1Start && time2Start < time1End)) {
                    return false;  // Interference detected
                } else {
                    continue; // No interference
                }
            }
        }
        return true;
    }

    virtual void saveCourseToFile(ofstream& outputFile) const {
        outputFile << "Course Type: Base Course" << endl;
        outputFile << "Course ID: " << id << endl;
        outputFile << "Course Name: " << name << endl;
        outputFile << "Day: ";
        // Loop through the set and print each element
        for (const auto& day : getDays()) {
            switch (day) {
                case DayOfWeek::Saturday:
                    outputFile << "Saturday ";
                    break;
                case DayOfWeek::Sunday:
                    outputFile << "Sunday ";
                    break;
                case DayOfWeek::Monday:
                    outputFile << "Monday ";
                    break;
                case DayOfWeek::Tuesday:
                    outputFile << "Tuesday ";
                    break;
                case DayOfWeek::Wednesday:
                    outputFile << "Wednesday ";
                    break;
                case DayOfWeek::Thursday:
                    outputFile << "Thursday ";
                    break;
                case DayOfWeek::Friday:
                    outputFile << "Friday ";
                    break;
            }
        }
        outputFile << endl;
        outputFile << "Start Time: " << startHour << ":" << startMinute << endl;
        outputFile << "Duration: " << durationHour << " hours, " << durationMinute << " minutes" << endl;
        outputFile << "Requires Projector: " << (hasProjector ? "Yes" : "No") << endl;
        outputFile << "Students: ";
        for (const int student : students) {
            outputFile << student << " ";
        }
        outputFile << endl;
        outputFile << "Teacher: " << teacher << endl;
        outputFile << "Location: " << location << endl;
        outputFile << endl;
    }

    bool operator<(const Course& other) const {
        return id < other.id;
    }
};

vector<Course*> Course::courses = {}; // Define the static vector

// University course class
class UniversityCourse : public Course {
public:
    using Course::Course; // Inherit base class constructors

    void saveCourseToFile(ofstream& outputFile) const override {
        outputFile << "Course Type: University Course" << endl;
        Course::saveCourseToFile(outputFile);
    }
};

// Scientific course class
class ScientificCourse : public Course {
private:
    int sessionCount;

public:
    ScientificCourse() : Course() {
        setSessionCount();
    }

    ScientificCourse(const string& courseId, const string& courseName, const set<DayOfWeek>& courseDays,
                     int courseStartHour, int courseStartMinute, int courseDurationHour, int courseDurationMinute,
                     bool courseHasProjector, int courseCapacity, const vector<int>& courseStudents,
                     const string& courseTeacher, int courseLocation, int courseSessionCount) 
        : Course(courseId, courseName, courseDays, courseStartHour, courseStartMinute,
                 courseDurationHour, courseDurationMinute, courseHasProjector, courseCapacity,
                 courseStudents, courseTeacher, courseLocation), sessionCount(courseSessionCount) {
        courses.push_back(this); // Add the current object to the courses vector
        mergeSort(Course::courses); // Sort the vector after adding a new object
    }

    void setSessionCount() {
        cout << "Enter the new session count: ";
        cin >> sessionCount;
    }

    int getSessionCount() const {
        return sessionCount;
    }

    void displayDetails() const override {
        Course::displayDetails();
        cout << "Session Count: " << sessionCount << endl;
    }

    int getCompletionTime() const override {
        time_t now = time(0);
        tm* currentTime = localtime(&now);

        int currentHour = currentTime->tm_hour;
        int currentMinute = currentTime->tm_min;

        int courseStart = startHour * 60 + startMinute;
        int current = currentHour * 60 + currentMinute;

        if (current >= courseStart) {
            int timeRemaining = current + durationHour * 60 + durationMinute - courseStart;
            int sessionDuration = durationHour * 60 + durationMinute;
            int sessionsCompleted = timeRemaining / sessionDuration;

            if (sessionsCompleted >= sessionCount) {
                return -1; // Course completed
            } else {
                int sessionTimeRemaining = timeRemaining % sessionDuration;
                return sessionDuration - sessionTimeRemaining;
            }
        } else {
            return -1; // Course hasn't started yet
        }
    }

    void saveCourseToFile(ofstream& outputFile) const override {
        outputFile << "Course Type: Scientific Course" << endl;
        Course::saveCourseToFile(outputFile);
        outputFile << "Session Count: " << sessionCount << endl;
        outputFile << endl;
    }
};


// functions.cpp
bool hasCommonElements(const set<DayOfWeek>& set1, const set<DayOfWeek>& set2) {
    set<DayOfWeek> sortedSet1(set1.begin(), set1.end());
    set<DayOfWeek> sortedSet2(set2.begin(), set2.end());

    set<DayOfWeek> commonElements;
    set_intersection(sortedSet1.begin(), sortedSet1.end(),
                        sortedSet2.begin(), sortedSet2.end(),
                        inserter(commonElements, commonElements.begin()));

    return !commonElements.empty();
}
// Function to compare the duration of two courses
bool compareDuration(const Course* a, const Course* b) {
    int durationA = a->getDurationHour() * 60 + a->getDurationMinute();
    int durationB = b->getDurationHour() * 60 + b->getDurationMinute();
    return durationA < durationB;
}

// Function to perform binary search on courses based on course ID
int binarySearch(const vector<Course*>& courses, const string& id) {
    int left = 0;
    int right = courses.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (courses[mid]->getID() == id) {
            return mid;
        } else if (courses[mid]->getID() < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

// Function to check if a class number is available or not
bool isClassAvailable(const vector<Course*>& courses, int classNumber) {
    for (const Course* course : courses) {
        if (course->getLocation() == classNumber) {
            return false;
        }
    }
    return true;
}

// Function to generate a unique class number
int generateClassNumber(const vector<Course*>& courses) {
    int classNumber = 1;
    while (!isClassAvailable(courses, classNumber)) {
        classNumber++;
    }
    return classNumber;
}

// Function to edit course information
void editCourse(vector<Course*>& courses, const string& id) {
    int index = binarySearch(courses, id);
    if (index != -1) {
        Course* course = courses[index];

        // Use setters to update course information
        course->setName();  // Prompt the user and set a new name for the course
        course->setDay();  // Prompt the user and change the day of the course
        course->setStartHourMinute();  // Prompt the user and update the start hour and minute
        course->setDuration();  // Prompt the user and update the duration time
        course->setHasProjector();  // Prompt the user and change the projector availability
        course->setCapacity();   // Prompt the user and change the capacity
        course->setStudents();  // Prompt the user and reEnter the students
        course->setTeacher();  // Prompt the user and set a new teacher for the course
        course->setLocation();  // Prompt the user and reset the location

        cout << "Course information updated successfully!" << endl;
    } else {
        cout << "Course not found." << endl;
    }
}


// Function to display a full report and write it to a file
void generateFullReport(const vector<Course*>& courses) {
    string filename;
    cout << "Enter the filename to save the report: ";
    cin >> filename;

    ofstream outputFile(filename);
    if (!outputFile) {
        cout << "Error opening the file." << endl;
        return;
    }

    for (const Course* course : courses) {
        outputFile << "-----------------------------------------" << endl;
        course->saveCourseToFile(outputFile);
    }

    outputFile.close();
    cout << "Full report generated successfully!" << endl;
}
