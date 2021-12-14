%1D Heat Equation Simulation on the Rod
%Define Constants and initial conditions
 L = 1 %length of the domain in x direction (rod length)
 tmax = 0.1 %end time
 nx = 100 % number of nodes in the x direction
 nt = 10000 % number of time steps
 dx = L/(nx-1)
 dt =tmax/(nt -1)
 alpha = 1
 r = alpha*dt/dx^2
 r2 = 1-2*r
 
 %loop over time steps
 t = 0
 x=0:.01:5
 u = (1./(x+0.1)).*sin(2*pi*x)%initial condition
 for m = 1:nt
     uold = u %prepare for next step
     t = t+dt
     for i=2:nx-1
         u(i) = r*uold(i-1) + r2*uold(i) + r*uold(i+1);
     end
     plot(u); hold on;
     imagesc(u); hold on;
     pause(.1);
 end

%2D Heat Kernel Blurring
%Define Constants and initial conditions
 tmax = 0.01 ;%end time
 nx = 256 ; % if we define interval between 2pi, the step scaling is pi/127.5
 ny = 256 ;
 nt = 10000 ;% number of time steps
 % we define the space delta h = dh = dx = dy = pi/127    below  ;  no need dx in 2D -->  dx = L/(nx-1);
 % dy = L/(ny-1); 
 dh = pi/(nx-1)  ;  %the interval delta h is =  pi/127.5
 dt =tmax/(nt -1);  %time interval
 alpha = 1; % conductivity coefficient 
 
 %loop over time steps
 t = 0;
 x=(-pi):pi/127.5:pi;  %use different interval to get any size grid
 disp(size(x))  %show size of matrix in x , this example is 1x256 by using pi/127.5 
 y = x;
 u = (sin(x)).* (cos(y).'); % 256 x 256 grid with dx = pi/127.5 in above 
 %UU(:,:,m) = u;
 disp(size(u))
 Uold(:,:,1)  = u;
 %try to build 3 D loop below first time, 2nd dx-i, then dy -j
 for m = 1:nt
     %uold = u; %prepare for next steps
     t = t+dt;
     Uold(:,:,m+1)=0*u;
     for i=2:nx-1
         for j = 2:ny-1
 Uold(i,j,m+1) = Uold(i,j,m)+((-1/(dh^2))*dt)*(alpha*Uold(i,j-1,m)+Uold(i-1,j,m)-4*Uold(i,j,m)+Uold(i+1,j,m)+Uold(i,j+1,m));
         Uold(1,:,m+1)=0;
         Uold(end,:,m+1)=0;Uold(:,1,m+1)=0;Uold(:,end,m+1)=0;
         end
     end
%     surf(x,y,Uold(:,:,m)); %Use for 3D Plotting of Temp Distribution
     imagesc(Uold(:,:,m)); %Use for 2D Plotting of Temp Distribution
     hold on;
     pause(.1);
 end
