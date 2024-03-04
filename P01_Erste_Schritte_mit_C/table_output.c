#include <stdio.h>

#define NUM_ROWS 8 // Macro to define a constant number for rows

int main() {
	double conversionRate;
	printf("Enter conversion rate (1.00 BTC -> CHF): ");
	// Using & to pass the adress at which the value of 
	// the variable will be stored
	scanf("%lf", &conversionRate); // %lf is format specifier for double

	for (int i = 1; i <= NUM_ROWS; i++) {
		int chf = i * 200;
		// Divide to get converted value
		double btc = chf / conversionRate;
		// Formatting to keep table consistent
		printf("%5d CHF\t<-->\t%0.5f BTC \n", chf, btc);
	}

	return 0;
}
