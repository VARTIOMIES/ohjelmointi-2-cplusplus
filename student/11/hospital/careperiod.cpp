#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start), end_()
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start), end_()
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::set_end_date(const Date &end)
{
    end_ = end;
}

void CarePeriod::assign_staff(Person* staff_member)
{
    staff_.insert(staff_member);
}

void CarePeriod::print_info(const std::string& pre_text) const
{
    start_.print();
    std::cout << " - ";
    if (not end_.is_default())
    {
        end_.print();
    }
    std::cout << std::endl << pre_text;
    print_staff();
}

std::string CarePeriod::get_patient_id() const
{
    return patient_->get_id();
}

void CarePeriod::print_staff() const
{
    std::cout << "Staff:";
    if( staff_.empty() )
    {
        std::cout << " None" << std::endl;
        return;
    }
    for (Person* staff_member : staff_)
    {
        std::cout << " ";
        staff_member->print_id();
    }
    std::cout << std::endl;
}

