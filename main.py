from analysis.file_analysis import analyze_file
from utils.logger import write_log


def main():
    while True:
        print("\n========== CryptoLabX ==========")
        print("1. Encrypt")
        print("2. Decrypt")
        print("3. Attack")
        print("4. Analyze")
        print("5. Exit")
        print("================================")

        choice = input("Enter your choice (1-5): ")

        if choice == "1":
            write_log("Encrypt selected")
            print("\n[Encrypt] Coming Soon...\n")

        elif choice == "2":
            write_log("Decrypt selected")
            print("\n[Decrypt] Coming Soon...\n")

        elif choice == "3":
            write_log("Attack selected")
            print("\n[Attack] Coming Soon...\n")

        elif choice == "4":
            write_log("Analyze selected")

            filename = input("Enter filename (e.g., sample1.txt): ")

            try:
                analyze_file(f"datasets/{filename}")
            except FileNotFoundError:
                print("\nError: File not found in datasets folder.\n")

        elif choice == "5":
            write_log("Exit")
            print("\nThank you for using CryptoLabX.")
            break

        else:
            write_log("Invalid menu option")
            print("\nInvalid choice! Please enter a number between 1 and 5.\n")


if __name__ == "__main__":
    main()
