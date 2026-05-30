# Compile: python3 python3_changes.py
# Output:
# <class 'str'>
# <class 'bytes'>
# True
# 1.5
# 1

# Python 3 string model — str is Unicode text, bytes is raw binary
text = "café"
raw  = "café".encode("utf-8")

print(type(text))                  # <class 'str'>
print(type(raw))                   # <class 'bytes'>
print(text.encode("utf-8") == raw) # True

# Python 3 integer division
print(3 / 2)   # 1.5 (true division)
print(3 // 2)  # 1   (floor division)
