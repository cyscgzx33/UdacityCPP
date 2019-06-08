#include <iostream>
#include <string>

class BankAccount
{
  private:
      // declare member variables
    int account_number;
    std::string owner_name;
    double available_funds;
    
  public:
      // declare setters
    void setAccountNumber(int account_num);
    void setOwnerName(std::string name);
    void setAvailableFunds(double funds);
      // declare getters
    int getAccountNumber() const;
    std::string getOwnerName() const;
    double getAvailableFunds() const;
};

// implement setters
void BankAccount::setAccountNumber(int account_num) {
    this->account_number = account_num;
}

void BankAccount::setOwnerName(std::string name) {
    this->owner_name = name;
}

void BankAccount::setAvailableFunds(double funds) {
    this->available_funds = funds;
}
// implement getters
int BankAccount::getAccountNumber() const {
    return account_number;
}

std::string BankAccount::getOwnerName() const {
    return owner_name;
}

double BankAccount::getAvailableFunds() const {
    return available_funds;
}
int main(){
    // instantiate and output a bank account
    BankAccount bank_account;
    bank_account.setAccountNumber(12);
    bank_account.setOwnerName("Jacky Chan");
    bank_account.setAvailableFunds(123.34);
    
    std::cout << "this bank account has account number: "
              << bank_account.getAccountNumber() << std::endl
              << "which belongs to : "
              << bank_account.getOwnerName() << std::endl
              << "and it contains available funds: "
              << bank_account.getAvailableFunds() << std::endl;
}