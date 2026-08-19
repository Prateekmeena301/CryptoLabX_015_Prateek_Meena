from shift_cipher import decrypt


# Expected frequency of each letter in English
ENGLISH_FREQUENCIES = {
    'A': 8.167,
    'B': 1.492,
    'C': 2.782,
    'D': 4.253,
    'E': 12.702,
    'F': 2.228,
    'G': 2.015,
    'H': 6.094,
    'I': 6.966,
    'J': 0.153,
    'K': 0.772,
    'L': 4.025,
    'M': 2.406,
    'N': 6.749,
    'O': 7.507,
    'P': 1.929,
    'Q': 0.095,
    'R': 5.987,
    'S': 6.327,
    'T': 9.056,
    'U': 2.758,
    'V': 0.978,
    'W': 2.360,
    'X': 0.150,
    'Y': 1.974,
    'Z': 0.074
}


def calculate_chi_square(text):
    text = text.upper()

    letters = [char for char in text if char.isalpha()]

    total_letters = len(letters)

    if total_letters == 0:
        return float('inf')

    chi_square = 0

    for letter in ENGLISH_FREQUENCIES:

        observed = letters.count(letter)

        expected = (
            ENGLISH_FREQUENCIES[letter] / 100
        ) * total_letters

        chi_square += (
            (observed - expected) ** 2
        ) / expected

    return chi_square


def chi_square_attack(ciphertext):

    best_key = 0
    best_plaintext = ""
    best_score = float('inf')

    print("\n========== CHI-SQUARE ATTACK ==========")

    # Try all 26 possible keys
    for key in range(26):

        plaintext = decrypt(ciphertext, key)

        score = calculate_chi_square(plaintext)

        print(
            f"Key {key:2}: "
            f"{plaintext:<40} "
            f"Chi-Square: {score:.2f}"
        )

        # Lower score is better
        if score < best_score:
            best_score = score
            best_key = key
            best_plaintext = plaintext

    print("\n========== RESULT ==========")
    print("Predicted Key    :", best_key)
    print("Plaintext        :", best_plaintext)
    print("Chi-Square Score :", round(best_score, 2))


if __name__ == "__main__":

    ciphertext = input("Enter ciphertext: ")

    chi_square_attack(ciphertext)
