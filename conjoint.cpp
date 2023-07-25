#include <bits/stdc++.h>
using namespace std;
// #define int long long
int j = 0;
// Defining the registers and hardware
int PC = 0, MAR = 0, TMP = 0, MDR = 0, SP = 4096, A = 4, B = 8;
int Indirect = 0;
string opCode;
int addr = 0;
long long int H = 0;
// Defining Flags
int N = 0, Z = 0, C = 0, F = 0;
// Defining RAM
map<int, int> RAM;
string inst = "";
// Initializing the RAM
void initializeRAM() {
	for (int i = 0; i < 4096; i++) {
		RAM[i] = 0;
	}
	// Giving random values to check functionality
	RAM[100] = 9;
	RAM[9] = 14;
	RAM[102] = 7;
	RAM[104] = 102;
	// RAM[5] = 4;
	RAM[105] = 26;
	RAM[130] = 200;
	// RAM[9]=2;
}
// Mapping String Opcodes to their decimal values
map<string, int> IR;
void initializeOpCode() {
	IR["ADD"] = 0;
	IR["SUB"] = 1;
	IR["LDA"] = 2;
	IR["STA"] = 3;
	IR["ROR"] = 30;
	IR["ROL"] = 29;
	IR["ASR"] = 28;
	IR["RRX"] = 27;
	IR["PUSH"] = 26;
	IR["POP"] = 21;
	IR["ADI"] = 25;
	IR["SBI"] = 24;
	IR["CPI"] = 23;
	IR["LDI"] = 22;
	IR["RLX"] = 20;
	// NON - MRI Instructions
	IR["ADDN"] = 31;
	IR["SUBN"] = 31;
	IR["MOV"] = 31;
	IR["SWAP"] = 31;
	IR["CMP"] = 31;
	IR["CM"] = 31;
	IR["CL"] = 31;
	IR["DIV"] = 31;
	IR["MUL"] = 31;
}

void spacing() {
	cout << endl;
	cout << endl;
}

void ramInterrupt() {
	cout << "Interrupt Has occured" << endl;
	cout << "Handling the Interrupt: " << endl;
	cout << "Since given addr is out of bound of RAM size" << endl;
	cout << "Take modulo ram size to truncate the given addr" << endl;
	TMP %= 4096;
	cout << "Value in TMP after handling interrupt: " << TMP << endl;
	cout << "In this way the interrupt is handled" << endl;
	cout << "Resetting the Interrupt Flag......." << endl;
	F = 0;
	cout << "Interrupt Flag: " << F << endl;
}

void decode() {
	istringstream ss(inst);
	string word;
	vector<string> v;
	while (ss >> word) {
		v.push_back(word);
	}
	Indirect = stoi(v[0]);
	if (v.size() > 1)
		opCode = v[1];
	// opCode = opCode & 31;
	if (v.size() > 2) {
		TMP = stoi(v[2]);
		if (TMP > 4095) {
			F = 1;
			cout << "Interrupt Flag: " << F << endl;
			ramInterrupt();
		}
	}
}
void fetch() {
	// T0
	spacing();
	cout << "Fetch:" << endl;
	cout << "PC enabled and MAR enabled and loaded" << endl;
	MAR = PC;
	// T1
	cout << "RAM enabled and MDR loaded, PC Incremented" << endl;
	PC++;
	cout << "MAR:" << MAR << endl;
	cout << "PC: " << PC << endl;
	cout << "Accumulator: " << A << endl;
	cout << "Register B: " << B << endl;
	// T2
	decode();
	spacing();
	cout << "<------Decoding:------->" << endl;
	cout << "Address loaded in TMP register and opcode loaded in IR" << endl;
	cout << "I/D Bit:" << Indirect << endl;
	cout << "IR: " << IR[opCode] << endl;
	cout << "TMP: " << TMP << endl;
	// cout << "This is the opcode" << opCode << endl;
	// cout << "THis is the IR matching" << IR[opCode] << endl;
	spacing();
}

