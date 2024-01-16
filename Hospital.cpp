
#include <iostream>
#include <vector>

class Doctor {
public:
	Doctor(const std::string& name, int number) : name(name), number(number) {
		doctorinstanceCount++;
		freeTimes = std::make_shared<std::vector<std::string>>();
		doctorAppointmentCount = std::make_shared<int>();
	}
	void addFreeTime(const std::string& time) {
		freeTimes->push_back(time);
	}
	~Doctor() {
		//doctorinstanceCount--;
	}
	 const std::string& getName() const {
		return name;
	}
	 int getNumber()  {
		return number;
	}

	const std::shared_ptr<std::vector<std::string>> getFreeTimes() const  {
		return freeTimes;
	}
	static int getInstanceCount() {
		return  doctorinstanceCount;
	}
	std::shared_ptr<int> makeAppointment() {
		if (!freeTimes->empty()) {
			freeTimes->erase(freeTimes->begin());
			(*doctorAppointmentCount)++;
		}
		else {
			(*doctorAppointmentCount) = 0;
		}
		return doctorAppointmentCount;
	}
private:
	int number;
    std::string name;
	std::shared_ptr<std::vector<std::string>> freeTimes;
	static int  doctorinstanceCount;
	std::shared_ptr<int> doctorAppointmentCount = 0;
};

class MedicalExpertise {
public:
	MedicalExpertise(const std::string& name, int number) : name(name), number(number) {
		expertiseinstanceCount++;
	}
	~MedicalExpertise() {
		//expertiseinstanceCount--;
	}
	void addDoctor(Doctor& doctor) {
		doctors.push_back(doctor);
	}

	 const std::string& getName() const {
		return name;
	}
	 int getNumber()   {
		return number;
	}
	 const std::vector<Doctor>& getDoctors() const {
		return doctors;
	}
	static int getInstanceCount() {
		return expertiseinstanceCount;
	}
private:
	int number;
    std::string name;
	std::vector<Doctor> doctors;
	static int expertiseinstanceCount;
};
int Doctor::doctorinstanceCount = 0;
int MedicalExpertise::expertiseinstanceCount = 0;

int main()
{

	// Create medical expertise
	MedicalExpertise expertise1("Cardiology", 1);
	MedicalExpertise expertise2("Dermatology", 2);
	MedicalExpertise expertise3("Orthopedics", 3);

	// Create doctors
	Doctor doctor1("Dr. Smith", 1);
	Doctor doctor2("Dr. Johnson", 2);
	Doctor doctor3("Dr. Brown", 3);
	Doctor doctor4("Dr. Wilson", 4);
	Doctor doctor5("Dr. Davis",5);
	Doctor doctor6("Dr. White",6);

	// Add free times for doctors
	doctor1.addFreeTime("Monday 10:00 AM");
	doctor1.addFreeTime("Wednesday 2:00 PM");

	doctor2.addFreeTime("Tuesday 3:30 PM");
	doctor2.addFreeTime("Thursday 9:00 AM");

	doctor3.addFreeTime("Monday 9:00 AM");
	doctor3.addFreeTime("Wednesday 4:00 PM");

	doctor4.addFreeTime("Tuesday 10:30 AM");
	doctor4.addFreeTime("Thursday 3:00 PM");

	doctor5.addFreeTime("Monday 1:30 PM");
	doctor5.addFreeTime("Wednesday 10:00 AM");

	doctor6.addFreeTime("Tuesday 2:00 PM");
	doctor6.addFreeTime("Thursday 11:30 AM");

	expertise1.addDoctor(doctor1);
	expertise1.addDoctor(doctor2);

	expertise2.addDoctor(doctor3);
	expertise2.addDoctor(doctor4);

	expertise3.addDoctor(doctor5);
	expertise3.addDoctor(doctor6);

	std::vector<MedicalExpertise> expertises;
	expertises.push_back(expertise1);
	expertises.push_back(expertise2);
	expertises.push_back(expertise3);
	char choice = 'y';
	while (choice == 'y' || choice == 'Y') {
		for (int i = 0; i < expertises.size(); i++) {
			std::cout << " " << expertises[i].getName() << ":\n";
			std::vector<Doctor> doctors = expertises[i].getDoctors();
			for (int j = 0; j < doctors.size(); j++) {

				std::cout << "    Doctor: " << doctors[j].getName() << "\n";
				std::cout << "    Free Times:\n";
				std::shared_ptr<std::vector<std::string>>  freeTimes = doctors[j].getFreeTimes();
				for (int k = 0; k < freeTimes->size(); k++) {
					std::cout << "      " << (*freeTimes)[k] << "\n";
				}
			}
		}

		std::cout << Doctor::getInstanceCount() << std::endl;
		std::cout << MedicalExpertise::getInstanceCount() << std::endl;
		int expertiseIndex;
		int doctorIndex;
		std::cout << "Select a Expertise (enter expertise number): ";
		std::cin >> expertiseIndex;
		std::cout << "Select a Doctor (enter doctor number): ";
		std::cin >> doctorIndex;


		for (int i = 0; i < expertises.size(); i++) {
			if (expertiseIndex == expertises[i].getNumber()) {
				std::vector<Doctor> doctors = expertises[i].getDoctors();
				for (int j = 0; j < doctors.size(); j++) {
					if (doctorIndex == doctors[j].getNumber()) {
						std::shared_ptr<int> turn = doctors[j].makeAppointment();
						std::cout << "Your Appointment Number Is:" << (*turn) << std::endl;
					}
				}
			}
		}
		std::cout << "if you want to make another appointment press[y]:";
		std::cin >> choice;

	}

	return 0;
}




