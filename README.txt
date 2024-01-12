Program Author: Shiyam Vasanthan
Program Purpose: The purpose of this program is to ask the user whether they want to encrypt plaintext into cyphertext, or decrypt cyphertext into plaintext.
Source File: cypher.c
Compilation Command: gcc -Wall -o cypher -std=c99 cypher.c
Launching and Operating Instructions: Type ./cypher in the terminal. This is now an executable file. 
Once you run the program you will be prompted to enter either 0, 1, or 2.
Entering 0 will quit the program.
Entering 1 will prompt you to encrypt a message.
Entering 2 will prompt you to decrypt a message.
If you entered 1:
Type plaintext into the terminal and hit enter.
Just make sure to not exceed the maximum number of bytes 256, or else the text you entered after 256 characters will not be encoded.
It will then output a sequence of integers which are the integer values of the cyphertext bytes.
For example:
Input: (Muffled Speech). Yeah some nerds were here last night getting scared by random noises. They (Muffled Speech). Ghosts or something. We should mess with them, do you still have that fog machi (Muffled Speech).
Output: 153 212 157 219 189 209 164 192 224 213 137 228 129 226 174 197 203 243 182 137 240 206 250 137 246 147 254 222 176 209 163 133 246 78 5 192 114 35 231 143 154 106 35 161 237 142 25 237 141 255 150 107 155 237 157 250 31 237 209 178 20 119 215 164 71 130 112 111 147 225 167 156 28 74 35 175 195 172 65 163 237 216 49 218 63 142 52 4 80 114 27 160 0 40 97 214 48 106 58 125 89 123 12 76 89 62 29 85 20 30 90 29 85 36 87 59 8 56 83 49 1 114 17 116 89 47 7 108 66 37 11 113 30 29 25 106 50 51 106 46 66 98 43 44 95 40 20 123 18 52 76 62 74 42 67 46 10 104 8 103 71 154 53 216 56 111 139 240 108 10 98 42 35 243 178 48 100 14 51 221 189 219 180 67 227 138 35 194 42 69 161 137 196 87 141 211 167 128 100 6 117 207 134 1 226 46 7 203 193
If you entered 2:
Type a sequence of space-separated integers (max value is 255), and finally enter -1 when you want to stop. Then hit enter. 
Just make sure you don't enter more than 256 integers, or else the integers you entered after 256 will not be decrypted. 
For example:
Input: 153 212 157 219 189 209 164 192 224 213 137 228 129 226 174 197 203 243 182 137 240 206 250 137 246 147 254 222 176 209 163 133 246 78 5 192 114 35 231 143 154 106 35 161 237 142 25 237 141 255 150 107 155 237 157 250 31 237 209 178 20 119 215 164 71 130 112 111 147 225 167 156 28 74 35 175 195 172 65 163 237 216 49 218 63 142 52 4 80 114 27 160 0 40 97 214 48 106 58 125 89 123 12 76 89 62 29 85 20 30 90 29 85 36 87 59 8 56 83 49 1 114 17 116 89 47 7 108 66 37 11 113 30 29 25 106 50 51 106 46 66 98 43 44 95 40 20 123 18 52 76 62 74 42 67 46 10 104 8 103 71 154 53 216 56 111 139 240 108 10 98 42 35 243 178 48 100 14 51 221 189 219 180 67 227 138 35 194 42 69 161 137 196 87 141 211 167 128 100 6 117 207 134 1 226 46 7 203 193 -1
Output: (Muffled Speech). Yeah some nerds were here last night getting scared by random noises. They (Muffled Speech). Ghosts or something. We should mess with them, do you still have that fog machi (Muffled Speech).
