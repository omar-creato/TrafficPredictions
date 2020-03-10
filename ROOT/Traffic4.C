#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;

//Function for plotting
void ReverseYAxis (TMultiGraph *h);
void ReverseYAxis (TMultiGraph *h)
{
   // Remove the current axis
   h->GetYaxis()->SetLabelOffset(999);
   h->GetYaxis()->SetTickLength(0);

   // Redraw the new axis
   gPad->Update();
   TGaxis *newaxis = new TGaxis(gPad->GetUxmin(),
                                gPad->GetUymax(),
                                gPad->GetUxmin()-0.001,
                                gPad->GetUymin(),
                                h->GetYaxis()->GetXmin()-1,
                                h->GetYaxis()->GetXmax()+2,
                                510,"+");
   newaxis->SetLabelOffset(-0.03);
   newaxis->SetTitle(" Time ---->>>");
   newaxis->SetLabelSize(0.035);
   newaxis->Draw();
}


void ShiftXAxis (TMultiGraph *h, int Xmax);
void ShiftXAxis (TMultiGraph *h, int Xmax)
{
   // Remove the current axis
   h->GetXaxis()->SetLabelOffset(999);
   h->GetXaxis()->SetTickLength(0);

   // Redraw the new axis
   gPad->Update();
   TGaxis *newaxis = new TGaxis(gPad->GetUxmin(),
                                gPad->GetUymax(),
                                gPad->GetUxmax(),
                                gPad->GetUymax(),
                                -1,
                                Xmax+2,
                                510,"-");
   newaxis->SetLabelOffset(0.);
   newaxis->SetLabelSize(0.035);
   newaxis->SetTitle(" Position ---->>>");
   newaxis->Draw();
}


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
};

//Probability Function
bool Probability(float f)
{
	if (rand()%100 < f*100)
		return true;
	else
		return false;
}


int Traffic4()
{
	
	srand(time(NULL));
	cout<<"This should work!!!\n\n\n";
	int TotCars = 4;
	int TotSites = 30;
	int Tmax = 10;
	int Vmax = 5;
	float p = 0.5;
	int x2=0,x=0,v=0,d=0;
	Vehical car[TotCars][2];
//Initialisation Part
	
	car[0][0].SetCarData(0,0,9,4);
	car[1][0].SetCarData(0,0,16,0);	
	car[2][0].SetCarData(0,0,17,0);
	car[3][0].SetCarData(0,0,19,1);
//	car[4][0].SetCarData(0,0,49,0);	
//	car[5][0].SetCarData(0,0,50,0);
//	car[6][0].SetCarData(0,0,52,1);
//	car[7][0].SetCarData(0,0,60,4);
//	car[8][0].SetCarData(0,0,70,5);
	
	car[0][1].SetCarData(0,0,2,5);
	car[1][1].SetCarData(0,0,20,5);	
	car[2][1].SetCarData(0,0,26,0);
	car[3][1].SetCarData(0,0,28,1);
//	car[4][1].SetCarData(0,0,49,4);	
//	car[5][1].SetCarData(0,0,53,3);
//	car[6][1].SetCarData(0,0,58,0);
//	car[7][1].SetCarData(0,0,59,0);
//	car[8][1].SetCarData(0,0,62,1);
	
			

	for (int i = 1; i <= Tmax; i++)
	{
		for (int j = 0; j < TotCars; j++ )
		{
		    for (int k=0; k<2; k++)
		    {
		
			    x = car[j][k].CarData[i-1].Position;
			    v = car[j][k].CarData[i-1].Velocity;
			
			    if (j+1 == TotCars)
			    	x2 = car[0][k].CarData[i-1].Position;
    			else
    				x2 = car[j+1][k].CarData[i-1].Position;
     			if (x2 - x < 0)
    				d = TotSites - x + x2;
    			else
    				d = x2 - x;

//STEP 1	
    			if (v < Vmax && d > v + 1 )
   					v = v + 1; 
//STEP 2		
    			if (d <= v && v > 0 )
	    			v = d - 1;
//STEP 3
	    		if (Probability(p) == true && v > 0)
	    			v = v - 1;
//STEP 4
	    		if (x+v <= TotSites)
	    			x = x+v;
	    		else
	    			x = v - (TotSites - x);
				
	    		car[j][k].SetCarData(i,i,x,v);						
            }
//LOOP FOR LANES			
		}
//LOOP FOR CARS
	}
//LOOP FOR TIME
	
int flag =0;	



	
//Display	
	for (int i=0; i<= Tmax; i++)
	{
		
//For Lane 1
        cout << " --->|";		
		for (int j=1; j<=TotSites; j++)
		{	
			flag=0;
			for (int k=0; k<TotCars; k++)
			{
				if (car[k][0].CarData[i].Position == j)
				{
					flag=1;
					cout << car[k][0].CarData[i].Velocity << "";
					break;
				}				
			}//for comparing every car's position
			
			if (flag == 0)
				cout << "." ;
			
		}// for every site
		cout << "| --->\n     ";
		for (int m = 0; m<TotSites+2; m++)
		    cout << "_";
		cout << "\n\n";
		
//For Lane 2		
		cout << " <---|";		
		for (int j=TotSites; j>=1; j--)
		{	
			flag=0;
			for (int k=0; k<TotCars; k++)
			{
				if (car[k][1].CarData[i].Position == j)
				{
					flag=1;
					cout << "" << car[k][1].CarData[i].Velocity ;
					break;
				}				
			}//for comparing every car's position
			
			if (flag == 0)
				cout << "." ;
			
		}
		cout << "| <--- At Time t = " << i << "\n\n\n\n";
	}//For all time values
	
	
		
	
//Plotting
	TCanvas *c1 = new TCanvas("c1","Graph Draw Options",200,10,800,800);
//    c1->SetGrid();
    TGraph *step[TotCars][2];
    TMultiGraph *mg = new TMultiGraph();
	for (int i=0; i<TotCars; i++)
	{
	    step[i] = new TGraph();
	    for (int j=0; j<=Tmax; j++)
        {   
            step[i][0]->SetPoint(j,car[i][0].CarData[j].Position,Tmax-car[i].CarData[j].Time);
            step[i][1]->SetPoint(j,TotSites-car[i][0].CarData[j].Position+1,Tmax-car[i].CarData[j].Time);
            //step[i]->Draw("same A*");
            step[i][0]->SetMarkerStyle(i*2+1);
            step[i][1]->SetMarkerStyle(i*2+1);            
            c1->Update();

        } 
        mg->Add(step[i][0]);
        mg->Add(step[i][1]); 
        step[i][0]->SetMarkerStyle(20+i);
        step[i][0]->SetMarkerColor(1);
        step[i][0]->SetMarkerStyle(20+TotCars+i);
        step[i][0]->SetMarkerColor(2);        
	}
	mg->Draw("A pm p");
	ShiftXAxis(mg,TotSites);
	ReverseYAxis(mg);
	
	return 0;
}


