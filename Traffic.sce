clear()
clc


//Function for finding distance
function distance=d(row,col)
    flag = 0
    for i=col+1:num_cells
        if pos_time(row,i) ~= 0 then
            distance = i - col
            flag = 1
            break
        end
    end
    if flag ==0 then
        distance = num_cells
    end
     
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
L = 100
num_cells = int((L/7.5))
tot_time = 5
Vmax = 3
prob = 0.3
alpha = 0.4
beta0 = 0.4
pos_time=zeros(tot_time+1,num_cells)
num=linspace(1,num_cells,num_cells)

i=1
while i < num_cells
    if grand(1,1,"uin",1,2) - 1 == 1 then
        pos_time(1,i)=grand(1,1,"uin",1,Vmax)
        i = i + max(1, int( (pos_time(1,i)+1)/2 +1))
    else
        i=i+1
    end
end

disp(pos_time(1,:),"Initial positions")
disp("LOOP Bigins")
//Loop Begins
for t=1:tot_time

//Adding new cars
    if pos_time(t,1) == 0 &&  probability(alpha) == 1 then
        pos_time(t+1,1)=min(grand(1,1,"uin",1,d(t,1)*2),grand(1,1,"uin",1,Vmax))
    end
    
    for x=num_cells:-1:1
//        disp(t,"run for t")
//STEP 1
        if  pos_time(t,x) ~=0 then
//            disp(x,"run for x ")
            
            if pos_time(t,x) < Vmax && d(t,x) > pos_time(t,x) + 1 then
                if x+pos_time(t,x)+1 > num_cells then 
                    pos_time(t+1,x) = 0
                else
                    
                    if pos_time(t+1,x + pos_time(t,x)+1) ~= 0 then
                        disp("ERROR")
                    end
                    
                    pos_time(t+1,x + pos_time(t,x)+1) =  pos_time(t,x) + 1
                    pos_time(t+1,x) = 0
                end
            

//STEP 2
            elseif d(t,x) < pos_time(t,x)/2 then 
                if x+pos_time(t,x)-1 > num_cells then 
                    pos_time(t+1,x) = 0
                else
                    
                    if pos_time(t+1,x + pos_time(t,x)-1) ~= 0 then
                        disp("ERROR")
                    end
                    
                    pos_time(t+1,x + pos_time(t,x) - 1) = pos_time(t,x) - 1
                    pos_time(t+1,x) = 0
                end
            
        
//STEP 3
            elseif probability(prob) == 1 then
                if x+pos_time(t,x)-1 > num_cells then 
                    pos_time(t+1,x) = 0
                else
                    
                    if pos_time(t+1,x + pos_time(t,x)-1) ~= 0 then
                        disp("ERROR")
                    end
                    
                    pos_time(t+1,x + pos_time(t,x) - 1) = pos_time(t,x) - 1
                    pos_time(t+1,x) = 0
                end

//STEP 4
             else
                if x+pos_time(t,x) > num_cells then 
                    pos_time(t+1,x) = 0
                else
                    
                    pos_time(t+1,x + pos_time(t,x)) = pos_time(t,x)
                    pos_time(t+1,x) = 0
                 end
             end
            
            
            
        end 
    end
//Display            
    disp(pos_time(t,:))
end















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



























