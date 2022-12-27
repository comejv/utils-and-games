# (better) Python Trithemius
Simple encryption script based on the position of the char relative to a juxtaposed alphabet (that can be shuffled with a given key), then transformed into a letter again. Similar to the Trithemius cipher.

Non alphanumeric characters are not encrypted (except space when using level 2 or 3).

Structure can be preserved or not.

The same algorithm is applied sepparately to numbers if users choses to do so.

## Usage
This script can be used with a textual interface or through arguments.

### Textual interface

Execute the main file with python 3 : `python3 ./main.py`

### CLI usage :
```
python3 main.py [-h] [-e] [-d] [-s {0,1,2,3}] [-k KEY] [-t TEXT]

optional arguments:
  -h, --help            Show this help message and exit
  -e, --encrypt         Encrypt a string
  -d, --decrypt         Decrypt a string
  -s {0,1,2,3}, --security {0,1,2,3}
                        0 - encrypts only the words
                        1 - level 0 + encrypts numbers
                        2 - level 1 + word structure randomised
                        3 - level 2 + shuffles the alphabet
  -k KEY, --key KEY     Key to use for encryption/decryption
  -t TEXT, --text TEXT  The text to encrypt/decipher
```
## Encryption example
Encrypting the string `Test 123 hello!` using level 3 encryption and key = 1234 gives this output : `togz95rv7k9sw7q!`