void ADD() {
	spacing();
	cout << "Given OP code is for MRI ADD Instruction" << endl;
	cout << "<-----MRI ADD Instruction Execution------>" << endl;
	cout << endl;
	if (!Indirect) {
		// T3
		cout << "   Direct ADD operation: " << endl;
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "RAM enabled and value loaded into TMP register" << endl;
		TMP = RAM[MAR];
		cout << "Accumulator value added to TMP register and result stored in "
		     "Accumulator"
		     << endl;
		A = A + TMP;
	} else {
		// T3
		cout << "    Indirect ADD operation:   " << endl;
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "RAM enabled and address loaded into TMP register" << endl;
		TMP = RAM[MAR];
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "RAM enabled and value loaded into TMP register" << endl;
		TMP = RAM[MAR];
		cout << "Accumulator value added to TMP register and result stored in "
		     "Accumulator"
		     << endl;
		A = A + TMP;
	}
	C = A >> 18; // Works or not???
	if (C == 1)
		C = 1;
	else
		C = 0;
	if (A == 0)
		Z = 1;
	else
		Z = 0;
	if (A < 0)
		N = 1;
	else
		N = 0;
	A &= 262143;
	cout << "MAR: " << MAR << endl;
	cout << "TMP: " << TMP << endl;
	cout << "Final Value of Accumulator: " << A << endl;
	cout << "Carry Flag: " << C << endl;
	cout << "Zero Flag: " << Z << endl;
	cout << "Negative Flag: " << N << endl;
}

void SUB() {
	spacing();
	cout << "Given OP code is for SUB instruction" << endl;
	cout << "<-----SUB Instruction Execution------>" << endl;
	if (Indirect == 0) {
		cout << "   Direct Subtration Operation   " << endl;
		// T3
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "RAM enabled and value loaded into TMP register" << endl;
		TMP = RAM[MAR];
		cout << "TMP register subtracted from accumulator and result stored in "
		     "Accumulator"
		     << endl;
		A = A - TMP;
	} else if (Indirect == 1) {
		cout << "   Indirect Subtration Operation   " << endl;
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "RAM enabled and address loaded into TMP register" << endl;
		TMP = RAM[MAR];
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "RAM enabled and value loaded into TMP register" << endl;
		TMP = RAM[MAR];
		cout << "TMP register subtracted from accumulator and result stored in "
		     "Accumulator"
		     << endl;
		A = A - TMP;
	}
	C = A >> 18;
	if (C == 1)
		C = 1;
	else
		C = 0;
	if (A < 0)
		N = 1;
	else
		N = 0;
	if (A == 0)
		Z = 1;
	else
		Z = 0;
	A &= 262143;
	cout << "Value at the address: " << TMP << endl;
	cout << "Final Value of Accumulator: " << A << endl;
	cout << "Carry Flag: " << C << endl;
	cout << "Zero Flag: " << Z << endl;
	cout << "Negative Flag: " << N << endl;
}

void LDA() {
	spacing();
	cout << "Given OP code is for LDA Instruction" << endl;
	cout << "<----LDA instruction Execution--->" << endl;
	if (!Indirect) {
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "RAM enabled and Accumulator loaded" << endl;
		A = RAM[MAR];
	} else {
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "RAM enabled and TMP loaded" << endl;
		TMP = RAM[MAR];
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "RAM enabled and Accumulator loaded" << endl;
		A = RAM[MAR];
	}
	if (A == 0)
		Z = 1;
	cout << "MAR: " << MAR << endl;
	cout << "Value in given Address: " << RAM[MAR] << endl;
	cout << "Accumulator: " << A << endl;
	cout << "Z flag: " << Z << endl;
}

