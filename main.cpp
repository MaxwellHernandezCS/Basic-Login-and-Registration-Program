#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <sstream>

// Declare functions
void registration();
void login();

int main() {
    int option;
    
    // While loop to ask if user wants to register or login
    while (true){
        std::cout << "Welcome! Would you like to \n(1) Register \n(2) Login \n(3) Exit \nEnter choice:";
        std::cin >> option;
        
        // Error handling for input that isn't a number
        if (!std::cin) {
            // Clear fail state
            std::cin.clear(); 
            
            // Clear input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number.\n\n";
            continue;
        }
        
        switch(option){
            case 1:
            // register
            registration();
            break;
            
            case 2:
            // login
            login();
            break;
            
            case 3:
            // exit
            return 0;
            
            default:
            std::cout << "\"" << option << "\" is not a valid choice! Please try again.\n" << std::endl;
        }
    }
    return 0;
}

void login(){
    bool loginSuccess = false;
    std::string username, password;
    std::fstream readFile("data.txt");
    
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
            std::string tempUser, tempPass;
            // sstream to allow data to be read as tokens 
            std::stringstream ss(line);
            
            // Read each token up the comma and store it temporarily
            std::getline(ss, tempUser, ',');
            std::getline(ss, tempPass, ',');

            // Temp output for testing
            std::cout << "\n\nUsername found: " << tempUser;
            std::cout << "\nPassword found: " << tempPass;
            
            // Check if password and username match
            if (username == tempUser && password == tempPass){
                std::cout << "\nLogin success!" << std::endl;
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
    
    std::cout << "\nRegistration chosen! Please enter your username and password." << std::endl;
    std::cout << "Username:";
    std::cin >> username;
    std::cout << "Password:";
    std::cin >> password;
    
    // Check if data file opens
    std::fstream outputFile("data.txt", std::ios::app);
    if (!outputFile.is_open()){
        std::cout << "Error opening data file! Please try again";
    }
    // Import data into file
    outputFile << username << "," << password << "\n";
    outputFile.close();
    std::cout << "\nSuccessfully registered!" << std::endl;
}