void sizes() // These sizes are standard but are not always accurate depending on the compiler
{
	// Integer types, adding unsigned gives one more bit to the actual number (however the negative range is given up)
	char char1 = 'A'; // 1 byte
	short short1 = 10; // 2 bytes
	int int1 = 10; // 4 bytes
	long long1 = 10; // 4 bytes
	long long longLong1 = 10; // 8 bytes

	// Decimal types
	float float1 = 5.5f; // 4 bytes, must append f or else float1 is defined as a double
	double double1 = 5.5; // 8 bytes

	// Boolean
	bool bool1 = true; // 1 byte. 0 == false, 1 == true. However if a bool is assigned to any other number it will be considered true.

	// Getting compiler specific byte sizes of variables
	sizeof(bool);
	sizeof bool;
}
