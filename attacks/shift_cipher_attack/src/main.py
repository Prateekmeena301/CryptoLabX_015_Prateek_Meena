from shift_cipher import encrypt
from brute_force_dictionary import brute_force_dictionary
from chi_square_attack import chi_square_attack


def main():

    print("\n========== SHIFT CIPHER CRYPTANALYSIS ==========")
    print("1. Encrypt")
    print("2. Dictionary Attack")
    print("3. Chi-Square Attack")
    print("4. Exit")

    choice = input("\nEnter your choice: ")

    if choice == "1":

        plaintext = input("Enter plaintext: ")
        key = int(input("Enter key (0-25): "))

        ciphertext = encrypt(plaintext, key)

        print("\nCiphertext:", ciphertext)

    elif choice == "2":

        ciphertext = input("Enter ciphertext: ")

        brute_force_dictionary(ciphertext)

    elif choice == "3":

        ciphertext = input("Enter ciphertext: ")

        chi_square_attack(ciphertext)

    elif choice == "4":

        print("Exiting...")

    else:

        print("Invalid choice!")


if __name__ == "__main__":
    main()
