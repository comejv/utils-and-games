import argparse
import random
import subprocess
import sys

ANSI = {
    "BOLD": "\x1b[1m",
    "BOLDR": "\x1b[1;91m",
    "UNDER": "\x1b[4m",
    "REVB": "\x1b[5;7m",
    "ENDC": "\x1b[0m"
}

ALPHA = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
         'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

NUM = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']


def clear():
    print("\x1b[2J\x1b[H")


def eprint(text, *args, **kwargs):
    print(ANSI["BOLDR"] + "Error :", text +
          ANSI["ENDC"], *args, file=sys.stderr, **kwargs)


def wprint(text, *args, **kwargs):
    print(ANSI["BOLD"] + "Warning :", text +
          ANSI["ENDC"], *args, file=sys.stderr, **kwargs)


def binput(prompt):
    str_input = input(ANSI['BOLD'] + prompt + ANSI['ENDC'])
    bool_input = ['true', '1', 't', 'y', 'yes', 'i',
                  'false', '0', 'f', 'n', 'no', 'p']

    while str_input not in bool_input:
        str_input = input("\x1b[1F\x1b[K" +
                          ANSI["BOLD"] + prompt + ANSI["ENDC"])
    if str_input.lower() in bool_input[:6]:
        return True
    return False


def is_ascii(s):
    return all(ord(c) < 128 for c in s)


clear()
try:
    from unidecode import unidecode
    handle_diacritics = True
except ImportError:
    wprint("Unidecode module not found.")
    handle_diacritics = binput(
        "Do you want to install it with or skip and continue without diacritic characters ?\n(y : install / n : pass)")
    if handle_diacritics is True:
        subprocess.check_call(
            [sys.executable, "-m", "pip", "install", "unidecode"])
        from unidecode import unidecode
    else:
        wprint("Diacritics will not be handled.")


def encrypt(input, security_level, decrypt=False):
    """Decrypts each character according to its distance relative distance to item in list used to encrypt.

    Args:
        plain (string): the text to encrypt
        security_level (int): determines the level of encryption used

    Returns:
        string: the encrypted text
    """
    output = ""
    counter = 0

    for c in input:
        if security_level <= 1 and c in ALPHA:
            output += ALPHA[(ALPHA.index(c) + counter) % 26]

        elif security_level == 1 and c in NUM:
            output += NUM[(NUM.index(c) + counter) % 10]

        elif security_level >= 2 and c in ALPHANUM:
            output += ALPHANUM[(ALPHANUM.index(c) + counter) % 37]

        else:
            output += c

        counter += 1 if decrypt is False else -1

    return output


def decrypt(cipher, security_level):
    return encrypt(cipher, security_level, decrypt=True)


def main_textuel():
    clear()

    # Encrypt or Decrypt
    action = input(
        ANSI['BOLD'] + "Encrypt or Decrypt ? (e : encrypt / d : decrypt)" + ANSI['ENDC'])

    while action not in ['e', 'd']:
        action = input(
            ANSI['BOLD'] + "Encrypt or Decrypt ? (e : encrypt / d : decrypt)" + ANSI['ENDC'])

    security_level = int(input("What level of security do you want ? (0-3)"))

    # Only the words are encrypted
    if security_level <= 0:
        pass

    # Level 1 and numbers are encrypted
    elif security_level == 1:
        key = int(
            input(ANSI['BOLD'] + "Enter your key (integer): " + ANSI['ENDC']))
        random.Random(key).shuffle(ALPHA)
        random.Random(key).shuffle(NUM)

    # Level 2 and structure is not preserved
    elif security_level >= 2:
        global ALPHANUM
        ALPHANUM = ALPHA + NUM
        ALPHANUM.append(' ')

    # Level 3 and shuffle of ALPHANUM
    if security_level >= 3:
        key = int(
            input(ANSI['BOLD'] + "Enter your key (integer): " + ANSI['ENDC']))
        random.Random(key).shuffle(ALPHANUM)

    clear()
    text = input("Enter a string:\n")
    if handle_diacritics is False:
        while text.isascii() is False:
            text = input("Please use ASCII characters only:\n")
    else:
        text = unidecode(text)

    clear()

    # Encrypt plain text
    if action == 'e':
        print("Encrypted text :\n\n" + encrypt(text.lower(), security_level))

    # Decrypt cipher text
    elif action == 'd':
        print("Plain text :\n\n" + decrypt(text.lower(), security_level))

    input('\n\n' + ANSI["REVB"] +
          "PRESS ENTER TO CLEAR THE SCREEN" + ANSI['ENDC'])
    clear()


parser = argparse.ArgumentParser()

parser.add_argument('-e', '--encrypt', action='store_true',
                    help='Encrypt a string')
parser.add_argument('-d', '--decrypt', action='store_true',
                    help='Decrypt a string')
parser.add_argument('-s', '--security', type=int, default=0, choices=[0, 1, 2, 3],
                    help='0 - encrypts only the words\n\
                        1 - level 0 + encrypts numbers\n\
                        2 - level 1 + word structure randomised\n\
                        3 - level 2 + shuffles the alphabet')
parser.add_argument('-k', '--key', type=int, action='store',
                    help='Key to use for encryption/decryption')
parser.add_argument('-t', '--text', type=str, default=None)

args = parser.parse_args()


def main_args():
    if args.security == 1:
        random.Random(args.key).shuffle(ALPHA)
        random.Random(args.key).shuffle(NUM)

    if args.security >= 2:
        global ALPHANUM
        ALPHANUM = ALPHA + NUM
        ALPHANUM.append(' ')

    if args.security >= 3:
        random.Random(args.key).shuffle(ALPHANUM)

    if args.text is None:
        text = input()
    else:
        text = args.text

    print(encrypt(text, args.security, args.decrypt))


if __name__ == "__main__":
    try:
        if len(sys.argv) < 2:
            main_textuel()
        else:
            main_args()

    except KeyboardInterrupt:
        print("\x1b[2K\rProcess interrupted by user...")
        exit(1)
