#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <list>
#include <iostream>
#include "CovidCollection.h"
namespace sdds
{
	CovidCollection::CovidCollection(const char* filename)
	{
		std::ifstream file(filename);
		Covid covidObj{};
		std::string line{};

		auto getData = [](std::string& src, size_t index)
		{
			//Extract from src up to the index into temp
			std::string temp = src.substr(0, index);
			//Get rid of the information we just extracted
			if (src.length() >= index)
			{
				src = src.substr(index);
			}
			//Get rid of trailing whitespaces
			temp.erase(0, temp.find_first_not_of(' '));
			temp.erase(temp.find_last_not_of(' ') + 1);
			return temp;
		};

		if (!file)
		{
			std::cout << "ERROR: Invalid file name" << std::endl;
		}
		else
		{
			while (getline(file, line))
			{
				//Set member data using lambda expression
				covidObj.m_country = getData(line, 25);
				covidObj.m_city = getData(line, 25);
				covidObj.m_variant = getData(line, 25);
				covidObj.m_year = stoi(getData(line, 5));
				covidObj.m_numCases = stoi(getData(line, 5));
				covidObj.m_deaths = stoi(getData(line, 5));
				//Adding to the total cases/deaths 
				m_totalCases += covidObj.m_numCases;
				m_totalDeaths += covidObj.m_deaths;
				//Add the object to our vector
				m_covid.push_back(covidObj);
			}
		}
	}
	void CovidCollection::display(std::ostream& out) const
	{
		for_each(m_covid.begin(), m_covid.end(), [&out](const Covid& theCovid)
			{
				out << theCovid << std::endl;
			});

		out
			<< "----------------------------------------------------------------------------------------" << std::endl
			<< "|" << std::setw(80) << "Total Cases Around the World:  " << m_totalCases << " |" << std::endl
			<< "|" << std::setw(80) << "Total Deaths Around the World:  " << m_totalDeaths << " |" << std::endl;
	}
	void CovidCollection::sort(std::string field)
	{
		if (field == "country")
		{
			std::sort(m_covid.begin(), m_covid.end(), [](Covid& theCovid, Covid& secondCovid)
				{
					return theCovid.m_country < secondCovid.m_country;
				});
		}
		else if (field == "variant")
		{
			std::sort(m_covid.begin(), m_covid.end(), [](Covid& theCovid, Covid& secondCovid)
				{
					return theCovid.m_variant < secondCovid.m_variant;
				});
		}
		else if (field == "cases")
		{
			std::sort(m_covid.begin(), m_covid.end(), [](Covid& theCovid, Covid& secondCovid)
				{
					return theCovid.m_numCases < secondCovid.m_numCases;
				});
		}
		else if (field == "deaths")
		{
			std::sort(m_covid.begin(), m_covid.end(), [](Covid& theCovid, Covid& secondCovid)
				{
					return theCovid.m_deaths < secondCovid.m_deaths;
				});
		}
	}
	void CovidCollection::cleanList()
	{
		std::all_of(m_covid.begin(), m_covid.end(), [](Covid& theCovid)
			{
				if (theCovid.m_variant == "[None]")
				{
					theCovid.m_variant = "";
				}
				return true;
			});
	}
	bool CovidCollection::inCollection(std::string match) const
	{
		return std::any_of(m_covid.begin(), m_covid.end(), [match](const Covid& theCovid)
		{
				return theCovid.m_variant == match;
		});
	}
	std::list<Covid> CovidCollection::getListForCountry(std::string match) const
	{
		std::list<Covid> temp{};
		std::copy_if(m_covid.begin(), m_covid.end(), back_inserter(temp), [match](const Covid& theCovid)
			{
				return theCovid.m_country == match;
			});
		return temp;
	}
	std::list<Covid> CovidCollection::getListForVariant(std::string match) const
	{
		std::list<Covid> temp{};
		std::remove_copy_if(m_covid.begin(), m_covid.end(), back_inserter(temp), [match](const Covid& theCovid)
			{
				return theCovid.m_variant != match;
			});
		return temp;
	}
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid)
	{
		out << "| " << std::left << std::setw(20) << theCovid.m_country
			<< "  | " << std::setw(15) << theCovid.m_city
			<< " | " << std::setw(20) << theCovid.m_variant
			<< " | " << std::right << std::setw(6);
			if (theCovid.m_year > 0)
			{
				out << theCovid.m_year;
			}
			else
			{
				out << "";
			}
			out << " | "<< std::setw(4) << theCovid.m_numCases
			<< " | " << std::setw(3) << theCovid.m_deaths
			<< " |";
		return out;
	}
}