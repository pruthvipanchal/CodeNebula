# Compile: python3 exception_handling.py
# Output:
# 5.0
# None
# Need 100.00 but only have 50.00

class InsufficientFundsError(ValueError):
    def __init__(self, balance: float, amount: float):
        self.balance = balance
        self.amount = amount
        super().__init__(f"Need {amount:.2f} but only have {balance:.2f}")

def safe_divide(a, b):
    try:
        result = a / b
    except ZeroDivisionError:
        return None
    except TypeError as e:
        raise ValueError(f"Arguments must be numbers: {e}") from e
    else:
        return result  # only runs if no exception
    finally:
        pass  # always runs

print(safe_divide(10, 2))
print(safe_divide(10, 0))

try:
    raise InsufficientFundsError(50.0, 100.0)
except InsufficientFundsError as e:
    print(e)

# Exception chaining
try:
    try:
        int("not-a-number")
    except ValueError as e:
        raise RuntimeError("Config parsing failed") from e
except RuntimeError as e:
    print(f"Caught: {e}")
    print(f"Caused by: {e.__cause__}")
