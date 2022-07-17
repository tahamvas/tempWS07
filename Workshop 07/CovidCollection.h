
#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <string>
#include <vector>
namespace sdds{

    struct Covid
    {
        std::string m_country{};
        std::string m_city{};
        std::string m_variant{};
        int m_numCases{};
        int m_year{};
        int m_deaths{};
    };

    class CovidCollection
    {
        std::vector<Covid> m_covid{};
        size_t m_totalDeaths{};
        size_t m_totalCases{};
    public:
        CovidCollection(const char* filename);
        void display(std::ostream& out) const;
        void sort(std::string field);
        void cleanList();
        bool inCollection(std::string match) const;
        std::list<Covid> getListForCountry(std::string match) const;
        std::list<Covid> getListForVariant(std::string match) const;
    };
    std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}

#endif