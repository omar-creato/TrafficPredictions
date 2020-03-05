clear()
clc


//Function for finding distance
function distance=d(row,col)
    for i=col+1:num_cells
        if pos_time(row,i) ~= N then
            distance = i - col
            break
        end
    end
        distance = num_cells
endfunction


//Function to get Yes or No for a given probability
function YesOrNo = probability(p)
    if  modulo(int(rand()*100000),100) < p*100 then
        YesOrNo = 1
    else
        YesOrNo = 0
    end
endfunction

//Initialisation
num_cars=5
L = 200
num_cells = int((L/7.5))
tot_time = 5
Vmax = 4
prob = 0.3
alpha = 0.5
beta0 = 0.4

Void=poly(0,'o')
N=-0.01
//No car position and zero car position will coincide so poly N for no car
pos_time=zeros(tot_time+1,num_cells) + N 
num=linspace(1,num_cells,num_cells)

//Ensuring that the next car is atleast d/2 distance away while filling initially
i=1
while i < num_cells
    if grand(1,1,"uin",1,2) - 1 == 1 then
        pos_time(1,i)=grand(1,1,"uin",1,Vmax)
        i = i + (pos_time(1,i)+1)/2 +1
    else
        i=i+1
    end
end

disp("LOOP Bigins")
//Loop Begins
for t=1:tot_time

//Adding new cars
    if pos_time(t,1) == N &&  probability(alpha) == 1 then
//Maximum velocity should be Vmax, only if distance permits
        pos_time(t+1,1)=min(grand(1,1,"uin",1,d(t,1)*2),grand(1,1,"uin",1,Vmax))
    end
    
    for x=num_cells:-1:1
//        disp(t,"run for t")
//STEP 1
        if  pos_time(t,x) ~= N then
//            disp(x,"run for x ")
            
            if pos_time(t,x) < Vmax && d(t,x) > pos_time(t,x) + 1 then
                if x+pos_time(t,x)+1 > num_cells then 
                    pos_time(t+1,x) = N
                else
                    
                    if pos_time(t+1,x + pos_time(t,x)+1) ~= N then
                        disp("ERROR")
                    end
                    
                    pos_time(t+1,x + pos_time(t,x)+1) =  pos_time(t,x) + 1
                    pos_time(t+1,x) = N
                end
            

//STEP 2
            elseif d(t,x) < pos_time(t,x)/2 then 
                if x+pos_time(t,x)-1 > num_cells then 
                    pos_time(t+1,x) = N
                else
                    
                    if pos_time(t+1,x + pos_time(t,x)-1) ~= N then
                        disp("ERROR")
                    end
                    
                    pos_time(t+1,x + pos_time(t,x) - 1) = pos_time(t,x) - 1
                    if pos_time(t,x)-1 ~= 0
                        pos_time(t+1,x) = N
                    end
                end
            
        
//STEP 3
            elseif probability(prob) == 1 then
                if x+pos_time(t,x)-1 > num_cells then 
                    pos_time(t+1,x) = N
                else
                    
                    if pos_time(t+1,x + pos_time(t,x)-1) ~= N then
                        disp("ERROR")
                    end
                    
                    pos_time(t+1,x + pos_time(t,x) - 1) = pos_time(t,x) - 1
                    if pos_time(t,x)-1 ~= 0
                        pos_time(t+1,x) = N
                    end
                end

//STEP 4
             else
                if x+pos_time(t,x) > num_cells then 
                    pos_time(t+1,x) = N
                else
                    
                    pos_time(t+1,x + pos_time(t,x)) = pos_time(t,x)
                    if pos_time(t,x)-1 ~= 0
                        pos_time(t+1,x) = N
                    end
                 end
             end
            
            
            
        end //end of checking cars
        
    end //end or position loop
//Display            
    //disp(pos_time(t,:))
end //end of time loop

pos_time2 = zeros(tot_time+1,num_cells) + Void
for t = 1:tot_time+1
    for x = 1:num_cells 
        if pos_time(t,x) >0 then
            pos_time2(t,x)=pos_time(t,x)
            plot2d(x,t)
                a=gca()
            a.children(1).children.line_mode="off"
            a.children(1).children.mark_mode="on"
            a.children(1).children.mark_style= 11 //pos_time(t,x)
            a.children(1).children.mark_size= pos_time(t,x)*2 +1
            a.grid_style = [7,7]
            a.x_location = "top"
            a.axes_reverse = ["off","on"]
            a.data_bounds=[0,0;num_cells+1,tot_time+2]
        end
    end
end
xgrid(1)

disp(pos_time2(1,:),"Initial positions")
disp(pos_time2,"Positions after each time step")












//x=0
//y=0
//for i=1:10000
//    ch=probability(0.2)
//    if ch==0 then 
//        x=x+1
//    else
//        y=y+1
//    end
//end



























