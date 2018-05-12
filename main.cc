#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>  //pour aligner le tableau
#include <stdlib.h>     /* atof */

using namespace std;
//pour aligner le tableau
using std::cout;
using std::setw;
	
//Conversion km/h to time/km
/*int MS (double vitesse)
	{
	int tempo = 3600/vitesse;
	int min = tempo/60;
	int sec = tempo-(min*60);
	return min,sec;
	}*/

void detailSession(std::string fileName)
	{
	streampos size;
	char * memblock;
	double speed;
	double tempo;
	
	//on demande à l'utilisateur de saisir le nom du fichier
	std::string road = "/home/fran6/Thomas/Running/Thomas/";
	std::string extension = ".gpx";
	std::string global = road + fileName + extension;
		
	//on ouvre un fichier et on le charge dans un char
	ifstream file (global.c_str(), ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
	size = file.tellg();
	memblock = new char [size];
	file.seekg (0, ios::beg);
	file.read (memblock, size);
	file.close();
	
	//on transforme le char en string
	string str = memblock;
	//string to find
	std::string startlap="<gpxdata:index>";
	std::string endlap = "</gpxdata:index>";
	std::string starttime = "<gpxdata:elapsedTime>";
	std::string endtime = "</gpxdata:elapsedTime>";	
	std::string startdistance = "<gpxdata:distance>";
	std::string enddistance = "</gpxdata:distance>";
	std::string startvit = "avg";
	std::string endvit = "max";		
		
	//initialisation des variables
	int srtlap = 0;
	int edlap = 0;
	int time1 =0;
	int time2 =0;
	int distance1 =0;
	int distance2 =0;
	int vitesse1 =0;
	int vitesse2 =0; 

	//on affiche les titres
	cout << setw(3) << "lap" <<
        setw(8) << "time" <<
        setw(12) << "distance" <<
        setw(12) << "vitesse" << 
	setw(8) << "tempo" << '\n';	
	
	//initialisation des variables
	ofstream myfile;
	myfile.open ("/home/fran6/Thomas/Prog/running.cpp/test.txt");
	myfile << "lap" << ";" << "time" << ";" << "distance" << ";" << "vitesse" << ";" << "tempo" << endl;
	//boucle d'extraction des strings
	for(std::string::size_type pos=0; pos<str.size(); pos+=startlap.size())
	{
        pos=str.find(startlap, pos);
	int pos2=str.find(endlap, pos);
	int time1 = str.find(starttime, pos);
	int time2 = str.find(endtime, pos);
	int distance1 = str.find(startdistance, pos);	
	int distance2 = str.find(enddistance, pos);	
	int vitesse1 = str.find(startvit, pos);
	int vitesse2 = str.find(endvit, pos);
				
        if(pos==std::string::npos)
        break;
	
	double lap = atof(str.substr (pos+15,pos2-pos-15).c_str());
	double time = atof(str.substr (time1+21,time2-time1-21).c_str());
	double distance = atof(str.substr (distance1+18,distance2-distance1-18).c_str());
	double vitesse = atof(str.substr (vitesse1+5,vitesse2-vitesse1-73).c_str());
	int tempo = 3600/vitesse;
	int min = tempo/60;
	int sec = tempo-(min*60);
	/*MS(vitesse);*/
	
	//on affiche les valeurs ('setfill' s'applique partout, il faut donc le réinitialiser')
	cout << setw(3) << setfill (' ') << lap;
        cout << setw(8) << time;
        cout << setw(12) << distance;
        cout << setw(12) << vitesse;
	cout << setw(8) << min << "." << setfill ('0') << setw(2) << sec << endl;
	}
	
	myfile.close();
	delete[] memblock;
	}
	}
	
	int main () 
	{
	std::string fileName;
	cout << "Entrer le nom du fichier : ";
	cin >> fileName;
	detailSession(fileName);
	}
