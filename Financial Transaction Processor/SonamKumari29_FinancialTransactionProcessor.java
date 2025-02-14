import java.util.*;

public class SonamKumari29_FinancialTransactionProcessor {

    // Define transaction type constants
    private static final String DEPOSIT = "deposit";
    private static final String WITHDRAWAL = "withdrawal";
    private static final String TRANSFER = "transfer";

    // Define transaction limits for each type
    private static final int DEPOSIT_LIMIT = 50000;
    private static final int WITHDRAWAL_LIMIT = 50000;
    private static final int TRANSFER_LIMIT = 50000;

    // Define minimum balance threshold
    private static final int MIN_BALANCE = 1000;

    // Define valid transaction hours (e.g., 9 AM to 5 PM)
    private static final int START_HOUR = 9;
    private static final int END_HOUR = 17;

    public static void main(String[] args) {
        // Example input
        int balance = 5000;
        List<Transaction> transactions = new ArrayList<>();
        transactions.add(new Transaction(DEPOSIT, 2000, 10, 5));
        transactions.add(new Transaction(WITHDRAWAL, 1500, 12, 3));
        transactions.add(new Transaction(TRANSFER, 1000, 15, 2));

        // Process transactions
        Object result = processTransactions(balance, transactions);

        // Print the result
        if (result instanceof String) {
            System.out.println(result); // Output: -1 if no valid transactions
        } else {
            int[] output = (int[]) result;
            System.out.println("Output: (" + output[0] + ", " + output[1] + ")");
        }
    }

    // Method to process transactions
    public static Object processTransactions(int balance, List<Transaction> transactions) {
        int totalFee = 0;
        int finalBalance = balance;

        for (Transaction transaction : transactions) {
            // Check if the transaction is within valid hours
            if (transaction.transactionHour < START_HOUR || transaction.transactionHour > END_HOUR) {
                continue; // Skip transactions outside valid hours
            }

            // Check if the transaction amount exceeds the limit for its type
            if (transaction.type.equals(DEPOSIT) && transaction.amount > DEPOSIT_LIMIT) {
                continue; // Skip invalid deposit
            } else if (transaction.type.equals(WITHDRAWAL) && transaction.amount > WITHDRAWAL_LIMIT) {
                continue; // Skip invalid withdrawal
            } else if (transaction.type.equals(TRANSFER) && transaction.amount > TRANSFER_LIMIT) {
                continue; // Skip invalid transfer
            }

            // Check if the transaction violates the minimum balance constraint
            if (transaction.type.equals(WITHDRAWAL)) {
                if (finalBalance - transaction.amount < MIN_BALANCE) {
                    continue; // Skip withdrawal if it violates minimum balance
                }
            } else if (transaction.type.equals(TRANSFER)) {
                if (finalBalance - transaction.amount < MIN_BALANCE) {
                    continue; // Skip transfer if it violates minimum balance
                }
            }

            // Process the transaction
            if (transaction.type.equals(DEPOSIT)) {
                finalBalance += transaction.amount;
            } else if (transaction.type.equals(WITHDRAWAL)) {
                finalBalance -= transaction.amount;
            } else if (transaction.type.equals(TRANSFER)) {
                finalBalance -= transaction.amount;
            }

            // Add the transaction fee to the total fee
            totalFee += transaction.fee;
        }

        // If no valid transactions were processed, return -1
        if (totalFee == 0) {
            return "-1";
        }

        // Return the total fee and final balance as a tuple
        return new int[]{totalFee, finalBalance};
    }

    // Transaction class to represent a transaction
    static class Transaction {
        String type;
        int amount;
        int transactionHour;
        int fee;

        public Transaction(String type, int amount, int transactionHour, int fee) {
            this.type = type;
            this.amount = amount;
            this.transactionHour = transactionHour;
            this.fee = fee;
        }
    }
}