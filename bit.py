def bit_stuffing(data):
    s = ""
    count = 0
    for bit in data:
        s += bit
        if bit == "1":
            count += 1
            if count == 5:
                # Insert a 0 after five consecutive 1's
                s += "0"
                count = 0
        else:
            count = 0
    return s


def bit_unstuffing(stuffed_data):
    us = ""
    count = 0
    i = 0
    while i < len(stuffed_data):
        bit = stuffed_data[i]
        us += bit
        if bit == "1":
            count += 1
            if count == 5:
                # Skip the next 0 bit
                i += 1
                count = 0
        else:
            count = 0
        i += 1
    return us


# Example usage:
data = "011111101111110"
print("Original Data: ", data)
stuffed_data = bit_stuffing(data)
print("Bit Stuffed: ", stuffed_data)
unstuffed_data = bit_unstuffing(stuffed_data)
print("Bit Unstuffed: ", unstuffed_data)
