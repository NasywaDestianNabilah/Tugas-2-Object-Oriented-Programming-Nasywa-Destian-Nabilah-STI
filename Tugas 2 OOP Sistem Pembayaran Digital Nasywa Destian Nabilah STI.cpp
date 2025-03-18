// Tugas 2 OOP Sistem Pembayaran Digital Nasywa Destian Nabilah STI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Payment {
protected:
    int id;
    double amount;
    string date;
    string status;

public:
    Payment(int id, double amount, string date)
        : id(id), amount(amount), date(date), status("Pending") {}

    virtual bool validatePayment() = 0;
    virtual string processPayment() = 0;

    string refundPayment() {
        if (status == "Completed") {
            status = "Refunded";
            return "[REFUND] Payment ID " + to_string(id) + " has been successfully refunded.";
        }
        return "[REFUND FAILED] Payment ID " + to_string(id) + " cannot be refunded. Current status: " + status;
    }

    virtual void displayInfo() {
        cout << "=====================================" << endl;
        cout << " Payment ID  : " << id << endl;
        cout << " Amount      : Rp" << fixed << setprecision(2) << amount << endl;
        cout << " Date        : " << date << endl;
        cout << " Status      : " << status << endl;
        cout << "=====================================" << endl;
    }

    virtual ~Payment() {}
};

class CreditCardPayment : public Payment {
private:
    string cardNumber;
    string expiryDate;
    string cvv;

public:
    CreditCardPayment(int id, double amount, string date, string cardNumber, string expiryDate, string cvv)
        : Payment(id, amount, date), cardNumber(cardNumber), expiryDate(expiryDate), cvv(cvv) {}

    bool validatePayment() override {
        return (cardNumber.length() == 16 || cardNumber.length() == 15) && cvv.length() == 3;
    }

    string processPayment() override {
        if (validatePayment()) {
            status = "Completed";
            return "[SUCCESS] Credit card payment ID " + to_string(id) + " has been processed successfully.";
        }
        status = "Failed";
        return "[FAILED] Credit card payment ID " + to_string(id) + " failed due to invalid details.";
    }
};

class BankTransfer : public Payment {
private:
    string accountNumber;
    string bankName;
    string transferCode;

public:
    BankTransfer(int id, double amount, string date, string accountNumber, string bankName, string transferCode)
        : Payment(id, amount, date), accountNumber(accountNumber), bankName(bankName), transferCode(transferCode) {}

    bool validatePayment() override {
        return accountNumber.length() >= 10 && transferCode.length() == 6;
    }

    string processPayment() override {
        if (validatePayment()) {
            status = "Completed";
            return "[SUCCESS] Bank transfer payment ID " + to_string(id) + " to " + bankName + " has been processed successfully.";
        }
        status = "Failed";
        return "[FAILED] Bank transfer payment ID " + to_string(id) + " failed due to invalid details.";
    }
};

class DigitalWallet : public Payment {
private:
    string walletId;
    string provider;
    string phoneNumber;

public:
    DigitalWallet(int id, double amount, string date, string walletId, string provider, string phoneNumber)
        : Payment(id, amount, date), walletId(walletId), provider(provider), phoneNumber(phoneNumber) {}

    bool validatePayment() override {
        return phoneNumber.length() == 10;
    }

    string processPayment() override {
        if (validatePayment()) {
            status = "Completed";
            return "[SUCCESS] Digital wallet payment ID " + to_string(id) + " via " + provider + " has been processed successfully.";
        }
        status = "Failed";
        return "[FAILED] Digital wallet payment ID " + to_string(id) + " failed due to invalid details.";
    }
};

int main() {
    cout << "=====================================" << endl;
    cout << "      SISTEM PEMBAYARAN DIGITAL      " << endl;
    cout << "=====================================" << endl;

    CreditCardPayment cc_payment(1, 100000, "2025-03-15", "1234567812345678", "12/26", "123");
    BankTransfer bt_payment(2, 200000, "2025-03-15", "9876543210", "Bank BCA", "ABC123");
    DigitalWallet dw_payment(3, 50000, "2025-03-15", "DW12345", "PayFast", "0812345678");

    cout << endl << cc_payment.processPayment() << endl;
    cc_payment.displayInfo();

    cout << endl << bt_payment.processPayment() << endl;
    bt_payment.displayInfo();

    cout << endl << dw_payment.processPayment() << endl;
    dw_payment.displayInfo();

    cout << endl << cc_payment.refundPayment() << endl;
    cc_payment.displayInfo();

    return 0;
}