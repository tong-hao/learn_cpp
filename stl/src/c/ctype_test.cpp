#include <cctype>
#include <iostream>

// isalnum	Check if character is alphanumeric (function)
// isalpha	Check if character is alphabetic (function)
// isblank	Check if character is blank (function)
// iscntrl	Check if character is a control character (function)
// isdigit	Check if character is decimal digit (function)
// isgraph	Check if character has graphical representation (function)
// islower	Check if character is lowercase letter (function)
// isprint	Check if character is printable (function)
// ispunct	Check if character is a punctuation character (function)
// isspace	Check if character is a white-space (function)
// isupper	Check if character is uppercase letter (function)
// isxdigit	Check if character is hexadecimal digit (function)

int main() {
  char *str = "a1b2\0";
  int i = 0;
  while (i < 4) {
    std::cout << isalnum(str[i]) << std::endl;
    i++;
  }

  std::cout << tolower('A') << std::endl;
  std::cout << toupper('a') << std::endl;
}
