#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

void check_acc_nmb(string num) {
    ifstream fpin(num + ".txt");
    if (!fpin) {
        cout << "Error: Invalid account detail!\nTry Again!" << endl;
        return;
    }
    fpin.close();
    return;
}

void home_return() {
    // Code for returning to the main menu
}

bool is_number(string s) {
    try {
        stof(s);
        return true;
    } catch (invalid_argument) {
        return false;
    }
}

void write(string name, string oc, string pin) {
    if (is_number(name) || !is_number(oc) || !is_number(pin) || name == "") {
        cout << "Error: Invalid account detail\nPlease try again." << endl;
        return;
    }
    ifstream f1("Accnt_Record.txt");
    int accnt_no;
    f1 >> accnt_no;
    f1.close();
    accnt_no++;
    ofstream f1_out("Accnt_Record.txt");
    f1_out << accnt_no;
    f1_out.close();
    ofstream fdet(to_string(accnt_no) + ".txt");
    fdet << pin << endl;
    fdet << oc << endl;
    fdet << accnt_no << endl;
    fdet << name << endl;
    fdet.close();
    ofstream frec(to_string(accnt_no) + "-rec.txt");
    time_t now = time(0);
    char* dt = ctime(&now);
    frec << "Date                             credit      Debit     Balance" << endl;
    frec << "[" << dt << "]  " << oc << "              " << oc << endl;
    frec.close();
    cout << "Details: Your Account Number is: " << accnt_no << endl;
    return;
}

void crdt_write(string amt, string accnt, string name) {
    if (!is_number(amt)) {
        cout << "Error: Invalid account detail\nPlease try again." << endl;
        return;
    }
    ifstream fdet(accnt + ".txt");
    string pin;
    int camt;
    fdet >> pin;
    fdet >> camt;
    fdet.close();
    int amti = stoi(amt);
    int cb = amti + camt;
    ofstream fdet_out(accnt + ".txt");
    fdet_out << pin << endl;
    fdet_out << cb << endl;
    fdet_out << accnt << endl;
    fdet_out << name << endl;
    fdet_out.close();
    ofstream frec(accnt + "-rec.txt", ios::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    frec << "[" << dt << "]  " << amti << "              " << cb << endl;
    frec.close();
    cout << "Operation Successfull!!: Amount credited Successfully!!" << endl;
    return;
}

void debit_write(string amt, string accnt, string name) {
    if (!is_number(amt)) {
        cout << "Error: Invalid account deatils\nPlease try again." << endl;
        return;
    }
    ifstream fdet(accnt + ".txt");
    string pin;
    int camt;
    fdet >> pin;
    fdet >> camt;
    fdet.close();
    int amti = stoi(amt);
    if (amti > camt) {
        cout << "Error!!: You dont have that amount left in your account\nPlease try again." << endl;
    } else {
        int cb = camt - amti;
        ofstream fdet_out(accnt + ".txt");
        fdet_out << pin << endl;
        fdet_out << cb << endl;
        fdet_out << accnt << endl;
        fdet_out << name << endl;
        fdet_out.close();
        ofstream frec(accnt + "-rec.txt", ios::app);
        time_t now = time(0);
        char* dt = ctime(&now);
        frec << "[" << dt << "]  " << "              " << amti << "              " << cb << endl;
        frec.close();
        cout << "Operation Successfull!!: Amount Debited Successfully!!" << endl;
    }
    return;
}

void Cr_Amt(string accnt, string name) {
    string amt;
    cout << "Enter Amount to be credited: ";
    cin >> amt;
    crdt_write(amt, accnt, name);
}

void De_Amt(string accnt, string name) {
    string amt;
    cout << "Enter Amount to be debited: ";
    cin >> amt;
    debit_write(amt, accnt, name);
}

void disp_bal(string accnt) {
    ifstream fdet(accnt + ".txt");
    string pin;
    string bal;
    fdet >> pin;
    fdet >> bal;
    fdet.close();
    cout << "Balance: " << bal << endl;
}

void disp_tr_hist(string accnt) {
    ifstream frec(accnt + "-rec.txt");
    string line;
    cout << "Your Transaction History:" << endl;
    while (getline(frec, line)) {
        cout << line << endl;
    }
    frec.close();
}

void logged_in_menu(string accnt, string name) {
    cout << "Logged in as: " << name << endl;
    string choice;
    while (true) {
        cout << "1. Credit Amount in Your Account" << endl;
        cout << "2. Debit Amount in Your Account" << endl;
        cout << "3. Check Balance in Your Account" << endl;
        cout << "4. View Transaction History" << endl;
        cout << "5. Log Out Your Account" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "1") {
            Cr_Amt(accnt, name);
        } else if (choice == "2") {
            De_Amt(accnt, name);
        } else if (choice == "3") {
            disp_bal(accnt);
        } else if (choice == "4") {
            disp_tr_hist(accnt);
        } else if (choice == "5") {
            cout << "Logged Out: You Have Been Successfully Logged Out!!" << endl;
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}

void check_log_in(string name, string acc_num, string pin) {
    check_acc_nmb(acc_num);
    if (is_number(name) || !is_number(pin)) {
        cout << "Error: Invalid account details\nPlease try again." << endl;
        return;
    } else {
        logged_in_menu(acc_num, name);
    }
}

void log_in() {
    string name, acc_num, pin;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter account number: ";
    cin >> acc_num;
    cout << "Enter your PIN: ";
    cin >> pin;
    check_log_in(name, acc_num, pin);
}

void Create() {
    string name, oc, pin;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter opening credit: ";
    cin >> oc;
    cout << "Enter desirable PIN: ";
    cin >> pin;
    write(name, oc, pin);
}

void Main_Menu() {
    string choice;
    while (true) {
        cout << "1. Create New Account" << endl;
        cout << "2. Log In Your Account" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "1") {
            Create();
        } else if (choice == "2") {
            log_in();
        } else if (choice == "3") {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}

int main() {
    Main_Menu();
    return 0;
}


