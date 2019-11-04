#include <iostream>
#include <ctime>
#include <string>
#include <utility>
#include <cstdlib> 
#include <cmath>
using namespace std;

class Weather
{
	public:
		time_t t;
		string day;
		int year;
		double hourlyWeather[23];
		double minTemp_member;
		double maxTemp_member;
		double stdDev_member;
		double averageTemp_member;

		std::pair <double, int> temp_time;
		Weather()
		{
			//initialize array to 0. 
			for (int i = 0; i < 24; i++)
			{
				hourlyWeather[i] = 0;
			} 

			//assign random values to time array for purposes of quickly assigning values
			for(int i = 0; i < 24; ++i)
    		{
        		hourlyWeather[i] = ( std::rand() % 100);
    		}
		}

		pair<double,int> maxTemp(double hourlyWeather[])
		{
			pair<double, int> maxPair;
			int maxPosition = 0;
			int maxTemp = hourlyWeather[0];

			for (int i = 0; i < 24; i++)
			{
				if (maxTemp < hourlyWeather[i])
				{
					maxTemp = hourlyWeather[i];
					maxPosition = i + 1;
				}
				
			}
			maxPair.first = maxTemp;
			maxTemp_member = maxPair.first;
			maxPair.second = maxPosition;
			cout << "Max Temp: " << maxPair.first << " | Hour :" << maxPair.second << endl;
			return maxPair;
		}	

		pair<double,int> minTemp(double hourlyWeather[])
		{
			pair<double,int> minPair;
			int minPosition = 0;
			int minTemp = hourlyWeather[0];

			for (int i = 0; i < 24; i++)
			{
				if (minTemp > hourlyWeather[i])
				{
					minTemp = hourlyWeather[i];
					minPosition = i + 1;
				}
			}
			minPair.first = minTemp;
			minTemp_member = minPair.first;
			minPair.second = minPosition;
			cout << "Min Temp: " << minPair.first << " | Hour :" << minPair.second << endl;
			return minPair;

		}
		
		double averageDailyTemp(double hourlyWeather[])
		{
			double total = 0;
			for (int i = 0; i < 24; i++)
			{
				total = hourlyWeather[i] + total;
			}

			double average = total / 24;
			averageTemp_member = average;
			return average;
		}

		double standardDeviationDaily(double hourlyWeather[])
		{
			double average = averageDailyTemp(hourlyWeather);
			double residual = 0;
			double residualSum = 0;
			for (int i = 0; i < 24; i++)
			{
				residual = pow(hourlyWeather[i] - average, 2);
				/*cout << hourlyWeather[i] << " - " << average << endl;
				cout << "i: " << i << endl;
				cout << "residual: " << residual << endl;*/
				residualSum = residual + residualSum;
				//cout << "residualSum: " << residualSum << endl;
				
			}

			//mean of residuals
			double stdDev = sqrt(residualSum / 24);
			stdDev_member = stdDev;
			return stdDev;
		}

		void updateHourlyWeather()
		{
			cout << "How many hours do you want to update?" << endl;
			int numHoursToUpdate = 0;
			if (numHoursToUpdate < 0 || numHoursToUpdate > 24)
			{
				cout << "Too few or too many hours to update" << endl;
				updateHourlyWeather();
			}
			cin >> numHoursToUpdate;
			cout << "You entered " << numHoursToUpdate << " hours" << endl;

			for (int i = 0; i < numHoursToUpdate; i++)
			{
				cout << "Which hour do you want to update (pick between 0 and 23 inclusive" << endl;
				int hourToUpdate;
				cin >> hourToUpdate;
				while (hourToUpdate < 0 || hourToUpdate > 24)
				{
					cout << "Hours are out of bounds, enter between 0 and 23" << endl;
					cin >> hourToUpdate;
				}
				double updatedValue;
				cout << "Enter value you want to update hour to" << endl;
				cin >> updatedValue;
				hourlyWeather[hourToUpdate] = updatedValue;
			}
		}

		void printWeatherReport()
		{
			cout << "Minimum temperature for day:               " << minTemp_member << endl;
			cout << "Maximum temperature for day:               " << maxTemp_member << endl;
			cout << "Averge temperature for day:                " << averageTemp_member << endl;
			cout << "Standard deviation of temperature for day: " << stdDev_member << endl;
			cout << "Hour                   Temperature" << endl;
			for (int i = 0; i<24; i++)
			{
				cout << i << "                          " << hourlyWeather[i] << endl;
			}
		}
		
};

int main()
{
	time_t t;
    Weather w; //random numbers assigned to temperature in constructor for the sake of this assignment
    
    //calcuate data for report

    w.maxTemp(w.hourlyWeather);
    w.minTemp(w.hourlyWeather);
    cout << w.averageDailyTemp(w.hourlyWeather) << endl;
    cout << w.standardDeviationDaily(w.hourlyWeather) << endl;

    //end calculations

    //start printing report
    auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
    cout << "Report for: " << ctime(&timenow) << endl;
    w.printWeatherReport(); 

}