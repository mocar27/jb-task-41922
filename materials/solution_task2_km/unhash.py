# Loading file from memory
def load_data(path):
    file_path = path

    with open(file_path, 'r') as file:
        hashes = file.readlines()

    return [hash.strip() for hash in hashes]

# XOR operation on two hexadecimal string numbers
def xor_hex_strings(hex_str1, hex_str2):
    int_val1 = int(hex_str1, 16)
    int_val2 = int(hex_str2, 16)

    result_int = int_val1 ^ int_val2
    result_hex = hex(result_int)[2:]
    
    while len(result_hex) < 16:
        result_hex = '0' + result_hex

    return result_hex.upper()

hashes = load_data('hashes.txt')
initial_hash_result = hash_result = '3E4C3F5BDF80E7D3'
unhash_result_indices = []

# Decoding values from the hash array contained in the task which are used to hash the correct password
for _ in range(8):
    first_bits = hash_result[:2]

    for hash in hashes:
        if hash[:2] == first_bits:
            unhash_result_indices.append(hashes.index(hash))
            hash_result = xor_hex_strings(hash, hash_result)
            # In the hashing function there is a right bitshift, so we do left and look in the loaded hashes.txt file for a hash
            # whose first two letters match our current hash, because by reversing the xor of the result
            # we get the result of the previous xor hash
            hash_result = hash_result[2:] + '00'
            break

unhash_result_indices.reverse()
reveal_password = []

result = '0000000000000000'
for i in range(8):
    last_two_letters = result[-2:]
    index_in_hashes = hex(unhash_result_indices[i])[2:].upper()

    char = xor_hex_strings(result, index_in_hashes)[-2:]
    reveal_password.append(int(char, base=16))
    
    result = result[:-2]
    result = '00' + result
    result = xor_hex_strings(result, hashes[unhash_result_indices[i]])

string_result = ''.join(map(chr, reveal_password))
print(string_result)
