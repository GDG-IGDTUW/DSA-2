#include <iostream>
#include <vector>
#include <iomanip> // For formatting output

using namespace std;

class FinancialTransactionProcessor {
public:
    enum class TransactionType { DEPOSIT, WITHDRAWAL, TRANSFER };

    struct Transaction {
        TransactionType type;
        double amount;
        int transactionHour;
        double transactionFee;
        bool success; // Indicates if the transaction was processed successfully

        Transaction(TransactionType t, double amt, int hour, double fee)
            : type(t), amount(amt), transactionHour(hour), transactionFee(fee), success(false) {}
    };

    FinancialTransactionProcessor(double initialBalance) : balance(initialBalance) {}

    void addTransaction(TransactionType type, double amount, int hour) {
        double fee = calculateFee(type, amount, hour);
        transactions.emplace_back(type, amount, hour, fee);
    }

    pair<double, double> processTransactions() {
        double totalFee = 0;
        double currentBalance = balance;

        for (auto& transaction : transactions) {
            if (isValidTransaction(transaction, currentBalance)) {
                updateBalance(transaction, currentBalance);
                totalFee += transaction.transactionFee;
                transaction.success = true; // Mark successful transactions
            }
        }

        return {totalFee, currentBalance};
    }

    void displayTransactionHistory() const {
        cout << "\n--- Transaction History ---\n";
        cout << left << setw(15) << "Type" << setw(10) << "Amount" << setw(10) 
             << "Hour" << setw(10) << "Fee" << setw(15) << "Status" << endl;
        cout << "-------------------------------------------------------\n";

        for (const auto& transaction : transactions) {
            cout << setw(15) << getTransactionType(transaction.type)
                 << setw(10) << transaction.amount
                 << setw(10) << transaction.transactionHour
                 << setw(10) << transaction.transactionFee
                 << setw(15) << (transaction.success ? "Completed" : "Failed") << endl;
        }
    }

private:
    double balance;
    vector<Transaction> transactions;

    bool isValidTransaction(const Transaction& transaction, double currentBalance) {
        if (transaction.amount <= 0) return false;

        switch (transaction.type) {
            case TransactionType::WITHDRAWAL:
            case TransactionType::TRANSFER:
                return (transaction.amount + transaction.transactionFee <= currentBalance);
            case TransactionType::DEPOSIT:
                return true;
            default:
                return false;
        }
    }

    double calculateFee(TransactionType type, double amount, int hour) {
        if (type == TransactionType::DEPOSIT) return 0; // No fee for deposits

        double fee = (type == TransactionType::WITHDRAWAL) ? 3 : 2; // Base fees
        if (hour >= 9 && hour <= 18) fee *= 1.5; // Peak hour surcharge

        return fee;
    }

    void updateBalance(Transaction& transaction, double& currentBalance) {
        switch (transaction.type) {
            case TransactionType::DEPOSIT:
                currentBalance += transaction.amount;
                break;
            case TransactionType::WITHDRAWAL:
            case TransactionType::TRANSFER:
                currentBalance -= (transaction.amount + transaction.transactionFee);
                break;
        }
    }

    string getTransactionType(TransactionType type) const {
        switch (type) {
            case TransactionType::DEPOSIT: return "Deposit";
            case TransactionType::WITHDRAWAL: return "Withdrawal";
            case TransactionType::TRANSFER: return "Transfer";
            default: return "Unknown";
        }
    }
};

int main() {
    double initialBalance;
    cout << "Enter initial balance: ";
    cin >> initialBalance;

    FinancialTransactionProcessor processor(initialBalance);

    int numTransactions;
    cout << "Enter number of transactions: ";
    cin >> numTransactions;

    for (int i = 0; i < numTransactions; ++i) {
        int type, hour;
        double amount;
        cout << "Enter transaction type (0: Deposit, 1: Withdrawal, 2: Transfer), amount, and hour: ";
        cin >> type >> amount >> hour;

        if (type < 0 || type > 2 || amount <= 0 || hour < 0 || hour > 23) {
            cout << "Invalid transaction details. Skipping...\n";
            continue;
        }

        processor.addTransaction(static_cast<FinancialTransactionProcessor::TransactionType>(type), amount, hour);
    }

    

    auto result = processor.processTransactions();

    processor.displayTransactionHistory();

    cout << fixed << setprecision(2);
    cout << "\nFinal Report\n";
    cout << "-----------------------\n";
    cout << "Initial Balance: " << initialBalance << "\n";
    cout << "Total Fees Charged: " << result.first << "\n";
    cout << "Final Balance: " << result.second << "\n";

    

    return 0;
}
