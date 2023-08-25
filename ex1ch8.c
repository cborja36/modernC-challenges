#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

size_t strlen(const char *str) {
  size_t len = 0;
  while (true) {
    char c = str[len];
    if (c == '\0') {
      return len;
    }
    len++;
  }
}

long my_strtol(const char *str) {
  long result = 0;
  long exponent = 0;
  for (int i = strlen(str) - 1; i >= 0; --i) {
    result += (long)((str[i] - '0') * pow(10, exponent));
    ++exponent;
  }
  return result;
}

double my_strtoinvd(const char *str) {
  double result = 0;
  long exponent = -1;
  for (size_t i = 0; i < strlen(str); ++i) {
    result += (double)((str[i] - '0') * pow(10, exponent));
    --exponent;
  }
  return result;
}

int find(const char *str, char c) {
  size_t len = strlen(str);
  size_t i = 0;
  while (true) {
    if (i == len) {
      return -1;
    } else if (str[i] == c) {
      return i;
    }
    ++i;
  }
}

double my_strtod(const char *str) {
  double result = 0;
  size_t len = strlen(str);
  int pointpos = find(str, '.');

  // Process the sign
  bool minus_sign = find(str, '-') != -1;
  char str_without_sign[len + 1 - minus_sign];
  if (minus_sign) assert(str[0] == '-');
  for (size_t i = minus_sign; i < len; ++i) {
    str_without_sign[i - minus_sign] = str[i];
  }
  str_without_sign[len - minus_sign] = '\0';

  // Get the integer part
  size_t ipart_len = (pointpos == -1) ? len : pointpos;
  char ipart[ipart_len + 1];  // +1 for the null terminator
  for (size_t i = 0; i < ipart_len; ++i) {
    ipart[i] = str_without_sign[i];
  }
  ipart[ipart_len] = '\0';
  result += (double)my_strtol(ipart);

  // Get the decimal part
  if (pointpos != -1) {
    char dpart[(len - pointpos - 1) + 1];  // +1 for the null terminator
    for (size_t i = pointpos + 1; i < len; ++i) {
      dpart[i - pointpos - 1] = str_without_sign[i];
    }
    dpart[len - pointpos - 1] = '\0';
    result += my_strtoinvd(dpart);
  }

  return result * (minus_sign ? -1 : 1);
}

void dashed_lines(char* buffer, int n) {
    for(int i = 0; i < n; i++) {
        buffer[i] = '-';
    }
    buffer[n] = '\0';  // Null-terminate the string
}

int main(void) {
  const char *tests[] = {"123.456", "123",  "00123.00456", "-123.456",
                         "-123",    ".123", "-.123"};

  int num_tests = sizeof(tests) / sizeof(tests[0]);

  // Determine the max width for the input string for alignment purposes.
  int max_width = 0;
  for (int i = 0; i < num_tests; i++) {
    int len = strlen(tests[i]);
    if (len > max_width) {
      max_width = len;
    }
  }

  char buffer[max_width + 1];
  dashed_lines(buffer, max_width);
  printf("%*s | Output\n", max_width, "Input");   // Print the header.
  printf("%s-+-------------\n", buffer);                 // Print the separator.

  for (int i = 0; i < num_tests; i++) {
    printf("%*s | %lf\n", max_width, tests[i], my_strtod(tests[i]));
  }
}
