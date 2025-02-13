// File: SonamKumari29_FinancialTransactionProcessor.java

import java.util.*;

class Transaction {
    String type;
    int amount;
    int hour;
    int fee;

    // Constructor to initialize transaction details
    public Transaction(String type, int amount, int hour, int fee) {
        this.type = type;
        this.amount = amount;
        this.hour = hour;
        this.fee = fee;
    }
}

public class SonamKumari29_FinancialTransactionProcessor {

    // Method to process transactions and calculate total fee and final balance
    public static Object[] processTransactions(int balance, List<Transaction> transactions) {
        int totalFee = 0;
        int finalBalance = balance;

        // Iterate through each transaction
        for (Transaction t : transactions) {
            // Check if the transaction hour is valid (0-23)
            if (t.hour < 0 || t.hour > 23) {
                continue; // Skip invalid transaction hours
            }

            // Check if the transaction type is valid
            if (!t.type.equals("deposit") && !t.type.equals("withdrawal") && !t.type.equals("transfer")) {
                continue; // Skip invalid transaction types
            }

            // Check if the transaction amount is within limits
            if (t.amount <= 0 || t.amount > 50000) {
                continue; // Skip invalid transaction amounts
            }

            // Check if the transaction fee is within limits
            if (t.fee < 0 || t.fee > 10) {
                continue; // Skip invalid transaction fees
            }

            // Process deposit transaction
            if (t.type.equals("deposit")) {
                finalBalance += t.amount; // Add amount to balance
                totalFee += t.fee; // Add fee to total fee
            }
            // Process withdrawal transaction
            else if (t.type.equals("withdrawal")) {
                // Check if withdrawal is possible without going below minimum balance
                if (finalBalance - t.amount - t.fee >= 0) {
                    finalBalance -= t.amount; // Deduct amount from balance
                    totalFee += t.fee; // Add fee to total fee
                }
            }
            // Process transfer transaction
            else if (t.type.equals("transfer")) {
                // Check if transfer is possible without going below minimum balance
                if (finalBalance - t.amount - t.fee >= 0) {
                    finalBalance -= t.amount; // Deduct amount from balance
                    totalFee += t.fee; // Add fee to total fee
                }
            }
        }

        // If no valid transactions were processed, return -1
        if (totalFee == 0) {
            return new Object[]{-1};
        }

        // Return total fee and final balance
        return new Object[]{totalFee, finalBalance};
    }

    public static void main(String[] args) {
        // Example Input
        int balance = 5000;
        List<Transaction> transactions = new ArrayList<>();
        transactions.add(new Transaction("deposit", 2000, 10, 5));
        transactions.add(new Transaction("withdrawal", 1500, 12, 3));
        transactions.add(new Transaction("transfer", 1000, 15, 2));

        // Process transactions
        Object[] result = processTransactions(balance, transactions);

        // Print output
        if (result[0].equals(-1)) {
            System.out.println("Output: -1");
        } else {
            System.out.println("Output: (" + result[0] + ", " + result[1] + ")");
        }

        // Dry Run Explanation
        System.out.println("\nDry Run Explanation:");
        System.out.println("1. Initial Balance: 5000");
        System.out.println("2. Processing Transactions:");
        System.out.println("   - Deposit 2000 at hour 10: Balance = 5000 + 2000 = 7000, Fee = 5");
        System.out.println("   - Withdrawal 1500 at hour 12: Balance = 7000 - 1500 = 5500, Fee = 5 + 3 = 8");
        System.out.println("   - Transfer 1000 at hour 15: Balance = 5500 - 1000 = 4500, Fee = 8 + 2 = 10");
        System.out.println("3. Final Balance: 4500, Total Fee: 10");
        System.out.println("4. Output: (10, 4500)");
    }
}