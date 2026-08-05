from datetime import datetime

LOG_FILE = "cryptolabx.log"

def write_log(action):
    with open(LOG_FILE, "a") as file:
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        file.write(f"{timestamp} - {action}\n")
