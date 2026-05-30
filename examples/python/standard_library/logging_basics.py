# Compile: python3 logging_basics.py
# Output:
# JSON log lines printed to stdout

import logging
import json
import sys

class JSONFormatter(logging.Formatter):
    def format(self, record: logging.LogRecord) -> str:
        log_entry = {
            "level": record.levelname,
            "message": record.getMessage(),
            "module": record.module,
        }
        if record.exc_info:
            log_entry["exception"] = self.formatException(record.exc_info)
        return json.dumps(log_entry)

logger = logging.getLogger("myapp.service")
# Clear any existing handlers to avoid duplicate output in tests
logger.handlers.clear()
handler = logging.StreamHandler(sys.stdout)
handler.setFormatter(JSONFormatter())
logger.addHandler(handler)
logger.setLevel(logging.DEBUG)
logger.propagate = False

logger.info("Service started")
logger.debug("Connecting to %s", "localhost:5432")

try:
    1 / 0
except ZeroDivisionError:
    logger.error("Unexpected division error", exc_info=True)
