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


print_bitboard_from_num(0xAA55AA55AA55AA55)
