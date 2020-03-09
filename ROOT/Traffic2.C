#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;

//Function for plotting


//Class for keeping info o One car
struct TimeStamp
{
	int Time;
	int Position;
	int Velocity;
	

};

//Class to keep track of all cars
class Vehical: public TimeStamp
{
    private:
    int VehicalID;
  
    
    public:
    TimeStamp CarData[100];
//Constructors
    Vehical()
    {
    	VehicalID = 0;
    } 
    Vehical(int id)
    {
    	VehicalID = id;
    }
//Setter Functions    
    void SetCarData(int i, int t,int x, int v)
    {
    	CarData[i].Time = t;
    	CarData[i].Position = x;
    	CarData[i].Velocity = v;
    }   
    void SetVehicalID(int id)
    {
    	VehicalID = id;
    }   
    
//Getter functions    
    int GetVehicalID()
    {
    	return VehicalID;
    }   
    int GetCarTime(int i)
    {
    	return CarData[i].Time;
    }   
    int GetCarPosition(int i)
    {
    	return CarData[i].Position;
    }
    int GetCarVelocity(int i)
    {
    	return CarData[i].Velocity;
    }
    
// Print Function
	void PrintCarInfo(int i)
	{
		cout << " \nTime\tPosition\tvelocity\n " << endl;
		cout << CarData[i].Time <<"\t"<< CarData[i].Position <<"\t"<< CarData[i].Velocity << endl;
	}    
    
// Plotting Function    
    void PlotIt( Vehical a, int id, int Tmax,TGraph *step )
    {

        for (int j=0; j<=Tmax; j++)
        {   
            step->SetPoint(j,a.CarData[j].Position,a.CarData[j].Time);
            step->Draw("same A*");
            step->SetMarkerStyle(id+1);

        }   
    
    
        //delete step;
    } 
    
};

//Probability Function
bool Probability(float f)
{
	if (rand()%100 < f*100)
		return true;
	else
		return false;
}


int Traffic2()
{
	
	srand(time(NULL));
	cout<<"This should work!!!\n\n\n";
	int TotCars = 5;
	int TotSites = 20;
	int Tmax = 30;
	int Vmax = 5;
	float p = 0.5;
	int x2=0,x=0,v=0,d=0;
	Vehical car[TotCars];
//Initialisation Part
//	int xfirst
/*
	cars[0].SetCarData(0,0,rand()%Vmax,rand()%Vmax);
	for (int i = 1; i < TotCars; i++)
	{
		v = rand()%Vmax;
		x = car[i-1].GetCarPosition(0) + rand()%car[]
		car[i].SetVehicalID(i+1);
//		cars[i].SetCarData(0,0)
	}	
*/	
	
	car[0].SetCarData(0,0,3,5);
	car[1].SetCarData(0,0,8,4);	
	car[2].SetCarData(0,0,14,0);
	car[3].SetCarData(0,0,15,0);
	car[4].SetCarData(0,0,18,3);	
			

	for (int i = 1; i <= Tmax; i++)
	{
		for (int j = 0; j < TotCars; j++ )
		{
			x = car[j].CarData[i-1].Position;
			v = car[j].CarData[i-1].Velocity;
			
			if (j+1 == 5)
				x2 = car[0].CarData[i-1].Position;
			else
				x2 = car[j+1].CarData[i-1].Position;
			if (x2 - x < 0)
				d = TotSites - x + x2;
			else
				d = x2 - x;

//STEP 1	
			if (v < Vmax && d > v + 1 )
					v = v + 1; 
//STEP 2		
			if (d <= v && v > 0)
				v = d - 1;
//STEP 3
			if (Probability(p) == true && v > 0)
				v = v - 1;
//STEP 4
			if (x+v <= TotSites)
				x = x+v;
			else
				x = v - (TotSites - x);
				
			car[j].SetCarData(i,i,x,v);						

			
		}//LOOP FOR CARS
	}//LOOP FOR TIME
	
int flag =0;	



	
//Display	
	for (int i=0; i<= Tmax; i++)
	{
		for (int j=1; j<=TotSites; j++)
		{	
			flag=0;
			for (int k=0; k<TotCars; k++)
			{
				if (car[k].CarData[i].Position == j)
				{
					flag=1;
					cout << car[k].CarData[i].Velocity << "\t";
					break;
				}
			}//for comparing every car's position
			
			if (flag == 0)
				cout << ".\t" ;
			
		}// for every site
		
		cout << "\n";
	}//For all time values
	
	
	
	
	
//Plotting
	TCanvas *c1 = new TCanvas("c1","Graph Draw Options",200,10,800,800);
    c1->SetGrid();
	TGraph *step = new TGraph();
	for (int i=0; i<TotCars; i++)
	{
	    car[i].PlotIt(car[i],i,Tmax,step);
	    //c1->Update();
	}
	
	
	return 0;
}




