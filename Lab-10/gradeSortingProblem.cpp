#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Merge sort helper
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];
}

// Merge Sort Implementation
void mergeSort(vector<int>& arr, int left, int right) {
    if(left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

class Course {
public:
    string courseName;
    vector<int> grades;

    Course(string name) {
        courseName = name;
    }

    void addGrade(int g) {
        grades.push_back(g);
    }

    void sortGrades() {
        mergeSort(grades, 0, grades.size() - 1);
    }
};

// Function to merge all lists of courses
vector<int> mergeAll(vector<Course>& courses) {
    vector<int> result;

    for(auto& c : courses) {
        for(int g : c.grades)
            result.push_back(g);
    }

    mergeSort(result, 0, result.size() - 1);
    return result;
}

int main() {
    // creating unique dataset of 3 courses
    Course oop("OOP");
    Course dsa("DSA");
    Course db("Database");

    // adding grades for 5 students each
    oop.grades = {88, 75, 92, 68, 81};
    dsa.grades = {70, 85, 90, 65, 95};
    db.grades  = {80, 60, 89, 77, 94};

    // sorting each course list
    oop.sortGrades();
    dsa.sortGrades();
    db.sortGrades();

    // store all courses in a list
    vector<Course> allCourses = {oop, dsa, db};

    // merging all sorted lists
    vector<int> finalList = mergeAll(allCourses);

    // output individual sorted lists
    cout << "\nSorted OOP Grades: ";
    for(int g : oop.grades) cout << g << " ";

    cout << "\nSorted DSA Grades: ";
    for(int g : dsa.grades) cout << g << " ";

    cout << "\nSorted DB Grades: ";
    for(int g : db.grades) cout << g << " ";

    // output final merged list
    cout << "\n\nMerged Sorted Grades (All Courses): ";
    for(int g : finalList) cout << g << " ";

    return 0;
}
