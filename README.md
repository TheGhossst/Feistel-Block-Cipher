# Feistel-Block-Cipher
Feistel Block Cipher Algorithm C


c program to implement feistel's algorithm where a plain text is accepted and then plain text characters is converted into ascii and then to 8 bit binary. Divide the binary plain text into blocks of 8 bits and then perform the folowing operation to each block:
1. Divide the binary plain text block into 2 halves L1 and R1
2. Generate random binary keys(k1 and k2) of length equal to half the length of plain text block for 2 rounds
3. For First round do:  Generate function F1= Xor(R1,K1) then set L2=R1 and R2=Xor(F1,L1)
4. For second round do: Generate function F2=Xor(R2,K2) then set L3=R2 and R3=Xor(F2,L2)
5. Concat R3L3 to form the cipher text block and write to output file
6. Repeat this for all the blocks in the plain text till eof