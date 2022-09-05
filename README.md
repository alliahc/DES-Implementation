# DES-Implementation

Given a plaintext and a 64-bit key, this program will output the formed cipher text using DES. This program is based on https://academic.csuohio.edu/yuc/security/Chapter_06_Data_Encription_Standard.pdf. Additionally, the 64-bit key will go through a parity check. If the key fails the parity bit check, then the program will output `invalid key` instead of the cipher text.

## Limitations
- Plaintext can be up to 50 characters only
- Key can only be in binary form and is expected to be 64 bits always


