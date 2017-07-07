//////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~Code for Data Manipulation
//~~~~~~~~~~~~~~~~~~~~~~~~ By Arpita Tugave
///////////////////////////////////////////////////
#include<iostream>
#include <iomanip> 
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
using namespace std;

// functions
//note : no other functions are inline make all processing inline and thus the code runs faster
inline void Rectangle_i(const int n);

inline double round_func(double val)
{
	int return_val = (val * 1000);
	double diff = (val*1000) - (double)return_val;
	if (diff > 0.45) return ((val*1000)/1000) + 0.001;
	return (val * 1000) / 1000;
}

//Rectangle fucntion to process Q1, Q2 and Q3	
void Rectangle_i(const int n){

	//////////////////////////////////////////////////////////////extract axb values as of Q1
	const int m = 50; //grid size
	int ab_array[2][8]; // not generalized as grid size and rectangle size is fixed; else use linked list
	int ab_array_count = 0, j_min = n, j_max = n/2+1;

	//logic: see if a factor then find b from a+1 to previous b; code optimization
	for (int i = 1; i < j_min; i++){
		if (n%i == 0){
			if (i == 1){
				ab_array[0][ab_array_count] = i;
				ab_array[1][ab_array_count] = n;
				ab_array_count++;
			}
			else{
				for (int j = i + 1; j < j_max; j++){
					if (i*j == n){
						ab_array[0][ab_array_count] = i;
						ab_array[1][ab_array_count] = j;
						j_min = j; j_max = n / i;
						ab_array_count++;
					}
				}
			}
		}
	}
	
	// Time taken till Q1: 0 seconds

	////////////////////////////////////////////////////////////// Q2
	//formula : Given NXN grid, number of rectangles of size axb = (N-a+1) * (N-b+1);
	//code optimization: combine with the code to produce mirror axb values

	//considering bxa for corresponding axb 
	//Q1. answer
	cout << "Q1 : Possible values for a : ";
	double rectangle_number = 0;
	int half_array_count = ab_array_count;
	for (int i = 0, j = half_array_count; i < half_array_count; i++, j++){
		ab_array[0][j] = ab_array[1][i];
		ab_array[1][j] = ab_array[0][i];
		cout << ab_array[0][i] << " " << ab_array[0][j] << " ";
		//cout << ab_array[0][i] << " " << ab_array[1][i] << endl;
		//cout << ((50 - ab_array[0][i] + 1) * (50 - ab_array[1][i] + 1)) << endl;
		rectangle_number = ((m - ab_array[0][i] + 1) * (m - ab_array[1][i] + 1)) + rectangle_number;
		ab_array_count++;
	}
	//Q2. answer
	cout << endl;
	cout << "Q2 : Number of rectangles of area 30 in 50x50 grid: " << (2*rectangle_number) << endl;

	// Time taken till Q1: 0.005 seconds

	//////////////////////////////////////////////////////////////extract data from csv file
	// In order to reduce computation let us calculate solution to Q3, along with extracting data
	// Question 3 will be solved based on specific pattern found in the data
	//pattern : 1 2 3 4 5 - - - n - - - 5 4 3 2 1 will be the row border of nx- rectangle
	// establish this pattern on both sides, then for middle cells it is just product of these end rows and columns.
	int i = 0, j = 0; //defines rows and columns
	double grid_data[m][m]; //extract grid data
	ifstream data("grid.csv"); // declare file stream: 

	string line;
	double i_mul; // pattern multiplier
	double j_mul;
	//double sum = 0;
	double total = 0.0;
	double value_0 = 0.0, value_1 = 0.0;
	while (getline(data, line))
	{
		stringstream  lineStream(line);
		string        cell;
		string::size_type sz;

		while (std::getline(lineStream, cell, ','))
		{
			//arrange data into 2 dimensional array
			if (i == m) {
				i = 0; j++; //cout << cell << " " << j << endl; 
			}
			grid_data[i][j] = stod(cell, &sz); //convert from string to double
			//sum = sum + grid_data[i][j];

			for (int k = 0; k < ab_array_count; k++){
				//cout << ab_array[0][k] << " " << ab_array[1][k] << endl;
				if (ab_array[0][k] > m / 2) value_0 = m - ab_array[0][k] + 1;
				if (ab_array[1][k] > m / 2) value_1 = m - ab_array[1][k] + 1;
				((i + 1) <= 50 / 2) ? ((i + 1 >= value_1) ? (i_mul = value_1)
					: (i_mul = (double)i + 1)) : (50 - i <= value_1) ? (i_mul = (double)50 - i) : (i_mul = value_1);
				((j + 1) <= 50 / 2) ? ((j + 1 >= value_0) ? (j_mul = value_0)
					: (j_mul = (double)j + 1)) : (50 - j <= value_0) ? (j_mul = (double)50 - j) : (j_mul = value_0);
				total = total + (i_mul * j_mul * grid_data[i][j]);
			}
			i++;
		}
	}

	// you get 51,338.793 for 1x30 ; verified 
	// to get accurately 3 decimal digits as per the requirement
	//int round = (round_func(sum / 2500) * 1000);
	//cout << (double)round / 1000 << endl; // you get value as 49.045;

	//printf("%f \n", total / (2 * rectangle_number * 30.0));
	double sum = total / (2 * rectangle_number * 30.0);
	int round = (round_func(sum) * 1000);
	// Q3 : answer
	cout << "Q3 : The mean of the means of all the rectangles: " << (double)round / 1000 << endl; 

	/////////////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////// Main fucntion
int main(int argc, char *argv[]){

	clock_t begin = clock();

	/////////////////////////////////////////////////////run fucntion Rectangle_i
	
	Rectangle_i(30); 
	
	clock_t end = clock();

	cout << "Code takes: " << double(end - begin) / CLOCKS_PER_SEC << " seconds" << endl;
	
	return 0;
}
