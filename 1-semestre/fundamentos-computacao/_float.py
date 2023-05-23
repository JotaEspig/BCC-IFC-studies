def binary_frac(d):
    b = ""
    while len(b) < 23:
        d *= 2
        if d >= 1:
            b += "1"
            if d == 1:
                break
            d -= 1
        else:
            b += "0"

    while len(b) < 23:
        b += "0"
    return b
    

def float2bin(num: str):
    bits = ""
 
    integer, fraction = num.split(",")

    if int(integer) < 0 or integer[0] == "-":
        bits += "1"
    else:
        bits += "0"

    mantissa = binary_frac(float("." + fraction))
    
    integer_int = int(integer)
    expoent = 127
    if (integer_int > 1):
        while integer_int > 1:
            mantissa = str(integer_int & 1) + mantissa[:-1]
            integer_int = integer_int >> 1
            expoent += 1
    else:
        while integer_int < 1:
            integer_int = int(bin(integer_int)[2:] + mantissa[0], 2)
            mantissa = mantissa[1:]
            expoent -= 1

    bits += " | " + bin(expoent)[2:].rjust(8, "0")
    bits += " | " + mantissa
    return bits