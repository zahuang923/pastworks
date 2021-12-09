%% EE575 - Computational Methods in Freeform Lens Design with Source-Target Conditions
% Kevin Chew Figueroa & Zenas Adam Huang
% Given a collimated light source and desired target distribution, we determine 
% the shape of a refractive freeform surface by implementing the Gauss-Seidel 
% method as a numerical solution to a system of non-linear elliptical partial 
% differential equations, known as Monge-Ampere PDEs. (Wojtanowski 2018)
% 
% 
% 
% First we define our target distribution:

clf;
clear all;

img = imread("USC_logo.jpg");
imshow(img);
img_bw = im2bw(img);

global target_img;
target_img = imcomplement(img_bw);


%Turn the following section on to lower
%resolution of target image
downSampleScalar = 1;
target_img = imresize(target_img, [floor(size(target_img, 1)/downSampleScalar), floor(size(target_img, 2)/downSampleScalar)]);

target_img = imcomplement(target_img);
%imshow(target_img);
%Turn this on if you wish to add noise to the target image:
target_img = target_img + 0.1;
target_img(target_img>1) = 1.0;
%imshow(target_img)
%% 
% Next we define our hyperparameters:
% 
% stepsize:

global h;
h = 1;
%% 
% lens surface sample dimensions:

global sampleSize;
sampleSize = 99;
global stepSizeH;
%stepSizeH = 1;
stepSizeH = double(0.01);
%% 
% targetDistance 

global zT;
%zT = sampleSize*2;
zT = 2.0;
%zT = 20;

%% 
% targetSize

global Tmax;
Tmax = 10;
%Tmax = 500;
%% 
% Refractive Indicies:

refractiveIndexIn = 1.49; %PMMA
refractiveIndexOut = 1.0; %Vacuum
global n;
n = refractiveIndexIn/refractiveIndexOut;
%% 
% Stability:

total_itr = 50;
stabilityContainer = zeros(total_itr,1, 'double');

%% 
% Debug Containers:

global f1Container;
f1Container = [1];
global f2Container;
f2Container = [1];

global zLxContainer;
zLxContainer = [1];
global zLyContainer;
zLyContainer = [1];
%% 
% We generate the initial condition for a lens surface. A plano concave lens:

global zLens;

%lensSize:
D0 = 0.990;

%% 
% Here we generate outputs for reporting:

%PhysicalParametersTable:
LensSize = D0; %sideLength
TargetSize = Tmax*2; %sideLength
TargetDistance = zT;
PHYSICAL_PARAMETERS = table(n, LensSize, TargetSize, TargetDistance)

%SampleParametersTable:
LensSampleSize=sampleSize*sampleSize;
TargetSampleSize = size(target_img,1)*size(target_img,2);
stepSize = stepSizeH;
iterations = total_itr;
SAMPLING_PARAMETERS = table(LensSampleSize, TargetSampleSize, stepSize, iterations)

%TargetImage:
figure; imshow(target_img)
axis on
title('Target Distribution')
ylabel('TargetSampleHeight')
xlabel('TargetSampleWidth')

%D0 = double(sampleSize)/100;
%D0 = double(sampleSize)/5;
[X,Y] = meshgrid(0.01: 0.01:D0, 0.01:0.01:D0);
gridDescritization = (D0*(n-1)*zT) / (1/(2*Tmax));

%lensCoordinateCenter
global lensCoordCenter;
lensCoordCenter = double(D0)/2;
circleEq = ((X-lensCoordCenter).^2)+ (Y-lensCoordCenter).^2;
%circleEq = ((X).^2)+ (Y).^2;
zLens = double(circleEq) ./ ( gridDescritization + sqrt( double((gridDescritization^2) - circleEq)));
original_zLens = zLens;
surf (X,Y,original_zLens,"EdgeColor","none");
title('Initial Freeform Lens Geometry')
zlabel('Z Lens Height [mm]')
ylabel('Y Lens Width [mm]')
xlabel('X Lens Width [mm]')
alpha(0.5);
%2D Heatmap:
surf (X,Y,original_zLens,"EdgeColor","none");
title('Initial Freeform Lens Geometry - Heatmap')
zlabel('Z Lens Height [mm]')
ylabel('Y Lens Width [mm]')
xlabel('X Lens Width [mm]')
view(2)



