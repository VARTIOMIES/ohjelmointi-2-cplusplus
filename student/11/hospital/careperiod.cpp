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

void CarePeriod::print_date_info(const std::string& pre_text) const
{
    std::cout << pre_text;
    start_.print();
    std::cout << " - ";
    if (not end_.is_default())
    {
        end_.print();
    }
    std::cout << std::endl;
}

std::string CarePeriod::get_patient_id() const
{
    return patient_->get_id();
}

std::vector<std::string> CarePeriod::get_staff_ids() const
{
    std::vector<std::string> temp = {};
    for (Person* staff_member : staff_)
    {
        temp.push_back(staff_member->get_id());
    }
    return temp;
}

void CarePeriod::print_staff(const std::string& pre_text) const
{
    std::cout<< pre_text;
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

void CarePeriod::print_patient(const std::string& pre_text) const
{
    std::cout << pre_text << patient_->get_id() << std::endl;
}