void STA() {
	spacing();
	cout << "Given OP code is for STA Instruction" << endl;
	cout << "<---- STA Instruction Execution ---->" << endl;
	if (!Indirect) {
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "Accumulator enabled and RAM loaded" << endl;
		RAM[MAR] = A;
	} else {
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "RAM enabled and TMP laoded" << endl;
		TMP = RAM[MAR];
		cout << "TMP enabled and MAR enabled and loaded" << endl;
		MAR = TMP;
		cout << "Accumulator enabled and RAM loaded" << endl;
		RAM[MAR] = A;
	}
	cout << "Accumulator: " << A << endl;
	cout << "Value in the address " << MAR << ":" << RAM[MAR] << endl;
}

// void BUN() {
// 	spacing();
// 	cout << "Given OP code is for BUN Instruction" << endl;
// 	cout << "<-------BUN Instruction Execution------>" << endl;
// 	if (!Indirect) {
// 		cout << "TMP enabled and PC loaded" << endl;
// 		PC = TMP;
// 	} else {
// 		cout << "TMP enabled and MAR enabled and loaded" << endl;
// 		MAR = TMP;
// 		cout << "RAM enabled and TMP loaded" << endl;
// 		TMP = RAM[MAR];
// 		cout << "TMP enabled and PC loaded" << endl;
// 	}
// 	j = PC;
// 	cout << "PC: " << PC << endl;
// 	cout << "MAR: " << MAR << endl;
// 	cout << "TMP: " << TMP << endl;
// }

// NON-MRI instructions functions
void ADDN() {
	cout << "Given OP Code is for NON-MRI ADD Instruction" << endl;
	cout << "<---NON-MRI ADD Instruction Execution--->" << endl;
	cout << endl;
	if (Indirect == 0) {
		cout << "<---Adding A to A and storing the result in A--->" << endl;
		cout << "Initial Value of Accumulator: " << A << endl;
		A = A + A;

	} else {
		cout << "<---Adding A to B and storing the result in A" << endl;
		cout << "Initial Value of Accumulator: " << A << endl;
		cout << "Initial Value of register B: " << B << endl;
		A = A + B;
	}
	C = A >> 18;
	if (C == 1)
		C = 1;
	else
		C = 0;
	if (A == 0)
		Z = 1;
	else
		Z = 0;
	if (A < 0)
		N = 1;
	else
		N = 0;
	A &= 262143;

	cout << "Final Value of Accumulator: " << A << endl;
	cout << "Carry Flag: " << C << endl;
	cout << "Zero Flag: " << Z << endl;
	cout << "Negative Flag: " << N << endl;
}

void SUBN() {
	cout << "Given OP Code is for NON-MRI SUB Instruction" << endl;
	cout << "<---NON-MRI SUB Instruction Execution--->" << endl;
	cout << endl;
	if (Indirect == 0) {
		cout << "<---Subtracting A from B and storing the result in A--->" << endl;
		cout << "Initial Value of Accumulator: " << A << endl;
		cout << "Initial Value of register B: " << B << endl;
		A = B - A;

	} else {
		cout << "<---Subtracting register B from A and storing the result in A"
		     << endl;
		cout << "Initial Value of Accumulator: " << A << endl;
		cout << "Initial Value of register B: " << B << endl;
		A = A - B;
	}
	C = A >> 18;
	if (C == 1)
		C = 1;
	else
		C = 0;
	if (A < 0)
		N = 1;
	else
		N = 0;
	if (A == 0)
		Z = 1;
	else
		Z = 0;
	A &= 262143;

	cout << "Final Value of Accumulator: " << A << endl;
	cout << "Carry Flag: " << C << endl;
	cout << "Zero Flag: " << Z << endl;
	cout << "Negative Flag: " << N << endl;
}

void MOV() {
	cout << "Given OP Code is for NON-MRI MOV Instruction" << endl;
	cout << "<---NON-MRI MOV Instruction Execution--->" << endl;
	cout << endl;
	if (Indirect == 0) {
		cout << "<----Moving B to A--->" << endl;
		cout << "Register B enabled and Accumulator loaded" << endl;
		cout << "Initial Value of register B: " << B << endl;
		cout << "Initial Value of Accumulator: " << A << endl;
		A = B;
	} else {
		cout << "<----Moving A to B--->" << endl;
		cout << "Accumulator enabled and register B loaded" << endl;
		cout << "Initial Value of register B: " << B << endl;
		cout << "Initial Value of Accumulator: " << A << endl;
		B = A;
	}
	// if()
	cout << "Final Value of Accumulator: " << A << endl;
	cout << "Final Value of register B: " << B << endl;
}

