# Compile: python3 pattern_matching.py
# Output:
# Going north
# Getting sword
# Goodbye!
# Unknown: fly

def handle_command(command):
    match command.split():
        case ["quit"]:
            return "Goodbye!"
        case ["go", direction] if direction in ("north", "south", "east", "west"):
            return f"Going {direction}"
        case ["get", item, *rest]:
            extra = f" and {rest}" if rest else ""
            return f"Getting {item}{extra}"
        case _:
            return f"Unknown: {command}"

for cmd in ["go north", "get sword", "quit", "fly"]:
    print(handle_command(cmd))
