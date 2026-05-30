# Compile: python3 classes.py
# Output:
# BankAccount(owner='Alice', balance=1300.00)

class BankAccount:
    interest_rate = 0.02

    def __init__(self, owner: str, balance: float = 0.0):
        self._owner = owner
        self._balance = balance

    @property
    def balance(self) -> float:
        return self._balance

    def deposit(self, amount: float) -> None:
        if amount <= 0:
            raise ValueError("Deposit must be positive")
        self._balance += amount

    def withdraw(self, amount: float) -> None:
        if amount > self._balance:
            raise ValueError("Insufficient funds")
        self._balance -= amount

    @classmethod
    def from_dict(cls, data: dict) -> "BankAccount":
        return cls(data["owner"], data.get("balance", 0.0))

    def __repr__(self) -> str:
        return f"BankAccount(owner={self._owner!r}, balance={self._balance:.2f})"

acc = BankAccount.from_dict({"owner": "Alice", "balance": 1000})
acc.deposit(500)
acc.withdraw(200)
print(acc)

# Class vs instance attribute
a1 = BankAccount("Bob")
a2 = BankAccount("Carol")
print(BankAccount.interest_rate)  # 0.02 — shared class attribute
BankAccount.interest_rate = 0.025
print(a1.interest_rate, a2.interest_rate)  # both 0.025
