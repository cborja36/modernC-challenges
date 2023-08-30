-- Functions to emulate size_t behavior in Lua (since Lua uses double-precision floats for all numbers)
local function size_t_max()
    return 2^53 - 1  -- this is the largest integer that can be represented precisely in a Lua number
end

-- Function to pretty print numbers with comma separators
local function prettyu(n)
    if n < 1000 then
        io.write(n)
        return
    end
    prettyu(math.floor(n / 1000))
    io.write(string.format(",%03d", n % 1000))
end

-- Function to print progress in estimation
local function print_progress(iteration, estimation)
    io.write("\r>> Iteration (")
    prettyu(iteration)
    io.write(string.format(") <<\nReal value: %.16f\nEstimation: %.16f\nError:      %.12e", math.pi, 4 * estimation, math.abs(4 * estimation - math.pi)))
    io.write("\27[3A")  -- Equivalent to printf("\033[3A"); to move cursor up 3 lines
end

-- Function to estimate pi
local function f(n, verbose)
    local result = 0
    local current_term
    for i = 0, n do
        current_term = 1 / (2 * i + 1)
        if i % 2 == 1 then current_term = -current_term end
        result = result + current_term

        if verbose and i % 10000000 == 0 then
            print_progress(i, result)
        end
    end
    return result
end

-- Execute the main logic
f(size_t_max(), true)
