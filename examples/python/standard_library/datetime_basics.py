# Compile: python3 datetime_basics.py
# Output:
# UTC and New York times printed

from datetime import datetime, timedelta, timezone

try:
    from zoneinfo import ZoneInfo
    ny_tz = ZoneInfo("America/New_York")
    has_zoneinfo = True
except Exception:
    has_zoneinfo = False

utc_now = datetime.now(timezone.utc)
print(f"UTC: {utc_now.strftime('%Y-%m-%d %H:%M:%S %Z')}")

if has_zoneinfo:
    ny_time = utc_now.astimezone(ny_tz)
    print(f"New York: {ny_time.strftime('%Y-%m-%d %H:%M %Z')}")

# Arithmetic
deadline = datetime(2025, 12, 31, tzinfo=timezone.utc)
remaining = deadline - utc_now
print(f"Days until 2025-12-31: {remaining.days}")

one_week = timedelta(weeks=1)
next_week = utc_now + one_week
print(f"Next week: {next_week.strftime('%Y-%m-%d')}")

# Parsing ISO format
event_str = "2024-03-15T10:30:00+00:00"
event_dt  = datetime.fromisoformat(event_str)
print(f"Parsed: {event_dt}")

# strptime
dt = datetime.strptime("15/03/2024 10:30", "%d/%m/%Y %H:%M")
print(f"strptime: {dt}")
