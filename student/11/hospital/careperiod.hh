/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 *
 * Program author
 * Name: Onni Merilä
 * Student number: H299725
 * UserID: bvonme
 * E-Mail: onni.merila@tuni.fi
 *
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

    // Set the end date (Date class) for the care period.
    void set_end_date(const Date& end);

    // Add a staff member for the care period.
    void assign_staff(Person* staff_member);

    // Print start and end dates. Param pre_text gets printed before the dates.
    void print_date_info(const std::string& pre_text) const;

    // Getter function for the careperiods patient. Returns patient id in string
    std::string get_patient_id() const;

    // Getter function for the staff memebers of the care period. Returns vector
    // of staff ids in alphabetical order.
    std::vector<std::string> get_staff_ids() const;

    // Print functions for information about the care period. Both include
    // printing of the given pre_text.
    void print_staff(const std::string& pre_text) const;
    void print_patient(const std::string& pre_text) const;

private:
    Person* patient_;
    Date start_;
    Date end_;
    // Container for staff members who have been working on this care period.
    std::set<Person*> staff_;
};

#endif // CAREPERIOD_HH