%{
global zLens;
zLens = ones(sampleSize, sampleSize, 'double');

%zLens = rand(sampleSize);
originalzLens = zLens;

[X,Y] = meshgrid(1:sampleSize, 1:sampleSize);
C=X.*Y;
surf(X,Y,zLens, C)
%}
global i1;
global j1;

for itr = 1: total_itr
    zLensPrev = zLens;
    for i1 = 2:sampleSize-1
        for j1 = 2:sampleSize-1
            
            av1 = avfunc(zLens(i1+1,j1), zLens(i1-1,j1));
            av2 = avfunc(zLens(i1,j1+1), zLens(i1,j1-1));
            av3 = avfunc(zLens(i1+1,j1+1), zLens(i1-1,j1-1));
            av4 = avfunc(zLens(i1-1,j1+1), zLens(i1+1,j1-1));
            g = gfunc(i1,j1);
            %[g,f1,f2] = gfunc(i1,j1)
            
            %h4g = h4gfunc(i1,j1, av1, av2, av3, av4);
                
            %zLens(i1,j1) = 0.5*(av1 + av2 - sqrt( ( (av1-av2)^2 ) + (((av3-av4)^2)/2) + (stepSizeH^4) * (g^4) )  );
            zLens(i1,j1) = 0.5*(av1 + av2 - sqrt( ( (av1-av2)^2 ) + (((av3-av4)*0.5)^2) + (stepSizeH^4) * (g) )  );
            %zLens(i1,j1) = 0.5*(av1 + av2 - sqrt( ( (av1-av2)^2 ) + (((av3-av4)*0.5)^2) + (h4g)  ) );
        end
    end
    stabilityContainer(itr) = stabilityfunc(zLensPrev, zLens);
end

%% 
% OutputLens:

[Xoutput,Youtput] = meshgrid(0.01: 0.01:D0, 0.01:0.01:D0);
surf(Xoutput,Youtput,zLens,"EdgeColor","none");
title('Obtained Freeform Lens Geometry')
zlabel('Z Lens Height [mm]')
ylabel('Y Lens Width [mm]')
xlabel('X Lens Width [mm]')
alpha(0.5);
%Obtained Heatmap:
%2D Heatmap:
surf(Xoutput,Youtput,zLens,"EdgeColor","none");
title('Obtained Freeform Lens Geometry - Heatmap')
zlabel('Z Lens Height [mm]')
ylabel('Y Lens Width [mm]')
xlabel('X Lens Width [mm]')
view(2)

%% 
% 
% 
% System Stability:
% 
% Here we show the convergence of our numerical solution over time[iterations]:
% 
% We show system convergence vs. iteration:
% 
% 

stabilityDomain = 1: total_itr;
fit = polyfit( transpose(stabilityDomain) , stabilityContainer, 1);
plot(polyval(fit,stabilityContainer));
title('System Stability')
ylabel('?LensSurface')
xlabel('iterations')

%% 
% 
% 
% Change in Curvature:

[Ox,Oy]=imgradientxy(original_zLens);
surf(X,Y,Ox,"EdgeColor", "none")
title('Gradient - X Component of Initial Freeform Geometry')
surf(X,Y,Oy,"EdgeColor", "none")
title('Gradient - Y Component of Initial Freeform Geometry')

[Gx,Gy]=imgradientxy(original_zLens);
surf(X,Y,Gx,"EdgeColor", "none")
title('Gradient - X Component of Obtained Freeform Geometry')
surf(X,Y,Gy,"EdgeColor", "none")
title('Gradient - Y Component of Obtained Freeform Geometry')
%% 
% 
% 
% *Generated Helper Functions:*
% 
% System Stability 
% 
% We show system convergence vs. iteration:
% 
% 

