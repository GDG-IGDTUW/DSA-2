class TransactionProcessor:
    def __init__(self):
        self.accounts = {}  # account_id -> balance

    def create_account(self, account_id, initial_balance=0):
        if account_id in self.accounts:
            print("Account already exists.")
            return
        self.accounts[account_id] = initial_balance
        print(f"Account {account_id} created with balance ₹{initial_balance}.")

    def deposit(self, account_id, amount):
        if account_id not in self.accounts:
            print("-1")  # Account does not exist
            return
        self.accounts[account_id] += amount
        print(f"Deposited ₹{amount} to account {account_id}. New balance: ₹{self.accounts[account_id]}.")

    def withdraw(self, account_id, amount):
        if account_id not in self.accounts or self.accounts[account_id] < amount:
            print("-1")  # Insufficient funds or account does not exist
            return
        self.accounts[account_id] -= amount
        print(f"Withdrew ₹{amount} from account {account_id}. New balance: ₹{self.accounts[account_id]}.")

    def transfer(self, from_account, to_account, amount):
        if from_account not in self.accounts or to_account not in self.accounts:
            print("-1")  # One or both accounts do not exist
            return
        if self.accounts[from_account] < amount:
            print("-1")  # Insufficient funds
            return
        self.accounts[from_account] -= amount
        self.accounts[to_account] += amount
        print(f"Transferred ₹{amount} from account {from_account} to account {to_account}.")

    def check_balance(self, account_id):
        if account_id not in self.accounts:
            print("-1")  # Account does not exist
            return
        print(f"Account {account_id} balance: ₹{self.accounts[account_id]}.")


def main():
    processor = TransactionProcessor()
    
    while True:
        print("\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Check Balance\n6. Exit")
        choice = input("Enter choice: ")
        
        if choice == "6":
            break
        
        if choice == "1":
            account_id = input("Enter account ID: ")
            initial_balance = float(input("Enter initial balance: "))
            processor.create_account(account_id, initial_balance)
        
        elif choice == "2":
            account_id = input("Enter account ID: ")
            amount = float(input("Enter deposit amount: "))
            processor.deposit(account_id, amount)
        
        elif choice == "3":
            account_id = input("Enter account ID: ")
            amount = float(input("Enter withdrawal amount: "))
            processor.withdraw(account_id, amount)
        
        elif choice == "4":
            from_account = input("Enter sender account ID: ")
            to_account = input("Enter receiver account ID: ")
            amount = float(input("Enter transfer amount: "))
            processor.transfer(from_account, to_account, amount)
        
        elif choice == "5":
            account_id = input("Enter account ID: ")
            processor.check_balance(account_id)
        
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()
