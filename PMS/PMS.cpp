#include<iostream>
#include<string>
#include<cstdlib>
#include<map>
#include<fstream>
using namespace std;
                                      //Made by: Shashwat Singh
                          //Section:K19PT    Rollno.:32      Reg Number: 11912314

            

//<<--------------This the main class which are taking the input of the students----------->>>>>

class stinfo       //stinfo represents the student information
{
  private:
     long RegNum;   //registre by the this appliction and it provided by my application
     string FirstName;  //firstname of the student
	 string LastName;   //Lastname of the student as surname
	 string Section;    //taking the input for the class section for the further information if we want
	 float AvgCgpa;   //this the cgpa which is the avg of the y1,y2,y3
	 int InternExp;   //Internship expirence of the student
	 int CertMark;   //certification marks which we take before placement in his major intrest area it can be practical or written as per the subject
	 string Group;   //this will be divided on the basis of the some condition and it will pride the group according to the student are eligilble to sit that interview only where in group assigned
	 static long NextRegNum;
  public:
  	stinfo()
	  { }
	stinfo(string fName,string lName,string sect,float AvgCGPA,int InternE,int CertM,string g);
	long getRegNo()
	{
	 return RegNum;
	}
	string getFirstName()
	{
	  return FirstName;
	}
	string getLastName()
	{
		return LastName;
	}
	string getSection()
	{
		return Section;
	}
	float getAvgCGPA()
	{
		return AvgCgpa;
	}
	int Iexp()
	{
		return InternExp;
	}
	int skill()
	{
		return CertMark;
	}
	string grp()
	{
		return Group;
	 } 
  	static void setLastRegNo(long regNUM);
  	static long getLastRegNo();
	
	//here we are using operator overloading on filehandling and the cout of the object
	friend ofstream & operator << (ofstream &ofs, stinfo &sti);
	friend ifstream & operator >> (ifstream &ifs, stinfo &sti);
	friend ostream & operator << (ostream &os, stinfo &sti); 
	
	};
	long stinfo::NextRegNum=119123140;

//the fuction  and cunstructors of the class Student Info are written outside
//<---------------------------------------------------------------------------------------------------------------------------->  
    stinfo::stinfo(string fName,string lName,string sect,float AvgCGPA,int InternE,int CertM,string g)
     {
     	NextRegNum++;
     	RegNum=NextRegNum++;
     	FirstName=fName;
     	LastName=lName;
     	Section=sect;
     	AvgCgpa=AvgCGPA;
     	InternExp=InternE;
	    CertMark=CertM;
        Group=g;
	  }
    void stinfo::setLastRegNo(long regNUM)
       {
       	NextRegNum=regNUM;
	   }
     long stinfo::getLastRegNo()
       {
       	 return NextRegNum;
	   }
	//operator overloading are written below for the filehandling and as well as for the cout
	
	ofstream & operator << (ofstream &ofs, stinfo &sti)
	{
		ofs<<sti.RegNum<<endl;
		ofs<<sti.FirstName<<endl;
		ofs<<sti.LastName<<endl;
		ofs<<sti.Section<<endl;
		ofs<<sti.AvgCgpa<<endl;
		ofs<<sti.InternExp<<endl;
		ofs<<sti.CertMark<<endl;
		ofs<<sti.Group<<endl;
		return ofs;
	}
	ifstream & operator >> (ifstream &ifs, stinfo &sti)
	{
		ifs>>sti.RegNum;
		ifs>>sti.FirstName;
		ifs>>sti.LastName;
		ifs>>sti.Section;
		ifs>>sti.AvgCgpa;
		ifs>>sti.InternExp;
		ifs>>sti.CertMark;
		ifs>>sti.Group;
		return ifs;
	}   
	ostream & operator << (ostream &os, stinfo &sti)  
	{
	    os<<"Registration Number: "<<sti.getRegNo()<<endl;
		os<<"First Name of the Student:"<<sti.getFirstName()<<endl;
		os<<"Last Name of the Student: "<<sti.getLastName()<<endl;
		os<<"Last Section: "<<sti.getSection()<<endl;
		os<<"Avrage CGPA:"<<sti.getAvgCGPA()<<endl;
		os<<"Intership Experience: "<<sti.Iexp()<<" Months"<<endl;
		os<<"Got the marks in Certification Test : "<<sti.skill()<<endl;
		os<<"Selected in :"<<sti.grp()<<endl; 
		return os;	
	}
    
	
	
	//this is  the second class which bascially designed for the searching for the detail and mangement 
	class maement  //mangement
	{
		private:
			map<long,stinfo> details;
		public:
			maement();
			stinfo AddDetails(string fname,string lname,string sect, float avgcgpa,int intern,int mark,string group);
			stinfo Enquiry(long RegNUM);
	        void DeleteDetails(long RegNum);
	        void ShowAllRegisteredStudents();
	        ~ maement();
	};
	
