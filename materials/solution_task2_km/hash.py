# Pseudo-code for hashing function retrieved from decompiled binary

def hash_password():
    
    # Save rax as the result variable
    result = 0
    for i in range(8):
        rdx = input[i]      # Save one byte (one character) of input
        rcx[-2:] = result[-2:]
        rdx = rdx ^ rcx 
        result = result >> 2
        result = result ^ hashTable[some_const+rdx] # Where rdx only the last two bits (possibly) non-zero, and some_const = r10 + 9730

    return result

