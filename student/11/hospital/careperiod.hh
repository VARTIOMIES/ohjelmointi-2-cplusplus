/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>
#include <set>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();  
    // More public methods
    void set_end_date(const Date& end);

    void assign_staff(Person* staff_member);

    void print_date_info(const std::string& pre_text) const;

    std::string get_patient_id() const;

    std::vector<std::string> get_staff_ids() const;

    void print_staff(const std::string& pre_text) const;
    void print_patient(const std::string& pre_text) const;

private:
    Person* patient_;
    Date start_;
    Date end_;
    std::set<Person*> staff_;

    // More attributes and methods

};

#endif // CAREPERIOD_HH