function stabilityCalc = stabilityfunc(prevLens, currentLens)
global sampleSize;
stabilityCalc = double(sum( double(abs(double(double(currentLens) - double(prevLens)))), 'all' )) / double(sampleSize);
%stabilityCalc = sum( abs(currentLens - prevLens), 'all' ) / sampleSize;
end
%% 
% 
% 
% We transform Equation 14 which has an unknown continous function for zL(x,y) 
% into a quadratic formula for zL:
% 
% 

function h4g = h4gfunc(i1,j1, av1, av2, av3, av4)

global zLens;
h4g = 4*( av1-zLens(i1,j1) )*( av2-zLens(i1,j1) ) - ( ( (av3-av4)^2 )*0.25 );

end
%% 
% 
% 
% Average:

function avCalc= avfunc(input1, input2)
avCalc = double(input1 + input2)/2;
end
%% 
% 
% 
% Right Side of PDE:
% 
% 
% 
% such that I_0/I_T is the jacobian

function gCalc = gfunc(inputI, inputJ)
%function [gCalc,f1,f2] = gfunc(inputI, inputJ)

global n;
zLx = zLxfunc(inputI, inputJ);
zLy = zLyfunc(inputI, inputJ);

K = scalarfunc(zLx, zLy);

jacob = jacobianfunc(zLx, zLy, K);
%[jacob,f1,f2] = jacobianfunc(zLx, zLy, K);

gCalc = jacob * double(sqrt(double(1 + ((zLx^2) + (zLy^2))*(1-n^2)))) / (K^2);


end

%% 
% 
% 
% Descritized Tangent Components to the Lens surface:
% 
% 

function zLx = zLxfunc(inputI, inputJ)
global stepSizeH;
global zLens;
zLx = ( 1/double(2*stepSizeH) ) * ( zLens(inputI+1,inputJ) - zLens(inputI-1,inputJ) );
end

function zLy = zLyfunc(inputI, inputJ)
global stepSizeH;
global zLens;
zLy = ( 1/double(2*stepSizeH) ) * ( zLens(inputI,inputJ+1) - zLens(inputI,inputJ-1) );
end
%% 
% 
% 
% Scalar Function:
% 
% 

function K = scalarfunc(zLx, zLy)

global n;
K = double( n - sqrt( double(1+ ( (zLx^2) + (zLy^2) )*(1-n^2) ) ) ) / double( (zLx^2) + (zLy^2) + 1 );

end

%% 
% 
% 
% function f, for the jacobian given small source assumption is valid:
% 
% 

function jacob = jacobianfunc(zLx, zLy, K)
%function [jacob,f1,f2] = jacobianfunc(zLx, zLy, K)

global zT;
global target_img;
global lensCoordCenter;
global f1Container;
global f2Container;
global zLxContainer;
global zLyContainer;

global i1;
global j1;


%f1 = zT * double(zLx * K)/double(1-K);
%f2 = zT * double(zLy * K)/double(1-K);
%jacob = f1*f2;

%f1 =  floor( real (zT * double((zLx+lensCoordCenter) * K)/double(1-K))) +1;
%f2 =  floor( real (zT * double((zLy+lensCoordCenter) * K)/double(1-K))) +1;

i1_int = int16(i1);
j1_int = int16(j1);
f1 =  ceil( real (zT * double((zLx) * K)/double(1-K))) +i1_int+1;
f2 =  ceil( real (zT * double((zLy) * K)/double(1-K))) +j1_int+1;

%f1Container = [f1Container; f1];
%f2Container = [f2Container; f2];

zLxContainer = [zLxContainer; zLx];
zLyContainer = [zLyContainer; zLy];
%test = target_img(1.0,1.0)

%f1 = real(zT * double(zLx * K)/double(1-K));
%f2 = real(zT * double(zLy * K)/double(1-K));

%jacob = f1*f2;


%f1 = zT * double(zLx * K)/double(1-K);
%f2 = zT * double(zLy * K)/double(1-K);

f1Container = [f1Container; f1];
f2Container = [f2Container; f2];

%f1 = ceil((f1*50)+50);
%f2 = ceil((f2*50)+50);

jacob = double(1) / double(target_img(f1, f2));


end

%% 
%