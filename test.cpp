#include <iostream>
#include <cmath>

using namespace std;

void slice_number(double number, int length, char * output) {
	int pos = 0;

	double limit = pow(10, length - 1);

	if (number >= limit) number = limit - 1;
	if (number < 0) number = 0;

	if (number < 1) {
		pos = -1;
	} else {
		pos = (int) log10(number);
		if (number < pow(10, pos)) pos--;
	}

	int scale_power = length - pos - 2;
	int snip_num = round(number * pow(10, scale_power));

	for(int pow_pos = length - 2, char_pos = 0; char_pos < length; char_pos++) {
		if (pos == -1) {
			output[char_pos] = '.';
			char_pos++;
		}
		if (char_pos >= length) continue;

		double scale = pow(10, pow_pos);
		
		int temp_number = (int) (snip_num / scale);
		snip_num = snip_num - (int) (temp_number * scale);

		output[char_pos] = '0' + temp_number;

		pos--;
		pow_pos--;
	}
	
	output[length] = '\0';
}

int main() {

	for (int p = -10; p < 11; p++) {
		char out[5];
		double num = pow(10, p);
		slice_number(num, sizeof(out) - 1, out);
		
		cout << "Num: " << num << "\n";
		cout << "Out Num: " << out << "\n\n";

	}

	return 0;
}