void SWAP() {
	cout << "Given OP Code is for NON-MRI SWAP Instruction" << endl;
	cout << "<---NON-MRI SWAP Instruction Execution--->" << endl;
	cout << endl;
	cout << "Accumulator enabled and TMP register loaded" << endl;
	TMP = A;
	cout << "Accumulator: " << A << endl;
	cout << "TMP: " << TMP << endl;
	cout << "B register enabled and Accumulator loaded" << endl;
	A = B;
	cout << "B: " << B << endl;
	cout << "A: " << A << endl;
	cout << "TMP register enabled and B register loaded" << endl;
	B = TMP;
	cout << "TMP: " << TMP << endl;
	cout << "B: " << B << endl;
	cout << "Final Value in A after swapping: " << A << endl;
	cout << "Final Value in B after swapping: " << B << endl;
}

void CMP() {
	cout << "Given OP Code is for NON-MRI CMP Instruction" << endl;
	cout << "<---NON-MRI CMP Instruction Execution--->" << endl;
	cout << endl;
	C = 0, Z = 0;

	if (A < B)
		C = 1;
	else if (A == B)
		Z = 1;
	cout << "Value of Accumulator: " << A << endl;
	cout << "Value of register B: " << B << endl;
	cout << "Carry Flag: " << C << endl;
	cout << "Zero Flag: " << Z << endl;
}

void CL() {
	cout << "Given OP Code is for NON-MRI CLEAR Instruction" << endl;
	cout << "<---NON-MRI CL Instruction Execution--->" << endl;
	cout << endl;
	if (Indirect == 0) {
		cout << "Clearing the Value of Accumulator" << endl;
		cout << "Initial Value of Accumulator: " << A << endl;
		A = 0;
		cout << "Final Value of Accumulator: " << A << endl;
	} else {
		cout << "Clearing the Value of register B" << endl;
		cout << "Initial Value of register B: " << B << endl;
		B = 0;
		cout << "Final Value of register B: " << B << endl;
	}
	if (A == 0)
		Z = 1;
	else
		Z = 0;
	cout << "Z flag: " << Z << endl;
}

void CM() {
	cout << "Given OP Code is for NON-MRI Complement Instruction" << endl;
	cout << "<---NON-MRI CM Instruction Execution--->" << endl;
	cout << endl;
	if (Indirect == 0) {
		cout << "Complement Of Accumulator" << endl;
		cout << "Initial Value of Accumulator: " << A << endl;
		for (int i = 0; i < 18; i++) {
			if ((1 << i) & (A)) {
				A &= ~(1 << i);
			} else
				A |= (1 << i);
		}
		cout << "Final Value of Accumulator: " << A << endl;
	} else {
		cout << "Complement Of register B" << endl;
		cout << "Initial Value of register B: " << B << endl;
		for (int i = 0; i < 18; i++) {
			if ((1 << i) & (B)) {
				B &= ~(1 << i);
			} else
				B |= (1 << i);
		}
		cout << "Final Value of register B: " << B << endl;
	}
	if (A == 0)
		Z = 1;
	else
		Z = 0;
	cout << "Z flag: " << Z << endl;
}