//here the functions are written outside of class manegement
//<-------------------------------------------------------------------------------------------------------------------------------->>	
   maement::maement()
  {
  	 stinfo sti;
  	 ifstream infile;
  	 
  	 infile.open("pms.data");  //I have the data in the .data extension for easily we can read data.... and other reason also
  	 if(!infile)
  	 {
  	 	//cout<<"Error in Opening ! File Not Found !! "<<endl;
  	 	return;
	}
	while(!infile.eof())
	{
	 infile>>sti;
	 details.insert(pair<long,stinfo>(sti.getRegNo(),sti));
	}
	stinfo::setLastRegNo(sti.getRegNo());
     infile.close();
  }
  
  stinfo maement::AddDetails(string fname,string lname,string sect, float avgcgpa,int intern,int mark,string group)
  {
  	ofstream outfile;
  	stinfo st(fname,lname,sect,avgcgpa,intern,mark,group);
  	details.insert(pair<long,stinfo>(st.getRegNo(),st));
  	outfile.open("pms.data",ios::trunc);
  	
  	map<long,stinfo>::iterator itr;
  	for(itr=details.begin();itr!=details.end();itr++)
  	{
      outfile<<itr->second;	 
	}
	outfile.close();
	return st;
  }
  stinfo maement::Enquiry(long regnum) //here i have used the concept maping as i am providing the key as registration so by the help of
                             //that key that user can easily find the one student detail
  {
  	map<long,stinfo>::iterator itr=details.find(regnum);
  	return itr->second;
  }
  void maement::DeleteDetails(long regnum)  //by the concept of the maping we are deleting the one student only.....
  {
  	map<long,stinfo>::iterator itr=details.find(regnum);
  	cout<<"Details are Sucessfully Deleted !!"<<itr->second;
  	details.erase(regnum);
  }                                               //I will implement some more things here like by using group as key only user can get
  void maement::ShowAllRegisteredStudents()      //detail for the students of those group......
  {
  	map<long,stinfo>::iterator itr;
  	for(itr=details.begin();itr!=details.end();itr++)
  	{
  		cout<<"Details Are: "<<itr->first<<endl<<itr->second<<endl;
	}
  }
  maement::~maement()
  {
  	ofstream outfile;
  	outfile.open("pms.data",ios::trunc);
  	
  	map<long , stinfo>:: iterator itr;
  	for(itr=details.begin();itr!=details.end();itr++)
  	{
  		outfile<<itr->second;
	  }
	  outfile.close();
  }

//<==========These are the function for our main function which will used it for different-different purpose as mentioned============>

int calculateAvg(float y1, float y2 ,float y3)  //This function I have used for the calculating the Average of the CGPA that students get in three
	{                                     // years....
		float sum=0;
		float avg;
         sum=y1+y2+y3;
		avg=sum/3;
		cout<<avg;
		return avg;
	}

string SeperatingGroups(float avg,int certm,int intexp)  //By the use of this fuction we are classifying our students in different-different
{                                                        //As I have decided here 3 Groups , 1 puting in the waiting list , For not giving
	if(((avg>=7) && (intexp>=6)) && (certm>=85))         //any group to that type of Student as per my conditions.......
	{                                    
		return "Group A";                                  //Group A contains Top Copmanies > Group B >Group C;;;;;;; And then otherones as follows
	}
	else if(((avg==6) && (intexp==5)) &&(certm>=85)) 
	{
		return "Group B";
	}
	else if(((avg==5) || (intexp==4)) && (certm>=80))
	{
		return "Group C";
	}
	else if(((avg==5) || (intexp==0)) && (certm>=75))
	{
		return "Waiting list!";
	}
	else if(((avg<5) || (intexp==0)) && (certm<75))
	{
		return "You are not selected !";
	}
}
	
int main()
{
	maement M;
	stinfo St;
	
	int choice;
	string fname,lname,section;  //these the variables are used as the taking the first, last name and the section of the student
	float AvgCGPA,y1,y2,y3;   //this variable is used to store the avgerage of the CGPA which he got in y1,y2,y3
	long regNUM;        //registration number of the student
	int certmark,InternExp;   //certification marks and second variable is used for the internship experience
	string group;
	
	cout<<"------>Placement Mangement System<--------"<<endl;
	do
	{
		cout<<"\n\t  Select one option below";
		cout<<"\n\t1 Add The Detail Of the Student";
		cout<<"\n\t2 Enquiery About The Student Information";
		cout<<"\n\t3 Delete The Detail";
		cout<<"\n\t4 Show All The Registered Detail";
		cout<<"\n\t5 Quit";
		cout<<"\n Enter Your Choice: ";
		cin>>choice;
		switch(choice)
		{
		  case 1:
		     cout<<"Enter the First Name of the Student: ";
			 cin>>fname;
			 cout<<"Enter the Last Name of the student: ";
			 cin>>lname;
			 cout<<"Enter the Last Section of the student: ";
			 cin>>section;
			 cout<<"Enter the Certification Marks: ";
			 cin>>certmark;
			 cout<<"Enter the InternShip Experince(in Month) of the: ";
			 cin>>InternExp;
			 cout<<"Selection of the Groups: "<<endl;
			      cout<<"-----------You need To Enter some Detail-------------";
			      cout<<endl<<"-------------------CGPA in the First Year: ";
			      cin>>y1;
			      cout<<"-------------------CGPA in the Second Year: ";
			      cin>>y2;
			      cout<<"-------------------CGPA in the Third Year: ";
			      cin>>y3;
			      AvgCGPA=calculateAvg(y1,y2,y3);
			      group=SeperatingGroups(AvgCGPA,certmark,InternExp);
			St=M.AddDetails(fname,lname,section,AvgCGPA,InternExp,certmark,group);
		    cout<<endl<<"You are Registerd Successfully!"<<endl;
		    cout<<St;
		    break;
		    
		 case 2:
		    cout<<"Enter The Registration Number: ";
			cin>>regNUM;
			St=M.Enquiry(regNUM);
			cout<<endl<<"Your Detail is: "<<endl;
			cout<<St;
			break;
		 case 3:
		    cout<<"Enter The Registration Number: ";
			cin>>regNUM;
			M.DeleteDetails(regNUM);
			cout<<endl<<"Detail of the Student is Succesfully Deleted !!";	   
            cout<<St;
            break;
		 case 4:
		    M.ShowAllRegisteredStudents();
			break;
		 case 5:
		    break;
		
		default:
		  cout<<endl<<"Enter The Correct Choice !! ";
		  exit(0);					
		}
	}
	while(choice!=5);
}
