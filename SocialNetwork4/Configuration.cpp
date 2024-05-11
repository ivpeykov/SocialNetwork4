#include "Configuration.h"

const short Configuration::MAX_DIGITS_INPUT = calculate_MAX_DIGITS_INPUT();

constexpr short Configuration::calculate_MAX_DIGITS_INPUT()
{
	int count = 0;

	size_t num = SIZE_MAX;

	// Increment count until num becomes zero
	while (num != 0) {
		num /= 10; 
		count++;  
	}

	return count;
}
