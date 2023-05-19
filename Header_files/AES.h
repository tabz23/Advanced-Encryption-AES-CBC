// Rcon is constant word array of the form (RC[i], 0, 0, 0)
// RC[1] = 1, RC[j] = 2.RC[j-1] in GF(28).
// [x^(i-1),{00},{00},{00}], with x (i-1) being  powers of x (x is denoted as {02}) (note that i starts at 1, not 0).

unsigned char Rcon[11] = { 0xff,0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

uint8_t sbox[256] =
{
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

uint8_t inv_sbox[256] =
{
	0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
	0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
	0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
	0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
	0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
	0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
	0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
	0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
	0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
	0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
	0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
	0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
	0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
	0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
	0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

void print_hex(unsigned char* arr, int len)
{
	for (int i = 0; i < len; i++) {
		printf("%02x ", arr[i]);
	}
}

// KeyExpansion(byte key[4*Nk], word w[Nb*(Nr+1)], Nk)
void KeyExpansion(unsigned char key[16], unsigned char w[176]) { //16 bytes in, 44 words out = 176 bytes

	unsigned char temp[4]; //temp word
	unsigned char temp1;

	//for the first 4 words, copy initial key
	//for the first 16 bytes, copy initial key
	for (int i = 0; i < 4; i++) {
		w[(i * 4)] = key[4 * i];
		w[(i * 4) + 1] = key[4 * i + 1];
		w[(i * 4) + 2] = key[4 * i + 2];
		w[(i * 4) + 3] = key[4 * i + 3];
	}

	//for the remaining words
	for (int i = 4; i < 44; i++) {
		temp[0] = w[i * 4 - 4];
		temp[1] = w[i * 4 - 3];
		temp[2] = w[i * 4 - 2];
		temp[3] = w[i * 4 - 1];

		if (i % 4 == 0) {  //for every fourth word

			//The function RotWord() takes a word [a0,a1,a2,a3] as input,
			//performs a cyclic permutation, and returns the word [a1,a2,a3,a0].
			//RotWord(temp)
			temp1 = temp[0];
			temp[0] = temp[1];
			temp[1] = temp[2];
			temp[2] = temp[3];
			temp[3] = temp1;

			//SubWord is a function that takes a four-byte input word
			//and applies the S-box to each of the four bytes to produce an output word. 
			//SubWord(temp)
			temp[0] = sbox[temp[0]];
			temp[1] = sbox[temp[1]];
			temp[2] = sbox[temp[2]];
			temp[3] = sbox[temp[3]];

			temp[0] = temp[0] ^ Rcon[i / 4];
		}

		w[i * 4 + 0] = w[(i - 4) * 4 + 0] ^ temp[0];
		w[i * 4 + 1] = w[(i - 4) * 4 + 1] ^ temp[1];
		w[i * 4 + 2] = w[(i - 4) * 4 + 2] ^ temp[2];
		w[i * 4 + 3] = w[(i - 4) * 4 + 3] ^ temp[3];
	}
}

void SubBytes(unsigned char state[16]) {
	for (int i = 0; i < 16; i++)
		state[i] = sbox[state[i]];
}

void InvSubBytes(unsigned char state[16]) {
	for (int i = 0; i < 16; i++)
		state[i] = inv_sbox[state[i]];
}

void ShiftRows(unsigned char state[16])
{
	unsigned char tmp[16];

	// Column 1
	tmp[0] = state[0];
	tmp[1] = state[5];
	tmp[2] = state[10];
	tmp[3] = state[15];

	// Column 2
	tmp[4] = state[4];
	tmp[5] = state[9];
	tmp[6] = state[14];
	tmp[7] = state[3];

	// Column 3 
	tmp[8] = state[8];
	tmp[9] = state[13];
	tmp[10] = state[2];
	tmp[11] = state[7];

	// Column 4 
	tmp[12] = state[12];
	tmp[13] = state[1];
	tmp[14] = state[6];
	tmp[15] = state[11];

	for (int i = 0; i < 16; i++)
		state[i] = tmp[i];
}

void InvShiftRows(unsigned char state[16]) {

	unsigned char tmp[16];

	/* Column 1 */
	tmp[0] = state[0];
	tmp[1] = state[13];
	tmp[2] = state[10];
	tmp[3] = state[7];

	/* Column 2 */
	tmp[4] = state[4];
	tmp[5] = state[1];
	tmp[6] = state[14];
	tmp[7] = state[11];

	/* Column 3 */
	tmp[8] = state[8];
	tmp[9] = state[5];
	tmp[10] = state[2];
	tmp[11] = state[15];

	/* Column 4 */
	tmp[12] = state[12];
	tmp[13] = state[9];
	tmp[14] = state[6];
	tmp[15] = state[3];

	for (int i = 0; i < 16; i++)
		state[i] = tmp[i];
}

unsigned char xtime(unsigned char  a) // Like a mul 02
{	
	// FIRST CONDITION  If b7 = 0, the result is already in reduced form.  
	// SECOND CONDITION If b7 = 1, the reduction is accomplished by subtracting (i.e., XORing) with 0x1b since 0x1b =00011011. 
	// This works because if x7=1 we xor with 0x1b meaning it is like effectively obtaining the modulo when our answer is >= irreducible polynomial
	unsigned char temp;
	temp = a << 1;

	// First condition
	// 0x80 is 0b10000000
	if ((a & 0x80) != 0) {//last bit of a,x^7, is 1. meaning when we right shift, we get x^s8 which is not acceptable are getting modulo against the irreducible poly which limits the size of the remainder of this operation to being of size 8 bits x^7->x^0
		temp = temp ^ 0x1b;
	}    //note that 0b00011011 is 0x1b
	// Second condition
	return temp;
}

unsigned char GMul(unsigned char  a, unsigned char b)
{
	// Note that this works because we can write {57} � {13} = {57} � ({01} xor {02} xor {10})
	// This means that any 0x13 is wrriten as 00010011=00000001+00000001+00010000
	//we use this notation in the previous line to distribute the multiplicaion on garlois field over multiples of 2 and use our xtime( function efficiently.
	unsigned char temp = a;
	unsigned char res = 0;

	// Conventional loop would run for i=0->8. but my implementation is more efficient because if all bits towards left are 0, then we can quit our loop as result will not be changed
	while ((b & 0xff) != 0)//while b can be shifted more to the right
	{
		if ((b & 0x01) == 0x01)res = res ^ temp;//if lsb of b is 1
		temp = xtime(temp);//keep track  of everytime we call xtime( on mulitples of 2. use the previous multiple of 2 and apply xtime( on it to get the next value.
		b = b >> 1;
	}
	return res;
}

void MixColumns(unsigned char state[16])
{
	/*
	02 03 01 01     s0 s4 s8  s12
	01 02 03 01  .  s1 s5 s9  s13
	01 01 02 03     s2 s6 s10 s14
	03 01 01 02     s3 s7 s11 s15
	*/

	unsigned char tmpM[16];
	tmpM[0] = (xtime(state[0]) ^ GMul(0x03, state[1]) ^ state[2] ^ state[3]);
	tmpM[1] = (state[0] ^ xtime(state[1]) ^ GMul(0x03, state[2]) ^ state[3]);
	tmpM[2] = (state[0] ^ state[1] ^ xtime(state[2]) ^ GMul(0x03, state[3]));
	tmpM[3] = (GMul(0x03, state[0]) ^ state[1] ^ state[2] ^ xtime(state[3]));

	tmpM[4] = (xtime(state[4]) ^ GMul(0x03, state[5]) ^ state[6] ^ state[7]);
	tmpM[5] = (state[4] ^ xtime(state[5]) ^ GMul(0x03, state[6]) ^ state[7]);
	tmpM[6] = (state[4] ^ state[5] ^ xtime(state[6]) ^ GMul(0x03, state[7]));
	tmpM[7] = (GMul(0x03, state[4]) ^ state[5] ^ state[6] ^ xtime(state[7]));

	tmpM[8] = (xtime(state[8]) ^ GMul(0x03, state[9]) ^ state[10] ^ state[11]);
	tmpM[9] = (state[8] ^ xtime(state[9]) ^ GMul(0x03, state[10]) ^ state[11]);
	tmpM[10] = (state[8] ^ state[9] ^ xtime(state[10]) ^ GMul(0x03, state[11]));
	tmpM[11] = (GMul(0x03, state[8]) ^ state[9] ^ state[10] ^ xtime(state[11]));

	tmpM[12] = (xtime(state[12]) ^ GMul(0x03, state[13]) ^ state[14] ^ state[15]);
	tmpM[13] = (state[12] ^ xtime(state[13]) ^ GMul(0x03, state[14]) ^ state[15]);
	tmpM[14] = (state[12] ^ state[13] ^ xtime(state[14]) ^ GMul(0x03, state[15]));
	tmpM[15] = (GMul(0x03, state[12]) ^ state[13] ^ state[14] ^ xtime(state[15]));
	for (int i = 0; i < 16; i++)
		state[i] = tmpM[i];
}

void InvMixColumns(unsigned char state[16])
{
	unsigned char temp_i[16];
	/*
	0e 0b 0d 09     s0 s4 s8  s12
	09 0e 0b 0d  .  s1 s5 s9  s13
	0d 09 0e 0b     s2 s6 s10 s14
	0b 0d 09 0e     s3 s7 s11 s15
	*/
	temp_i[0] = GMul(0x0e, state[0]) ^ GMul(0x0b, state[1]) ^ GMul(0x0d, state[2]) ^ GMul(0x09, state[3]);
	temp_i[1] = GMul(0x09, state[0]) ^ GMul(0x0e, state[1]) ^ GMul(0x0b, state[2]) ^ GMul(0x0d, state[3]);
	temp_i[2] = GMul(0x0d, state[0]) ^ GMul(0x09, state[1]) ^ GMul(0x0e, state[2]) ^ GMul(0x0b, state[3]);
	temp_i[3] = GMul(0x0b, state[0]) ^ GMul(0x0d, state[1]) ^ GMul(0x09, state[2]) ^ GMul(0x0e, state[3]);
	temp_i[4] = GMul(0x0e, state[4]) ^ GMul(0x0b, state[5]) ^ GMul(0x0d, state[6]) ^ GMul(0x09, state[7]);
	temp_i[5] = GMul(0x09, state[4]) ^ GMul(0x0e, state[5]) ^ GMul(0x0b, state[6]) ^ GMul(0x0d, state[7]);
	temp_i[6] = GMul(0x0d, state[4]) ^ GMul(0x09, state[5]) ^ GMul(0x0e, state[6]) ^ GMul(0x0b, state[7]);
	temp_i[7] = GMul(0x0b, state[4]) ^ GMul(0x0d, state[5]) ^ GMul(0x09, state[6]) ^ GMul(0x0e, state[7]);
	temp_i[8] = GMul(0x0e, state[8]) ^ GMul(0x0b, state[9]) ^ GMul(0x0d, state[10]) ^ GMul(0x09, state[11]);
	temp_i[9] = GMul(0x09, state[8]) ^ GMul(0x0e, state[9]) ^ GMul(0x0b, state[10]) ^ GMul(0x0d, state[11]);
	temp_i[10] = GMul(0x0d, state[8]) ^ GMul(0x09, state[9]) ^ GMul(0x0e, state[10]) ^ GMul(0x0b, state[11]);
	temp_i[11] = GMul(0x0b, state[8]) ^ GMul(0x0d, state[9]) ^ GMul(0x09, state[10]) ^ GMul(0x0e, state[11]);
	temp_i[12] = GMul(0x0e, state[12]) ^ GMul(0x0b, state[13]) ^ GMul(0x0d, state[14]) ^ GMul(0x09, state[15]);
	temp_i[13] = GMul(0x09, state[12]) ^ GMul(0x0e, state[13]) ^ GMul(0x0b, state[14]) ^ GMul(0x0d, state[15]);
	temp_i[14] = GMul(0x0d, state[12]) ^ GMul(0x09, state[13]) ^ GMul(0x0e, state[14]) ^ GMul(0x0b, state[15]);
	temp_i[15] = GMul(0x0b, state[12]) ^ GMul(0x0d, state[13]) ^ GMul(0x09, state[14]) ^ GMul(0x0e, state[15]);
	for (int i = 0; i < 16; i++)
	{
		state[i] = temp_i[i];
	}
}

//AddRoundKey() is its own inverse, since it only involves an application of the XOR operation. 
void AddRoundKey(unsigned char state[16], unsigned char roundkey[16]) {
	for (int i = 0; i < 16; i++)
		state[i] = state[i] ^ roundkey[i];
}