def print_bitboard_from_num(num):
    board = [0] * 64
    for i in range(64):
        if num & (1 << i):
            board[i] = 1
    
    for i in range(8):
        for j in range(8):
            char = board[(7-i) * 8 + j]
            if char == 0:
                print(".", end="")
            else:
                print("X", end="")

        print("")


def operation(num):
    
    return num ^63


BITBOARD = 0x1E2222120E0A1222
print("Original:")
print_bitboard_from_num(BITBOARD)
print("Operation:")
print_bitboard_from_num(operation(BITBOARD))
