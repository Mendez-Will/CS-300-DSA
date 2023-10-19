
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

// Define a structure to represent a course
struct Course {
    std::string title;
    std::string department;
    std::vector<std::string> prerequisites;
};

int main() {
    std::unordered_map<std::string, Course> courseData; // Data structure using unordered_map

    std::cout << "Welcome to the course planner." << std::endl;
    //Menu Setup
    while (true) {
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "What would you like to do? ";
        //Choice limitation
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid option." << std::endl;
            continue;
        }

        switch (choice) {
        case 1: // Load Data Structure
        {
            std::string fileName;
            std::cout << "Enter the file name to load course data: ";
            std::cin.ignore(); // delete the newline character
            std::getline(std::cin, fileName);

            std::ifstream inputFile(fileName);

            if (!inputFile) {
                std::cerr << "Error: Cannot open the file." << std::endl;
            }
            else {
                // Read course data from the file and populate the data structure
                courseData.clear(); // Clear existing data
                std::string line;
                while (std::getline(inputFile, line)) {
                    std::istringstream iss(line);
                    std::string courseTitle, department;

                    // Use a comma as the delimiter
                    if (std::getline(iss, courseTitle, ',')) {
                        if (std::getline(iss, department, ',')) {
                            Course course;
                            course.title = courseTitle;
                            course.department = department;

                            //Parse and add prerequisites
                            std::string prerequisite;
                            while (std::getline(iss, prerequisite, ',')) {
                                if (prerequisite != "-1") {
                                    course.prerequisites.push_back(prerequisite);
                                }
                            }

                            courseData[courseTitle] = course;
                        }
                    }
                }

                inputFile.close();
                std::cout << "Data loaded into the data structure." << std::endl;
            }
        }
        break;

        case 2: // Print Course List
            std::cout << "Here is a sample schedule:" << std::endl;
            for (const auto& coursePair : courseData) {
                const Course& course = coursePair.second; // Access the Course structure
                std::cout << course.title << ", " << course.department << std::endl;
            }
            break;


        case 3: // Print Course
        {
            std::string courseTitle;
            std::cout << "What course do you want to know about? ";
            std::cin.ignore(); // Delete the newline character
            std::getline(std::cin, courseTitle);

            if (courseData.find(courseTitle) != courseData.end()) {
                const Course& course = courseData[courseTitle];
                std::cout << course.title << ", " << course.department << std::endl;
                if (!course.prerequisites.empty()) {
                    std::cout << "Prerequisites: ";
                    for (const std::string& prereq : course.prerequisites) {
                        std::cout << prereq << " ";
                    }
                    std::cout << std::endl;
                }
                else {
                    std::cout << "No prerequisites." << std::endl;
                }
            }
            else {
                std::cout << "Course not found." << std::endl;
            }
        }
        break;

        case 9: // Exit
            std::cout << "Thank you for using the course planner!" << std::endl;
            return 0;

        default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }

    return 0;
}
