# Python Module: Text Display Functions

This Python module contains a collection of functions for displaying text in various formats, such as bold, italic, and error messages. It also includes functions for getting user input and displaying data in a table format.
It heavily relies on ANSI escape sequences.

## Functions

Here is a list of functions included in this module:

### clear()

- Description: Clears the screen.
- Usage: `clear()`

### pitalic(\*args, \*\*kwargs)

- Description: Displays *args in italic. \*\*kwargs will be passed to python's print function.
- Usage: `pitalic("Your Text Here")` or `pitalic(*list_to_unpack)` etc.
- Output : *Your Text Here*

### pbold(\*args, \*\*kwargs)

- Description: Displays *args in bold. \*\*kwargs will be passed to python's print function.
- Usage: `pbold("Your Text Here")` or `pbold(*list_to_unpack)` etc.
- Output : **Your Text Here**
  
### pwarn(\*args, \*\*kwargs)

- Description: Displays *args in yellow and bold. \*\*kwargs will be passed to python's print function.
- Usage: `pwarn("Your Text Here")` or `pwarn(*list_to_unpack)` etc.
- Output : <span style="color:yellow">**Your Text Here**</span> (but actually yellow and bold)

### perror(\*args, \*\*kwargs)

- Description: Displays *args in red and bold. \*\*kwargs will be passed to python's print function.
- Usage: `perror("Your Text Here")` or `perror(*list_to_unpack)` etc.
- Output : <span style="color:red">**Your Text Here**</span> (but actually red and bold)

### pblink(\*args, \*\*kwargs)

- Description: Displays *args in blinking. \*\*kwargs will be passed to python's print function.
- Usage: `pblink("Your Text Here")` or `pblink(*list_to_unpack)` etc.
- Output : Your Text Here (but actually blinking)

### bool_input(prompt: str) -> bool

- Description: Asks the user to enter a boolean value. Can parse regular bool inputs like `y`, `n`, `true`, `false`, etc.
- Usage: `user_input = bool_input("Enter True or False: ")`

### print_table(data: list, headers: list)

- Description: Displays the data in a table format.
- Usage: 
    ```python
    data = [['John', 28], ['Jane', 25]]
    headers = ['Name', 'Age']
    print_table(data, headers)
    ```
- Output:
  ```
    | Name | Age |
    **************
    | John | 28  |
    | Jane | 25  |
  ```

### print_as_form(inputs: list) -> list[str]

- Description: Displays a form and returns the user's responses.
- Usage: 
    ```python
    form_questions = ['Name', 'Age', 'City']
    
    user_responses = print_as_form(form_questions)
    ```
- Output:
  ```
    Name: 
    Age: 
    City: 
  ```

## Combined example

```python
from fmt import form_input, print_table
headers = ['Name', 'Age', 'Location']
data = []
while True:
    user = fmt.form_input(headers)
    if user is None:
        break
    else:
        data += [user]
fmt.print_table(data, headers)
```
If user inputs A, B, C, ... L, the output will be:
```
| Name | Age | Location |
*************************
| A    | B   | C        |
| D    | E   | F        |
| G    | H   | I        |
| J    | K   | L        |
```
(with headers in bold)