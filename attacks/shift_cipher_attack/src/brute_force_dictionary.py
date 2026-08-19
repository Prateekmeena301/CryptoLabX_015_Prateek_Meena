from shift_cipher import decrypt


DICTIONARY_FILE = "../dictionary/english_words.txt"


def load_dictionary():
    words = set()

    with open(DICTIONARY_FILE, "r") as file:
        for line in file:
            words.add(line.strip().upper())

    return words


def dictionary_score(text, dictionary):
    words = text.upper().split()

    score = 0

    for word in words:
        if word in dictionary:
            score += 1

    return score


def brute_force_dictionary(ciphertext):
    dictionary = load_dictionary()

    best_key = 0
    best_plaintext = ""
    best_score = -1

    print("\n========== BRUTE FORCE + DICTIONARY ==========")

    for key in range(26):
        plaintext = decrypt(ciphertext, key)

        score = dictionary_score(plaintext, dictionary)

        print(f"Key {key:2}: {plaintext:<30} Score: {score}")

        if score > best_score:
            best_score = score
            best_key = key
            best_plaintext = plaintext

    print("\n========== RESULT ==========")
    print("Predicted Key    :", best_key)
    print("Plaintext        :", best_plaintext)
    print("Dictionary Score :", best_score)


if __name__ == "__main__":
    ciphertext = input("Enter ciphertext: ")

    brute_force_dictionary(ciphertext)