// Immediate Addresssing
void rotInterrupt() {
	cout << "Interrupt Has occured" << endl;
	cout << "Handling the Interrupt: " << endl;
	cout << "Since rotations are more than the rotations possible by barrel "
	     "shifter"
	     << endl;
	cout << "Take modulo 3 to the no of rotations given" << endl;
	TMP %= 3;
	cout << "No. of rotations after handling interrupt: " << TMP << endl;
	cout << "In this way the interrupt is handled" << endl;
	cout << "Resetting the Interrupt Flag......." << endl;
	F = 0;
	cout << "Interrupt Flag: " << F << endl;
}
void ROR() {
	cout << "Given OP Code is for Immediate ROR Instruction" << endl;
	cout << "<---Immediate ROR Instruction--->" << endl;
	cout << "Given number of rotations: " << TMP << endl;
	cout << "Initial Value of Accumulator: " << A << endl;

	if (TMP > 3) {
		F = 1;
		cout << "Interrupt Flag: " << F << endl;
		rotInterrupt();
	}
	int t = TMP;
	for (int i = 0; i < t; i++) {
		int temp = (1 << 0) & A;
		A = A >> 1;
		if (temp) {
			A |= (1 << 17);
		} else
			A &= ~(1 << 17);
	}
	cout << "Final Value of Accumulator after performing " << TMP
	     << " right rotations: " << A << endl;
	if (A == 0)
		Z = 1;
	cout << "Zero Flag: " << Z << endl;
}

void ROL() {
	cout << "Given OP Code for Immediate ROL Instruction" << endl;
	cout << "<---Immediate ROL Instruction Execution--->" << endl;
	cout << endl;
	cout << "Given number of rotations: " << TMP << endl;
	cout << "Initial Value of Accumulator: " << A << endl;

	if (TMP > 3) {
		F = 1;
		cout << "Interrupt Flag: " << F << endl;
		rotInterrupt();
	}
	int t = TMP;
	for (int i = 0; i < t; i++) {
		int temp = (1 << 17) & A;
		A = A << 1;
		if (temp) {
			A |= (1 << 0);
		} else
			A &= ~(1 << 0);
	}
	A &= 262143;
	cout << "Final Value of Accumulator after performing " << TMP
	     << " left rotations: " << A << endl;
	if (A == 0)
		Z = 1;
	cout << "Zero Flag: " << Z << endl;
}

void ASR() {
	cout << "Given OP Code is for Immediate ASR Instruction" << endl;
	cout << "<---Immediate ASR Instruction Execution--->" << endl;
	cout << endl;
	cout << "Given number of rotations: " << TMP << endl;
	cout << "Initial Value of Accumulator: " << A << endl;
	if (TMP > 3) {
		F = 1;
		cout << "Interrupt Flag: " << F << endl;
		rotInterrupt();
	}
	int t = TMP;
	int temp = (1 << 17) & A;
	for (int i = 0; i < t; i++) {
		A = A >> 1;
		if (temp) {
			A |= (1 << 17);
		} else
			A &= ~(1 << 17);
	}
	cout << "Final Value of Accumulator after performing " << TMP
	     << " right rotations: " << A << endl;
	if (A == 0)
		Z = 1;
	cout << "Zero Flag: " << Z << endl;
}

void RRX() {
	cout << "Given OP Code is for Immediate RRX Instruction" << endl;
	cout << "<---Immediate RRX Instruction Execution--->" << endl;
	cout << endl;
	cout << "Initial Value of Accumulator: " << A << endl;
	cout << "Initial Value of Carry Flag: " << C << endl;
	int temp = (1 << 0) & A;
	int temp2 = C;
	C = temp ? 1 : 0;
	A = A >> 1;
	if (temp2) {
		A |= (1 << 17);
	} else
		A &= ~(1 << 17);

	cout << "Final Value of Accumulator: " << A << endl;
	cout << "Final Value of Carry Flag: " << C << endl;
}

void RLX() {
	cout << "Given OP Code is for Immediate RLX Instruction" << endl;
	cout << "<---Immediate RLX Instruction Execution--->" << endl;
	cout << endl;
	cout << "Initial Value of Accumulator: " << A << endl;
	cout << "Initial Value of Carry Flag: " << C << endl;
	int temp = (1 << 17) & A;
	int temp2 = C;
	C = temp ? 1 : 0;
	A = A << 1;
	if (temp2) {
		A |= (1 << 0);
	} else
		A &= ~(1 << 0);
	A &= 262143;
	cout << "Final Value of Accumulator: " << A << endl;
	cout << "Final Value of Carry Flag: " << C << endl;
}

