%Laplace-Beltrami Eigenvectors
clc;clear all;close all;
[V,F] = read_off('teapot.obj'); %Change obj file for different surface
s11=struct('faces',F,'vertices',V);
L=surface_laplacian(s11);
[V D]=eigs(L,10,'sm'); 
% Plot the eigenvectors of Laplace Beltrami operator
for jj=1:10
subplot(1,10,jj);patch('faces',s11.faces,'vertices',s11.vertices,'facevertexcdata',V(:,jj),'edgecolor','none','facecolor','interp');
    axis equal; material dull;view(90,0);camlight;material dull;axis off;axis tight;
end 


%Surface Laplacian on Cortex
clc;clear all;close all;
load s11
L=surface_laplacian(s11);
[V D]=eigs(L,11,'sm');
V1 = V(:,2:11);
diageig = diag(D);
diageig = diageig(2:11);
Rsqrt = sqrt(diageig);
R1 = 1 ./Rsqrt;
GPS = [];
for kk = 1:10
    GPS = [GPS,R1(kk).* V1(:,kk)];
end
[idx,C] = kmeans(GPS,4);
patch('faces',s11.faces,'vertices',s11.vertices,'facevertexcdata',idx,'edgecolor','none','facecolor','interp');
axis equal; material dull;view(90,0);camlight;material dull;axis off;axis tight;
 

%Surface Projection on Basis Functions
clc;clear all;close all;
%load s11
[V,F] = read_off('bunny.obj');
s11=struct('faces',F,'vertices',V);
L=surface_laplacian(s11);
%change 2nd argument to specify no. of basis functions
[V D]=eigs(L,1752,'sm'); 
Projection = V*V';
Projx = Projection*s11.vertices(:,1);
Projy = Projection*s11.vertices(:,2);
Projz = Projection*s11.vertices(:,3);
ProjectedVertices = [Projx,Projy,Projz];
patch('faces',s11.faces,'vertices',ProjectedVertices,'facevertexcdata',V(:,10),'edgecolor','none','facecolor','interp');
axis equal; material dull;view(0,90);camlight;material dull;axis off;axis tight;
