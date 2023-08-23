import math


def prettyu(n):
    return "{:,}".format(n)


def f(n, verbose=True):
    result = 0.0

    first = True
    for i in range(n + 1):
        current_term = 1.0 / (2 * i + 1)
        if i % 2 == 1:
            current_term *= -1
        result += current_term

        if verbose and i % 10000000 == 0:
            if not first:
                # Move cursor up by 3 lines (like the ANSI code \033[3A in C)
                print("\033[3A", end="")
            print("\r>> Iteration ({}) <<".format(prettyu(i)))
            print("Real value:   {:.16f}".format(math.pi))
            print("Estimation:   {:.16f}".format(4 * result))
            print("Error:        {:.12e}".format(abs(4 * result - math.pi)), end="")
            first = False

    return result


def calculate_precision(n_decimals):
    threshold = 2 * 10**n_decimals - 3.0 / 2
    return math.ceil(threshold)


if __name__ == "__main__":
    f(int(calculate_precision(64)))
