#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include "CovidCollection.h"
#include "CovidCollection.h"


void printbar(std::ostream& out = std::cout)
{
	out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');
}

void printHeader(const char* title, std::ostream& out = std::cout)
{
	printbar(out);
	out << "| " << std::left << std::setw(85) << title << std::right << "|\n";
	printbar(out);
}

int main(int argc, char** argv)
{
	

	sdds::CovidCollection theCollection("covids.txt");

	printHeader("The original collection");
	theCollection.display(std::cout);
	printbar();
}