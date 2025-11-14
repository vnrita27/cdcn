FLAG = "~"  # Frame delimiter
ESC = "}"  # Escape character


def byte_stuffing(data):
    s = FLAG  # at starting
    for ch in data:
        if ch == FLAG:
            s += ESC + FLAG
        elif ch == ESC:
            s += ESC + ESC
        else:
            s += ch
    s += FLAG  # end of all
    return s


def byte_unstuffing(stuffed_data):
    us = ""
    i = 1  # skip 1st flag
    while i < len(stuffed_data) - 1:  # leave last flag
        if stuffed_data[i] == ESC:
            i += 1
            us += stuffed_data[i]
        else:
            us += stuffed_data[i]
        i += 1
    return us


data = "Hello~World}Test~"
print("Original Data:    ", data)
stuffed_data = byte_stuffing(data)
print("Byte Stuffed:     ", stuffed_data)
unstuffed_data = byte_unstuffing(stuffed_data)
print("Byte Unstuffed:   ", unstuffed_data)