void PUSH() {
	cout << "Given OP Code is for Immediate PUSH Instruction" << endl;
	cout << "<---Immediate PUSH Instruction Execution--->" << endl;
	cout << endl;
	cout << "Initial Address of Stack Pointer: " << SP << endl;
	SP--;
	RAM[SP] = TMP;
	cout << "Final Address of Stack Pointer: " << SP << endl;
	cout << "Value at the address pointed by Stack Pointer: " << RAM[SP] << endl;
}

void POP() {
	cout << "Given OP Code is for POP Instruction" << endl;
	cout << "<---POP Instruction Execution--->" << endl;
	cout << endl;
	cout << "Initial Address of Stack Pointer: " << SP << endl;
	cout << "Value at this Address: " << RAM[SP] << endl;
	A = RAM[SP];
	SP++;
	cout << "Final Address of Stack Pointer: " << SP << endl;
	cout << "Popped Value is Stored in Accumulator" << endl;
	cout << "Value in Accumulator: " << A << endl;
	if (A == 0)
		Z = 1;
	else
		Z = 0;
	cout << "Z Flag: " << Z << endl;
}

void ADI() {
	cout << "Given OP Code is for Immediate ADD Instruction" << endl;
	cout << "<---Immediate ADD Instruction Execution--->" << endl;
	cout << endl;
	A += TMP;
	if ((1 << 18) & A) {
		C = 1;
	}
	A &= 262143;
	cout << "Value in the Accumulator after Addition: " << A << endl;
	cout << "Carry Flag: " << C << endl;
}

void SBI() {
	cout << "Given OP Code is for Immediate SBI Instruction" << endl;
	cout << "<---Immediate SBI Instruction Execution--->" << endl;
	cout << endl;
	A -= TMP;
	if (A < 0)
		N = 1;
	else
		N = 0;
	if (A == 0)
		Z = 1;
	else
		Z = 0;
	A &= 262143;
	cout << "Value in Accumulator after Subtration: " << A << endl;
	cout << "Zero Flag: " << Z << endl;
	cout << "Negative Flag: " << N << endl;
}

void CPI() {
	cout << "Given OP Code is for Immediate Compare Instruction" << endl;
	cout << "<---Immediate CPI Instruction Execution--->" << endl;
	cout << endl;
	if (A < TMP)
		C = 1;
	else if (A > TMP)
		C = 0;
	if (A == TMP)
		Z = 1;
	else
		Z = 0;
	cout << "Value of Accumulator: " << A << endl;
	cout << "Value of given Immediate Value: " << TMP << endl;
	cout << "Carry Flag: " << C << endl;
	cout << "Zero Flag: " << Z << endl;
}

void LDI() {
	cout << "Given OP Code is for Immediate LDI Instruction" << endl;
	cout << "<---Immediate LDI Instruction Execution--->" << endl;
	cout << endl;

	A = TMP;

	if (A == 0)
		Z = 1;
	else
		Z = 0;
	if (A < 0)
		N = 1;
	else
		N = 0;
	cout << "Value of Immediate Value given: " << TMP << endl;
	cout << "Value of Accumulator: " << A << endl;
	cout << "Zero Flag: " << Z << endl;
	cout << "Negative Flag: " << N << endl;
}

void MUL() {
	cout << "Given OP Code is for MUL Instruction" << endl;
	cout << "<---MUL Instruction Execution--->" << endl;
	cout << endl;

	if (Indirect == 0) {
		cout << "Multiplying A to A" << endl;
		cout << "Value in Accumulator: " << A << endl;
		H = A * A;
	} else {
		cout << "Multiplying A to B" << endl;
		cout << "Value in Accumulator: " << A << endl;
		cout << "Value in register B: " << B << endl;
		H = A * B;
	}
	H &= 68719476735;
	cout << "Final result after Multiplying: " << H << endl;
	cout << "Value in register H: " << H << endl;
	C = H >> 36;
	if (C == 1)
		C = 1;
	else
		C = 0;
	cout << "Carry Flag: " << C << endl;
}

