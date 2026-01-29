#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

// File to be used
std::string fileName = "Projects/Login/data.txt";

// Declare functions
void registration();
void login();
int isNumber(int min, int max);

int main() {
    // While loop to ask if user wants to register or login
    while (true){
        std::cout << "Welcome! Would you like to \n(1) Register \n(2) Login \n(3) Exit";

        // Switch that uses a function which asks for input and checks if it's valid, if valid it returns the input.
        switch(isNumber(1,3)){
            case 1:
            registration();
            break;

            case 2:
            login();
            break;

            case 3:
            // exit
            return 0;

            default:
                std::cout << "Critical Error Occurred! Please try again" << std::endl;
        }
    }
}

// Function to check if input is numerical within the given range
int isNumber(const int min, const int max){
    int value;

    while (true) {
        // Get input from user
        std::cout << "\nEnter choice:";
        std::cin >> value;

        // Check if numerical input was given
        if (!std::cin || std::cin.peek() != '\n') {
            // Clear fail state and empty cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        // Check if input is between correct min and max range
        if (value < min || value > max) {
            std::cout << "Error! Please choose between " << min << " and " << max << ".\n";
            continue;
        }

        // Clear input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // If input passes all checks, return it.
        return value;
    }
}

void login(){
    bool loginSuccess = false;
    std::string username, password;
    std::fstream readFile(fileName);

    // while loop to check for Successful login
    while (!loginSuccess){
        std::cout << "\nEnter your username and password";
        std::cout << "\nUsername:";
        std::cin >> username;
        std::cout << "Password:";
        std::cin >> password;

        // Move reading pointer to start of file
        readFile.clear();
        readFile.seekp(0);
        std::string line;

        // While loop to go through data to check for username and password match
        while (std::getline(readFile, line)){
            // Temporary strings to store read data
            std::string tempUser, tempPass, token, tempSecNum, tempSecAnswer;

            // sstream to allow data to be read as tokens
            std::stringstream ss(line);

            // Read each token up the comma and store it temporarily
            std::getline(ss, tempUser, ',');
            std::getline(ss, tempPass, ',');
            std::getline(ss, token, ',');
            std::getline(ss, tempSecAnswer, ',');

            // Convert string 'token' to integer
            tempSecNum = std::stoi(token);

            // Check if password and username match, if true close file and end outer loop
            if (username == tempUser && password == tempPass){
                std::cout << "\nLogin success!\n" << std::endl;
                readFile.close();
                loginSuccess = true;
            }
        }

        // Output if login wasn't successful
        if (!loginSuccess){
        std::cout << "\nInvalid username or password, please try again" << std::endl;
        }
    }
}

void registration() {
    std::string username;
    std::string password;
    std::string security_answer;

    std::cout << "\nRegistration chosen! Please enter your username and password. You will also be asked to enter a security question and answer." << std::endl;
    std::cout << "Username:";
    std::getline(std::cin, username);

    // Username input protection
    while (username.find(',') != std::string::npos || username.find(' ') != std::string::npos) {
        std::cout << "\nUsername cannot contain a comma or a space, please try again." << std::endl;
        std::cout << "Username:";
        std::getline(std::cin, username);
    }

    std::cout << "Password:";
    std::getline(std::cin, password);

    // Password input protection
    while (password.find(',') != std::string::npos) {
        std::cout << "\nPassword cannot contain a comma, please try again" << std::endl;
        std::cout << "Password:";
        std::getline(std::cin, password);
    }

    std::cout << "\nWhich security question would you like to use?";
    std::cout << "\n1. What is your mother's maiden name?";
    std::cout << "\n2. What was the name of your first pet?";
    std::cout << "\n3. What was your childhood nickname?";
    int security_question = isNumber(1,3);

    std::cout << "\nSecurity question answer (case sensitive):";
    std::getline(std::cin, security_answer);

    // Security answer input protection
    while (security_answer.find(',') != std::string::npos) {
        std::cout << "\nSecurity answer cannot contain a comma, please try again" << std::endl;
        std::cout << "Security question answer (case sensitive):";
        std::getline(std::cin, security_answer);
    }

    // Check if data file opens
    std::fstream outputFile(fileName, std::ios::app);
    if (!outputFile.is_open()){
        std::cout << "Error opening data file! User could not be successfully registered.";
    } else { // Import data into file
        outputFile << username << "," << password << "," << security_question << "," << security_answer << "\n";
        outputFile.close();
        std::cout << "\nSuccessfully registered!" << std::endl;
    }
}