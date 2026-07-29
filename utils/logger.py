from datetime import datetime

def log_menu(option):

    with open("outputs/execution.log", "a") as file:

        file.write(f"{datetime.now()} --> Option {option}\n")
