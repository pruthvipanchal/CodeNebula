# Compile: python3 os_sys_basics.py
# Output:
# Python version printed

import os
import sys

db_url = os.environ.get("DATABASE_URL", "sqlite:///dev.db")
debug  = os.environ.get("DEBUG", "false").lower() == "true"

print(f"DB URL: {db_url}")
print(f"Debug:  {debug}")
print(f"PID:    {os.getpid()}")
print(f"Python: {sys.version_info.major}.{sys.version_info.minor}")
print(f"Platform: {sys.platform}")

# Directory operations
import tempfile, shutil
tmp = tempfile.mkdtemp()
nested = os.path.join(tmp, "output", "reports")
os.makedirs(nested, exist_ok=True)
print(f"Created: {os.path.exists(nested)}")
shutil.rmtree(tmp)

# os.path utilities
path = "/home/user/projects/app/main.py"
print(os.path.dirname(path))   # /home/user/projects/app
print(os.path.basename(path))  # main.py
print(os.path.splitext(path))  # ('/home/user/projects/app/main', '.py')
