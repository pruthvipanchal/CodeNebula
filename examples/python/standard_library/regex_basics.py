# Compile: python3 regex_basics.py
# Output:
# IP: 192.168.1.1
# Path: /api/users
# Status: 200
# Smith, John, Doe, Jane

import re

LOG_PATTERN = re.compile(
    r"(?P<ip>\d+\.\d+\.\d+\.\d+)\s+"
    r"\[(?P<date>[^\]]+)\]\s+"
    r'"(?P<method>\w+)\s+(?P<path>\S+)"'
    r"\s+(?P<status>\d+)"
)

log_line = '192.168.1.1 [15/Mar/2024:10:30:00] "GET /api/users" 200'
if m := LOG_PATTERN.search(log_line):
    print(f"IP: {m.group('ip')}")
    print(f"Path: {m.group('path')}")
    print(f"Status: {m.group('status')}")

text = "John Smith, Jane Doe"
swapped = re.sub(r"(\w+) (\w+)", r"\2, \1", text)
print(swapped)

# findall
emails = "Contact alice@example.com or bob@test.org for info"
found = re.findall(r"[\w.+-]+@[\w-]+\.\w+", emails)
print(found)

# split
csv = "one,two,,three,four"
parts = re.split(r",+", csv)
print(parts)
