/* Program author
 * Name: Onni Merilä
 * Student number: H299725
 * UserID: bvonme
 * E-Mail: onni.merila@tuni.fi
 *
 * Notes about the program and it's implementation:
 * */

#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Deallocating patients
    for( std::map<std::string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Deallocating care periods
    for( std::vector<CarePeriod*>::iterator
         iter = all_care_periods_.begin();
         iter != all_care_periods_.end();
         ++iter )
    {
        delete *iter;
    }

}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);
    // Checking if there is already a patient in hospital with the same name.
    if (current_patients_.find(patient_id) != current_patients_.end())
    {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    // If given patient is a new patient, create a new patient object
    // and add it to the container all_patients_
    Person* new_patient = nullptr;
    if (all_patients_.find(patient_id) == all_patients_.end())
    {
        new_patient = new Person(patient_id);
        all_patients_.insert({patient_id,new_patient});
    }

    // else put the pointer to point on the existing Patient object
    else
    {
        new_patient = all_patients_.at(patient_id);
    }

    // Add patient to current patients
    current_patients_.insert({patient_id,new_patient});
    std::cout << PATIENT_ENTERED << std::endl;
    
    // Lets create a new careperiod for the new patient and add it to hospitals
    // care_period register
    CarePeriod* new_care_period = new CarePeriod(utils::today,new_patient);
    all_care_periods_.push_back(new_care_period);
    current_care_periods_.insert({patient_id,new_care_period});

}

void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);
    if (not is_name_in_container(patient_id,current_patients_))
    {
        return;
    }
    // Lets take the leaving patient out of current_patients and end his/her
    // ongoing care period and add the ending date to the careperiod.
    current_patients_.erase(patient_id);
    current_care_periods_.at(patient_id)->set_end_date(utils::today);
    current_care_periods_.erase(patient_id);
    std::cout << PATIENT_LEFT << std::endl;
}

void Hospital::assign_staff(Params params)
{
    std::string staff_id = params.at(0);
    std::string patient_id = params.at(1);

    // Finds out, if any of the given names are unknown
    if (not is_name_in_container(staff_id,staff_))
    {
        return;
    }
    else if (not is_name_in_container(patient_id,current_patients_))
    {
        return;
    }

    Person* staff_member = staff_.at(staff_id);

    // Finds out the care period of the patient and assigns staff member to it
    current_care_periods_.at(patient_id)->assign_staff(staff_member);

    std::cout << STAFF_ASSIGNED << patient_id<< std::endl;
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);

    // Find out if given patient has been in this hospital
    if (not is_name_in_container(patient_id,all_patients_))
    {
        return;
    }
    Person* patient = all_patients_.at(patient_id);

    // Find all the care periods of the patient and print info
    for (CarePeriod* care_period : all_care_periods_)
    {
        if (care_period->get_patient_id()==patient_id)
        {
            care_period->print_date_info(CARE_PERIOD_TITLE);
            care_period->print_staff(STAFF_TITLE);
        }
    }

    // Print all medicines of the patient
    std::cout << MEDICINE_TITLE;
    patient->print_medicines("  - ");


}

void Hospital::print_care_periods_per_staff(Params params)
{
    std::string staff_id = params.at(0);
    if(not is_name_in_container(staff_id,staff_))
    {
        return;
    }
    // Find all careperiods, the staff member has worked on
    std::vector<CarePeriod*> worked_care_periods = {};
    for(CarePeriod* care_period : all_care_periods_)
    {
        for (std::string worked_staff : care_period->get_staff_ids())
        {
            if (worked_staff==staff_id)
            {
                worked_care_periods.push_back(care_period);
            }
        }
    }
    if (worked_care_periods.empty())
    {
        std::cout << NONE << std::endl;
    }
    else
    {
        for(CarePeriod* care_period : worked_care_periods)
        {
            care_period->print_date_info("");
            care_period->print_patient(PATIENT_TITLE);
        }
    }
}

void Hospital::print_all_medicines(Params)
{
    // lets first find all medicines and save them to all_medicines

    std::map<std::string,std::set<std::string>> all_medicines =
            get_all_medicines();
    // Printing vvv
    if (all_medicines.empty())
    {
        std::cout << NONE << std::endl;
        return;
    }
    for (std::pair<std::string,std::set<std::string>> medicine : all_medicines)
    {
        std::cout << medicine.first << " prescribed for" << std::endl;
        for (std::string patient : medicine.second)
        {
            std::cout << "* " << patient << std::endl;
        }
    }
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << NONE << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{
    print_many_patients(all_patients_);
}

void Hospital::print_current_patients(Params)
{
    print_many_patients(current_patients_);
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

std::map<std::string, std::set<std::string> > Hospital::get_all_medicines() const
{
    // First string is the name of the medicine, and second set of string is all
    // patients who have that medicine.
    std::map<std::string,std::set<std::string>> all_medicines = {};
    for( std::pair<std::string, Person*> patient : all_patients_)
    {
        std::vector<std::string> medicines = patient.second->get_medicines();
        for (std::string medicine : medicines)
        {
            if (all_medicines.find(medicine) == all_medicines.end())
            {
                std::string name = patient.second->get_id();
                all_medicines.insert({medicine,{name}});
            }
            else
            {
                all_medicines.at(medicine).insert(patient.second->get_id());
            }
        }
    }
    return all_medicines;
}

void Hospital::print_many_patients(std::map<std::string, Person *> container) const
{
    if (container.empty())
    {
        std::cout << NONE << std::endl;
    }

    for(auto patient : container)
    {
        patient.second->print_id();
        std::cout << std::endl;
        for (auto care_period : all_care_periods_)
        {
            if (care_period->get_patient_id()==patient.first)
            {
                care_period->print_date_info(CARE_PERIOD_TITLE);
                care_period->print_staff(STAFF_TITLE);
            }
        }
        std::cout << MEDICINE_TITLE;
        patient.second->print_medicines("  - ");
    }
}

bool Hospital::is_name_in_container(const std::string& name,
                                    const std::map<std::string, Person *>
                                    container) const
{
    if (container.find(name) == container.end())
    {
        std::cout << CANT_FIND << name << std::endl;
        return false;
    }
    return true;
}
