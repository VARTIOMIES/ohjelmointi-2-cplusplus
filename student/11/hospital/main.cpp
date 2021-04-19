/* Hospital
 *
 * Desc:
 *  This program generates a Hospital system. It keeps track of patients,
 * staff, care periods and medicines and has a list of commands to control
 * the hospital and things happening inside of it. At start, this program
 * generates a hospital. After generating a new hospital, the program asks for
 * commands until user enters quit command. All the commands are listed below.
 *  Patients and staff members are instances of the class Person. Their info
 * is stored in separate STL-containers in the class Hospital. Patients and
 * staff can be identified by their names that are/have to be given when adding
 * new people to the hospital. Patients can be added and removed with commands,
 * but staff are permanent.
 *  When a patient is added, the class Hospital calls for a new object of class
 * CarePeriod. That new object describes a single care period of a single
 * patient. The careperiod can have only one patient, but can include from zero
 * to many staff members, that are taking care of the patient. A careperiod last
 * for so long,until the patient leaves hospital. The ending date is then stored
 * in the object. All care periods are stored in a STL-container in the class
 * Hospital in a chronological order. When the same patient comes back to the
 * hospital, new CarePeriod object is created, and patients previous careperiods
 * can still be found in the system.
 *  A CarePeriod has a starting and ending date, which are instances of class
 * Date. The class Hospital uses the class Date when creating a new CarePeriod
 * and the date can be changed with some commands in the class Hospital.
 *  A patient may have madicines and they are described as a struct inside the
 * class Person, since the medicines are specific for every patient, and they
 * dont have or need any operations. The class hospital can add and remove
 * medicines from it's patients, who are currently in the hospital.
 *  Command checking is done in Cli -class. Cli checks, if given input is known
 * and if there are correct amount of parameters given in the input.
 *  The module Utils provides general functions used in the program.
 *
 *  The functionalities of the commands are written in Hospital -class. The
 * Hospital -class is the main structure of the program, and it handles the
 * functionality and calls other classes when necessary to create a modular
 * program.
 * Commands and describtion:
 * - QUIT : Terminates the program with the return value EXIT_SUCCESS. Does not
 *          print anything. The command takes no parameters, and if they are
 *          given, they will just be ignored.
 * - HELP : Prints all available commands and their acronyms and the describtion
 *          of the command.
 * - READ_FROM <file> : Reads commands from a file which name is given as a
 *                      parameter <file>. If the file contains erronous commands
 *                      it just ignores them and continues reading the file. If
 *                      no file is found with the given name, an error message
 *                      is printed.
 * - SET_DATE <dd> <mm> <yyyy> : Sets the date according to the given parameters
 *                               of integer type. The date is in the form
 *                               dd.mm.yyyy . If parameters are erronous,program
 *                               prints an error message.
 * - ADVNACE_DATE <non-negative integer> : The command advances the current date
 *                                         with the given number of days ahead.
 *                                         if the parameter is erronous, the
 *                                         program prints an error message
 * - RECRUIT <id> : Adds a new staff member to the hospital. Command needs one
 *                  parameter that can be a name, to identify the new object of
 *                  class Person. If a staffmember with the given id already
 *                  exists, the program prints an error message.
 * - PRINT_ALL_STAFF : Prints all staff members recruited in alphabetical order
 * - ADD_MEDICINE <medicine name> <strength> <dosage> <patient id>
 *      : Adds a medicine with a given strength and dosage for a given patient.
 *        Strength is given as milligrams. The strength and dosage must be
 *        integer numbers. Medicines can be presrcibed only for patients who
 *        are currently in a hospital and have an on-going care period. If
 *        patient already has medicine with the same name, the strength and
 *        dosage can be changed witht this command. If parameters are erronous,
 *        program prints an error message.
 * - REMOVE_MEDICINE <medicine name> <patient id>
 *      : Removes medicine from a patient. The medicine can be removed only from
 *        a patient currently in the hospital. If the patient does not have the
 *        given medicine, nothing happens and no error message is given. If the
 *        given patient cannot be found, the program prints an error message.
 * - ENTER <id> : Adds a new patient in the hospital. Requires one parameter
 *                that can be the name of the patient. The id will be later used
 *                to identify the patient. When patient enters, new care period
 *                is created for the patient, with starting date which is the
 *                current value of 'today' variable of Utils module. If there
 *                already is a patient in the hospital with the same name(id),
 *                the program prints an error message. If patient with the same
 *                name has previously visited the hospital, no new patient is
 *                created, but a new CarePeriod is created for the already
 *                existing Person object.
 * - LEAVE <id> : Removes  patient from the hospital, but keeps the data about
 *                their care period. The current care period is closed and the
 *                endind date (today) is stored in the info of the careperiod.
 *                If the patient to be removed is not currently in the hospital,
 *                the program prints an error message.
 * - ASSIGN_STAFF <staff member id> <patient id>
 *      : Assigns the given staff member to work in the given patient's current
 *        care period. If staff member already is assigned for the patient,
 *        nothing happens and no error message is given.
 * - PRINT_PATIENT_INFO <patient id> : Prints info about all careperiods and
 *                                     medicines of the given patient. Info of
 *                                     care period includes start date, possible
 *                                     end date, and all staff memebers assigned
 *                                     for the care period. The care periods are
 *                                     printed in chronological order.
 * - PRINT_CARE_PERIOD <staff member id> : Prints the care periods that given
 *                                         staff member has worked on or works
 *                                         in at the moment in chronological
 *                                         order.
 * - PRINT_ALL_MEDICINES : Prints all medicines currently used by patients who
 *                         have visited the hospital.
 * - PRINT_ALL_PATIENTS : Prints info about all patients who have visited the
 *                        hospital. Info includes information of the careperiods
 *                        of a patient and infromation of their medication.
 * - PRINT_CURRENT_PATIENTS : Prints info about patients that are currently in
 *                            the hospital and has a care preiod going on.
 *
 * Program author
 * Name: Onni Merilä
 * Student number: H299725
 * UserID: bvonme
 * E-Mail: onni.merila@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 */
#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";


int main()
{
    Hospital* hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    delete hospital;
    return EXIT_SUCCESS;
}
