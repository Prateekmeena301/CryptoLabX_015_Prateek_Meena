from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

BLOCK_SIZE = 16


class PaddingOracle:
    def __init__(self, key):
        self.__key = key
        self.queries = 0

    def check(self, ciphertext, iv):
        self.queries += 1

        try:
            cipher = AES.new(self.__key, AES.MODE_CBC, iv)
            plaintext = cipher.decrypt(ciphertext)
            unpad(plaintext, BLOCK_SIZE)
            return True
        except ValueError:
            return False


def encrypt_message(plaintext, key, iv):
    cipher = AES.new(key, AES.MODE_CBC, iv)
    return cipher.encrypt(pad(plaintext, BLOCK_SIZE))


def recover_block(target, previous, oracle):
    intermediate = [0] * BLOCK_SIZE
    recovered = [0] * BLOCK_SIZE

    for position in range(BLOCK_SIZE - 1, -1, -1):
        padding_value = BLOCK_SIZE - position
        modified = bytearray(previous)

        for j in range(position + 1, BLOCK_SIZE):
            modified[j] = intermediate[j] ^ padding_value

        found = False

        for guess in range(256):
            modified[position] = guess

            if not oracle.check(target, bytes(modified)):
                continue

            if padding_value == 1 and position > 0:
                confirmation = bytearray(modified)
                confirmation[position - 1] ^= 1

                if not oracle.check(target, bytes(confirmation)):
                    continue

            intermediate[position] = guess ^ padding_value
            recovered[position] = (
                intermediate[position] ^ previous[position]
            )

            found = True
            break

        if not found:
            raise RuntimeError(
                f"Failed to recover byte at position {position}"
            )

    return bytes(recovered)


def padding_oracle_attack(ciphertext, iv, oracle):
    if len(iv) != BLOCK_SIZE:
        raise ValueError("IV must be exactly 16 bytes")

    if len(ciphertext) == 0 or len(ciphertext) % BLOCK_SIZE != 0:
        raise ValueError("Ciphertext length must be a positive multiple of 16")

    blocks = [
        ciphertext[i:i + BLOCK_SIZE]
        for i in range(0, len(ciphertext), BLOCK_SIZE)
    ]

    recovered = bytearray()
    previous = iv

    for index, target in enumerate(blocks, start=1):
        print(f"Recovering block {index}/{len(blocks)}...")

        plaintext_block = recover_block(
            target,
            previous,
            oracle
        )

        recovered.extend(plaintext_block)
        previous = target

    return unpad(bytes(recovered), BLOCK_SIZE)


def main():
    key = get_random_bytes(BLOCK_SIZE)
    iv = get_random_bytes(BLOCK_SIZE)

    original_plaintext = (
        b"Padding oracle attack demonstration using AES-CBC!"
    )

    ciphertext = encrypt_message(original_plaintext, key, iv)

    oracle = PaddingOracle(key)

    print("AES-CBC Padding Oracle Attack")
    print("-" * 40)
    print("IV:", iv.hex())
    print("Ciphertext:", ciphertext.hex())
    print()

    recovered_plaintext = padding_oracle_attack(
        ciphertext,
        iv,
        oracle
    )

    print()
    print("Original plaintext:", original_plaintext.decode("utf-8"))
    print("Recovered plaintext:", recovered_plaintext.decode("utf-8"))
    print("Oracle queries:", oracle.queries)
    print("Recovery successful:", recovered_plaintext == original_plaintext)


if __name__ == "__main__":
    main()
