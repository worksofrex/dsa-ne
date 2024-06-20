#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <typename T>
class LinkedList {
	T *head;
	public: 
	
	string filename;
	LinkedList(string filename){
		this->head = NULL;
		this->filename = filename;
	}
	
	
	bool is_empty() {
		return head == NULL;
	}
	
	void add_node(T *newNode){
		if(exists_by_id(newNode->id)) {
			cout << "The given ID already exists" << endl;
			return;
		}
		if(is_empty()){
			head = newNode;
		} else{
			T *tail = head;
			while(tail->next){
				tail = tail->next;
			}
			tail->next = newNode;
		}
	}
	
	void print_nodes(){
		if(is_empty()) { 
			cout << "Linked list is empty" << endl;
			return;
		}
		
		T *temp = this->head;
		while(temp != NULL){
			temp->print();
			temp = temp->next;
		}
	}
	
	bool exists_by_id(int id){
		if(is_empty()) return false;
		T *temp = this->head;
		while(temp != NULL){
			if(temp->id == id) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	
	void save_to_csv(){
		if(is_empty()) {
			cout << "Can't save an empty list;" << endl;
			return;
		}
		ofstream file;
		file.open(this->filename, ios::ate);
		if(!file.is_open()){
			cout << "Unable to open file " << this->filename  << endl;
			return;
		}
		T *temp = this->head;
		while(temp != NULL){
			file << temp->to_string() << '\n';
			temp = temp->next;
		}
		
		cout << "Data saved into " << this->filename << endl;
	}
};

class Doctor{
	public:
	
	int id;
	string name;
	string specialization;
	Doctor *next;
	
	Doctor(){
		this->next = NULL;
	}
	
	Doctor(int doctor_id, string name, string specialization){
		this->id = doctor_id;
		this->name = name;
		this->specialization = specialization;
		this->next = NULL;
	}
	
	
	void print(){
		cout << "ID: " << this->id << "\tName:  " << this->name << "\tSpecialization: " << this->specialization << endl; 
	}
	
	string to_string(){
		return "" +  std::to_string(this->id) + "," + this->name + "," + this->specialization;
	}
};

class Patient{
	public:
	
	int id;
	string name;
	string dob;
	string gender;
	
	Patient *next;
	
	Patient(){
		this->next = NULL;
	}
	
	Patient(int patient_id,  string name, string dob, string gender){
		this->id = patient_id;
		this->name = name;
		this->dob = dob;
		this->gender  = gender;
		this->next = NULL;
	}
	
	
	void print(){
		cout << "ID: " << this->id << "\tName:  " << this->name << "\tDate of Birth: " << this->dob << "\tGender: " << this->gender << endl; 
	}
	
	string to_string(){
		return "" +  std::to_string(this->id) + "," + this->name + "," + this->dob + "," + this->gender;
	}
};

class Appointment{
	public:
	
	int id;
	int patient_id;
	int doctor_id;
	string appointment_date;
	
	Appointment *next;
	
	Appointment(){
		this->next = NULL;
	}
	
	Appointment(int appointment_id,  int patient_id, int doctor_id, string appointment_date){
		this->id = appointment_id;
		this->patient_id = patient_id;
		this->doctor_id = doctor_id;
		this->appointment_date = appointment_date;
		this->next = NULL;
	}
	
	
	void print(){
		cout << "ID: " << this->id << "\tPatient ID:  " << this->patient_id << "\tDoctor ID: " << this->doctor_id << "\tAppointment date: " << this->appointment_date << endl; 
	}
	
	string to_string(){
		return "" +  std::to_string(this->id) + "," + std::to_string(this->patient_id) + "," + std::to_string(this->doctor_id) + "," + this->appointment_date;
	}
};

namespace commands {
	void help(){
		cout << "Menu:\n";
		cout << "\t1. Register a patient \n\t2. Register a doctor \n\t3. Register an appointment \n\t4. Display Patients \n\t5. Display Doctors \n\t6. Display appointments \n\t7. Exit";
		cout << endl;
	}
	
	int choose(){
		int choice;
		cout << "Enter your choice: " ;
		cin >> choice;
		return choice;	
	}
	
	
	template <typename T>
	void display(LinkedList<T> *l){
		l->print_nodes();
	}
	
	void register_patient(LinkedList<Patient> *patientsLL){
		
		cout << "PATIENT REGISTRATION \n_________________________" << endl;
		Patient *new_patient = new Patient();
		
		while(true){
			int patientid;
			cout <<  "ID: ";
			cin >> patientid;
			if(patientsLL->exists_by_id(patientid)) {
				cout << "Given id already exists" << endl;
			} else {
				new_patient->id = patientid;
				break; 
			}
		}
		cout <<  "NAME: ";
		cin.ignore();
		getline(cin, new_patient->name);
		cout << "DoB: ";
		cin >> new_patient->dob;
		cout  << "GENDER: ";
		cin >> new_patient->gender;
		patientsLL->add_node(new_patient);
		
	}
	
	void register_doctor(LinkedList<Doctor> *doctorLL){
		
		cout << "\nDOCTOR REGISTRATION \n_________________________\n" << endl;
		Doctor *new_doctor = new Doctor();
		while(true){
			int doctor_id;
			cout <<  "ID: ";
			cin >> doctor_id;
			if(doctorLL->exists_by_id(doctor_id)) {
				cout << "Given id already exists" << endl;
			} else {
				new_doctor->id = doctor_id;
				break; 
			}
		}
		cout <<  "NAME: ";
		cin.ignore();
		getline(cin, new_doctor->name);
		cout << "SPECIALIZATION: ";
		getline(cin, new_doctor->specialization);
		doctorLL->add_node(new_doctor);
		
	}
	
	void register_appointment(LinkedList<Appointment> *appointmentsLL, LinkedList<Patient> *patientsLL, LinkedList<Doctor> *doctorsLL){
		
		cout << "\nAPPOINTMENT REGISTRATION \n_________________________\n" << endl;
		Appointment *new_appointment = new Appointment();
		
		while(true){
			int appointment_id;
			cout <<  "ID: ";
			cin >> appointment_id;
			if(appointmentsLL->exists_by_id(appointment_id)) {
				cout << "Given id already exists" << endl;
			} else {
				new_appointment->id = appointment_id;
				break; 
			}
		}
		
		while(true){
			int patientid;
			cout <<  "P_ID: ";
			cin >> patientid;
			if(! patientsLL->exists_by_id(patientid)) {
				cout << "Patient does not exist, retry;" << endl;
			} else {
				new_appointment->patient_id = patientid;
				break; 
			}
		}
		
		while(true){
			int doctorid;
			cout <<  "D_ID: ";
			cin >> doctorid;
			if(! doctorsLL->exists_by_id(doctorid)) {
				cout << "Doctor does not exist, retry;" << endl;
			} else {
				new_appointment->doctor_id = doctorid;
				break; 
			}
		}
		
		cout << "DATE: ";
		cin >> new_appointment->appointment_date ;
		

		appointmentsLL->add_node(new_appointment);
		
	}
	
	void load_data(LinkedList<Appointment> *appointmentsLL, LinkedList<Patient> *patientsLL, LinkedList<Doctor> *doctorsLL){
		// Loading doctors
		{	
			ifstream file;
			file.open(doctorsLL->filename);
			
			string line;
			
			while(getline(file, line)){

				stringstream ss(line);
	
				string id, name, specialization;
				getline(ss, id, ',');
				getline(ss, name, ',');
				getline(ss, specialization, ',');
				Doctor *doctor_from_csv_line = new Doctor(stoi(id), name, specialization);
				doctorsLL->add_node(doctor_from_csv_line); 
			} 
			
			// Loading patients
			{	
				ifstream file;
				file.open(patientsLL->filename);
				
				string line;
				
				while(getline(file, line)){
					stringstream ss(line);
		
					string id, name, dob, gender;
					getline(ss, id, ',');
					getline(ss, name, ',');
					getline(ss, dob, ',');
					getline(ss, gender, ',');
				
					Patient *patient_from_csv_line = new Patient(stoi(id), name, dob, gender);
					patientsLL->add_node(patient_from_csv_line); 
				} 
			}
			
			// Loading appointments
			{	
				ifstream file;
				file.open(appointmentsLL->filename);
				
				string line;
				
				while(getline(file, line)){
					stringstream ss(line);
					string id, p_id, d_id, date;
					getline(ss, id, ',');
					getline(ss, p_id, ',');
					getline(ss, d_id, ',');
					getline(ss, date, ',');
					
					Appointment *appointment_from_csv_line = new Appointment(stoi(id), stoi(p_id), stoi(d_id), date);
					appointmentsLL->add_node(appointment_from_csv_line); 
				}
				
				file.close();
			}
		}
	}
}

int main(){
	
	cout << "RUHENGERI HOSPITAL MANAGEMENT SYSTEM" << endl;
	cout << "Hospitals system used to manage patients, doctor and their appointments\n" << endl;
	
	LinkedList<Doctor> *doctorsLL = new LinkedList<Doctor>("doctors.csv");
	LinkedList<Patient> *patientsLL = new LinkedList<Patient>("patients.csv");
	LinkedList<Appointment> *appointmentsLL = new LinkedList<Appointment>("appointments.csv");
	commands::load_data(appointmentsLL, patientsLL, doctorsLL);
	
	while (true){
		commands::help();
		int command = commands::choose();
		switch(command){
			case 1:
				commands::register_patient(patientsLL);
				break;
			case 2:
				commands::register_doctor(doctorsLL);
				break;
			case 3:
				commands::register_appointment(appointmentsLL, patientsLL, doctorsLL);
				break;
			case 4:
				commands::display(patientsLL);
				break;
			case 5: 
				commands::display(doctorsLL);
				break;
			case 6: 
				commands::display(appointmentsLL);
				break;
			case 7:
				
				cout << "Saving appointments..\n"; 
				appointmentsLL->save_to_csv(); 
				
				cout << "Saving patients..\n"; 
				patientsLL->save_to_csv();
				
				cout << "Saving doctors..\n"; 
				doctorsLL->save_to_csv();
				cout << "DONE !";
				cout  << endl;
				cout << ":)>>  Bye!" << endl;
				exit(0);
				break;
			default:
				cout << "! Invalid command\n See how this system is used below \n";
		}
		
		// Break for  a new command
		cout <<  "\n\n" ;
		
	}
	
	
//	Doctor *doctor1  = new Doctor(1, "MUGABO Jackson", "Generalist");
//	Doctor *doctor2  = new Doctor(2, "KALINGA Davis", "Brain surgery");
//	Doctor *doctor3  = new Doctor(2, "BABALAO Thecat", "Heart surgery");
//	doctorsLL->add_node(doctor1);
//	doctorsLL->add_node(doctor2);
//	doctorsLL->add_node(doctor3);
//	doctorsLL->print_nodes();
//	
//	
//	
//	
//
//	Patient *p1=  new Patient(1, "KEZA  Jena", "1989-30-12", "female");
//	Patient *p2 = new Patient(2,  "MICO Thebest",  "2000-01-01", "male");
//	patientsLL->add_node(p1);
//	patientsLL->add_node(p2);
//	patientsLL->print_nodes();
//	
//	
// 
// 	Appointment *app1 = new Appointment(1, 1, 1, "12-08-2024");
// 	Appointment *app2 = new Appointment(2,2,1, "20-06-2024");
// 	Appointment *app3 = new Appointment(2,4,5, "01-07-2024");
// 	appointmentsLL->add_node(app1);
// 	appointmentsLL->add_node(app2);
// 	
// 	appointmentsLL->print_nodes();
 

	
	
	return 0;
}
