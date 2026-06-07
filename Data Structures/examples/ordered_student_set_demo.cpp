#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../sets/ordered_dynamic_set.hpp"

/*
    Student

    Represents a student with:
    - name: student's name.
    - registration: student's registration number.

    The registration number is used as the key in the ordered set.
*/
struct Student {
    std::string name;
    int registration = 0;
};

/*
    Extracts the key from a Student.

    The ordered set uses this function to compare and organize students.
*/
int student_key(const Student& student) {
    return student.registration;
}

/*
    Prints one student.
*/
void print_student(const Student& student) {
    std::cout << "Name: " << student.name << '\n';
    std::cout << "Registration: " << student.registration << '\n';
}

/*
    Prints all students currently stored in the ordered set.

    Since the set keeps the elements sorted by key, the students are printed
    in ascending order of registration number.
*/
void print_students(
    const ds::OrderedDynamicSet<Student, int, student_key>& students
) {
    if (ds::is_empty(students)) {
        std::cout << "\nThe set is empty.\n";
        return;
    }

    std::cout << "\nCurrent students:\n\n";

    for (std::size_t i = 0; i < students.size; ++i) {
        std::cout << "[" << i << "]\n";
        print_student(students.data[i]);
        std::cout << '\n';
    }
}

/*
    Inserts a student into the ordered set.

    Returns:
    - true  if the student was inserted.
    - false if the student could not be inserted.
*/
bool insert_student(
    ds::OrderedDynamicSet<Student, int, student_key>& students,
    const Student& student
) {
    if (!ds::insert(students, student)) {
        std::cout << "Error: could not insert student "
                  << student.name
                  << ". The registration may already exist or memory allocation failed.\n";

        return false;
    }

    return true;
}

/*
    Reads a registration number from the user.

    Returns:
    - true  if a valid integer was read.
    - false otherwise.
*/
bool read_registration(int& registration) {
    std::cout << "\nWhich registration do you want to remove? ";

    if (!(std::cin >> registration)) {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::cout << "Error: invalid input.\n";
        return false;
    }

    return true;
}

/*
    Removes a student by registration number.

    Returns:
    - true  if a student was removed.
    - false if no student with that registration was found.
*/
bool remove_student_by_registration(
    ds::OrderedDynamicSet<Student, int, student_key>& students,
    int registration
) {
    Student removed_student;

    if (!ds::remove_by_key(students, registration, &removed_student)) {
        std::cout << "Error: no student found with registration "
                  << registration << ".\n";

        return false;
    }

    std::cout << "\nRemoved student:\n";
    print_student(removed_student);

    return true;
}

int main() {
    ds::OrderedDynamicSet<Student, int, student_key> students;

    if (!ds::initialize(students)) {
        std::cout << "Error: not enough memory to initialize the set.\n";
        return 1;
    }

    /*
        Initial student data.

        These values are inserted in arbitrary order.
        The set stores them sorted by registration number.
    */
    std::vector<Student> initial_students = {
        {"Matheus",   396436},
        {"Emanuelly", 345678},
        {"Gael",      282956},
        {"Jadson",    123456}
    };

    for (const Student& student : initial_students) {
        if (!insert_student(students, student)) {
            ds::destroy(students);
            return 2;
        }
    }

    /*
        Repeatedly prints the set and asks which student should be removed.
    */
    while (!ds::is_empty(students)) {
        print_students(students);

        int registration = 0;

        if (!read_registration(registration)) {
            continue;
        }

        remove_student_by_registration(students, registration);
    }

    std::cout << "\nAll students were removed.\n";

    ds::destroy(students);

    return 0;
}