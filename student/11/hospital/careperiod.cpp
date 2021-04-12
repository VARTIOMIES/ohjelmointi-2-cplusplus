#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::set_end_date(const Date &end)
{
    end_ = end;
}

void CarePeriod::assign_staff(const std::string& id, Person* staff_member)
{
    staff_.insert({id,staff_member});
}