void divAInterrupt()
{

	cout << "Interrupt Has occured" << endl;
	cout << "Handling the Interrupt: " << endl;
	cout << "Since A=0 and we cannot divide by zero, we increment A to 1" << endl;
	A = A + 1;
	cout << "Value in Accumulator after incrementing: " << A << endl;
	cout << "Now dividing B by A i.e; dividing A by 1" << endl;
	cout << "In this way the interrupt is handled" << endl;
	cout << "Resetting the Interrupt Flag......." << endl;
	F = 0;
	cout << "Interrupt Flag: " << F << endl;
}

void divBInterrupt() {
	cout << "Interrupt Has occured" << endl;
	cout << "Handling the Interrupt: " << endl;
	cout << "Since B=0 and we cannot divide by zero, we increment B to 1" << endl;
	B = B + 1;
	cout << "Value in register B after incrementing: " << B << endl;
	cout << "Now dividing A by B i.e; dividing A by 1" << endl;
	cout << "In this way the interrupt is handled" << endl;
	cout << "Resetting the Interrupt Flag......." << endl;
	F = 0;
	cout << "Interrupt Flag: " << F << endl;
}

void DIV() {
	cout << "Given OP Code is for DIV Instruction" << endl;
	cout << "<---DIV Instruction Execution--->" << endl;
	cout << endl;
	cout << "Accumulator initial Value: " << A << endl;
	cout << "Register B initial Value: " << B << endl;
	if (Indirect == 0) {
		if (A == 0) {
			F = 1;

			cout << "Interrupt Flag: " << F << endl;
			divAInterrupt();
		}
		cout << "Dividing B by A" << endl;
		A = B / A;

	} else {
		if (B == 0) {
			F = 1;
			cout << "Interrupt Flag: " << F << endl;
			divBInterrupt();
		}
		cout << "Dividing A by B" << endl;
		A /= B;
	}
	cout << "Value of Accumulator after dividing: " << A << endl;
}
// NON-MRI operation From here
void NON_MRI() {
	switch (TMP) {
	case 0:
		ADDN();
		break;
	case 1:
		SUBN();
		break;
	case 2:
		MOV();
		break;
	case 4:
		SWAP();
		break;
	case 8:
		CMP();
		break;
	case 16:
		CL();
		break;
	case 32:
		CM();
		break;
	case 64:
		DIV();
		break;
	case 128:
		MUL();
		break;
	}
}

void operation() {
	while (1) {
		getline(cin, inst);
		if (inst == "HLT")
			break;

		// cout<<inst;
		// cout << Indirect << endl;
		// cout << opCode << endl;
		// cout << addr << endl;

		fetch();
		if (IR[opCode] == 31)
			NON_MRI();
		// cout << IR[opCode] << endl;
		else {
			switch (IR[opCode]) {
			case 0:
				ADD();
				break;
			case 1:
				SUB();
				break;
			case 2:
				LDA();
				break;
			case 3:
				STA();
				break;
			case 4:
				break;
			case 30:
				ROR();
				break;
			case 29:
				ROL();
				break;
			case 28:
				ASR();
				break;
			case 27:
				RRX();
				break;
			case 26:
				PUSH();
				break;
			case 21:
				POP();
				break;
			case 25:
				ADI();
				break;
			case 24:
				SBI();
				break;
			case 23:
				CPI();
				break;
			case 22:
				LDI();
				break;
			case 20:
				RLX();
				break;

			}
		}
		// }
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "          Program Execution Completed" << endl;
	cout << "                  Thank You          " << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	initializeRAM();
	initializeOpCode();
	operation();
	// return 0;
}