#include <iostream>
#include <cmath>

void slice_number(double number, int length, char * output) {
	cout << "Num: " << number << "\n";
	int pos = 0, scale_power = 0;

	double limit = pow(10, length - 1);

	if (number >= limit) number = limit - 1;
	if (number < 0) number = 0;

	if (number < 1) {
		pos = -1;
	} else {
		pos = (int) log10(number);
		if (number < pow(10, pos)) pos--;
	}

	scale_power = length - pos - 2;
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

		pos--;
		pow_pos--;
	}

	cout << "Out Num: " << output << "\n";
	cout << "\n";
}

int main() {
	cout << "Hey bud.\n";

	char out[5];

	for (int p = -10; p < 11; p++) {
/*		for (int n = 0; n < 10; n++) {
			double num = n * pow(10, p);
			slice_number(num, 5, out);
		}/**/
		slice_number(pow(3.15, p), 5, out);

	}/**/


	return 0;
}
