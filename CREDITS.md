milestone 1:

hex_to_byte:

I asked "how do I approach this" and got:

To approach implementing the hex_to_byte function without directly showing the code, here’s a breakdown of the logic you need to follow to achieve the desired functionality:

Understand Hexadecimal Digits: Each hexadecimal character (0–9, A–F, or a–f) represents a value in base 16:

Digits '0' to '9' represent values 0 to 9.
Letters 'A' to 'F' (uppercase) or 'a' to 'f' (lowercase) represent values 10 to 15.
Convert Characters to Numeric Values:

For characters '0' to '9', you can get their integer value by subtracting the ASCII value of '0' from the character. This gives the direct numeric value (e.g., '3' - '0' equals 3).
For characters 'A' to 'F', subtracting 'A' from the character and adding 10 gives the correct value (e.g., 'B' - 'A' gives 1, and adding 10 gives 11).
Similarly, for characters 'a' to 'f', subtract 'a' and add 10.
Combine the Digits:

Since h1 is the most significant hex digit, shift its numeric value by 4 bits to the left. This makes room for h2, which will occupy the lower 4 bits.
Add the value of h2 to get the final byte value.
Return the Result:

The function should return this combined value as an 8-bit integer, which represents the two hex digits as a single byte.
Testing with Assertions:

Use assertions with test cases to verify that the function works as expected, like the ones given:
hex_to_byte('c', '8') == 200
hex_to_byte('0', '3') == 3
hex_to_byte('0', 'a') == 10
hex_to_byte('1', '0') == 16
By following these steps, you can create the hex_to_byte function to convert two hex characters into a single byte in an efficient way. The key is in understanding ASCII character manipulation and bitwise operations to combine the values.

- I fllowed the approach and coded the function

hextr_to_hash:

- founded a similar example on stackoverflow and I just followed the indexing.

milestone 2:

check_password:
- tried to do SHA256((unsigned char*)password, strlen(password), computed_hash); without the '(unsigned char*) and then I ask chatgpt "anything missing" and it told me put unsigned char* in

milestone 3:
crack_password:
- wrote this all by myself

main: 
- Asked chatgpt to assist:
    - learned what strcspn does
    - how to match up with the autograder output because it didn't pass the first few times I did myself

other:
- Debugging throuhgout the PA.
- "Why isn't this working?"