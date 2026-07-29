from collections import Counter

def analyze_file(filepath):

    try:

        with open(filepath, "r") as file:

            text = file.read()

        print("\n========== Analysis ==========")

        print("Characters :", len(text))

        print("Words :", len(text.split()))

        print("Lines :", len(text.splitlines()))

        print("Unique Characters :", len(set(text)))

        letters = [c.lower() for c in text if c.isalpha()]

        freq = Counter(letters)

        print("\nLetter Frequency")

        for i in sorted(freq):

            print(i, ":", freq[i])

    except FileNotFoundError:

        print("File not found")
