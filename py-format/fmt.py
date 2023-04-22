# Basic python module providing functions to output
# formatted text using ANSI escape sequences.

# Author : Côme VINCENT, 2023

def clear() -> None:
    """Clears the terminal screen, deletes scrollback buffer and
    moves the cursor to the top left corner of the screen."""
    print("\x1b[3J\x1b[H\x1b[J", end="")


def pitalic(*args, **kwargs) -> None:
    """Prints given arguments in italic. Stdout unless specified."""
    print("\x1b[3m", end="")
    print(*args, **kwargs)
    print("\x1b[23m", end="")


def pbold(*args, **kwargs) -> None:
    """Prints given arguments in bold. Stdout unless specified."""
    print("\x1b[1m", end="")
    print(*args, **kwargs)
    print("\x1b[22m", end="")


def pwarn(*args, **kwargs) -> None:
    """Prints given arguments in bold yellow. Stdout unless specified."""
    print("\x1b[33m", end="")
    print(*args, **kwargs)
    print("\x1b[39m", end="")


def perror(*args, **kwargs) -> None:
    """Prints given arguments in bold red. Stdout unless specified."""
    print("\x1b[31m", end="")
    print(*args, **kwargs)
    print("\x1b[39m", end="")


def pblink(s: str, **kwargs) -> None:
    """Prints a string in blink. Stdout unless specified."""
    print("\x1b[5m" + s + "\x1b[25m", **kwargs)


def bool_input(prompt: str) -> bool:
    """Asks the user to input a boolean value.
    Cancel with Ctrl+C."""

    # Get the user input
    bold_prompt = "\x1b[1m" + prompt + "\x1b[0m"
    try:
        str_input = input(bold_prompt).lower()
    except KeyboardInterrupt:
        print()
        exit(0)

    # Check if the input is valid
    bool_input = ['true', '1', 't', 'y', 'yes', 'o',
                  'false', '0', 'f', 'n', 'no', 'n']

    while True:
        try:
            if bool_input.index(str_input) < 6:
                return True
            else:
                return False
        except ValueError:
            try:
                str_input = input(bold_prompt).lower()
            except KeyboardInterrupt:
                print()
                exit(0)


def print_table(data: list[str], headers: list[str]) -> None:
    """Shows a formatted table in the terminal."""
    max_length_column = [0] * len(headers)
    for i in range(len(data)):
        for j in range(len(data[i])):
            if len(str(data[i][j])) > max_length_column[j]:
                max_length_column[j] = len(str(data[i][j]))

    print("|", end="")
    for i, header in enumerate(headers):
        if len(header) > max_length_column[i]:
            max_length_column[i] = len(header)
        pbold(" " + header.ljust(max_length_column[i]) + " |", end="")
    print()

    print("*" * (sum(max_length_column) + 3 * len(headers) + 1))

    for row in data:
        print("|", end="")
        for i in range(len(row)):
            print(" " + str(row[i]).ljust(max_length_column[i]) + " |", end="")
        print()


def form_input(inputs: list) -> list[str]:
    """Asks the user to input a list of values."""
    answers = [None] * len(inputs)

    # Calcul des longueurs des labels
    inputs = [i + " : " for i in inputs]
    label_lengths = [len(i) for i in inputs]
    n_labels = len(inputs)

    # Affichage des labels
    pbold(*inputs, sep="\n", end="")

    # Affichage des champs de saisie
    print(f"\x1b[{n_labels - 1}F", end="")
    for i in range(n_labels):
        print(f"\x1b[{label_lengths[i]}C", end="")
        try:
            answers[i] = input()
        except KeyboardInterrupt:
            clear()
            return None
    return answers


if __name__ == "__main__":
    clear()
    pitalic("This is italic")
    pbold("This is bold")
    pwarn("This is a warning")
    perror("This is an error")
    pblink("This is blinking")
    print(bool_input("Do you like this module ?"))
    print_table(data=[["Hello", "World"], ["This", "Is", "A", "Table"]], headers=["A", "B", "C", "D"])
