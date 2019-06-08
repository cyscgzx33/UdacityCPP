#include <iostream>

class Student {
  private:
  	std::string name_;
  	int grade_;
  	double gpa_;

  public:
  	Student(std::string name, int grade, double gpa);
  	Student(); // Note: this is NECESSARY if you want to create an instance w/o init

  	// getter functions (accessors)
  	std::string getName() const; 
  	int getGrade() const;
  	double getGPA() const;

  	// setter functions (mutators): w/ sanity check 
  	void setName(std::string name);
  	void setGrade(int grade);
  	void setGPA(double gpa);
};

Student::Student(std::string name, int grade, double gpa) {
	// run verification of input first	
	if ( grade < 0 || gpa > 4.0 || gpa < 0.0) 
		throw "Please check if the inputs are valid: grade AND/OR gpa";
	this->name_ = name;
	this->grade_ = grade;
	this->gpa_ = gpa;
}

// Note: it MUST be defined
Student::Student() {}

std::string Student::getName() const {
	return this->name_;
}

int Student::getGrade() const {
	return this->grade_;
}

double Student::getGPA() const {
	return this->gpa_;
}

void Student::setName(std::string name) {
	if (name.length() <= 0)
		throw "Please check if the input is valid: name";
	this->name_ = name;
}

void Student::setGrade(int grade) {
	if (grade < 0)
		throw "Please check if the input is valid: grade";
	this->grade_ = grade;
}

void Student::setGPA(double gpa) {
	if (gpa > 4.0 || gpa < 0.0)
		throw "Please check if the input is valid: gpa";
	this->gpa_ = gpa;
}


int main() {

	// instantiate one student
	try {
		Student student_1("Jacky Chan", 8, -1.0);
	} catch ( const char* msg ) {
		std::cerr << msg << std::endl;
	}


	// instantiate another student
	Student student_2;

	try {
		student_2.setName("Bruce Lee");
	} catch ( const char* msg ) {
		std::cerr << msg << std::endl;
	}

	try {
		student_2.setGrade(-2);
	} catch ( const char* msg ) {
		std::cerr << msg << std::endl;
	}	

	try {
		student_2.setGPA(4.3);
	} catch ( const char* msg ) {
		std::cerr << msg << std::endl;
	}
	

	std::cout << "The student 1 has info: (name, grade, gpa) = (" << student_1.getName() << " ," 
			  													  << student_1.getGrade() << " ,"
			  													  << student_1.getGPA() << ")"
			  													  << std::endl;

	std::cout << "The student 2 has info: (name, grade, gpa) = (" << student_2.getName() << " ," 
			  													  << student_2.getGrade() << " ,"
			  													  << student_2.getGPA() << ")"
			  													  << std::endl;
	return 0;
}